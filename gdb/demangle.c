/* Basic C++ demangling support for GDB.

   Copyright 1991, 1992, 1993, 1994, 1995, 1996, 1998, 1999, 2000,
   2001, 2003 Free Software Foundation, Inc.

   Written by Fred Fish at Cygnus Support.

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


/*  This file contains support code for C++ demangling that is common
   to a styles of demangling, and GDB specific. */

#include "defs.h"
#include "command.h"
#include "gdbcmd.h"
#include "demangle.h"
#include "gdb_string.h"

/* Select the default C++ demangling style to use.  The default is "auto",
   which allows gdb to attempt to pick an appropriate demangling style for
   the executable it has loaded.  It can be set to a specific style ("gnu",
   "lucid", "arm", "hp", etc.) in which case gdb will never attempt to do auto
   selection of the style unless you do an explicit "set demangle auto".
   To select one of these as the default, set DEFAULT_DEMANGLING_STYLE in
   the appropriate target configuration file. */

#ifndef DEFAULT_DEMANGLING_STYLE
#define DEFAULT_DEMANGLING_STYLE AUTO_DEMANGLING_STYLE_STRING
#endif

extern void _initialize_demangler (void);

/* String name for the current demangling style.  Set by the
   "set demangle-style" command, printed as part of the output by the
   "show demangle-style" command. */

static char *current_demangling_style_string;

/* The array of names of the known demanglyng styles.  Generated by
   _initialize_demangler from libiberty_demanglers[] array.  */

static const char **demangling_style_names;

static void set_demangling_command (char *, int, struct cmd_list_element *);

/* Set current demangling style.  Called by the "set demangle-style"
   command after it has updated the current_demangling_style_string to
   match what the user has entered.

   If the user has entered a string that matches a known demangling style
   name in the demanglers[] array then just leave the string alone and update
   the current_demangling_style enum value to match.

   If the user has entered a string that doesn't match, including an empty
   string, then print a list of the currently known styles and restore
   the current_demangling_style_string to match the current_demangling_style
   enum value.

   Note:  Assumes that current_demangling_style_string always points to
   a malloc'd string, even if it is a null-string. */

static void
set_demangling_command (char *ignore, int from_tty, struct cmd_list_element *c)
{
  const struct demangler_engine *dem;

  /*  First just try to match whatever style name the user supplied with
     one of the known ones.  Don't bother special casing for an empty
     name, we just treat it as any other style name that doesn't match.
     If we match, update the current demangling style enum. */

  for (dem = libiberty_demanglers; 
       dem->demangling_style != unknown_demangling; 
       dem++)
    {
      if (strcmp (current_demangling_style_string,
		  dem->demangling_style_name) == 0)
	{
	  current_demangling_style = dem->demangling_style;
	  break;
	}
    }

  /* Check to see if we found a match.  If not, gripe about any non-empty
     style name and supply a list of valid ones.  FIXME:  This should
     probably be done with some sort of completion and with help. */

  if (dem->demangling_style == unknown_demangling)
    {
      if (*current_demangling_style_string != '\0')
	{
	  printf_unfiltered (_("Unknown demangling style `%s'.\n"),
			     current_demangling_style_string);
	}
      printf_unfiltered (_("The currently understood settings are:\n\n"));
      for (dem = libiberty_demanglers; 
	   dem->demangling_style != unknown_demangling; 
	   dem++)
	{
	  printf_unfiltered ("%-10s %s\n", dem->demangling_style_name,
			     dem->demangling_style_doc);
	  if (dem->demangling_style == current_demangling_style)
	    {
	      xfree (current_demangling_style_string);
	      current_demangling_style_string =
		savestring (dem->demangling_style_name,
			    strlen (dem->demangling_style_name));
	    }
	}
      if (current_demangling_style == unknown_demangling)
	{
	  /* This can happen during initialization if gdb is compiled with
	     a DEMANGLING_STYLE value that is unknown, so pick the first
	     one as the default. */
	  current_demangling_style = libiberty_demanglers[0].demangling_style;
	  current_demangling_style_string =
	    savestring (
              libiberty_demanglers[0].demangling_style_name,
	      strlen (libiberty_demanglers[0].demangling_style_name));
	  warning (_("`%s' style demangling chosen as the default."),
		   current_demangling_style_string);
	}
    }
}

/* Fake a "set demangle-style" command. */

void
set_demangling_style (char *style)
{
  if (current_demangling_style_string != NULL)
    {
      xfree (current_demangling_style_string);
    }
  current_demangling_style_string = savestring (style, strlen (style));
  set_demangling_command ((char *) NULL, 0, (struct cmd_list_element *) NULL);
}

/* G++ uses a special character to indicate certain internal names.  Which
   character it is depends on the platform:
   - Usually '$' on systems where the assembler will accept that
   - Usually '.' otherwise (this includes most sysv4-like systems and most
     ELF targets)
   - Occasionally '_' if neither of the above is usable

   We check '$' first because it is the safest, and '.' often has another
   meaning.  We don't currently try to handle '_' because the precise forms
   of the names are different on those targets.  */

static char cplus_markers[] = {'$', '.', '\0'};

int
is_cplus_marker (int c)
{
  return c && strchr (cplus_markers, c) != NULL;
}

void
_initialize_demangler (void)
{
  struct cmd_list_element *set, *show;
  int i, ndems;

  /* Fill the demangling_style_names[] array.  */
  for (ndems = 0;
       libiberty_demanglers[ndems].demangling_style != unknown_demangling; 
       ndems++)
    ;
  demangling_style_names = xcalloc (ndems + 1, sizeof (char *));
  for (i = 0;
       libiberty_demanglers[i].demangling_style != unknown_demangling; 
       i++)
    demangling_style_names[i] =
      xstrdup (libiberty_demanglers[i].demangling_style_name);

  set = add_set_enum_cmd ("demangle-style", class_support,
			  demangling_style_names,
			  (const char **) &current_demangling_style_string,
			  "Set the current C++ demangling style.\n\
Use `set demangle-style' without arguments for a list of demangling styles.",
			  &setlist);
  show = deprecated_add_show_from_set (set, &showlist);
  set_cmd_sfunc (set, set_demangling_command);

  /* Set the default demangling style chosen at compilation time. */
  set_demangling_style (DEFAULT_DEMANGLING_STYLE);
}
