/* This testcase is part of GDB, the GNU debugger.

   Copyright 1996, 1999, 2003 Free Software Foundation, Inc.

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
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA.  */

#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>

enum tests {
  code_entry_point, code_descriptor, data_pointer
};

static volatile enum tests test;

/* Some basic types and zero buffers.  */

typedef long data_t;
typedef long code_t (void);
static volatile data_t *data[10];
static volatile code_t *code[10];

sigjmp_buf env;

extern void
keeper (int sig)
{
  siglongjmp (env, 0);
}

extern long
bowler (void)
{
  switch (test)
    {
    case data_pointer:
      return *data[0];
    case code_entry_point:
      return code[0] ();
    case code_descriptor:
      return ((code_t *) &code) ();
    }
}

int
main ()
{
  static volatile int i;

  struct sigaction act;
  memset (&act, 0, sizeof act);
  act.sa_handler = keeper;
  sigaction (SIGSEGV, &act, NULL);

  for (i = 0; i < 10; i++)
    {
      sigsetjmp (env, 1);
      bowler ();
    }
}
