/* TUI data manipulation routines.

   Copyright 1998, 1999, 2000, 2001, 2002, 2003 Free Software Foundation,
   Inc.

   Contributed by Hewlett-Packard Company.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#include "defs.h"
#include "symtab.h"
#include "tui/tui.h"
#include "tui/tui-data.h"
#include "tui/tui-wingeneral.h"

#ifdef HAVE_NCURSES_H       
#include <ncurses.h>
#else
#ifdef HAVE_CURSES_H
#include <curses.h>
#endif
#endif

/****************************
** GLOBAL DECLARATIONS
****************************/
TuiWinInfoPtr winList[MAX_MAJOR_WINDOWS];

/***************************
** Private data
****************************/
static TuiLayoutType _currentLayout = UNDEFINED_LAYOUT;
static int _termHeight, _termWidth;
static TuiGenWinInfo _locator;
static TuiGenWinInfo _execInfo[2];
static TuiWinInfoPtr _srcWinList[2];
static TuiList _sourceWindows =
{(OpaqueList) _srcWinList, 0};
static int _defaultTabLen = DEFAULT_TAB_LEN;
static TuiWinInfoPtr _winWithFocus = (TuiWinInfoPtr) NULL;
static TuiLayoutDef _layoutDef =
{SRC_WIN,			/* displayMode */
 FALSE,				/* split */
 TUI_UNDEFINED_REGS,		/* regsDisplayType */
 TUI_SFLOAT_REGS};		/* floatRegsDisplayType */
static int _winResized = FALSE;


/*********************************
** Static function forward decls
**********************************/
static void freeContent (TuiWinContent, int, TuiWinType);
static void freeContentElements (TuiWinContent, int, TuiWinType);



/*********************************
** PUBLIC FUNCTIONS
**********************************/

/******************************************
** ACCESSORS & MUTATORS FOR PRIVATE DATA
******************************************/

/* Answer a whether the terminal window has been resized or not.   */
int
tui_win_resized (void)
{
  return _winResized;
}


/* Set a whether the terminal window has been resized or not.   */
void
tui_set_win_resized_to (int resized)
{
  _winResized = resized;
}


/* Answer a pointer to the current layout definition.   */
TuiLayoutDefPtr
tui_layout_def (void)
{
  return &_layoutDef;
}


/* Answer the window with the logical focus.    */
TuiWinInfoPtr
tui_win_with_focus (void)
{
  return _winWithFocus;
}


/* Set the window that has the logical focus.   */
void
tui_set_win_with_focus (TuiWinInfoPtr winInfo)
{
  _winWithFocus = winInfo;
}


/* Answer the length in chars, of tabs.    */
int
tui_default_tab_len (void)
{
  return _defaultTabLen;
}


/* Set the length in chars, of tabs.   */
void
tui_set_default_tab_len (int len)
{
  _defaultTabLen = len;
}


/*
   ** currentSourceWin()
   **        Accessor for the current source window.  Usually there is only
   **        one source window (either source or disassembly), but both can
   **        be displayed at the same time.
 */
TuiListPtr
tui_source_windows (void)
{
  return &_sourceWindows;
}


/* Clear the list of source windows.  Usually there is only one source
   window (either source or disassembly), but both can be displayed at
   the same time.  */
void
tui_clear_source_windows (void)
{
  _sourceWindows.list[0] = (Opaque) NULL;
  _sourceWindows.list[1] = (Opaque) NULL;
  _sourceWindows.count = 0;
}


/* Clear the pertinant detail in the source windows.   */
void
tui_clear_source_windows_detail (void)
{
  int i;

  for (i = 0; i < (tui_source_windows ())->count; i++)
    tui_clear_win_detail ((TuiWinInfoPtr) (tui_source_windows ())->list[i]);
}


/* Add a window to the list of source windows.  Usually there is only
   one source window (either source or disassembly), but both can be
   displayed at the same time.  */
void
tui_add_to_source_windows (TuiWinInfoPtr winInfo)
{
  if (_sourceWindows.count < 2)
    _sourceWindows.list[_sourceWindows.count++] = (Opaque) winInfo;
}


