/* IA-64 ELF support for BFD.
   Copyright 1998, 1999, 2000, 2001, 2002, 2003, 2008
   Free Software Foundation, Inc.
   Contributed by David Mosberger-Tang <davidm@hpl.hp.com>

   This file is part of BFD, the Binary File Descriptor library.

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
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston, MA 02110-1301, USA.  */

#ifndef _ELF_IA64_H
#define _ELF_IA64_H

/* Bits in the e_flags field of the Elf64_Ehdr:  */

#define EF_IA_64_MASKOS	 0x0000000f	/* OS-specific flags.  */
#define EF_IA_64_ARCH	 0xff000000	/* Arch. version mask.  */

/* ??? These four definitions are not part of the SVR4 ABI.
   They were present in David's initial code drop, so it is probable
   that they are used by HP/UX.  */
#define EF_IA_64_TRAPNIL (1 << 0)	/* Trap NIL pointer dereferences.  */
#define EF_IA_64_EXT	 (1 << 2)	/* Program uses arch. extensions.  */
#define EF_IA_64_BE	 (1 << 3)	/* PSR BE bit set (big-endian).  */
#define EFA_IA_64_EAS2_3 0x23000000	/* IA64 EAS 2.3.  */

#define EF_IA_64_ABI64		    (1 << 4) /* 64-bit ABI.  */
/* Not used yet.  */
#define EF_IA_64_REDUCEDFP	    (1 << 5) /* Only FP6-FP11 used.  */
#define EF_IA_64_CONS_GP	    (1 << 6) /* gp as program wide constant.  */
#define EF_IA_64_NOFUNCDESC_CONS_GP (1 << 7) /* And no function descriptors.  */
/* Not used yet.  */
#define EF_IA_64_ABSOLUTE	    (1 << 8) /* Load at absolute addresses.  */

#define ELF_STRING_ia64_archext		".IA_64.archext"
#define ELF_STRING_ia64_pltoff		".IA_64.pltoff"
#define ELF_STRING_ia64_unwind		".IA_64.unwind"
#define ELF_STRING_ia64_unwind_info	".IA_64.unwind_info"
#define ELF_STRING_ia64_unwind_once	".gnu.linkonce.ia64unw."
#define ELF_STRING_ia64_unwind_info_once ".gnu.linkonce.ia64unwi."
/* .IA_64.unwind_hdr is only used by HP-UX.  */
#define ELF_STRING_ia64_unwind_hdr	".IA_64.unwind_hdr"

/* Bits in the sh_flags field of Elf64_Shdr:  */

#define SHF_IA_64_SHORT		  0x10000000	/* Section near gp.  */
#define SHF_IA_64_NORECOV	  0x20000000	/* Spec insns w/o recovery.  */

#define SHF_IA_64_HP_TLS	  0x01000000	/* HP specific TLS flag.  */

#define SHF_IA_64_VMS_GLOBAL      0x0100000000ULL /* Global for clustering.  */
#define SHF_IA_64_VMS_OVERLAID    0x0200000000ULL /* To be overlaid.  */
#define SHF_IA_64_VMS_SHARED      0x0400000000ULL /* Shared btw processes.  */
#define SHF_IA_64_VMS_VECTOR      0x0800000000ULL /* Priv change mode vect.  */
#define SHF_IA_64_VMS_ALLOC_64BIT 0x1000000000ULL /* Allocate beyond 2GB.  */
#define SHF_IA_64_VMS_PROTECTED   0x2000000000ULL /* Export from sharable.  */

/* Possible values for sh_type in Elf64_Shdr: */

#define SHT_IA_64_EXT		(SHT_LOPROC + 0)	/* Extension bits.  */
#define SHT_IA_64_UNWIND	(SHT_LOPROC + 1)	/* Unwind bits.  */
#define SHT_IA_64_LOPSREG	(SHT_LOPROC + 0x8000000)
/* ABI says (SHT_LOPROC + 0xfffffff) but I think it's a typo -- this makes sense.  */
#define SHT_IA_64_HIPSREG	(SHT_LOPROC + 0x8ffffff)
#define SHT_IA_64_PRIORITY_INIT (SHT_LOPROC + 0x9000000)

