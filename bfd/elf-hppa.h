/* Common code for PA ELF implementations.
   Copyright (C) 1999 Free Software Foundation, Inc.

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
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#define ELF_HOWTO_TABLE_SIZE       R_PARISC_UNIMPLEMENTED + 1

/* This file is included by multiple PA ELF BFD backends with different
   sizes.

   Most of the routines are written to be size independent, but sometimes
   external constraints require 32 or 64 bit specific code.  We remap
   the definitions/functions as necessary here.  */
#if ARCH_SIZE == 64
#define ELF_R_TYPE(X)   ELF64_R_TYPE(X)
#define ELF_R_SYM(X)   ELF64_R_SYM(X)
#define _bfd_elf_hppa_gen_reloc_type _bfd_elf64_hppa_gen_reloc_type
#define elf_hppa_relocate_section elf64_hppa_relocate_section
#define bfd_elf_bfd_final_link bfd_elf64_bfd_final_link
#define elf_hppa_final_link elf64_hppa_final_link
#endif
#if ARCH_SIZE == 32
#define ELF_R_TYPE(X)   ELF32_R_TYPE(X)
#define ELF_R_SYM(X)   ELF32_R_SYM(X)
#define _bfd_elf_hppa_gen_reloc_type _bfd_elf32_hppa_gen_reloc_type
#define elf_hppa_relocate_section elf32_hppa_relocate_section
#define bfd_elf_bfd_final_link bfd_elf32_bfd_final_link
#define elf_hppa_final_link elf32_hppa_final_link
#endif

static boolean
elf_hppa_relocate_section
  PARAMS ((bfd *, struct bfd_link_info *, bfd *, asection *,
           bfd_byte *, Elf_Internal_Rela *, Elf_Internal_Sym *, asection **));

static bfd_reloc_status_type elf_hppa_final_link_relocate
  PARAMS ((Elf_Internal_Rela *, bfd *, bfd *, asection *,
           bfd_byte *, bfd_vma, struct bfd_link_info *,
           asection *, struct elf_link_hash_entry *,
	   struct elf64_hppa_dyn_hash_entry *));

static unsigned long elf_hppa_relocate_insn
  PARAMS ((unsigned long, long, unsigned long));

static boolean elf_hppa_add_symbol_hook
  PARAMS ((bfd *, struct bfd_link_info *, const Elf_Internal_Sym *,
	   const char **, flagword *, asection **, bfd_vma *));

static boolean elf_hppa_final_link
  PARAMS ((bfd *, struct bfd_link_info *));

/* ELF/PA relocation howto entries.  */

