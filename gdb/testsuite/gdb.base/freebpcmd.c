/* Test program for GDB crashes while doing bp commands that continue inferior.
   Copyright 2003 Free Software Foundation, Inc.

   This file is part of the gdb testsuite.

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

int
main (int argc, char **argv)
{
  int i;

#ifdef usestubs
  set_debug_traps();
  breakpoint();
#endif

  for (i = 0; i < 100; i++)
    printf (">>> %d\n", i); /* euphonium */

  return 0;
}
