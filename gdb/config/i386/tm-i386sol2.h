/* Macro definitions for GDB on an Intel i386 running Solaris 2.
   Copyright 1998, 1999, 2000 Free Software Foundation, Inc.

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

#ifndef TM_I386SOL2_H
#define TM_I386SOL2_H 1

#define HAVE_I387_REGS
#include "i386/tm-i386v4.h"

/* If the current gcc for for this target does not produce correct
   debugging information for float parameters, both prototyped and
   unprototyped, then define this macro.  This forces gdb to always
   assume that floats are passed as doubles and then converted in the
   callee. */

#define COERCE_FLOAT_TO_DOUBLE(formal, actual) (1)

/* Signal handler frames under Solaris 2 are recognized by a return address
   of 0xFFFFFFFF, the third parameter on the signal handler stack is
   a pointer to an ucontext.  */
#undef sigtramp_saved_pc
#undef I386V4_SIGTRAMP_SAVED_PC
#define SIGCONTEXT_PC_OFFSET (36 + 14 * 4)
#undef IN_SIGTRAMP
#define IN_SIGTRAMP(pc, name) (pc == 0xFFFFFFFF)

/* The SunPRO compiler puts out 0 instead of the address in N_SO symbols,
   and for SunPRO 3.0, N_FUN symbols too.  */
#define SOFUN_ADDRESS_MAYBE_MISSING

extern char *sunpro_static_transform_name (char *);
#define STATIC_TRANSFORM_NAME(x) sunpro_static_transform_name (x)
#define IS_STATIC_TRANSFORM_NAME(name) ((name)[0] == '.')

#define FAULTED_USE_SIGINFO

/* Macros to extract process id and thread id from a composite pid/tid.
   Allocate lower 16 bits for process id, next 15 bits for thread id, and
   one bit for a flag to indicate a user thread vs. a kernel thread.  */
#define PIDGET0(PID)		(((PID) & 0xffff))
#define PIDGET(PID)		((PIDGET0 (PID) == 0xffff) ? -1 : PIDGET0 (PID))
#define TIDGET(PID)		(((PID) & 0x7fffffff) >> 16)
#define MERGEPID(PID, TID)	(((PID) & 0xffff) | ((TID) << 16))

#endif /* ifndef TM_I386SOL2_H */
