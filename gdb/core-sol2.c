/* Machine independent support for Solaris 2 core files for GDB.
   Copyright 1994, 1995, 1996, 1998, 1999, 2000, 2001
   Free Software Foundation, Inc.

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


/* Solaris comes with two flavours of core files, cores generated by
   an ELF executable and cores generated by programs that were
   run under BCP (the part of Solaris which allows it to run SunOS4
   a.out files).
   This file combines the core register fetching from core-regset.c
   and sparc-nat.c to be able to read both flavours.  */

#include "defs.h"

#if defined (__sparcv9)
/* Fails to get included by the Solaris system header files.  */
# include <v9/sys/privregs.h>
#endif

#include <time.h>
#include <sys/types.h>
#include <sys/regset.h>
#include <sys/procfs.h>
#include <fcntl.h>
#include <errno.h>
#include "gdb_string.h"
#include "regcache.h"

#include "inferior.h"
#include "target.h"
#include "command.h"
#include "gdbcore.h"

/* Prototypes for supply_gregset etc. */
#include "gregset.h"

static void fetch_core_registers (char *, unsigned, int, CORE_ADDR);

/* Fetch registers from core file data pointed to by CORE_REG_SECT.  When
   WHICH is 0, the the general register set is fetched; when WHICH is
   2, the floating point registers are fetched.  CORE_REG_SIZE is used
   to validate the size of the data pointed to by CORE_REG_SECT.  REG_ADDR
   is unused. */

static void
fetch_core_registers (char *core_reg_sect, unsigned core_reg_size, int which,
		      CORE_ADDR reg_addr)
{
  int i;

  if (which == 0)
    {
      prgregset_t prgregset;

      if (core_reg_size == sizeof (prgregset_t))
	{
	  memcpy ((char *) &prgregset, core_reg_sect, sizeof (prgregset));
	  supply_gregset (&prgregset);
	}
#if defined (HAVE_PRGREGSET32_T)
      /* 32-bit corefile, 64-bit debugger.  */
      else if (core_reg_size == sizeof (prgregset32_t))
	{
	  prgreg32_t *core_gregs;

	  /* Can't use memcpy here, because the core file contains
	     32-bit regs; supply_register expects 64-bit regs.  */
	  core_gregs = (prgreg32_t *) core_reg_sect;
	  for (i = 0; i < NPRGREG; i++)
	    prgregset[i] = core_gregs[i];

	  supply_gregset (&prgregset);
	}
#endif /* HAVE_PRGREGSET32_T */
      else if (core_reg_size == sizeof (struct regs))
	{
	  struct regs *gregs = (struct regs *) core_reg_sect;

	  /* G0 *always* holds 0.  */
	  *(int *) &deprecated_registers[DEPRECATED_REGISTER_BYTE (0)] = 0;

	  /* The globals and output registers.  */
	  memcpy (&deprecated_registers[DEPRECATED_REGISTER_BYTE (G1_REGNUM)],
		  &gregs->r_g1, 15 * DEPRECATED_REGISTER_RAW_SIZE (G1_REGNUM));
	  *(int *) &deprecated_registers[DEPRECATED_REGISTER_BYTE (PS_REGNUM)]
	    = gregs->r_ps;
	  *(int *) &deprecated_registers[DEPRECATED_REGISTER_BYTE (PC_REGNUM)]
	    = gregs->r_pc;
	  *(int *) &deprecated_registers[DEPRECATED_REGISTER_BYTE (gdbarch_tdep (current_gdbarch)->npc_regnum)]
	    = gregs->r_npc;
	  *(int *) &deprecated_registers[DEPRECATED_REGISTER_BYTE (Y_REGNUM)]
	    = gregs->r_y;

	  /* My best guess at where to get the locals and input
	     registers is exactly where they usually are, right above
	     the stack pointer.  If the core dump was caused by a bus error
	     from blowing away the stack pointer (as is possible) then this
	     won't work, but it's worth the try. */
	  {
	    int sp;

	    sp = *(int *) &deprecated_registers[DEPRECATED_REGISTER_BYTE (SP_REGNUM)];
	    if (0 != target_read_memory (sp,
					 &deprecated_registers[DEPRECATED_REGISTER_BYTE (L0_REGNUM)],
					 16 * DEPRECATED_REGISTER_RAW_SIZE (L0_REGNUM)))
	      {
		warning ("couldn't read input and local registers from core file\n");
	      }
	  }
	}
      else
	{
	  warning ("wrong size gregset struct in core file");
	}
    }
  else if (which == 2)
    {
      prfpregset_t prfpregset;

      if (core_reg_size == sizeof (prfpregset_t))
	{
	  memcpy ((char *) &prfpregset, core_reg_sect, sizeof (prfpregset));
	  supply_fpregset (&prfpregset);
	}
#if defined (HAVE_PRFPREGSET32_T)
      /* 32-bit corefile, 64-bit debugger.  */
      else if (core_reg_size == sizeof (prfpregset32_t))
	{
	  prfpregset32_t *core_fpregset;

	  /* Can't use memcpy here, because the core file contains
	     32-bit regs; supply_fpregset expects 64-bit regs.  */

	  core_fpregset = (prfpregset32_t *) core_reg_sect;
	  for (i = 0; i < 16; i++)
	    prfpregset.pr_fr.pr_dregs[i] = core_fpregset->pr_fr.pr_dregs[i];
	  while (i < 32)
	    prfpregset.pr_fr.pr_dregs[i++] = 0;

	  prfpregset.pr_fsr         = core_fpregset->pr_fsr;
	  prfpregset.pr_qcnt        = core_fpregset->pr_qcnt;
	  prfpregset.pr_q_entrysize = core_fpregset->pr_q_entrysize;
	  prfpregset.pr_en          = core_fpregset->pr_en;
	  /* We will not use the pr_q array.  */

	  supply_fpregset (&prfpregset);
	}
#endif /* HAVE_PRFPREGSET32_T */
      else if (core_reg_size >= sizeof (struct fpu))
	{
	  struct fpu *fpuregs = (struct fpu *) core_reg_sect;

	  memcpy (&deprecated_registers[DEPRECATED_REGISTER_BYTE (FP0_REGNUM)],
		  &fpuregs->fpu_fr, sizeof (fpuregs->fpu_fr));
	  memcpy (&deprecated_registers[DEPRECATED_REGISTER_BYTE (FPS_REGNUM)],
		  &fpuregs->fpu_fsr, sizeof (FPU_FSR_TYPE));
	}
      else
	{
	  warning ("wrong size fpregset struct in core file");
	}
    }
}


/* Register that we are able to handle solaris core file formats. */

static struct core_fns solaris_core_fns =
{
  bfd_target_elf_flavour,		/* core_flavour */
  default_check_format,			/* check_format */
  default_core_sniffer,			/* core_sniffer */
  fetch_core_registers,			/* core_read_registers */
  NULL					/* next */
};

void
_initialize_core_solaris (void)
{
  add_core_fns (&solaris_core_fns);
}
