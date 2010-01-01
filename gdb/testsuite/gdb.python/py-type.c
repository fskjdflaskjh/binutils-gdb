/* This testcase is part of GDB, the GNU debugger.

   Copyright 2009, 2010 Free Software Foundation, Inc.

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

struct s
{
  int a;
  int b;
};

#ifdef __cplusplus
struct C
{
  int c;
  int d;
};

struct D : C
{
  int e;
  int f;
};
#endif

int
main ()
{
  int ar[2] = {1,2};
  struct s st;
#ifdef __cplusplus
  C c;
  c.c = 1;
  c.d = 2;
  D d;
  d.e = 3;
  d.f = 4;
#endif

  st.a = 3;
  st.b = 5;

  return 0;      /* break to inspect struct and array.  */
}
