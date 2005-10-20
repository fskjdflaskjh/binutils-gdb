/* Common target dependent code for GDB on ARM systems.
   Copyright 2002, 2003 Free Software Foundation, Inc.

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

/* Register numbers of various important registers.  Note that some of
   these values are "real" register numbers, and correspond to the
   general registers of the machine, and some are "phony" register
   numbers which are too large to be actual register numbers as far as
   the user is concerned but do serve to get the desired values when
   passed to read_register.  */

enum gdb_regnum {
  ARM_A1_REGNUM = 0,		/* first integer-like argument */
  ARM_A4_REGNUM = 3,		/* last integer-like argument */
  ARM_AP_REGNUM = 11,
  ARM_SP_REGNUM = 13,		/* Contains address of top of stack */
  ARM_LR_REGNUM = 14,		/* address to return to from a function call */
  ARM_PC_REGNUM = 15,		/* Contains program counter */
  ARM_F0_REGNUM = 16,		/* first floating point register */
  ARM_F3_REGNUM = 19,		/* last floating point argument register */
  ARM_F7_REGNUM = 23, 		/* last floating point register */
  ARM_FPS_REGNUM = 24,		/* floating point status register */
  ARM_PS_REGNUM = 25,		/* Contains processor status */
  ARM_FP_REGNUM = 11,		/* Frame register in ARM code, if used.  */
  THUMB_FP_REGNUM = 7,		/* Frame register in Thumb code, if used.  */
  ARM_NUM_ARG_REGS = 4, 
  ARM_LAST_ARG_REGNUM = ARM_A4_REGNUM,
  ARM_NUM_FPA_ARG_REGS = 4,
  ARM_LAST_FPA_ARG_REGNUM = ARM_F3_REGNUM,
};

/* Size of integer registers.  */
#define INT_REGISTER_SIZE		4

/* Say how long FPA registers are.  Used for documentation purposes and
   code readability in this header.  IEEE extended doubles are 80
   bits.  DWORD aligned they use 96 bits.  */
#define FPA_REGISTER_SIZE	12

/* Status registers are the same size as general purpose registers.
   Used for documentation purposes and code readability in this
   header.  */
#define STATUS_REGISTER_SIZE	4

/* Number of machine registers.  The only define actually required 
   is NUM_REGS.  The other definitions are used for documentation
   purposes and code readability.  */
/* For 26 bit ARM code, a fake copy of the PC is placed in register 25 (PS)
   (and called PS for processor status) so the status bits can be cleared
   from the PC (register 15).  For 32 bit ARM code, a copy of CPSR is placed
   in PS.  */
#define NUM_FPA_REGS	8	/* Number of FPA floating point registers.  */
#define NUM_SREGS	2	/* Number of status registers.  */
#define NUM_GREGS	16	/* Number of general purpose registers.  */

/* Optional supported coprocessors.  */
enum
{
  NUM_IWMMXT_COP0REGS = 16,
  NUM_IWMMXT_COP1REGS = 16,
  NUM_IWMMXT_REGS = NUM_IWMMXT_COP0REGS + NUM_IWMMXT_COP1REGS,
  IWMMXT_COP0_REGSIZE = 8,
  IWMMXT_COP1_REGSIZE = 4
};

enum
{
  /* Status registers.  */
  NUM_VFP_XREGS = 16,
  VFP_XREG_SIZE = 4,
  /* Single precision registers.  */
  NUM_VFP_SREGS = 32,
  VFP_SREG_SIZE = 4,
  /* Pseudo regs for access to double precision values.  */
  NUM_VFP_PSEUDOS = 16
};

/* Instruction condition field values.  */
#define INST_EQ		0x0
#define INST_NE		0x1
#define INST_CS		0x2
#define INST_CC		0x3
#define INST_MI		0x4
#define INST_PL		0x5
#define INST_VS		0x6
#define INST_VC		0x7
#define INST_HI		0x8
#define INST_LS		0x9
#define INST_GE		0xa
#define INST_LT		0xb
#define INST_GT		0xc
#define INST_LE		0xd
#define INST_AL		0xe
#define INST_NV		0xf

