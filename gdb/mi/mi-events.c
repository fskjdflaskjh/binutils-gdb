/* MI Event Handlers
   Copyright 2002 Free Software Foundation, Inc.

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
#include "ui-out.h"
#include "interps.h"
#include "gdb.h"
#include "breakpoint.h"

#include "mi.h"

void 
mi_interp_stack_changed_hook (void)
{
  struct ui_out *saved_ui_out = uiout;
  struct mi_out *tmp_mi_out;

  if (gdb_current_interpreter_is_named (GDB_INTERPRETER_MI0))
    uiout = gdb_interpreter_ui_out (mi0_interp);
  else
    uiout = gdb_interpreter_ui_out (mi_interp);

  ui_out_list_begin (uiout, "MI_HOOK_RESULT");
  ui_out_field_string (uiout, "HOOK_TYPE", "stack_changed");
  ui_out_list_end (uiout);
  uiout = saved_ui_out;
}

void 
mi_interp_frame_changed_hook (int new_frame_number)
{
  struct ui_out *saved_ui_out = uiout;
  struct mi_out *tmp_mi_out;

  if (gdb_current_interpreter_is_named (GDB_INTERPRETER_MI0))
    uiout = gdb_interpreter_ui_out (mi0_interp);
  else
    uiout = gdb_interpreter_ui_out (mi_interp);

  ui_out_list_begin (uiout, "MI_HOOK_RESULT");
  ui_out_field_string (uiout, "HOOK_TYPE", "frame_changed");
  ui_out_field_int (uiout, "frame", new_frame_number);
  ui_out_list_end (uiout);
  uiout = saved_ui_out;

}

void
mi_interp_context_hook (int thread_id)
{
  struct ui_out *saved_ui_out = uiout;
  struct mi_out *tmp_mi_out;

  if (gdb_current_interpreter_is_named (GDB_INTERPRETER_MI0))
    uiout = gdb_interpreter_ui_out (mi0_interp);
  else
    uiout = gdb_interpreter_ui_out (mi_interp);

  ui_out_list_begin (uiout, "MI_HOOK_RESULT");
  ui_out_field_string (uiout, "HOOK_TYPE", "thread_changed");
  ui_out_field_int (uiout, "thread", thread_id);
  ui_out_list_end (uiout);
  uiout = saved_ui_out;
}

void
mi_interp_create_breakpoint_hook (struct breakpoint *bpt)
{
  CORE_ADDR unusued_addr;
  struct ui_out *saved_ui_out = uiout;
  struct mi_out *tmp_mi_out;

  if (gdb_current_interpreter_is_named (GDB_INTERPRETER_MI0))
    uiout = gdb_interpreter_ui_out (mi0_interp);
  else
    uiout = gdb_interpreter_ui_out (mi_interp);

  /* This is a little inefficient, but it probably isn't worth adding
     a gdb_breakpoint_query that takes a bpt structure... */

  ui_out_list_begin (uiout, "MI_HOOK_RESULT");
  ui_out_field_string (uiout, "HOOK_TYPE", "breakpoint_create");
  gdb_breakpoint_query (uiout, bpt->number);
  ui_out_list_end (uiout);
  uiout = saved_ui_out; 
}

void
mi_interp_modify_breakpoint_hook (struct breakpoint *bpt)
{

  CORE_ADDR unusued_addr;
  struct ui_out *saved_ui_out = uiout;
  struct mi_out *tmp_mi_out;

  if (gdb_current_interpreter_is_named (GDB_INTERPRETER_MI0))
    uiout = gdb_interpreter_ui_out (mi0_interp);
  else
    uiout = gdb_interpreter_ui_out (mi_interp);

  /* This is a little inefficient, but it probably isn't worth adding
     a gdb_breakpoint_query that takes a bpt structure... */

  ui_out_list_begin (uiout, "MI_HOOK_RESULT");
  ui_out_field_string (uiout, "HOOK_TYPE", "breakpoint_modify");
  gdb_breakpoint_query (uiout, bpt->number);
  ui_out_list_end (uiout);
  uiout = saved_ui_out; 
}

void
mi_interp_delete_breakpoint_hook (struct breakpoint *bpt)
{
  CORE_ADDR unusued_addr;
  struct ui_out *saved_ui_out = uiout;
  struct mi_out *tmp_mi_out;

  if (gdb_current_interpreter_is_named (GDB_INTERPRETER_MI0))
    uiout = gdb_interpreter_ui_out (mi0_interp);
  else
    uiout = gdb_interpreter_ui_out (mi_interp);

  /* This is a little inefficient, but it probably isn't worth adding
     a gdb_breakpoint_query that takes a bpt structure... */

  ui_out_list_begin (uiout, "MI_HOOK_RESULT");
  ui_out_field_string (uiout, "HOOK_TYPE", "breakpoint_delete");
  ui_out_field_int (uiout, "bkptno", bpt->number);
  ui_out_list_end (uiout);
  uiout = saved_ui_out; 
}

static void
event_notify (const char *string, ...)
{
  va_list args;

  if (!gdb_current_interpreter_is_named (GDB_INTERPRETER_MI0)
      && !gdb_current_interpreter_is_named (GDB_INTERPRETER_MI1))
    {
      va_start (args, string);
      vfprintf_unfiltered (mi_event_channel, string, args);
      va_end (args);
      gdb_flush (mi_event_channel);
    }
}

/* breakpoint-create,number=bpnum */
void
mi_create_breakpoint (int bpnum)
{
  event_notify ("breakpoint-create,number=\"%d\"", bpnum);
}

void
mi_modify_breakpoint (int bpnum)
{
  event_notify ("breakpoint-modify,number=\"%d\"", bpnum);
}

void
mi_delete_breakpoint (int bpnum)
{
  event_notify ("breakpoint-delete,number=\"%d\"", bpnum);
}

void
mi_create_tracepoint (int tpnum)
{
  event_notify ("tracepoint-create,number=\"%d\"", tpnum);
}

void
mi_modify_tracepoint (int tpnum)
{
  event_notify ("tracepoint-modify,number=\"%d\"", tpnum);
}

void
mi_delete_tracepoint (int tpnum)
{
  event_notify ("tracepoint-delete,number=\"%d\"", tpnum);
}

void
mi_architecture_changed (void)
{
  event_notify ("architecture-changed");
}

void
mi_register_update(int regno)
{
  event_notify ("register-update,number=\"%d\"", regno);
}