/* SHT_IA_64_HP_OPT_ANOT is only generated by HPUX compilers for its
   optimization annotation section.  GCC does not generate it but we
   want readelf to know what they are.  Do not use two capital Ns in
   annotate or sed will turn it into 32 or 64 during the build.  */
#define SHT_IA_64_HP_OPT_ANOT	0x60000004

/* OpenVMS section types.  */
/* The section contains PC-to-source correlation information for use by the
   VMS RTL's traceback facility.  */
#define SHT_IA_64_VMS_TRACE          0x60000000
/* The section contains routine signature information for use by the
   translated image executive.  */
#define SHT_IA_64_VMS_TIE_SIGNATURES 0x60000001
/* The section contains dwarf-3 information.  */
#define SHT_IA_64_VMS_DEBUG          0x60000002
/* The section contains the dwarf-3 string table.  */
#define SHT_IA_64_VMS_DEBUG_STR      0x60000003
/* The section contains linkage information to perform consistency checking
   accross object modules.  */
#define SHT_IA_64_VMS_LINKAGES       0x60000004
/* The section allows the symbol vector in an image to be location through
   the section table.  */
#define SHT_IA_64_VMS_SYMBOL_VECTOR  0x60000005
/* The section contains inter-image fixups.  */
#define SHT_IA_64_VMS_FIXUP          0x60000006

/* Bits in the p_flags field of Elf64_Phdr:  */

#define PF_IA_64_NORECOV	0x80000000

/* Possible values for p_type in Elf64_Phdr:  */

#define PT_IA_64_ARCHEXT	(PT_LOPROC + 0)	/* Arch extension bits,  */
#define PT_IA_64_UNWIND 	(PT_LOPROC + 1)	/* IA64 unwind bits.  */

/* HP-UX specific values for p_type in Elf64_Phdr.
   These values are currently just used to make
   readelf more usable on HP-UX.  */

#define PT_IA_64_HP_OPT_ANOT	(PT_LOOS + 0x12)
#define PT_IA_64_HP_HSL_ANOT	(PT_LOOS + 0x13)
#define PT_IA_64_HP_STACK	(PT_LOOS + 0x14)

/* Possible values for d_tag in Elf64_Dyn:  */

#define DT_IA_64_PLT_RESERVE	(DT_LOPROC + 0)

/* VMS specific values for d_tag in Elf64_Dyn:  */

#define DT_IA_64_VMS_SUBTYPE         (DT_LOOS + 0)
#define DT_IA_64_VMS_IMGIOCNT        (DT_LOOS + 2)
#define DT_IA_64_VMS_LNKFLAGS        (DT_LOOS + 8)
#define DT_IA_64_VMS_VIR_MEM_BLK_SIZ (DT_LOOS + 10)
#define DT_IA_64_VMS_IDENT           (DT_LOOS + 12)
#define DT_IA_64_VMS_NEEDED_IDENT    (DT_LOOS + 16)
#define DT_IA_64_VMS_IMG_RELA_CNT    (DT_LOOS + 18)
#define DT_IA_64_VMS_SEG_RELA_CNT    (DT_LOOS + 20)
#define DT_IA_64_VMS_FIXUP_RELA_CNT  (DT_LOOS + 22)
#define DT_IA_64_VMS_FIXUP_NEEDED    (DT_LOOS + 24)
#define DT_IA_64_VMS_SYMVEC_CNT      (DT_LOOS + 26)
#define DT_IA_64_VMS_XLATED          (DT_LOOS + 30)
#define DT_IA_64_VMS_STACKSIZE       (DT_LOOS + 32)
#define DT_IA_64_VMS_UNWINDSZ        (DT_LOOS + 34)
#define DT_IA_64_VMS_UNWIND_CODSEG   (DT_LOOS + 36)
#define DT_IA_64_VMS_UNWIND_INFOSEG  (DT_LOOS + 38)
#define DT_IA_64_VMS_LINKTIME        (DT_LOOS + 40)
#define DT_IA_64_VMS_SEG_NO          (DT_LOOS + 42)
#define DT_IA_64_VMS_SYMVEC_OFFSET   (DT_LOOS + 44)
#define DT_IA_64_VMS_SYMVEC_SEG      (DT_LOOS + 46)
#define DT_IA_64_VMS_UNWIND_OFFSET   (DT_LOOS + 48)
#define DT_IA_64_VMS_UNWIND_SEG      (DT_LOOS + 50)
#define DT_IA_64_VMS_STRTAB_OFFSET   (DT_LOOS + 52)
#define DT_IA_64_VMS_SYSVER_OFFSET   (DT_LOOS + 54)
#define DT_IA_64_VMS_IMG_RELA_OFF    (DT_LOOS + 56)
#define DT_IA_64_VMS_SEG_RELA_OFF    (DT_LOOS + 58)
#define DT_IA_64_VMS_FIXUP_RELA_OFF  (DT_LOOS + 60)
#define DT_IA_64_VMS_PLTGOT_OFFSET   (DT_LOOS + 62)
#define DT_IA_64_VMS_PLTGOT_SEG      (DT_LOOS + 64)
#define DT_IA_64_VMS_FPMODE          (DT_LOOS + 66)

