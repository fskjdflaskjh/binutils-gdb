/* Target-dependent code for FreeBSD/sparc64.

   Copyright 2003 Free Software Foundation, Inc.

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
#include "gdbcore.h"
#include "osabi.h"
#include "regcache.h"
#include "target.h"

#include "gdb_string.h"

#include "sparc64-tdep.h"

/* From <machine/reg.h>.  */
const struct sparc_gregset sparc64fbsd_gregset =
{
  26 * 8,			/* "tstate" */
  25 * 8,			/* %pc */
  24 * 8,			/* %npc */
  28 * 8,			/* %y */
  16 * 8,			/* %fprs */
  -1,
  1 * 8,			/* %g1 */
  -1,				/* %l0 */
  8				/* sizeof (%y) */
};


/* Size of `struct reg' and `struct fpreg'.  */
static const int sparc64fbsd_sizeof_struct_reg = 256;
static const int sparc64fbsd_sizeof_struct_fpreg = 272;

static void
fetch_core_registers (char *core_reg_sect, unsigned core_reg_size, int which,
                      CORE_ADDR ignore)
{
  switch (which)
    {
    case 0:  /* Integer registers */
      if (core_reg_size != sparc64fbsd_sizeof_struct_reg)
	warning ("Wrong size register set in core file.");
      else
	sparc64_supply_gregset (&sparc64fbsd_gregset, current_regcache,
				-1, core_reg_sect);
      break;

    case 2:  /* Floating pointer registers */
      if (core_reg_size != sparc64fbsd_sizeof_struct_fpreg)
	warning ("Wrong size FP register set in core file.");
      else
	sparc64_supply_fpregset (current_regcache, -1, core_reg_sect);
      break;

    default:
      /* Don't know what kind of register request this is; just ignore it.  */
      break;
    }
}

static struct core_fns sparc64fbsd_core_fns =
{
  bfd_target_elf_flavour,		/* core_flavour */
  default_check_format,			/* check_format */
  default_core_sniffer,			/* core_sniffer */
  fetch_core_registers,			/* core_read_registers */
  NULL
};


static void
sparc64fbsd_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  sparc64_init_abi (info, gdbarch);
}

/* Provide a prototype to silence -Wmissing-prototypes.  */
void _initialize_sparc64fbsd_tdep (void);

void
_initialize_sparc64fbsd_tdep (void)
{
  gdbarch_register_osabi (bfd_arch_sparc, bfd_mach_sparc_v9,
			  GDB_OSABI_FREEBSD_ELF, sparc64fbsd_init_abi);

  add_core_fns (&sparc64fbsd_core_fns);
}