/* Clear the pertinant detail in the windows.   */
void
tui_clear_win_detail (TuiWinInfoPtr winInfo)
{
  if (m_winPtrNotNull (winInfo))
    {
      switch (winInfo->generic.type)
	{
	case SRC_WIN:
	case DISASSEM_WIN:
	  winInfo->detail.sourceInfo.startLineOrAddr.addr = 0;
	  winInfo->detail.sourceInfo.horizontalOffset = 0;
	  break;
	case CMD_WIN:
	  winInfo->detail.commandInfo.curLine =
	    winInfo->detail.commandInfo.curch = 0;
	  break;
	case DATA_WIN:
	  winInfo->detail.dataDisplayInfo.dataContent =
	    (TuiWinContent) NULL;
	  winInfo->detail.dataDisplayInfo.dataContentCount = 0;
	  winInfo->detail.dataDisplayInfo.regsContent =
	    (TuiWinContent) NULL;
	  winInfo->detail.dataDisplayInfo.regsContentCount = 0;
	  winInfo->detail.dataDisplayInfo.regsDisplayType =
	    TUI_UNDEFINED_REGS;
	  winInfo->detail.dataDisplayInfo.regsColumnCount = 1;
	  winInfo->detail.dataDisplayInfo.displayRegs = FALSE;
	  break;
	default:
	  break;
	}
    }

  return;
}				/* clearWinDetail */


/*
   ** sourceExecInfoPtr().
   **        Accessor for the source execution info ptr.
 */
TuiGenWinInfoPtr
tui_source_exec_info_win_ptr (void)
{
  return &_execInfo[0];
}				/* sourceExecInfoWinPtr */


/*
   ** disassemExecInfoPtr().
   **        Accessor for the disassem execution info ptr.
 */
TuiGenWinInfoPtr
tui_disassem_exec_info_win_ptr (void)
{
  return &_execInfo[1];
}				/* disassemExecInfoWinPtr */


/* Accessor for the locator win info.  Answers a pointer to the static
   locator win info struct.  */
TuiGenWinInfoPtr
tui_locator_win_info_ptr (void)
{
  return &_locator;
}				/* locatorWinInfoPtr */


/* Accessor for the termHeight.  */
int
tui_term_height (void)
{
  return _termHeight;
}


/* Mutator for the term height.   */
void
tui_set_term_height_to (int h)
{
  _termHeight = h;
}


/* Accessor for the termWidth.   */
int
tui_term_width (void)
{
  return _termWidth;
}


/* Mutator for the termWidth.  */
void
tui_set_term_width_to (int w)
{
  _termWidth = w;
}


/* Accessor for the current layout.   */
TuiLayoutType
tui_current_layout (void)
{
  return _currentLayout;
}


/* Mutator for the current layout.  */
void
tui_set_current_layout_to (TuiLayoutType newLayout)
{
  _currentLayout = newLayout;
}


/*
   ** setGenWinOrigin().
   **        Set the origin of the window
 */
void
setGenWinOrigin (TuiGenWinInfoPtr winInfo, int x, int y)
{
  winInfo->origin.x = x;
  winInfo->origin.y = y;

  return;
}				/* setGenWinOrigin */


/*****************************
** OTHER PUBLIC FUNCTIONS
*****************************/


/* Answer the next window in the list, cycling back to the top if
   necessary.  */
TuiWinInfoPtr
tui_next_win (TuiWinInfoPtr curWin)
{
  TuiWinType type = curWin->generic.type;
  TuiWinInfoPtr nextWin = (TuiWinInfoPtr) NULL;

  if (curWin->generic.type == CMD_WIN)
    type = SRC_WIN;
  else
    type = curWin->generic.type + 1;
  while (type != curWin->generic.type && m_winPtrIsNull (nextWin))
    {
      if (winList[type] && winList[type]->generic.isVisible)
	nextWin = winList[type];
      else
	{
	  if (type == CMD_WIN)
	    type = SRC_WIN;
	  else
	    type++;
	}
    }

  return nextWin;
}				/* tuiNextWin */


/* Answer the prev window in the list, cycling back to the bottom if
   necessary.  */
TuiWinInfoPtr
tui_prev_win (TuiWinInfoPtr curWin)
{
  TuiWinType type = curWin->generic.type;
  TuiWinInfoPtr prev = (TuiWinInfoPtr) NULL;

  if (curWin->generic.type == SRC_WIN)
    type = CMD_WIN;
  else
    type = curWin->generic.type - 1;
  while (type != curWin->generic.type && m_winPtrIsNull (prev))
    {
      if (winList[type]->generic.isVisible)
	prev = winList[type];
      else
	{
	  if (type == SRC_WIN)
	    type = CMD_WIN;
	  else
	    type--;
	}
    }

  return prev;
}


