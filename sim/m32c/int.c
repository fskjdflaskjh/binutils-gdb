/* int.c --- M32C interrupt handling.

Copyright (C) 2005, 2007, 2008 Free Software Foundation, Inc.
Contributed by Red Hat, Inc.

This file is part of the GNU simulators.

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


#include "int.h"
#include "cpu.h"
#include "mem.h"

void
trigger_fixed_interrupt (int addr)
{
  int s = get_reg (sp);
  int f = get_reg (flags);
  int p = get_reg (pc);

  if (A16)
    {
      s -= 4;
      put_reg (sp, s);
      mem_put_hi (s, p);
      mem_put_qi (s + 2, f);
      mem_put_qi (s + 3, ((f >> 4) & 0x0f) | (p >> 16));
    }
  else
    {
      s -= 6;
      put_reg (sp, s);
      mem_put_si (s, p);
      mem_put_hi (s + 4, f);
    }
  put_reg (pc, mem_get_psi (addr));
  set_flags (FLAGBIT_U | FLAGBIT_I | FLAGBIT_D, 0);
}

void
trigger_based_interrupt (int vector)
{
  int addr = get_reg (intb) + vector * 4;
  if (vector <= 31)
    set_flags (FLAGBIT_U, 0);
  trigger_fixed_interrupt (addr);
}
