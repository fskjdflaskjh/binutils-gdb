/* Target-dependent code for DICOS running on i386's, for GDB.

   Copyright (C) 2008, 2009, 2010, 2011 Free Software Foundation, Inc.

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
#include "osabi.h"
#include "gdb_string.h"
#include "dicos-tdep.h"

static CORE_ADDR
i386_dicos_push_dummy_code (struct gdbarch *gdbarch,
			    CORE_ADDR sp, CORE_ADDR funaddr,
			    struct value **args, int nargs,
			    struct type *value_type,
			    CORE_ADDR *real_pc, CORE_ADDR *bp_addr,
			    struct regcache *regcache)
{
  int bplen;
  CORE_ADDR bppc = sp;

  gdbarch_breakpoint_from_pc (gdbarch, &bppc, &bplen);
  *bp_addr = sp - bplen;
  *real_pc = funaddr;

  return *bp_addr;
}

static void
i386_dicos_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  dicos_init_abi (gdbarch);

  set_gdbarch_push_dummy_code (gdbarch, i386_dicos_push_dummy_code);
}

static enum gdb_osabi
i386_dicos_osabi_sniffer (bfd *abfd)
{
  char *target_name = bfd_get_target (abfd);

  /* On x86-DICOS, the Load Module's "header" section is 36 bytes.  */
  if (strcmp (target_name, "elf32-i386") == 0
      && dicos_load_module_p (abfd, 36))
    return GDB_OSABI_DICOS;

  return GDB_OSABI_UNKNOWN;
}

/* Provide a prototype to silence -Wmissing-prototypes.  */
void _initialize_i386_dicos_tdep (void);

void
_initialize_i386_dicos_tdep (void)
{
  gdbarch_register_osabi_sniffer (bfd_arch_i386, bfd_target_elf_flavour,
                                  i386_dicos_osabi_sniffer);

  gdbarch_register_osabi (bfd_arch_i386, 0, GDB_OSABI_DICOS,
                          i386_dicos_init_abi);
}