/* Answer the window represented by name.    */
TuiWinInfoPtr
tui_partial_win_by_name (char *name)
{
  TuiWinInfoPtr winInfo = (TuiWinInfoPtr) NULL;

  if (name != (char *) NULL)
    {
      int i = 0;

      while (i < MAX_MAJOR_WINDOWS && m_winPtrIsNull (winInfo))
	{
          if (winList[i] != 0)
            {
              char *curName = tui_win_name (&winList[i]->generic);
              if (strlen (name) <= strlen (curName) &&
                  strncmp (name, curName, strlen (name)) == 0)
                winInfo = winList[i];
            }
	  i++;
	}
    }

  return winInfo;
}				/* partialWinByName */


/*
   ** winName().
   **      Answer the name of the window
 */
char *
tui_win_name (TuiGenWinInfoPtr winInfo)
{
  char *name = (char *) NULL;

  switch (winInfo->type)
    {
    case SRC_WIN:
      name = SRC_NAME;
      break;
    case CMD_WIN:
      name = CMD_NAME;
      break;
    case DISASSEM_WIN:
      name = DISASSEM_NAME;
      break;
    case DATA_WIN:
      name = DATA_NAME;
      break;
    default:
      name = "";
      break;
    }

  return name;
}				/* winName */


void
tui_initialize_static_data (void)
{
  tui_init_generic_part (tui_source_exec_info_win_ptr ());
  tui_init_generic_part (tui_disassem_exec_info_win_ptr ());
  tui_init_generic_part (tui_locator_win_info_ptr ());
}


TuiGenWinInfoPtr
tui_alloc_generic_win_info (void)
{
  TuiGenWinInfoPtr win;

  if ((win = (TuiGenWinInfoPtr) xmalloc (
		     sizeof (TuiGenWinInfoPtr))) != (TuiGenWinInfoPtr) NULL)
    tui_init_generic_part (win);

  return win;
}				/* allocGenericWinInfo */


/*
   ** initGenericPart().
 */
void
tui_init_generic_part (TuiGenWinInfoPtr win)
{
  win->width =
    win->height =
    win->origin.x =
    win->origin.y =
    win->viewportHeight =
    win->contentSize =
    win->lastVisibleLine = 0;
  win->handle = (WINDOW *) NULL;
  win->content = (OpaquePtr) NULL;
  win->contentInUse =
    win->isVisible = FALSE;
  win->title = 0;
}


/*
   ** initContentElement().
 */
void
initContentElement (TuiWinElementPtr element, TuiWinType type)
{
  element->highlight = FALSE;
  switch (type)
    {
    case SRC_WIN:
    case DISASSEM_WIN:
      element->whichElement.source.line = (char *) NULL;
      element->whichElement.source.lineOrAddr.lineNo = 0;
      element->whichElement.source.isExecPoint = FALSE;
      element->whichElement.source.hasBreak = FALSE;
      break;
    case DATA_WIN:
      tui_init_generic_part (&element->whichElement.dataWindow);
      element->whichElement.dataWindow.type = DATA_ITEM_WIN;
      ((TuiGenWinInfoPtr) & element->whichElement.dataWindow)->content =
	(OpaquePtr) tui_alloc_content (1, DATA_ITEM_WIN);
      ((TuiGenWinInfoPtr)
       & element->whichElement.dataWindow)->contentSize = 1;
      break;
    case CMD_WIN:
      element->whichElement.command.line = (char *) NULL;
      break;
    case DATA_ITEM_WIN:
      element->whichElement.data.name = (char *) NULL;
      element->whichElement.data.type = TUI_REGISTER;
      element->whichElement.data.itemNo = UNDEFINED_ITEM;
      element->whichElement.data.value = (Opaque) NULL;
      element->whichElement.data.highlight = FALSE;
      break;
    case LOCATOR_WIN:
      element->whichElement.locator.fileName[0] =
	element->whichElement.locator.procName[0] = (char) 0;
      element->whichElement.locator.lineNo = 0;
      element->whichElement.locator.addr = 0;
      break;
    case EXEC_INFO_WIN:
      memset(element->whichElement.simpleString, ' ',
             sizeof(element->whichElement.simpleString));
      break;
    default:
      break;
    }
  return;
}				/* initContentElement */

