/* This testcase is part of GDB, the GNU debugger.

   Copyright 2008, 2009, 2010 Free Software Foundation, Inc.

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

volatile int var;

void
empty (void)
{
}

int
main (void)
{
  var = 1;
  /* Workaround PR 38: We may miss the first watchpoint hit as we stop on the
     exact instruction which would cause the watchpoint hit.  */
  var = 2;
  return 0;
}
