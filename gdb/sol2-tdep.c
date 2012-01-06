/* Target-dependent code for Solaris.

   Copyright (C) 2006-2012 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "defs.h"
#include "frame.h"
#include "symtab.h"
#include "inferior.h"

#include "sol2-tdep.h"

CORE_ADDR
sol2_skip_solib_resolver (struct gdbarch *gdbarch, CORE_ADDR pc)
{
  struct minimal_symbol *msym;

  msym = lookup_minimal_symbol("elf_bndr", NULL, NULL);
  if (msym && SYMBOL_VALUE_ADDRESS (msym) == pc)
    return frame_unwind_caller_pc (get_current_frame ());

  return 0;
}

/* This is how we want PTIDs from Solaris core files to be
   printed.  */

char *
sol2_core_pid_to_str (struct gdbarch *gdbarch, ptid_t ptid)
{
  static char buf[80];

  xsnprintf (buf, sizeof buf, "LWP %ld", ptid_get_lwp (ptid));
  return buf;
}