/*
   ** initWinInfo().
 */
void
initWinInfo (TuiWinInfoPtr winInfo)
{
  tui_init_generic_part (&winInfo->generic);
  winInfo->canHighlight =
    winInfo->isHighlighted = FALSE;
  switch (winInfo->generic.type)
    {
    case SRC_WIN:
    case DISASSEM_WIN:
      winInfo->detail.sourceInfo.executionInfo = (TuiGenWinInfoPtr) NULL;
      winInfo->detail.sourceInfo.hasLocator = FALSE;
      winInfo->detail.sourceInfo.horizontalOffset = 0;
      winInfo->detail.sourceInfo.startLineOrAddr.addr = 0;
      winInfo->detail.sourceInfo.filename = 0;
      break;
    case DATA_WIN:
      winInfo->detail.dataDisplayInfo.dataContent = (TuiWinContent) NULL;
      winInfo->detail.dataDisplayInfo.dataContentCount = 0;
      winInfo->detail.dataDisplayInfo.regsContent = (TuiWinContent) NULL;
      winInfo->detail.dataDisplayInfo.regsContentCount = 0;
      winInfo->detail.dataDisplayInfo.regsDisplayType =
	TUI_UNDEFINED_REGS;
      winInfo->detail.dataDisplayInfo.regsColumnCount = 1;
      winInfo->detail.dataDisplayInfo.displayRegs = FALSE;
      break;
    case CMD_WIN:
      winInfo->detail.commandInfo.curLine = 0;
      winInfo->detail.commandInfo.curch = 0;
      break;
    default:
      winInfo->detail.opaque = (Opaque) NULL;
      break;
    }

  return;
}				/* initWinInfo */


TuiWinInfoPtr
tui_alloc_win_info (TuiWinType type)
{
  TuiWinInfoPtr winInfo = (TuiWinInfoPtr) NULL;

  winInfo = (TuiWinInfoPtr) xmalloc (sizeof (TuiWinInfo));
  if (m_winPtrNotNull (winInfo))
    {
      winInfo->generic.type = type;
      initWinInfo (winInfo);
    }

  return winInfo;
}				/* allocWinInfo */


/*
   ** allocContent().
   **        Allocates the content and elements in a block.
 */
TuiWinContent
tui_alloc_content (int numElements, TuiWinType type)
{
  TuiWinContent content = (TuiWinContent) NULL;
  char *elementBlockPtr = (char *) NULL;
  int i;

  if ((content = (TuiWinContent)
  xmalloc (sizeof (TuiWinElementPtr) * numElements)) != (TuiWinContent) NULL)
    {				/*
				   ** All windows, except the data window, can allocate the elements
				   ** in a chunk.  The data window cannot because items can be
				   ** added/removed from the data display by the user at any time.
				 */
      if (type != DATA_WIN)
	{
	  if ((elementBlockPtr = (char *)
	   xmalloc (sizeof (TuiWinElement) * numElements)) != (char *) NULL)
	    {
	      for (i = 0; i < numElements; i++)
		{
		  content[i] = (TuiWinElementPtr) elementBlockPtr;
		  initContentElement (content[i], type);
		  elementBlockPtr += sizeof (TuiWinElement);
		}
	    }
	  else
	    {
	      tuiFree ((char *) content);
	      content = (TuiWinContent) NULL;
	    }
	}
    }

  return content;
}				/* allocContent */


/* Adds the input number of elements to the windows's content.  If no
   content has been allocated yet, allocContent() is called to do
   this.  The index of the first element added is returned, unless
   there is a memory allocation error, in which case, (-1) is
   returned.  */
int
tui_add_content_elements (TuiGenWinInfoPtr winInfo, int numElements)
{
  TuiWinElementPtr elementPtr;
  int i, indexStart;

  if (winInfo->content == (OpaquePtr) NULL)
    {
      winInfo->content = (OpaquePtr) tui_alloc_content (numElements, winInfo->type);
      indexStart = 0;
    }
  else
    indexStart = winInfo->contentSize;
  if (winInfo->content != (OpaquePtr) NULL)
    {
      for (i = indexStart; (i < numElements + indexStart); i++)
	{
	  if ((elementPtr = (TuiWinElementPtr)
	       xmalloc (sizeof (TuiWinElement))) != (TuiWinElementPtr) NULL)
	    {
	      winInfo->content[i] = (Opaque) elementPtr;
	      initContentElement (elementPtr, winInfo->type);
	      winInfo->contentSize++;
	    }
	  else			/* things must be really hosed now! We ran out of memory!? */
	    return (-1);
	}
    }

  return indexStart;
}				/* addContentElements */