#define FLAG_N		0x80000000
#define FLAG_Z		0x40000000
#define FLAG_C		0x20000000
#define FLAG_V		0x10000000

/* Type of floating-point code in use by inferior.  There are really 3 models
   that are traditionally supported (plus the endianness issue), but gcc can
   only generate 2 of those.  The third is APCS_FLOAT, where arguments to
   functions are passed in floating-point registers.  

   In addition to the traditional models, VFP adds two more. 

   If you update this enum, don't forget to update fp_model_strings in 
   arm-tdep.c.  */

enum arm_float_model
{
  ARM_FLOAT_AUTO,	/* Automatic detection.  Do not set in tdep.  */
  ARM_FLOAT_SOFT_FPA,	/* Traditional soft-float (mixed-endian on LE ARM).  */
  ARM_FLOAT_FPA,	/* FPA co-processor.  GCC calling convention.  */
  ARM_FLOAT_SOFT_VFP,	/* Soft-float with pure-endian doubles.  */
  ARM_FLOAT_VFP,	/* Full VFP calling convention.  */
  ARM_FLOAT_LAST	/* Keep at end.  */
};

/* ABI used by the inferior.  */
enum arm_abi_kind
{
  ARM_ABI_AUTO,
  ARM_ABI_APCS,
  ARM_ABI_AAPCS,
  ARM_ABI_LAST
};

/* Target-dependent structure in gdbarch.  */
struct gdbarch_tdep
{
  /* These fields are architecture-specific properties of the target.
     After connecting to a new target, we check the target's properties,
     and switch to a new gdbarch if necessary.   */

  int target_has_iwmmxt_regs;    /* Does the target have iWMMXt registers?  */

  int target_has_vfp_regs;	/* Does the target have VFP registers?  */

  /* End of target properties.  */

  /* The ABI for this architecture.  It should never be set to
     ARM_ABI_AUTO.  */
  enum arm_abi_kind arm_abi;

  enum arm_float_model fp_model; /* Floating point calling conventions.  */

  CORE_ADDR lowest_pc;		/* Lowest address at which instructions 
				   will appear.  */

  const char *arm_breakpoint;	/* Breakpoint pattern for an ARM insn.  */
  int arm_breakpoint_size;	/* And its size.  */
  const char *thumb_breakpoint;	/* Breakpoint pattern for an ARM insn.  */
  int thumb_breakpoint_size;	/* And its size.  */

  int jb_pc;			/* Offset to PC value in jump buffer. 
				   If this is negative, longjmp support
				   will be disabled.  */
  size_t jb_elt_size;		/* And the size of each entry in the buf.  */

  int first_iwmmxt_regnum;	/* The first iWMMXt register, or -1 if none.  */

  int target_iwmmxt_regnum;	/* The target-supplied numbering for the
				   iWMMXt registers, or -1 if none.  */
  int first_vfp_regnum;		/* The first VFP register, or -1 if none.  */
  int first_vfp_pseudo;		/* The first VFP pseudoreg, or -1 if none.  
				   This is an offset from NUM_REGS.  */

  int target_vfp_regnum;	/* The target-supplied numbering for the
				   VFP registers, or -1 if none.  */
};

#ifndef LOWEST_PC
#define LOWEST_PC (gdbarch_tdep (current_gdbarch)->lowest_pc)
#endif

/* Prototypes for internal interfaces needed by more than one MD file.  */
int arm_pc_is_thumb_dummy (CORE_ADDR);

int arm_pc_is_thumb (CORE_ADDR);

CORE_ADDR thumb_get_next_pc (CORE_ADDR);

CORE_ADDR arm_get_next_pc (CORE_ADDR);
