/* Target-dependent code for the GNU C Library (glibc).

   Copyright (C) 2002, 2003, 2007, 2008, 2009, 2010, 2011
   Free Software Foundation, Inc.

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

#ifndef GLIBC_TDEP_H
#define GLIBC_TDEP_H

struct gdbarch;

extern CORE_ADDR glibc_skip_solib_resolver (struct gdbarch *gdbarch,
					    CORE_ADDR);

#endif /* glibc-tdep.h */