/* Delete all curses windows associated with winInfo, leaving everything
   else intact.  */
void
tuiDelWindow (TuiWinInfoPtr winInfo)
{
  TuiGenWinInfoPtr genericWin;

  switch (winInfo->generic.type)
    {
    case SRC_WIN:
    case DISASSEM_WIN:
      genericWin = tui_locator_win_info_ptr ();
      if (genericWin != (TuiGenWinInfoPtr) NULL)
	{
	  tui_delete_win (genericWin->handle);
	  genericWin->handle = (WINDOW *) NULL;
	  genericWin->isVisible = FALSE;
	}
      if (winInfo->detail.sourceInfo.filename)
        {
          xfree (winInfo->detail.sourceInfo.filename);
          winInfo->detail.sourceInfo.filename = 0;
        }
      genericWin = winInfo->detail.sourceInfo.executionInfo;
      if (genericWin != (TuiGenWinInfoPtr) NULL)
	{
	  tui_delete_win (genericWin->handle);
	  genericWin->handle = (WINDOW *) NULL;
	  genericWin->isVisible = FALSE;
	}
      break;
    case DATA_WIN:
      if (winInfo->generic.content != (OpaquePtr) NULL)
	{
	  tui_del_data_windows (winInfo->detail.dataDisplayInfo.regsContent,
				winInfo->detail.dataDisplayInfo.regsContentCount);
	  tui_del_data_windows (winInfo->detail.dataDisplayInfo.dataContent,
				winInfo->detail.dataDisplayInfo.dataContentCount);
	}
      break;
    default:
      break;
    }
  if (winInfo->generic.handle != (WINDOW *) NULL)
    {
      tui_delete_win (winInfo->generic.handle);
      winInfo->generic.handle = (WINDOW *) NULL;
      winInfo->generic.isVisible = FALSE;
    }
}


void
tui_free_window (TuiWinInfoPtr winInfo)
{
  TuiGenWinInfoPtr genericWin;

  switch (winInfo->generic.type)
    {
    case SRC_WIN:
    case DISASSEM_WIN:
      genericWin = tui_locator_win_info_ptr ();
      if (genericWin != (TuiGenWinInfoPtr) NULL)
	{
	  tui_delete_win (genericWin->handle);
	  genericWin->handle = (WINDOW *) NULL;
	}
      tui_free_win_content (genericWin);
      if (winInfo->detail.sourceInfo.filename)
        {
          xfree (winInfo->detail.sourceInfo.filename);
          winInfo->detail.sourceInfo.filename = 0;
        }
      genericWin = winInfo->detail.sourceInfo.executionInfo;
      if (genericWin != (TuiGenWinInfoPtr) NULL)
	{
	  tui_delete_win (genericWin->handle);
	  genericWin->handle = (WINDOW *) NULL;
	  tui_free_win_content (genericWin);
	}
      break;
    case DATA_WIN:
      if (winInfo->generic.content != (OpaquePtr) NULL)
	{
	  tui_free_data_content (winInfo->detail.dataDisplayInfo.regsContent,
				 winInfo->detail.dataDisplayInfo.regsContentCount);
	  winInfo->detail.dataDisplayInfo.regsContent =
	    (TuiWinContent) NULL;
	  winInfo->detail.dataDisplayInfo.regsContentCount = 0;
	  tui_free_data_content (winInfo->detail.dataDisplayInfo.dataContent,
				 winInfo->detail.dataDisplayInfo.dataContentCount);
	  winInfo->detail.dataDisplayInfo.dataContent =
	    (TuiWinContent) NULL;
	  winInfo->detail.dataDisplayInfo.dataContentCount = 0;
	  winInfo->detail.dataDisplayInfo.regsDisplayType =
	    TUI_UNDEFINED_REGS;
	  winInfo->detail.dataDisplayInfo.regsColumnCount = 1;
	  winInfo->detail.dataDisplayInfo.displayRegs = FALSE;
	  winInfo->generic.content = (OpaquePtr) NULL;
	  winInfo->generic.contentSize = 0;
	}
      break;
    default:
      break;
    }
  if (winInfo->generic.handle != (WINDOW *) NULL)
    {
      tui_delete_win (winInfo->generic.handle);
      winInfo->generic.handle = (WINDOW *) NULL;
      tui_free_win_content (&winInfo->generic);
    }
  if (winInfo->generic.title)
    xfree (winInfo->generic.title);
  xfree (winInfo);
}