/* This section only used by HP-UX, The HP linker gives weak symbols
   precedence over regular common symbols.  We want common to override
   weak.  Using this common instead of SHN_COMMON does that.  */
#define SHN_IA_64_ANSI_COMMON SHN_LORESERVE

/* This section is only used by OpenVMS.  Symbol is defined in the symbol
   vector (only possible for image files).  */
#define SHN_IA_64_VMS_SYMVEC SHN_LOOS

/* IA64-specific relocation types: */

/* Relocs apply to specific instructions within a bundle.  The least
   significant 2 bits of the address indicate which instruction in the
   bundle the reloc refers to (0=first slot, 1=second slow, 2=third
   slot, 3=undefined) and the remaining bits give the address of the
   bundle (16 byte aligned).

   The top 5 bits of the reloc code specifies the expression type, the
   low 3 bits the format of the data word being relocated.  */

#include "elf/reloc-macros.h"

START_RELOC_NUMBERS (elf_ia64_reloc_type)
  RELOC_NUMBER (R_IA64_NONE, 0x00)	/* none */

  RELOC_NUMBER (R_IA64_IMM14, 0x21)	/* symbol + addend, add imm14 */
  RELOC_NUMBER (R_IA64_IMM22, 0x22)	/* symbol + addend, add imm22 */
  RELOC_NUMBER (R_IA64_IMM64, 0x23)	/* symbol + addend, mov imm64 */
  RELOC_NUMBER (R_IA64_DIR32MSB, 0x24)	/* symbol + addend, data4 MSB */
  RELOC_NUMBER (R_IA64_DIR32LSB, 0x25)	/* symbol + addend, data4 LSB */
  RELOC_NUMBER (R_IA64_DIR64MSB, 0x26)	/* symbol + addend, data8 MSB */
  RELOC_NUMBER (R_IA64_DIR64LSB, 0x27)	/* symbol + addend, data8 LSB */

  RELOC_NUMBER (R_IA64_GPREL22, 0x2a)	/* @gprel(sym+add), add imm22 */
  RELOC_NUMBER (R_IA64_GPREL64I, 0x2b)	/* @gprel(sym+add), mov imm64 */
  RELOC_NUMBER (R_IA64_GPREL32MSB, 0x2c) /* @gprel(sym+add), data4 MSB */
  RELOC_NUMBER (R_IA64_GPREL32LSB, 0x2d) /* @gprel(sym+add), data4 LSB */
  RELOC_NUMBER (R_IA64_GPREL64MSB, 0x2e) /* @gprel(sym+add), data8 MSB */
  RELOC_NUMBER (R_IA64_GPREL64LSB, 0x2f) /* @gprel(sym+add), data8 LSB */

  RELOC_NUMBER (R_IA64_LTOFF22, 0x32)	/* @ltoff(sym+add), add imm22 */
  RELOC_NUMBER (R_IA64_LTOFF64I, 0x33)	/* @ltoff(sym+add), mov imm64 */

  RELOC_NUMBER (R_IA64_PLTOFF22, 0x3a)	/* @pltoff(sym+add), add imm22 */
  RELOC_NUMBER (R_IA64_PLTOFF64I, 0x3b)	/* @pltoff(sym+add), mov imm64 */
  RELOC_NUMBER (R_IA64_PLTOFF64MSB, 0x3e) /* @pltoff(sym+add), data8 MSB */
  RELOC_NUMBER (R_IA64_PLTOFF64LSB, 0x3f) /* @pltoff(sym+add), data8 LSB */

  RELOC_NUMBER (R_IA64_FPTR64I, 0x43)	/* @fptr(sym+add), mov imm64 */
  RELOC_NUMBER (R_IA64_FPTR32MSB, 0x44)	/* @fptr(sym+add), data4 MSB */
  RELOC_NUMBER (R_IA64_FPTR32LSB, 0x45)	/* @fptr(sym+add), data4 LSB */
  RELOC_NUMBER (R_IA64_FPTR64MSB, 0x46)	/* @fptr(sym+add), data8 MSB */
  RELOC_NUMBER (R_IA64_FPTR64LSB, 0x47)	/* @fptr(sym+add), data8 LSB */

  RELOC_NUMBER (R_IA64_PCREL60B, 0x48)	/* @pcrel(sym+add), brl */
  RELOC_NUMBER (R_IA64_PCREL21B, 0x49)	/* @pcrel(sym+add), ptb, call */
  RELOC_NUMBER (R_IA64_PCREL21M, 0x4a)	/* @pcrel(sym+add), chk.s */
  RELOC_NUMBER (R_IA64_PCREL21F, 0x4b)	/* @pcrel(sym+add), fchkf */
  RELOC_NUMBER (R_IA64_PCREL32MSB, 0x4c) /* @pcrel(sym+add), data4 MSB */
  RELOC_NUMBER (R_IA64_PCREL32LSB, 0x4d) /* @pcrel(sym+add), data4 LSB */
  RELOC_NUMBER (R_IA64_PCREL64MSB, 0x4e) /* @pcrel(sym+add), data8 MSB */
  RELOC_NUMBER (R_IA64_PCREL64LSB, 0x4f) /* @pcrel(sym+add), data8 LSB */

  RELOC_NUMBER (R_IA64_LTOFF_FPTR22, 0x52) /* @ltoff(@fptr(s+a)), imm22 */
  RELOC_NUMBER (R_IA64_LTOFF_FPTR64I, 0x53) /* @ltoff(@fptr(s+a)), imm64 */
  RELOC_NUMBER (R_IA64_LTOFF_FPTR32MSB, 0x54) /* @ltoff(@fptr(s+a)), 4 MSB */
  RELOC_NUMBER (R_IA64_LTOFF_FPTR32LSB, 0x55) /* @ltoff(@fptr(s+a)), 4 LSB */
  RELOC_NUMBER (R_IA64_LTOFF_FPTR64MSB, 0x56) /* @ltoff(@fptr(s+a)), 8 MSB */
  RELOC_NUMBER (R_IA64_LTOFF_FPTR64LSB, 0x57) /* @ltoff(@fptr(s+a)), 8 LSB */

  RELOC_NUMBER (R_IA64_SEGREL32MSB, 0x5c) /* @segrel(sym+add), data4 MSB */
  RELOC_NUMBER (R_IA64_SEGREL32LSB, 0x5d) /* @segrel(sym+add), data4 LSB */
  RELOC_NUMBER (R_IA64_SEGREL64MSB, 0x5e) /* @segrel(sym+add), data8 MSB */
  RELOC_NUMBER (R_IA64_SEGREL64LSB, 0x5f) /* @segrel(sym+add), data8 LSB */

  RELOC_NUMBER (R_IA64_SECREL32MSB, 0x64) /* @secrel(sym+add), data4 MSB */
  RELOC_NUMBER (R_IA64_SECREL32LSB, 0x65) /* @secrel(sym+add), data4 LSB */
  RELOC_NUMBER (R_IA64_SECREL64MSB, 0x66) /* @secrel(sym+add), data8 MSB */
  RELOC_NUMBER (R_IA64_SECREL64LSB, 0x67) /* @secrel(sym+add), data8 LSB */

  RELOC_NUMBER (R_IA64_REL32MSB, 0x6c)	/* data 4 + REL */
  RELOC_NUMBER (R_IA64_REL32LSB, 0x6d)	/* data 4 + REL */
  RELOC_NUMBER (R_IA64_REL64MSB, 0x6e)	/* data 8 + REL */
  RELOC_NUMBER (R_IA64_REL64LSB, 0x6f)	/* data 8 + REL */

  RELOC_NUMBER (R_IA64_LTV32MSB, 0x74)	/* symbol + addend, data4 MSB */
  RELOC_NUMBER (R_IA64_LTV32LSB, 0x75)	/* symbol + addend, data4 LSB */
  RELOC_NUMBER (R_IA64_LTV64MSB, 0x76)	/* symbol + addend, data8 MSB */
  RELOC_NUMBER (R_IA64_LTV64LSB, 0x77)	/* symbol + addend, data8 LSB */

  RELOC_NUMBER (R_IA64_PCREL21BI, 0x79)	/* @pcrel(sym+add), ptb, call */
  RELOC_NUMBER (R_IA64_PCREL22, 0x7a)	/* @pcrel(sym+add), imm22 */
  RELOC_NUMBER (R_IA64_PCREL64I, 0x7b)	/* @pcrel(sym+add), imm64 */

  RELOC_NUMBER (R_IA64_IPLTMSB, 0x80)	/* dynamic reloc, imported PLT, MSB */
  RELOC_NUMBER (R_IA64_IPLTLSB, 0x81)	/* dynamic reloc, imported PLT, LSB */
  RELOC_NUMBER (R_IA64_COPY, 0x84)	/* dynamic reloc, data copy */
  RELOC_NUMBER (R_IA64_LTOFF22X, 0x86)  /* LTOFF22, relaxable.  */
  RELOC_NUMBER (R_IA64_LDXMOV, 0x87)	/* Use of LTOFF22X.  */

  RELOC_NUMBER (R_IA64_TPREL14, 0x91)	 /* @tprel(sym+add), add imm14 */
  RELOC_NUMBER (R_IA64_TPREL22, 0x92)	 /* @tprel(sym+add), add imm22 */
  RELOC_NUMBER (R_IA64_TPREL64I, 0x93)	 /* @tprel(sym+add), add imm64 */
  RELOC_NUMBER (R_IA64_TPREL64MSB, 0x96) /* @tprel(sym+add), data8 MSB */
  RELOC_NUMBER (R_IA64_TPREL64LSB, 0x97) /* @tprel(sym+add), data8 LSB */

  RELOC_NUMBER (R_IA64_LTOFF_TPREL22, 0x9a) /* @ltoff(@tprel(s+a)), add imm22 */

  RELOC_NUMBER (R_IA64_DTPMOD64MSB, 0xa6) /* @dtpmod(sym+add), data8 MSB */
  RELOC_NUMBER (R_IA64_DTPMOD64LSB, 0xa7) /* @dtpmod(sym+add), data8 LSB */
  RELOC_NUMBER (R_IA64_LTOFF_DTPMOD22, 0xaa) /* @ltoff(@dtpmod(s+a)), imm22 */

  RELOC_NUMBER (R_IA64_DTPREL14, 0xb1)    /* @dtprel(sym+add), imm14 */
  RELOC_NUMBER (R_IA64_DTPREL22, 0xb2)    /* @dtprel(sym+add), imm22 */
  RELOC_NUMBER (R_IA64_DTPREL64I, 0xb3)   /* @dtprel(sym+add), imm64 */
  RELOC_NUMBER (R_IA64_DTPREL32MSB, 0xb4) /* @dtprel(sym+add), data4 MSB */
  RELOC_NUMBER (R_IA64_DTPREL32LSB, 0xb5) /* @dtprel(sym+add), data4 LSB */
  RELOC_NUMBER (R_IA64_DTPREL64MSB, 0xb6) /* @dtprel(sym+add), data8 MSB */
  RELOC_NUMBER (R_IA64_DTPREL64LSB, 0xb7) /* @dtprel(sym+add), data8 LSB */

  RELOC_NUMBER (R_IA64_LTOFF_DTPREL22, 0xba) /* @ltoff(@dtprel(s+a)), imm22 */

  FAKE_RELOC (R_IA64_MAX_RELOC_CODE, 0xba)
END_RELOC_NUMBERS (R_IA64_max)

#endif /* _ELF_IA64_H */