static reloc_howto_type elf_hppa_howto_table[ELF_HOWTO_TABLE_SIZE] =
{
  {R_PARISC_NONE, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_NONE"},

  /* The values in DIR32 are to placate the check in
     _bfd_stab_section_find_nearest_line.  */
  {R_PARISC_DIR32, 0, 2, 32, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DIR32", false, 0, 0xffffffff, false},
  {R_PARISC_DIR21L, 0, 0, 21, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DIR21L"},
  {R_PARISC_DIR17R, 0, 0, 17, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DIR17R"},
  {R_PARISC_DIR17F, 0, 0, 17, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DIR17F"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_DIR14R, 0, 0, 14, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DIR14R"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_PCREL32, 0, 0, 32, true, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL32"},

  {R_PARISC_PCREL21L, 0, 0, 21, true, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL21L"},
  {R_PARISC_PCREL17R, 0, 0, 17, true, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL17R"},
  {R_PARISC_PCREL17F, 0, 0, 17, true, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL17F"},
  {R_PARISC_PCREL17C, 0, 0, 17, true, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL17C"},
  {R_PARISC_PCREL14R, 0, 0, 14, true, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL14R"},
  {R_PARISC_PCREL14F, 0, 0, 14, true, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL14F"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_DPREL21L, 0, 0, 21, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DPREL21L"},
  {R_PARISC_DPREL14WR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DPREL14WR"},

  {R_PARISC_DPREL14DR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DPREL14DR"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_DPREL14R, 0, 0, 14, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DPREL14R"},
  {R_PARISC_DPREL14F, 0, 0, 14, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DPREL14F"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_DLTREL21L, 0, 0, 21, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DLTREL21L"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},

  {R_PARISC_DLTREL14R, 0, 0, 14, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DLTREL14R"},
  {R_PARISC_DLTREL14F, 0, 0, 14, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DLTREL14F"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_DLTIND21L, 0, 0, 21, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DLTIND21L"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_DLTIND14R, 0, 0, 14, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DLTIND14R"},
  {R_PARISC_DLTIND14F, 0, 0, 14, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DLTIND14F"},

  {R_PARISC_SETBASE, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_SETBASE"},
  {R_PARISC_SECREL32, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_SECREL32"},
  {R_PARISC_BASEREL21L, 0, 0, 21, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_BASEREL21L"},
  {R_PARISC_BASEREL17R, 0, 0, 17, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_BASEREL17R"},
  {R_PARISC_BASEREL17F, 0, 0, 17, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_BASEREL17F"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_BASEREL14R, 0, 0, 14, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_BASEREL14R"},
  {R_PARISC_BASEREL14F, 0, 0, 14, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_BASEREL14F"},
  {R_PARISC_SEGBASE, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_SEGBASE"},
  {R_PARISC_SEGREL32, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_SEGREL32"},

  {R_PARISC_PLTOFF21L, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PLTOFF21L"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_PLTOFF14R, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PLTOFF14R"},
  {R_PARISC_PLTOFF14F, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PLTOFF14F"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_LTOFF_FPTR32, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_FPTR32"},
  {R_PARISC_LTOFF_FPTR21L, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_FPTR21L"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},

  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_LTOFF_FPTR14R, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_FPTR14R"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_FPTR64, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_FPTR64"},
  {R_PARISC_PLABEL32, 0, 0, 32, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PLABEL32"},
  {R_PARISC_PLABEL21L, 0, 0, 21, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PLABEL21L"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},

  {R_PARISC_PLABEL14R, 0, 0, 14, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PLABEL14R"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_PCREL64, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL64"},
  {R_PARISC_PCREL22C, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL22C"},
  {R_PARISC_PCREL22F, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL22F"},
  {R_PARISC_PCREL14WR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL14WR"},
  {R_PARISC_PCREL14DR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL14DR"},
  {R_PARISC_PCREL16F, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL16F"},
  {R_PARISC_PCREL16WF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL16WF"},
  {R_PARISC_PCREL16DF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PCREL16DF"},

  {R_PARISC_DIR64, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DIR64"},
  {R_PARISC_DIR64WR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DIR64WR"},
  {R_PARISC_DIR64DR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DIR64DR"},
  {R_PARISC_DIR14WR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DIR14WR"},
  {R_PARISC_DIR14DR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DIR14DR"},
  {R_PARISC_DIR16F, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DIR16F"},
  {R_PARISC_DIR16WF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DIR16WF"},
  {R_PARISC_DIR16DF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DIR16DF"},
  {R_PARISC_GPREL64, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_GPREL64"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},

  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_DLTREL14WR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DLTREL14WR"},
  {R_PARISC_DLTREL14DR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DLTREL14DR"},
  {R_PARISC_GPREL16F, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_GPREL16F"},
  {R_PARISC_GPREL16WF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_GPREL16WF"},
  {R_PARISC_GPREL16DF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_GPREL16DF"},
  {R_PARISC_LTOFF64, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF64"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_DLTIND14WR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DLTIND14WR"},

  {R_PARISC_DLTIND14DR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_DLTIND14DR"},
  {R_PARISC_LTOFF16F, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF16F"},
  {R_PARISC_LTOFF16DF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF16DF"},
  {R_PARISC_SECREL64, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_SECREL64"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_BASEREL14WR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_BSEREL14WR"},
  {R_PARISC_BASEREL14DR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_BASEREL14DR"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},

  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_SEGREL64, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_SEGREL64"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_PLTOFF14WR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PLTOFF14WR"},
  {R_PARISC_PLTOFF14DR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PLTOFF14DR"},
  {R_PARISC_PLTOFF16F, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PLTOFF16F"},
  {R_PARISC_PLTOFF16WF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PLTOFF16WF"},
  {R_PARISC_PLTOFF16DF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_PLTOFF16DF"},

  {R_PARISC_LTOFF_FPTR64, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_LTOFF_FPTR14WR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_FPTR14WR"},
  {R_PARISC_LTOFF_FPTR14DR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_FPTR14DR"},
  {R_PARISC_LTOFF_FPTR16F, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_FPTR16F"},
  {R_PARISC_LTOFF_FPTR16WF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_FPTR16WF"},
  {R_PARISC_LTOFF_FPTR16DF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_COPY, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_COPY"},
  {R_PARISC_IPLT, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_IPLT"},

  {R_PARISC_EPLT, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_EPLT"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},

  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},

  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_TPREL32, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_TPREL32"},
  {R_PARISC_TPREL21L, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_TPREL21L"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_TPREL14R, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_TPREL14R"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},

  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_LTOFF_TP21L, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_TP21L"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_LTOFF_TP14R, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_LTOFF_TP14F, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_TP14F"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},

  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},

  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},

  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},

  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},

  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_TPREL64, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_TPREL64"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_TPREL14WR, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_TPREL14WR"},

  {R_PARISC_TPREL14DR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_TPREL14DR"},
  {R_PARISC_TPREL16F, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_TPREL16F"},
  {R_PARISC_TPREL16WF, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_TPREL16WF"},
  {R_PARISC_TPREL16DF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_TPREL16DF"},
  {R_PARISC_LTOFF_TP64, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_TP64"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_UNIMPLEMENTED, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_UNIMPLEMENTED"},
  {R_PARISC_LTOFF_TP14WR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_TP14WR"},
  {R_PARISC_LTOFF_TP14DR, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_TP14DR"},
  {R_PARISC_LTOFF_TP16F, 0, 0, 0, false, 0, complain_overflow_dont, NULL, "R_PARISC_LTOFF_TP16F"},

  {R_PARISC_LTOFF_TP16WF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_TP16WF"},
  {R_PARISC_LTOFF_TP16DF, 0, 0, 0, false, 0, complain_overflow_bitfield, bfd_elf_generic_reloc, "R_PARISC_LTOFF_TP16DF"},
};

#define OFFSET_14R_FROM_21L 4
#define OFFSET_14F_FROM_21L 5

/* Return one (or more) BFD relocations which implement the base
   relocation with modifications based on format and field.  */

elf_hppa_reloc_type **
_bfd_elf_hppa_gen_reloc_type (abfd, base_type, format, field, ignore, sym)
     bfd *abfd;
     elf_hppa_reloc_type base_type;
     int format;
     int field;
     int ignore;
     asymbol *sym;
{
  elf_hppa_reloc_type *finaltype;
  elf_hppa_reloc_type **final_types;

  /* Allocate slots for the BFD relocation.  */
  final_types = ((elf_hppa_reloc_type **)
		 bfd_alloc (abfd, sizeof (elf_hppa_reloc_type *) * 2));
  if (final_types == NULL)
    return NULL;

  /* Allocate space for the relocation itself.  */
  finaltype = ((elf_hppa_reloc_type *)
	       bfd_alloc (abfd, sizeof (elf_hppa_reloc_type)));
  if (finaltype == NULL)
    return NULL;

  /* Some reasonable defaults.  */
  final_types[0] = finaltype;
  final_types[1] = NULL;

#define final_type finaltype[0]

  final_type = base_type;

  /* Just a tangle of nested switch statements to deal with the braindamage
     that a different field selector means a completely different relocation
     for PA ELF.  */
  switch (base_type)
    {
    /* We have been using generic relocation types.  However, that may not
       really make sense.  Anyway, we need to support both R_PARISC_DIR64
       and R_PARISC_DIR32 here.  */
    case R_PARISC_DIR32:
    case R_PARISC_DIR64:
    case R_HPPA_ABS_CALL:
      switch (format)
	{
	case 14:
	  switch (field)
	    {
	    case e_rsel:
	    case e_rrsel:
	      final_type = R_PARISC_DIR14R;
	      break;
	    case e_rtsel:
	      final_type = R_PARISC_DLTIND14R;
	      break;
	    case e_rtpsel:
	      final_type = R_PARISC_LTOFF_FPTR14DR;
	      break;
	    case e_tsel:
	      final_type = R_PARISC_DLTIND14F;
	      break;
	    case e_rpsel:
	      final_type = R_PARISC_PLABEL14R;
	      break;
	    default:
	      return NULL;
	    }
	  break;

	case 17:
	  switch (field)
	    {
	    case e_fsel:
	      final_type = R_PARISC_DIR17F;
	      break;
	    case e_rsel:
	    case e_rrsel:
	      final_type = R_PARISC_DIR17R;
	      break;
	    default:
	      return NULL;
	    }
	  break;

	case 21:
	  switch (field)
	    {
	    case e_lsel:
	    case e_lrsel:
	      final_type = R_PARISC_DIR21L;
	      break;
	    case e_ltsel:
	      final_type = R_PARISC_DLTIND21L;
	      break;
	    case e_ltpsel:
	      final_type = R_PARISC_LTOFF_FPTR21L;
	      break;
	    case e_lpsel:
	      final_type = R_PARISC_PLABEL21L;
	      break;
	    default:
	      return NULL;
	    }
	  break;

	case 32:
	  switch (field)
	    {
	    case e_fsel:
	      final_type = R_PARISC_DIR32;
	      /* When in 64bit mode, a 32bit relocation is supposed to
		 be a section relative relocation.  Dwarf2 (for example)
		 uses 32bit section relative relocations.  */
	      if (bfd_get_arch_info (abfd)->bits_per_address != 32)
	        final_type = R_PARISC_SECREL32;
	      break;
	    case e_psel:
	      final_type = R_PARISC_PLABEL32;
	      break;
	    default:
	      return NULL;
	    }
	  break;

	case 64:
	  switch (field)
	    {
	    case e_fsel:
	      final_type = R_PARISC_DIR64;
	      break;
	    case e_psel:
	      final_type = R_PARISC_FPTR64;
	      break;
	    default:
	      return NULL;
	    }
	  break;

	default:
	  return NULL;
	}
      break;


    case R_HPPA_GOTOFF:
      switch (format)
	{
	case 14:
	  switch (field)
	    {
	    case e_rsel:
	    case e_rrsel:
	      final_type = base_type + OFFSET_14R_FROM_21L;
	      break;
	    case e_fsel:
	      final_type = base_type + OFFSET_14F_FROM_21L;
	      break;
	    default:
	      return NULL;
	    }
	  break;

	case 21:
	  switch (field)
	    {
	    case e_lrsel:
	    case e_lsel:
	      final_type = base_type;
	      break;
	    default:
	      return NULL;
	    }
	  break;

	default:
	  return NULL;
	}
      break;


    case R_HPPA_PCREL_CALL:
      switch (format)
	{
	case 14:
	  switch (field)
	    {
	    case e_rsel:
	    case e_rrsel:
	      final_type = R_PARISC_PCREL14R;
	      break;
	    case e_fsel:
	      final_type = R_PARISC_PCREL14F;
	      break;
	    default:
	      return NULL;
	    }
	  break;

	case 17:
	  switch (field)
	    {
	    case e_rsel:
	    case e_rrsel:
	      final_type = R_PARISC_PCREL17R;
	      break;
	    case e_fsel:
	      final_type = R_PARISC_PCREL17F;
	      break;
	    default:
	      return NULL;
	    }
	  break;

	case 22:
	  switch (field)
	    {
	    case e_fsel:
	      final_type = R_PARISC_PCREL22F;
	      break;
	    default:
	      return NULL;
	    }
	  break;

	case 21:
	  switch (field)
	    {
	    case e_lsel:
	    case e_lrsel:
	      final_type = R_PARISC_PCREL21L;
	      break;
	    default:
	      return NULL;
	    }
	  break;

	default:
	  return NULL;
	}
      break;

    case R_PARISC_SEGREL32:
    case R_PARISC_SEGBASE:
      /* The defaults are fine for these cases.  */
      break;

    default:
      return NULL;
    }

  return final_types;
}

/* Translate from an elf into field into a howto relocation pointer.  */

static void
elf_hppa_info_to_howto (abfd, bfd_reloc, elf_reloc)
     bfd *abfd;
     arelent *bfd_reloc;
     Elf_Internal_Rela *elf_reloc;
{
  BFD_ASSERT (ELF_R_TYPE(elf_reloc->r_info)
	      < (unsigned int) R_PARISC_UNIMPLEMENTED);
  bfd_reloc->howto = &elf_hppa_howto_table[ELF_R_TYPE (elf_reloc->r_info)];
}

/* Translate from an elf into field into a howto relocation pointer.  */

static void
elf_hppa_info_to_howto_rel (abfd, bfd_reloc, elf_reloc)
     bfd *abfd;
     arelent *bfd_reloc;
     Elf_Internal_Rel *elf_reloc;
{
  BFD_ASSERT (ELF_R_TYPE(elf_reloc->r_info)
	      < (unsigned int) R_PARISC_UNIMPLEMENTED);
  bfd_reloc->howto = &elf_hppa_howto_table[ELF_R_TYPE (elf_reloc->r_info)];
}

/* Return the address of the howto table entry to perform the CODE
   relocation for an ARCH machine.  */

static reloc_howto_type *
elf_hppa_reloc_type_lookup (abfd, code)
     bfd *abfd;
     bfd_reloc_code_real_type code;
{
  if ((int) code < (int) R_PARISC_UNIMPLEMENTED)
    {
      BFD_ASSERT ((int) elf_hppa_howto_table[(int) code].type == (int) code);
      return &elf_hppa_howto_table[(int) code];
    }
  return NULL;
}

static void
elf_hppa_final_write_processing (abfd, linker)
     bfd *abfd;
     boolean linker;
{
  int mach = bfd_get_mach (abfd);

  elf_elfheader (abfd)->e_flags &= ~(EF_PARISC_ARCH | EF_PARISC_TRAPNIL
				     | EF_PARISC_EXT | EF_PARISC_LSB
				     | EF_PARISC_WIDE | EF_PARISC_NO_KABP
				     | EF_PARISC_LAZYSWAP);

  if (mach == 10)
    elf_elfheader (abfd)->e_flags |= EFA_PARISC_1_0;
  else if (mach == 11)
    elf_elfheader (abfd)->e_flags |= EFA_PARISC_1_1;
  else if (mach == 20)
    elf_elfheader (abfd)->e_flags |= EFA_PARISC_2_0;
  else if (mach == 25)
    elf_elfheader (abfd)->e_flags |= EF_PARISC_WIDE | EFA_PARISC_2_0;
}

/* Return true if SYM represents a local label symbol.  */

static boolean
elf_hppa_is_local_label_name (abfd, name)
     bfd *abfd ATTRIBUTE_UNUSED;
     const char *name;
{
  return (name[0] == 'L' && name[1] == '$');
}

/* Set the correct type for an ELF section.  We do this by the
   section name, which is a hack, but ought to work.  */

static boolean
elf_hppa_fake_sections (abfd, hdr, sec)
     bfd *abfd;
     Elf64_Internal_Shdr *hdr;
     asection *sec;
{
  register const char *name;

  name = bfd_get_section_name (abfd, sec);

  if (strcmp (name, ".PARISC.unwind") == 0)
    {
      int indx;
      asection *sec;
      hdr->sh_type = SHT_LOPROC + 1;
      /* ?!? How are unwinds supposed to work for symbols in arbitrary
	 sections?  Or what if we have multiple .text sections in a single
	 .o file?  HP really messed up on this one.

	 Ugh.  We can not use elf_section_data (sec)->this_idx at this
	 point because it is not initialized yet.

	 So we (gasp) recompute it here.  Hopefully nobody ever changes the
	 way sections are numbered in elf.c!  */
      for (sec = abfd->sections, indx = 1; sec; sec = sec->next, indx++)
	{
	  if (sec->name && strcmp (sec->name, ".text") == 0)
	    {
	      hdr->sh_info = indx;
	      break;
	    }
	}

      /* I have no idea if this is really necessary or what it means.  */
      hdr->sh_entsize = 4;
    }
  return true;
}

/* Hook called by the linker routine which adds symbols from an object
   file.  HP's libraries define symbols with HP specific section
   indices, which we have to handle.  */

static boolean
elf_hppa_add_symbol_hook (abfd, info, sym, namep, flagsp, secp, valp)
     bfd *abfd;
     struct bfd_link_info *info ATTRIBUTE_UNUSED;
     const Elf_Internal_Sym *sym;
     const char **namep ATTRIBUTE_UNUSED;
     flagword *flagsp ATTRIBUTE_UNUSED;
     asection **secp;
     bfd_vma *valp;
{
  int index = sym->st_shndx;

  switch (index)
    {
    case SHN_PARISC_ANSI_COMMON:
      *secp = bfd_make_section_old_way (abfd, ".PARISC.ansi.common");
      (*secp)->flags |= SEC_IS_COMMON;
      *valp = sym->st_size;
      break;

    case SHN_PARISC_HUGE_COMMON:
      *secp = bfd_make_section_old_way (abfd, ".PARISC.huge.common");
      (*secp)->flags |= SEC_IS_COMMON;
      *valp = sym->st_size;
      break;
    }

  return true;
}

/* Called after we have seen all the input files/sections, but before
   final symbol resolution and section placement has been determined.

   We use this hook to (possibly) provide a value for __gp, then we
   fall back to the generic ELF final link routine.  */

static boolean
elf_hppa_final_link (abfd, info)
     bfd *abfd;
     struct bfd_link_info *info;
{
  /* Make sure we've got ourselves a suitable __gp value.  */
  if (!info->relocateable)
    {
      bfd_vma min_short_vma = (bfd_vma) -1, max_short_vma = 0;
      struct elf_link_hash_entry *gp;
      bfd_vma gp_val = 0;
      asection *os;

      /* Find the .opd section.  __gp's value should be the same as
	 the start of .PARISC.global section.  */
      for (os = abfd->sections; os ; os = os->next)
	{
	  bfd_vma lo, hi;

	  /* This would be cleaner if we marked sections with an attribute
	     indicating they are short sections.  */
	  if (strcmp (os->name, ".PARISC.global") == 0)
	    break;
	}

      BFD_ASSERT (os != NULL)

      gp_val = (os->output_section->vma + os->output_offset);
		   
      gp = elf_link_hash_lookup (elf_hash_table (info), "__gp", true,
				 true, false);
      gp->root.type = bfd_link_hash_defined;
      gp->root.u.def.section = os;
      gp->root.u.def.value = 0;
      _bfd_set_gp_value (abfd, gp_val);
    }

  /* Invoke the regular ELF backend linker to do all the work.  */
  return bfd_elf_bfd_final_link (abfd, info);
}

/* Relocate an HPPA ELF section.  */

static boolean
elf_hppa_relocate_section (output_bfd, info, input_bfd, input_section,
			   contents, relocs, local_syms, local_sections)
     bfd *output_bfd;
     struct bfd_link_info *info;
     bfd *input_bfd;
     asection *input_section;
     bfd_byte *contents;
     Elf_Internal_Rela *relocs;
     Elf_Internal_Sym *local_syms;
     asection **local_sections;
{
  Elf_Internal_Shdr *symtab_hdr;
  Elf_Internal_Rela *rel;
  Elf_Internal_Rela *relend;
  struct elf64_hppa_link_hash_table *hppa_info = elf64_hppa_hash_table (info);

  symtab_hdr = &elf_tdata (input_bfd)->symtab_hdr;

  rel = relocs;
  relend = relocs + input_section->reloc_count;
  for (; rel < relend; rel++)
    {
      int r_type;
      reloc_howto_type *howto;
      unsigned long r_symndx;
      struct elf_link_hash_entry *h;
      Elf_Internal_Sym *sym;
      asection *sym_sec;
      bfd_vma relocation;
      bfd_reloc_status_type r;
      const char *sym_name;
      char *dyn_name;
      char *dynh_buf = NULL;
      size_t dynh_buflen = 0;
      struct elf64_hppa_dyn_hash_entry *dyn_h = NULL;

      r_type = ELF_R_TYPE (rel->r_info);
      if (r_type < 0 || r_type >= (int) R_PARISC_UNIMPLEMENTED)
	{
	  bfd_set_error (bfd_error_bad_value);
	  return false;
	}

      r_symndx = ELF_R_SYM (rel->r_info);

      if (info->relocateable)
	{
	  /* This is a relocateable link.  We don't have to change
	     anything, unless the reloc is against a section symbol,
	     in which case we have to adjust according to where the
	     section symbol winds up in the output section.  */
	  if (r_symndx < symtab_hdr->sh_info)
	    {
	      sym = local_syms + r_symndx;
	      if (ELF_ST_TYPE (sym->st_info) == STT_SECTION)
		{
		  sym_sec = local_sections[r_symndx];
		  rel->r_addend += sym_sec->output_offset;
		}
	    }

	  continue;
	}

      /* This is a final link.  */
      h = NULL;
      sym = NULL;
      sym_sec = NULL;
      if (r_symndx < symtab_hdr->sh_info)
	{
	  /* This is a local symbol.  */
	  sym = local_syms + r_symndx;
	  sym_sec = local_sections[r_symndx];
	  relocation = ((ELF_ST_TYPE (sym->st_info) == STT_SECTION
			   ? 0 : sym->st_value)
			 + sym_sec->output_offset
			 + sym_sec->output_section->vma);

	  /* If this symbol has an entry in the PA64 dynamic hash
	     table, then get it.  */
	  dyn_name = get_dyn_name (input_bfd, h, rel,
				   &dynh_buf, &dynh_buflen);
	  dyn_h = elf64_hppa_dyn_hash_lookup (&hppa_info->dyn_hash_table,
					      dyn_name, false, false);

	}
      else
	{
	  /* This is not a local symbol.  */
	  long indx;

	  indx = r_symndx - symtab_hdr->sh_info;
	  h = elf_sym_hashes (input_bfd)[indx];
	  while (h->root.type == bfd_link_hash_indirect
		 || h->root.type == bfd_link_hash_warning)
	    h = (struct elf_link_hash_entry *) h->root.u.i.link;
	  if (h->root.type == bfd_link_hash_defined
	      || h->root.type == bfd_link_hash_defweak)
	    {
	      sym_sec = h->root.u.def.section;


	      /* If this symbol has an entry in the PA64 dynamic hash
		 table, then get it.  */
	      dyn_name = get_dyn_name (input_bfd, h, rel,
				       &dynh_buf, &dynh_buflen);
	      dyn_h = elf64_hppa_dyn_hash_lookup (&hppa_info->dyn_hash_table,
						  dyn_name, false, false);

	      /* If we have a relocation against a symbol defined in a
		 shared library and we have not created an entry in the
		 PA64 dynamic symbol hash table for it, then we lose.  */
	      if (sym_sec->output_section == NULL && dyn_h == NULL)
		{
		  (*_bfd_error_handler)
		    (_("%s: warning: unresolvable relocation against symbol `%s' from %s section"),
		     bfd_get_filename (input_bfd), h->root.root.string,
		     bfd_get_section_name (input_bfd, input_section));
		  relocation = 0;
		}
	      else if (sym_sec->output_section)
		relocation = (h->root.u.def.value
			      + sym_sec->output_offset
			      + sym_sec->output_section->vma);
	      /* Value will be provided via one of the offsets in the
		 dyn_h hash table entry.  */
	      else
		relocation = 0;
	    }
	  else if (h->root.type == bfd_link_hash_undefweak)
	    relocation = 0;
	  else
	    {
	      if (!((*info->callbacks->undefined_symbol)
		    (info, h->root.root.string, input_bfd,
		     input_section, rel->r_offset)))
		return false;
	      break;
	    }
	}

      if (h != NULL)
	sym_name = h->root.root.string;
      else
	{
	  sym_name = bfd_elf_string_from_elf_section (input_bfd,
						      symtab_hdr->sh_link,
						      sym->st_name);
	  if (sym_name == NULL)
	    return false;
	  if (*sym_name == '\0')
	    sym_name = bfd_section_name (input_bfd, sym_sec);
	}

      r = elf_hppa_final_link_relocate (rel, input_bfd, output_bfd,
					input_section, contents,
					relocation, info, sym_sec,
					h, dyn_h);

      if (r != bfd_reloc_ok)
	{
	  switch (r)
	    {
	    default:
	      abort ();
	    case bfd_reloc_overflow:
	      {
		if (!((*info->callbacks->reloc_overflow)
		      (info, sym_name, howto->name, (bfd_vma) 0,
			input_bfd, input_section, rel->r_offset)))
		  return false;
	      }
	      break;
	    }
	}
    }
  return true;
}


/* Compute the value for a relocation (REL) during a final link stage,
   then insert the value into the proper location in CONTENTS. 

   VALUE is a tentative value for the relocation and may be overridden
   and modified here based on the specific relocation to be performed.

   For example we do conversions for PC-relative branches in this routine
   or redirection of calls to external routines to stubs. 

   The work of actually applying the relocation is left to a helper
   routine in an attempt to reduce the complexity and size of this
   function.  */

static bfd_reloc_status_type
elf_hppa_final_link_relocate (rel, input_bfd, output_bfd,
			      input_section, contents, value,
			      info, sym_sec, h, dyn_h)
     Elf_Internal_Rela *rel;
     bfd *input_bfd;
     bfd *output_bfd;
     asection *input_section;
     bfd_byte *contents;
     bfd_vma value;
     struct bfd_link_info *info;
     asection *sym_sec;
     struct elf_link_hash_entry *h;
     struct elf64_hppa_dyn_hash_entry *dyn_h;
{
  unsigned long insn;
  bfd_vma offset = rel->r_offset;
  bfd_vma addend = rel->r_addend;
  reloc_howto_type *howto = elf_hppa_howto_table + ELF_R_TYPE (rel->r_info);
  unsigned long r_type = howto->type;
  unsigned long r_format = howto->bitsize;
  unsigned long r_field = e_fsel;
  bfd_byte *hit_data = contents + offset;
  struct elf64_hppa_link_hash_table *hppa_info = elf64_hppa_hash_table (info);

  insn = bfd_get_32 (input_bfd, hit_data);

/* For reference here a quick summary of the relocations found in the
   HPUX 11.00 PA64 .o and .a files, but not yet implemented.  This is mostly
   a guide to help prioritize what relocation support is worked on first.
   The list will be deleted eventually.

   27210 R_PARISC_SEGREL32
   772 R_PARISC_PLTOFF14DR
   386 R_PARISC_PLTOFF21L
   6 R_PARISC_LTOFF64
   5 R_PARISC_SEGREL64  */

  switch (r_type)
    {
    case R_PARISC_NONE:
      break;

    /* Random PC relative relocs.  */
    case R_PARISC_PCREL21L:
    case R_PARISC_PCREL14R:
    case R_PARISC_PCREL14F:
    case R_PARISC_PCREL14WR:
    case R_PARISC_PCREL14DR:
    case R_PARISC_PCREL16F:
    case R_PARISC_PCREL16WF:
    case R_PARISC_PCREL16DF:
      {
	if (r_type == R_PARISC_PCREL21L)
	  r_field = e_lsel;
	else if (r_type == R_PARISC_PCREL14F
		 || r_type == R_PARISC_PCREL16F
		 || r_type == R_PARISC_PCREL16WF
		 || r_type == R_PARISC_PCREL16DF)
	  r_field = e_fsel;
	else
	  r_field = e_rsel;

	/* If this is a call to a function defined in another dynamic
	   library, then redirect the call to the local stub for this
	   function.  */
	if (sym_sec->output_section == NULL)
	  value = dyn_h->stub_offset;
  
	/* Turn VALUE into a proper PC relative address.  */
	value -= (offset + input_section->output_offset
		  + input_section->output_section->vma);

	/* Adjust for any field selectors.  */
	value = hppa_field_adjust (value, -8 + addend, r_field);

	/* Apply the relocation to the given instruction.  */
	insn = elf_hppa_relocate_insn (insn, value, r_type);
	break;
      }

    /* Basic function call support.  I'm not entirely sure if PCREL14F is
       actually needed or even handled correctly.

       Note for a call to a function defined in another dynamic library
       we want to redirect the call to a stub.  */
    case R_PARISC_PCREL22F:
    case R_PARISC_PCREL17F:
    case R_PARISC_PCREL22C:
    case R_PARISC_PCREL17C:
    case R_PARISC_PCREL17R:
      {
	if (r_type == R_PARISC_PCREL17R)
	  r_field = e_rsel;
	else
	  r_field = e_fsel;

	/* If this is a call to a function defined in another dynamic
	   library, then redirect the call to the local stub for this
	   function.  */
	if (sym_sec->output_section == NULL)
	  value = dyn_h->stub_offset;
  
	/* Turn VALUE into a proper PC relative address.  */
	value -= (offset + input_section->output_offset
		  + input_section->output_section->vma);

	/* Adjust for any field selectors.  */
	value = hppa_field_adjust (value, -8 + addend, e_fsel);

	/* All branches are implicitly shifted by 2 places.  */
	value >>= 2;

	/* Apply the relocation to the given instruction.  */
	insn = elf_hppa_relocate_insn (insn, value, r_type);
	break;
      }

    /* Indirect references to data through the DLT.  */
    case R_PARISC_DLTIND14R:
    case R_PARISC_DLTIND14F:
    case R_PARISC_DLTIND14DR:
    case R_PARISC_DLTIND14WR:
    case R_PARISC_DLTIND21L:
    case R_PARISC_LTOFF_FPTR14R:
    case R_PARISC_LTOFF_FPTR14DR:
    case R_PARISC_LTOFF_FPTR14WR:
    case R_PARISC_LTOFF_FPTR21L:
    case R_PARISC_LTOFF_FPTR16F:
    case R_PARISC_LTOFF_FPTR16WF:
    case R_PARISC_LTOFF_FPTR16DF:
    case R_PARISC_LTOFF_TP21L:
    case R_PARISC_LTOFF_TP14R:
    case R_PARISC_LTOFF_TP14F:
    case R_PARISC_LTOFF_TP14WR:
    case R_PARISC_LTOFF_TP14DR:
    case R_PARISC_LTOFF_TP16F:
    case R_PARISC_LTOFF_TP16WF:
    case R_PARISC_LTOFF_TP16DF:
      {
	/* We want the value of the DLT offset for this symbol, not
	   the symbol's actual address.  */
	value = dyn_h->dlt_offset + hppa_info->dlt_sec->output_offset;

	/* All DLTIND relocations are basically the same at this point,
	   except that we need different field selectors for the 21bit
	   version vs the 14bit versions.  */
	if (r_type == R_PARISC_DLTIND21L
	    || r_type == R_PARISC_LTOFF_FPTR21L
	    || r_type == R_PARISC_LTOFF_TP21L)
	  value = hppa_field_adjust (value, addend, e_lrsel);
	else if (r_type == R_PARISC_DLTIND14F
		 || r_type == R_PARISC_LTOFF_FPTR16F
		 || r_type == R_PARISC_LTOFF_FPTR16WF
		 || r_type == R_PARISC_LTOFF_FPTR16DF
		 || r_type == R_PARISC_LTOFF_TP16F
		 || r_type == R_PARISC_LTOFF_TP16WF
		 || r_type == R_PARISC_LTOFF_TP16DF)
	  value = hppa_field_adjust (value, addend, e_fsel);
	else
	  value = hppa_field_adjust (value, addend, e_rrsel);

	insn = elf_hppa_relocate_insn (insn, value, r_type);
	break;
      }

    case R_PARISC_DLTREL14R:
    case R_PARISC_DLTREL14F:
    case R_PARISC_DLTREL14DR:
    case R_PARISC_DLTREL14WR:
    case R_PARISC_DLTREL21L:
    case R_PARISC_DPREL21L:
    case R_PARISC_DPREL14WR:
    case R_PARISC_DPREL14DR:
    case R_PARISC_DPREL14R:
    case R_PARISC_DPREL14F:
    case R_PARISC_GPREL16F:
    case R_PARISC_GPREL16WF:
    case R_PARISC_GPREL16DF:
      {
	/* Subtract out the global pointer value to make value a DLT
	   relative address.  */
	value -= _bfd_get_gp_value (output_bfd);

	/* All DLTREL relocations are basically the same at this point,
	   except that we need different field selectors for the 21bit
	   version vs the 14bit versions.  */
	if (r_type == R_PARISC_DLTREL21L
	    || r_type == R_PARISC_DPREL21L)
	  value = hppa_field_adjust (value, addend, e_lrsel);
	else if (r_type == R_PARISC_DLTREL14F
		 || r_type == R_PARISC_DPREL14F
		 || r_type == R_PARISC_GPREL16F
		 || r_type == R_PARISC_GPREL16WF
		 || r_type == R_PARISC_GPREL16DF)
	  value = hppa_field_adjust (value, addend, e_fsel);
	else
	  value = hppa_field_adjust (value, addend, e_rrsel);

	insn = elf_hppa_relocate_insn (insn, value, r_type);
	break;
      }

    case R_PARISC_LTOFF_FPTR32:
      {
	/* We want the value of the DLT offset for this symbol, not
	   the symbol's actual address.  */
	value = dyn_h->dlt_offset + hppa_info->dlt_sec->output_offset;
	bfd_put_32 (input_bfd, value, hit_data);
	return bfd_reloc_ok;
      }

    case R_PARISC_LTOFF_FPTR64:
    case R_PARISC_LTOFF_TP64:
      {
	/* We want the value of the DLT offset for this symbol, not
	   the symbol's actual address.  */
	value = dyn_h->dlt_offset + hppa_info->dlt_sec->output_offset;
	bfd_put_64 (input_bfd, value, hit_data);
	return bfd_reloc_ok;
      }

    case R_PARISC_DIR32:
      bfd_put_32 (input_bfd, value + addend, hit_data);
      return bfd_reloc_ok;

    case R_PARISC_DIR64:
      bfd_put_64 (input_bfd, value + addend, hit_data);
      return bfd_reloc_ok;

    case R_PARISC_GPREL64:
      /* Subtract out the global pointer value to make value a DLT
	 relative address.  */
      value -= _bfd_get_gp_value (output_bfd);
      value += addend;

      bfd_put_64 (input_bfd, value + addend, hit_data);
      return bfd_reloc_ok;

    case R_PARISC_PCREL32:
      {
	/* If this is a call to a function defined in another dynamic
	   library, then redirect the call to the local stub for this
	   function.  */
	if (sym_sec->output_section == NULL)
	  value = dyn_h->stub_offset;
  
	/* Turn VALUE into a proper PC relative address.  */
	value -= (offset + input_section->output_offset
		  + input_section->output_section->vma);

	value += addend;
	value -= 8;
	bfd_put_64 (input_bfd, value, hit_data);
	return bfd_reloc_ok;
      }

    case R_PARISC_PCREL64:
      {
	/* If this is a call to a function defined in another dynamic
	   library, then redirect the call to the local stub for this
	   function.  */
	if (sym_sec->output_section == NULL)
	  value = dyn_h->stub_offset;
  
	/* Turn VALUE into a proper PC relative address.  */
	value -= (offset + input_section->output_offset
		  + input_section->output_section->vma);

	value += addend;
	value -= 8;
	bfd_put_64 (input_bfd, value, hit_data);
	return bfd_reloc_ok;
      }


    /* These do not require any work here.  They are simply passed
       through as dynamic relocations.  */
    case R_PARISC_FPTR64:
      return bfd_reloc_ok;

    /* Something we don't know how to handle.  */
    default:
      /* ?!? This is temporary as we flesh out basic linker support, once
	 the basic support is functional we will return the not_supported
	 error conditional appropriately.  */
#if 0
      return bfd_reloc_not_supported;
#else
      return bfd_reloc_ok;
#endif
    }

  /* Update the instruction word.  */
  bfd_put_32 (input_bfd, insn, hit_data);
  return (bfd_reloc_ok);
}

/* Relocate the given INSN.  VALUE should be the actual value we want
   to insert into the instruction, ie by this point we should not be
   concerned with computing an offset relative to the DLT, PC, etc.
   Instead this routine is meant to handle the bit manipulations needed
   to insert the relocation into the given instruction.  */

static unsigned long
elf_hppa_relocate_insn (insn, sym_value, r_type)
     unsigned long insn;
     long sym_value;
     unsigned long r_type;
{
  long constant_value;

  switch (r_type)
    {
    /* This is any 22bit branch.  In PA2.0 syntax it corresponds to
       the "B" instruction.  */
    case R_PARISC_PCREL22F:
    case R_PARISC_PCREL22C:
      {
	unsigned int w3, w2, w1, w;

	/* These are 22 bit branches.  Mask off bits we do not care
	   about.  */
	sym_value &= 0x3fffff;

	/* Now extract the W1, W2, W3 and W fields from the value.  */
	dis_assemble_22 (sym_value, &w3, &w1, &w2, &w);

	/* Mask out bits for the value in the instruction.  */
	insn &= 0xfc00e002;

	/* Insert the bits for the W1, W2 and W fields into the
	   instruction.  */
	insn |= (w3 << 21) | (w2 << 2) | (w1 << 16) | w;
	return insn;
       }

    /* This is any 17bit branch.  In PA2.0 syntax it also corresponds to
       the "B" instruction as well as BE.  */
    case R_PARISC_PCREL17F:
    case R_PARISC_DIR17F:
    case R_PARISC_PCREL17C:
    case R_PARISC_PCREL17R:
      {
	unsigned int w2, w1, w;

	/* These are 17 bit branches.  Mask off bits we do not care
	   about.  */
	sym_value &= 0x1ffff;

	/* Now extract the W1, W2 and W fields from the value.  */
	dis_assemble_17 (sym_value, &w1, &w2, &w);

	/* Mask out bits for the value in the instruction.  */
	insn &= 0xffe0e002;

	/* Insert the bits for the W1, W2 and W fields into the
	   instruction.  */
	insn |= (w2 << 2) | (w1 << 16) | w;
	return insn;
      }

    /* ADDIL or LDIL instructions.  */
    case R_PARISC_DLTREL21L:
    case R_PARISC_DLTIND21L:
    case R_PARISC_LTOFF_FPTR21L:
    case R_PARISC_PCREL21L:
    case R_PARISC_LTOFF_TP21L:
    case R_PARISC_DPREL21L:
      {
        int w;

	/* Mask off bits in INSN we do not want.  */
	insn &= 0xffe00000;

	/* Turn the 21bit value into the proper format.  */
	dis_assemble_21 (sym_value, &w);

	/* And insert the proper bits into INSN.  */
        return insn | w;
      }

    /* LDO and integer loads/stores with 14bit displacements.  */
    case R_PARISC_DLTREL14R:
    case R_PARISC_DLTREL14F:
    case R_PARISC_DLTIND14R:
    case R_PARISC_DLTIND14F:
    case R_PARISC_LTOFF_FPTR14R:
    case R_PARISC_LTOFF_FPTR16F:
    case R_PARISC_PCREL14R:
    case R_PARISC_PCREL14F:
    case R_PARISC_PCREL16F:
    case R_PARISC_LTOFF_TP14R:
    case R_PARISC_LTOFF_TP14F:
    case R_PARISC_LTOFF_TP16F:
    case R_PARISC_DPREL14R:
    case R_PARISC_DPREL14F:
    case R_PARISC_GPREL16F:
      {
        int w;

	/* Mask off bits in INSN we do not want.  */
	insn &= 0xffffc000;

	/* Turn the 14bit value into the proper format.  */
	low_sign_unext (sym_value, 14, &w);

	/* And insert the proper bits into INSN.  */
        return insn | w;
      }

    /* Doubleword loads and stores with a 14bit displacement.  */
    case R_PARISC_DLTREL14DR:
    case R_PARISC_DLTIND14DR:
    case R_PARISC_LTOFF_FPTR14DR:
    case R_PARISC_LTOFF_FPTR16DF:
    case R_PARISC_PCREL14DR:
    case R_PARISC_PCREL16DF:
    case R_PARISC_LTOFF_TP14DR:
    case R_PARISC_LTOFF_TP16DF:
    case R_PARISC_DPREL14DR:
    case R_PARISC_GPREL16DF:
      {
        int w;

	/* Mask off bits in INSN we do not want.  */
	insn &= 0xffffc00e;

	/* The sign bit at 14 moves into bit zero in the destination.  */
        insn |= ((sym_value & 0x2000) >> 13);

	/* Turn off the bits in sym_value we do not care about.  */
	sym_value &= 0x1ff8;

	/* Now shift it one bit position left so that it lines up with the
	   destination field in INSN.  */
	sym_value <<= 1;

	return insn | sym_value;
      }

    /* Floating point single word load/store instructions.  */
    case R_PARISC_DLTREL14WR:
    case R_PARISC_DLTIND14WR:
    case R_PARISC_LTOFF_FPTR14WR:
    case R_PARISC_LTOFF_FPTR16WF:
    case R_PARISC_PCREL14WR:
    case R_PARISC_PCREL16WF:
    case R_PARISC_LTOFF_TP14WR:
    case R_PARISC_LTOFF_TP16WF:
    case R_PARISC_DPREL14WR:
    case R_PARISC_GPREL16WF:
      {
        int w;

	/* Mask off bits in INSN we do not want.  */
	insn &= 0xffffc006;

	/* The sign bit at 14 moves into bit zero in the destination.  */
        insn |= ((sym_value & 0x2000) >> 13);

	/* Turn off the bits in sym_value we do not care about.  */
	sym_value &= 0x1ffc;

	/* Now shift it one bit position left so that it lines up with the
	   destination field in INSN.  */
	sym_value <<= 1;

	return insn | sym_value;
      }


    default:
      return insn;
    }
}