void
tui_free_all_source_wins_content (void)
{
  int i;

  for (i = 0; i < (tui_source_windows ())->count; i++)
    {
      TuiWinInfoPtr winInfo = (TuiWinInfoPtr) (tui_source_windows ())->list[i];

      if (m_winPtrNotNull (winInfo))
	{
	  tui_free_win_content (&(winInfo->generic));
	  tui_free_win_content (winInfo->detail.sourceInfo.executionInfo);
	}
    }
}


void
tui_free_win_content (TuiGenWinInfoPtr winInfo)
{
  if (winInfo->content != (OpaquePtr) NULL)
    {
      freeContent ((TuiWinContent) winInfo->content,
		   winInfo->contentSize,
		   winInfo->type);
      winInfo->content = (OpaquePtr) NULL;
    }
  winInfo->contentSize = 0;

  return;
}				/* freeWinContent */


void
tui_del_data_windows (TuiWinContent content, int contentSize)
{
  int i;

  /*
     ** Remember that data window content elements are of type TuiGenWinInfoPtr,
     ** each of which whose single element is a data element.
   */
  for (i = 0; i < contentSize; i++)
    {
      TuiGenWinInfoPtr genericWin = &content[i]->whichElement.dataWindow;

      if (genericWin != (TuiGenWinInfoPtr) NULL)
	{
	  tui_delete_win (genericWin->handle);
	  genericWin->handle = (WINDOW *) NULL;
	  genericWin->isVisible = FALSE;
	}
    }
}


void
tui_free_data_content (TuiWinContent content, int contentSize)
{
  int i;

  /*
     ** Remember that data window content elements are of type TuiGenWinInfoPtr,
     ** each of which whose single element is a data element.
   */
  for (i = 0; i < contentSize; i++)
    {
      TuiGenWinInfoPtr genericWin = &content[i]->whichElement.dataWindow;

      if (genericWin != (TuiGenWinInfoPtr) NULL)
	{
	  tui_delete_win (genericWin->handle);
	  genericWin->handle = (WINDOW *) NULL;
	  tui_free_win_content (genericWin);
	}
    }
  freeContent (content,
	       contentSize,
	       DATA_WIN);

  return;
}				/* freeDataContent */


/**********************************
** LOCAL STATIC FUNCTIONS        **
**********************************/


/*
   ** freeContent().
 */
static void
freeContent (TuiWinContent content, int contentSize, TuiWinType winType)
{
  if (content != (TuiWinContent) NULL)
    {
      freeContentElements (content, contentSize, winType);
      tuiFree ((char *) content);
    }

  return;
}				/* freeContent */


/*
   ** freeContentElements().
 */
static void
freeContentElements (TuiWinContent content, int contentSize, TuiWinType type)
{
  if (content != (TuiWinContent) NULL)
    {
      int i;

      if (type == SRC_WIN || type == DISASSEM_WIN)
	{
	  /* free whole source block */
	  if (content[0]->whichElement.source.line != (char *) NULL)
	    tuiFree (content[0]->whichElement.source.line);
	}
      else
	{
	  for (i = 0; i < contentSize; i++)
	    {
	      TuiWinElementPtr element;

	      element = content[i];
	      if (element != (TuiWinElementPtr) NULL)
		{
		  switch (type)
		    {
		    case DATA_WIN:
		      tuiFree ((char *) element);
		      break;
		    case DATA_ITEM_WIN:
		      /*
		         ** Note that data elements are not allocated
		         ** in a single block, but individually, as needed.
		       */
		      if (element->whichElement.data.type != TUI_REGISTER)
			tuiFree ((char *)
				 element->whichElement.data.name);
		      tuiFree ((char *) element->whichElement.data.value);
		      tuiFree ((char *) element);
		      break;
		    case CMD_WIN:
		      tuiFree ((char *) element->whichElement.command.line);
		      break;
		    default:
		      break;
		    }
		}
	    }
	}
      if (type != DATA_WIN && type != DATA_ITEM_WIN)
	tuiFree ((char *) content[0]);	/* free the element block */
    }

  return;
}				/* freeContentElements */
