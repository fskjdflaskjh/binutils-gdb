/* Target-dependent code for the HP PA architecture, for GDB.

   Copyright 1986, 1987, 1989, 1990, 1991, 1992, 1993, 1994, 1995,
   1996, 1998, 1999, 2000, 2001, 2002, 2003, 2004 Free Software
   Foundation, Inc.

   Contributed by the Center for Software Science at the
   University of Utah (pa-gdb-bugs@cs.utah.edu).

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
#include "bfd.h"
#include "inferior.h"
#include "regcache.h"
#include "completer.h"
#include "osabi.h"
#include "gdb_assert.h"
#include "arch-utils.h"
/* For argument passing to the inferior */
#include "symtab.h"
#include "dis-asm.h"
#include "trad-frame.h"
#include "frame-unwind.h"
#include "frame-base.h"

#include "gdbcore.h"
#include "gdbcmd.h"
#include "objfiles.h"
#include "hppa-tdep.h"

static int hppa_debug = 0;

/* Some local constants.  */
static const int hppa32_num_regs = 128;
static const int hppa64_num_regs = 96;

/* hppa-specific object data -- unwind and solib info.
   TODO/maybe: think about splitting this into two parts; the unwind data is 
   common to all hppa targets, but is only used in this file; we can register 
   that separately and make this static. The solib data is probably hpux-
   specific, so we can create a separate extern objfile_data that is registered
   by hppa-hpux-tdep.c and shared with pa64solib.c and somsolib.c.  */
const struct objfile_data *hppa_objfile_priv_data = NULL;

/* Get at various relevent fields of an instruction word. */
#define MASK_5 0x1f
#define MASK_11 0x7ff
#define MASK_14 0x3fff
#define MASK_21 0x1fffff

/* Define offsets into the call dummy for the _sr4export address.
   See comments related to CALL_DUMMY for more info.  */
#define SR4EXPORT_LDIL_OFFSET (HPPA_INSTRUCTION_SIZE * 12)
#define SR4EXPORT_LDO_OFFSET (HPPA_INSTRUCTION_SIZE * 13)

/* Sizes (in bytes) of the native unwind entries.  */
#define UNWIND_ENTRY_SIZE 16
#define STUB_UNWIND_ENTRY_SIZE 8

/* FIXME: brobecker 2002-11-07: We will likely be able to make the
   following functions static, once we hppa is partially multiarched.  */
int hppa_pc_requires_run_before_use (CORE_ADDR pc);
int hppa_instruction_nullified (void);

/* Handle 32/64-bit struct return conventions.  */

static enum return_value_convention
hppa32_return_value (struct gdbarch *gdbarch,
		     struct type *type, struct regcache *regcache,
		     void *readbuf, const void *writebuf)
{
  if (TYPE_LENGTH (type) <= 2 * 4)
    {
      /* The value always lives in the right hand end of the register
	 (or register pair)?  */
      int b;
      int reg = TYPE_CODE (type) == TYPE_CODE_FLT ? HPPA_FP4_REGNUM : 28;
      int part = TYPE_LENGTH (type) % 4;
      /* The left hand register contains only part of the value,
	 transfer that first so that the rest can be xfered as entire
	 4-byte registers.  */
      if (part > 0)
	{
	  if (readbuf != NULL)
	    regcache_cooked_read_part (regcache, reg, 4 - part,
				       part, readbuf);
	  if (writebuf != NULL)
	    regcache_cooked_write_part (regcache, reg, 4 - part,
					part, writebuf);
	  reg++;
	}
      /* Now transfer the remaining register values.  */
      for (b = part; b < TYPE_LENGTH (type); b += 4)
	{
	  if (readbuf != NULL)
	    regcache_cooked_read (regcache, reg, (char *) readbuf + b);
	  if (writebuf != NULL)
	    regcache_cooked_write (regcache, reg, (const char *) writebuf + b);
	  reg++;
	}
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  else
    return RETURN_VALUE_STRUCT_CONVENTION;
}

static enum return_value_convention
hppa64_return_value (struct gdbarch *gdbarch,
		     struct type *type, struct regcache *regcache,
		     void *readbuf, const void *writebuf)
{
  /* RM: Floats are returned in FR4R, doubles in FR4.  Integral values
     are in r28, padded on the left.  Aggregates less that 65 bits are
     in r28, right padded.  Aggregates upto 128 bits are in r28 and
     r29, right padded.  */ 
  if (TYPE_CODE (type) == TYPE_CODE_FLT
      && TYPE_LENGTH (type) <= 8)
    {
      /* Floats are right aligned?  */
      int offset = register_size (gdbarch, HPPA_FP4_REGNUM) - TYPE_LENGTH (type);
      if (readbuf != NULL)
	regcache_cooked_read_part (regcache, HPPA_FP4_REGNUM, offset,
				   TYPE_LENGTH (type), readbuf);
      if (writebuf != NULL)
	regcache_cooked_write_part (regcache, HPPA_FP4_REGNUM, offset,
				    TYPE_LENGTH (type), writebuf);
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  else if (TYPE_LENGTH (type) <= 8 && is_integral_type (type))
    {
      /* Integrals are right aligned.  */
      int offset = register_size (gdbarch, HPPA_FP4_REGNUM) - TYPE_LENGTH (type);
      if (readbuf != NULL)
	regcache_cooked_read_part (regcache, 28, offset,
				   TYPE_LENGTH (type), readbuf);
      if (writebuf != NULL)
	regcache_cooked_write_part (regcache, 28, offset,
				    TYPE_LENGTH (type), writebuf);
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  else if (TYPE_LENGTH (type) <= 2 * 8)
    {
      /* Composite values are left aligned.  */
      int b;
      for (b = 0; b < TYPE_LENGTH (type); b += 8)
	{
	  int part = min (8, TYPE_LENGTH (type) - b);
	  if (readbuf != NULL)
	    regcache_cooked_read_part (regcache, 28 + b / 8, 0, part,
				       (char *) readbuf + b);
	  if (writebuf != NULL)
	    regcache_cooked_write_part (regcache, 28 + b / 8, 0, part,
					(const char *) writebuf + b);
	}
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
  else
    return RETURN_VALUE_STRUCT_CONVENTION;
}

/* Routines to extract various sized constants out of hppa 
   instructions. */

/* This assumes that no garbage lies outside of the lower bits of 
   value. */

int
hppa_sign_extend (unsigned val, unsigned bits)
{
  return (int) (val >> (bits - 1) ? (-1 << bits) | val : val);
}

/* For many immediate values the sign bit is the low bit! */

int
hppa_low_hppa_sign_extend (unsigned val, unsigned bits)
{
  return (int) ((val & 0x1 ? (-1 << (bits - 1)) : 0) | val >> 1);
}

/* Extract the bits at positions between FROM and TO, using HP's numbering
   (MSB = 0). */

int
hppa_get_field (unsigned word, int from, int to)
{
  return ((word) >> (31 - (to)) & ((1 << ((to) - (from) + 1)) - 1));
}

/* extract the immediate field from a ld{bhw}s instruction */

int
hppa_extract_5_load (unsigned word)
{
  return hppa_low_hppa_sign_extend (word >> 16 & MASK_5, 5);
}

/* extract the immediate field from a break instruction */

unsigned
hppa_extract_5r_store (unsigned word)
{
  return (word & MASK_5);
}

/* extract the immediate field from a {sr}sm instruction */

unsigned
hppa_extract_5R_store (unsigned word)
{
  return (word >> 16 & MASK_5);
}

/* extract a 14 bit immediate field */

int
hppa_extract_14 (unsigned word)
{
  return hppa_low_hppa_sign_extend (word & MASK_14, 14);
}

/* extract a 21 bit constant */

int
hppa_extract_21 (unsigned word)
{
  int val;

  word &= MASK_21;
  word <<= 11;
  val = hppa_get_field (word, 20, 20);
  val <<= 11;
  val |= hppa_get_field (word, 9, 19);
  val <<= 2;
  val |= hppa_get_field (word, 5, 6);
  val <<= 5;
  val |= hppa_get_field (word, 0, 4);
  val <<= 2;
  val |= hppa_get_field (word, 7, 8);
  return hppa_sign_extend (val, 21) << 11;
}

/* extract a 17 bit constant from branch instructions, returning the
   19 bit signed value. */

int
hppa_extract_17 (unsigned word)
{
  return hppa_sign_extend (hppa_get_field (word, 19, 28) |
		      hppa_get_field (word, 29, 29) << 10 |
		      hppa_get_field (word, 11, 15) << 11 |
		      (word & 0x1) << 16, 17) << 2;
}


/* Compare the start address for two unwind entries returning 1 if 
   the first address is larger than the second, -1 if the second is
   larger than the first, and zero if they are equal.  */

static int
compare_unwind_entries (const void *arg1, const void *arg2)
{
  const struct unwind_table_entry *a = arg1;
  const struct unwind_table_entry *b = arg2;

  if (a->region_start > b->region_start)
    return 1;
  else if (a->region_start < b->region_start)
    return -1;
  else
    return 0;
}

static void
record_text_segment_lowaddr (bfd *abfd, asection *section, void *data)
{
  if ((section->flags & (SEC_ALLOC | SEC_LOAD | SEC_READONLY))
       == (SEC_ALLOC | SEC_LOAD | SEC_READONLY))
    {
      bfd_vma value = section->vma - section->filepos;
      CORE_ADDR *low_text_segment_address = (CORE_ADDR *)data;

      if (value < *low_text_segment_address)
          *low_text_segment_address = value;
    }
}

static void
internalize_unwinds (struct objfile *objfile, struct unwind_table_entry *table,
		     asection *section, unsigned int entries, unsigned int size,
		     CORE_ADDR text_offset)
{
  /* We will read the unwind entries into temporary memory, then
     fill in the actual unwind table.  */

  if (size > 0)
    {
      unsigned long tmp;
      unsigned i;
      char *buf = alloca (size);
      CORE_ADDR low_text_segment_address;

      /* For ELF targets, then unwinds are supposed to
	 be segment relative offsets instead of absolute addresses. 

	 Note that when loading a shared library (text_offset != 0) the
	 unwinds are already relative to the text_offset that will be
	 passed in.  */
      if (gdbarch_tdep (current_gdbarch)->is_elf && text_offset == 0)
	{
          low_text_segment_address = -1;

	  bfd_map_over_sections (objfile->obfd,
				 record_text_segment_lowaddr, 
				 &low_text_segment_address);

	  text_offset = low_text_segment_address;
	}

      bfd_get_section_contents (objfile->obfd, section, buf, 0, size);

      /* Now internalize the information being careful to handle host/target
         endian issues.  */
      for (i = 0; i < entries; i++)
	{
	  table[i].region_start = bfd_get_32 (objfile->obfd,
					      (bfd_byte *) buf);
	  table[i].region_start += text_offset;
	  buf += 4;
	  table[i].region_end = bfd_get_32 (objfile->obfd, (bfd_byte *) buf);
	  table[i].region_end += text_offset;
	  buf += 4;
	  tmp = bfd_get_32 (objfile->obfd, (bfd_byte *) buf);
	  buf += 4;
	  table[i].Cannot_unwind = (tmp >> 31) & 0x1;
	  table[i].Millicode = (tmp >> 30) & 0x1;
	  table[i].Millicode_save_sr0 = (tmp >> 29) & 0x1;
	  table[i].Region_description = (tmp >> 27) & 0x3;
	  table[i].reserved1 = (tmp >> 26) & 0x1;
	  table[i].Entry_SR = (tmp >> 25) & 0x1;
	  table[i].Entry_FR = (tmp >> 21) & 0xf;
	  table[i].Entry_GR = (tmp >> 16) & 0x1f;
	  table[i].Args_stored = (tmp >> 15) & 0x1;
	  table[i].Variable_Frame = (tmp >> 14) & 0x1;
	  table[i].Separate_Package_Body = (tmp >> 13) & 0x1;
	  table[i].Frame_Extension_Millicode = (tmp >> 12) & 0x1;
	  table[i].Stack_Overflow_Check = (tmp >> 11) & 0x1;
	  table[i].Two_Instruction_SP_Increment = (tmp >> 10) & 0x1;
	  table[i].Ada_Region = (tmp >> 9) & 0x1;
	  table[i].cxx_info = (tmp >> 8) & 0x1;
	  table[i].cxx_try_catch = (tmp >> 7) & 0x1;
	  table[i].sched_entry_seq = (tmp >> 6) & 0x1;
	  table[i].reserved2 = (tmp >> 5) & 0x1;
	  table[i].Save_SP = (tmp >> 4) & 0x1;
	  table[i].Save_RP = (tmp >> 3) & 0x1;
	  table[i].Save_MRP_in_frame = (tmp >> 2) & 0x1;
	  table[i].extn_ptr_defined = (tmp >> 1) & 0x1;
	  table[i].Cleanup_defined = tmp & 0x1;
	  tmp = bfd_get_32 (objfile->obfd, (bfd_byte *) buf);
	  buf += 4;
	  table[i].MPE_XL_interrupt_marker = (tmp >> 31) & 0x1;
	  table[i].HP_UX_interrupt_marker = (tmp >> 30) & 0x1;
	  table[i].Large_frame = (tmp >> 29) & 0x1;
	  table[i].Pseudo_SP_Set = (tmp >> 28) & 0x1;
	  table[i].reserved4 = (tmp >> 27) & 0x1;
	  table[i].Total_frame_size = tmp & 0x7ffffff;

	  /* Stub unwinds are handled elsewhere. */
	  table[i].stub_unwind.stub_type = 0;
	  table[i].stub_unwind.padding = 0;
	}
    }
}

/* Read in the backtrace information stored in the `$UNWIND_START$' section of
   the object file.  This info is used mainly by find_unwind_entry() to find
   out the stack frame size and frame pointer used by procedures.  We put
   everything on the psymbol obstack in the objfile so that it automatically
   gets freed when the objfile is destroyed.  */

static void
read_unwind_info (struct objfile *objfile)
{
  asection *unwind_sec, *stub_unwind_sec;
  unsigned unwind_size, stub_unwind_size, total_size;
  unsigned index, unwind_entries;
  unsigned stub_entries, total_entries;
  CORE_ADDR text_offset;
  struct hppa_unwind_info *ui;
  struct hppa_objfile_private *obj_private;

  text_offset = ANOFFSET (objfile->section_offsets, 0);
  ui = (struct hppa_unwind_info *) obstack_alloc (&objfile->objfile_obstack,
					   sizeof (struct hppa_unwind_info));

  ui->table = NULL;
  ui->cache = NULL;
  ui->last = -1;

  /* For reasons unknown the HP PA64 tools generate multiple unwinder
     sections in a single executable.  So we just iterate over every
     section in the BFD looking for unwinder sections intead of trying
     to do a lookup with bfd_get_section_by_name. 

     First determine the total size of the unwind tables so that we
     can allocate memory in a nice big hunk.  */
  total_entries = 0;
  for (unwind_sec = objfile->obfd->sections;
       unwind_sec;
       unwind_sec = unwind_sec->next)
    {
      if (strcmp (unwind_sec->name, "$UNWIND_START$") == 0
	  || strcmp (unwind_sec->name, ".PARISC.unwind") == 0)
	{
	  unwind_size = bfd_section_size (objfile->obfd, unwind_sec);
	  unwind_entries = unwind_size / UNWIND_ENTRY_SIZE;

	  total_entries += unwind_entries;
	}
    }

  /* Now compute the size of the stub unwinds.  Note the ELF tools do not
     use stub unwinds at the curren time.  */
  stub_unwind_sec = bfd_get_section_by_name (objfile->obfd, "$UNWIND_END$");

  if (stub_unwind_sec)
    {
      stub_unwind_size = bfd_section_size (objfile->obfd, stub_unwind_sec);
      stub_entries = stub_unwind_size / STUB_UNWIND_ENTRY_SIZE;
    }
  else
    {
      stub_unwind_size = 0;
      stub_entries = 0;
    }

  /* Compute total number of unwind entries and their total size.  */
  total_entries += stub_entries;
  total_size = total_entries * sizeof (struct unwind_table_entry);

  /* Allocate memory for the unwind table.  */
  ui->table = (struct unwind_table_entry *)
    obstack_alloc (&objfile->objfile_obstack, total_size);
  ui->last = total_entries - 1;

  /* Now read in each unwind section and internalize the standard unwind
     entries.  */
  index = 0;
  for (unwind_sec = objfile->obfd->sections;
       unwind_sec;
       unwind_sec = unwind_sec->next)
    {
      if (strcmp (unwind_sec->name, "$UNWIND_START$") == 0
	  || strcmp (unwind_sec->name, ".PARISC.unwind") == 0)
	{
	  unwind_size = bfd_section_size (objfile->obfd, unwind_sec);
	  unwind_entries = unwind_size / UNWIND_ENTRY_SIZE;

	  internalize_unwinds (objfile, &ui->table[index], unwind_sec,
			       unwind_entries, unwind_size, text_offset);
	  index += unwind_entries;
	}
    }

  /* Now read in and internalize the stub unwind entries.  */
  if (stub_unwind_size > 0)
    {
      unsigned int i;
      char *buf = alloca (stub_unwind_size);

      /* Read in the stub unwind entries.  */
      bfd_get_section_contents (objfile->obfd, stub_unwind_sec, buf,
				0, stub_unwind_size);

      /* Now convert them into regular unwind entries.  */
      for (i = 0; i < stub_entries; i++, index++)
	{
	  /* Clear out the next unwind entry.  */
	  memset (&ui->table[index], 0, sizeof (struct unwind_table_entry));

	  /* Convert offset & size into region_start and region_end.  
	     Stuff away the stub type into "reserved" fields.  */
	  ui->table[index].region_start = bfd_get_32 (objfile->obfd,
						      (bfd_byte *) buf);
	  ui->table[index].region_start += text_offset;
	  buf += 4;
	  ui->table[index].stub_unwind.stub_type = bfd_get_8 (objfile->obfd,
							  (bfd_byte *) buf);
	  buf += 2;
	  ui->table[index].region_end
	    = ui->table[index].region_start + 4 *
	    (bfd_get_16 (objfile->obfd, (bfd_byte *) buf) - 1);
	  buf += 2;
	}

    }

  /* Unwind table needs to be kept sorted.  */
  qsort (ui->table, total_entries, sizeof (struct unwind_table_entry),
	 compare_unwind_entries);

  /* Keep a pointer to the unwind information.  */
  obj_private = (struct hppa_objfile_private *) 
	        objfile_data (objfile, hppa_objfile_priv_data);
  if (obj_private == NULL)
    {
      obj_private = (struct hppa_objfile_private *)
	obstack_alloc (&objfile->objfile_obstack, 
                       sizeof (struct hppa_objfile_private));
      set_objfile_data (objfile, hppa_objfile_priv_data, obj_private);
      obj_private->unwind_info = NULL;
      obj_private->so_info = NULL;
      obj_private->dp = 0;
    }
  obj_private->unwind_info = ui;
}

/* Lookup the unwind (stack backtrace) info for the given PC.  We search all
   of the objfiles seeking the unwind table entry for this PC.  Each objfile
   contains a sorted list of struct unwind_table_entry.  Since we do a binary
   search of the unwind tables, we depend upon them to be sorted.  */

struct unwind_table_entry *
find_unwind_entry (CORE_ADDR pc)
{
  int first, middle, last;
  struct objfile *objfile;
  struct hppa_objfile_private *priv;

  if (hppa_debug)
    fprintf_unfiltered (gdb_stdlog, "{ find_unwind_entry 0x%s -> ",
		        paddr_nz (pc));

  /* A function at address 0?  Not in HP-UX! */
  if (pc == (CORE_ADDR) 0)
    {
      if (hppa_debug)
	fprintf_unfiltered (gdb_stdlog, "NULL }\n");
      return NULL;
    }

  ALL_OBJFILES (objfile)
  {
    struct hppa_unwind_info *ui;
    ui = NULL;
    priv = objfile_data (objfile, hppa_objfile_priv_data);
    if (priv)
      ui = ((struct hppa_objfile_private *) priv)->unwind_info;

    if (!ui)
      {
	read_unwind_info (objfile);
        priv = objfile_data (objfile, hppa_objfile_priv_data);
	if (priv == NULL)
	  error ("Internal error reading unwind information.");
        ui = ((struct hppa_objfile_private *) priv)->unwind_info;
      }

    /* First, check the cache */

    if (ui->cache
	&& pc >= ui->cache->region_start
	&& pc <= ui->cache->region_end)
      {
	if (hppa_debug)
	  fprintf_unfiltered (gdb_stdlog, "0x%s (cached) }\n",
            paddr_nz ((CORE_ADDR) ui->cache));
        return ui->cache;
      }

    /* Not in the cache, do a binary search */

    first = 0;
    last = ui->last;

    while (first <= last)
      {
	middle = (first + last) / 2;
	if (pc >= ui->table[middle].region_start
	    && pc <= ui->table[middle].region_end)
	  {
	    ui->cache = &ui->table[middle];
	    if (hppa_debug)
	      fprintf_unfiltered (gdb_stdlog, "0x%s }\n",
                paddr_nz ((CORE_ADDR) ui->cache));
	    return &ui->table[middle];
	  }

	if (pc < ui->table[middle].region_start)
	  last = middle - 1;
	else
	  first = middle + 1;
      }
  }				/* ALL_OBJFILES() */

  if (hppa_debug)
    fprintf_unfiltered (gdb_stdlog, "NULL (not found) }\n");

  return NULL;
}

static const unsigned char *
hppa_breakpoint_from_pc (CORE_ADDR *pc, int *len)
{
  static const unsigned char breakpoint[] = {0x00, 0x01, 0x00, 0x04};
  (*len) = sizeof (breakpoint);
  return breakpoint;
}

/* Return the name of a register.  */

const char *
hppa32_register_name (int i)
{
  static char *names[] = {
    "flags",  "r1",      "rp",     "r3",
    "r4",     "r5",      "r6",     "r7",
    "r8",     "r9",      "r10",    "r11",
    "r12",    "r13",     "r14",    "r15",
    "r16",    "r17",     "r18",    "r19",
    "r20",    "r21",     "r22",    "r23",
    "r24",    "r25",     "r26",    "dp",
    "ret0",   "ret1",    "sp",     "r31",
    "sar",    "pcoqh",   "pcsqh",  "pcoqt",
    "pcsqt",  "eiem",    "iir",    "isr",
    "ior",    "ipsw",    "goto",   "sr4",
    "sr0",    "sr1",     "sr2",    "sr3",
    "sr5",    "sr6",     "sr7",    "cr0",
    "cr8",    "cr9",     "ccr",    "cr12",
    "cr13",   "cr24",    "cr25",   "cr26",
    "mpsfu_high","mpsfu_low","mpsfu_ovflo","pad",
    "fpsr",    "fpe1",   "fpe2",   "fpe3",
    "fpe4",   "fpe5",    "fpe6",   "fpe7",
    "fr4",     "fr4R",   "fr5",    "fr5R",
    "fr6",    "fr6R",    "fr7",    "fr7R",
    "fr8",     "fr8R",   "fr9",    "fr9R",
    "fr10",   "fr10R",   "fr11",   "fr11R",
    "fr12",    "fr12R",  "fr13",   "fr13R",
    "fr14",   "fr14R",   "fr15",   "fr15R",
    "fr16",    "fr16R",  "fr17",   "fr17R",
    "fr18",   "fr18R",   "fr19",   "fr19R",
    "fr20",    "fr20R",  "fr21",   "fr21R",
    "fr22",   "fr22R",   "fr23",   "fr23R",
    "fr24",    "fr24R",  "fr25",   "fr25R",
    "fr26",   "fr26R",   "fr27",   "fr27R",
    "fr28",    "fr28R",  "fr29",   "fr29R",
    "fr30",   "fr30R",   "fr31",   "fr31R"
  };
  if (i < 0 || i >= (sizeof (names) / sizeof (*names)))
    return NULL;
  else
    return names[i];
}

const char *
hppa64_register_name (int i)
{
  static char *names[] = {
    "flags",  "r1",      "rp",     "r3",
    "r4",     "r5",      "r6",     "r7",
    "r8",     "r9",      "r10",    "r11",
    "r12",    "r13",     "r14",    "r15",
    "r16",    "r17",     "r18",    "r19",
    "r20",    "r21",     "r22",    "r23",
    "r24",    "r25",     "r26",    "dp",
    "ret0",   "ret1",    "sp",     "r31",
    "sar",    "pcoqh",   "pcsqh",  "pcoqt",
    "pcsqt",  "eiem",    "iir",    "isr",
    "ior",    "ipsw",    "goto",   "sr4",
    "sr0",    "sr1",     "sr2",    "sr3",
    "sr5",    "sr6",     "sr7",    "cr0",
    "cr8",    "cr9",     "ccr",    "cr12",
    "cr13",   "cr24",    "cr25",   "cr26",
    "mpsfu_high","mpsfu_low","mpsfu_ovflo","pad",
    "fpsr",    "fpe1",   "fpe2",   "fpe3",
    "fr4",    "fr5",     "fr6",    "fr7",
    "fr8",     "fr9",    "fr10",   "fr11",
    "fr12",   "fr13",    "fr14",   "fr15",
    "fr16",    "fr17",   "fr18",   "fr19",
    "fr20",   "fr21",    "fr22",   "fr23",
    "fr24",    "fr25",   "fr26",   "fr27",
    "fr28",  "fr29",    "fr30",   "fr31"
  };
  if (i < 0 || i >= (sizeof (names) / sizeof (*names)))
    return NULL;
  else
    return names[i];
}

/* This function pushes a stack frame with arguments as part of the
   inferior function calling mechanism.

   This is the version of the function for the 32-bit PA machines, in
   which later arguments appear at lower addresses.  (The stack always
   grows towards higher addresses.)

   We simply allocate the appropriate amount of stack space and put
   arguments into their proper slots.  */
   
CORE_ADDR
hppa32_push_dummy_call (struct gdbarch *gdbarch, CORE_ADDR func_addr,
			struct regcache *regcache, CORE_ADDR bp_addr,
			int nargs, struct value **args, CORE_ADDR sp,
			int struct_return, CORE_ADDR struct_addr)
{
  /* Stack base address at which any pass-by-reference parameters are
     stored.  */
  CORE_ADDR struct_end = 0;
  /* Stack base address at which the first parameter is stored.  */
  CORE_ADDR param_end = 0;

  /* The inner most end of the stack after all the parameters have
     been pushed.  */
  CORE_ADDR new_sp = 0;

  /* Two passes.  First pass computes the location of everything,
     second pass writes the bytes out.  */
  int write_pass;
  for (write_pass = 0; write_pass < 2; write_pass++)
    {
      CORE_ADDR struct_ptr = 0;
      /* The first parameter goes into sp-36, each stack slot is 4-bytes.  
         struct_ptr is adjusted for each argument below, so the first
	 argument will end up at sp-36.  */
      CORE_ADDR param_ptr = 32;
      int i;
      int small_struct = 0;

      for (i = 0; i < nargs; i++)
	{
	  struct value *arg = args[i];
	  struct type *type = check_typedef (VALUE_TYPE (arg));
	  /* The corresponding parameter that is pushed onto the
	     stack, and [possibly] passed in a register.  */
	  char param_val[8];
	  int param_len;
	  memset (param_val, 0, sizeof param_val);
	  if (TYPE_LENGTH (type) > 8)
	    {
	      /* Large parameter, pass by reference.  Store the value
		 in "struct" area and then pass its address.  */
	      param_len = 4;
	      struct_ptr += align_up (TYPE_LENGTH (type), 8);
	      if (write_pass)
		write_memory (struct_end - struct_ptr, VALUE_CONTENTS (arg),
			      TYPE_LENGTH (type));
	      store_unsigned_integer (param_val, 4, struct_end - struct_ptr);
	    }
	  else if (TYPE_CODE (type) == TYPE_CODE_INT
		   || TYPE_CODE (type) == TYPE_CODE_ENUM)
	    {
	      /* Integer value store, right aligned.  "unpack_long"
		 takes care of any sign-extension problems.  */
	      param_len = align_up (TYPE_LENGTH (type), 4);
	      store_unsigned_integer (param_val, param_len,
				      unpack_long (type,
						   VALUE_CONTENTS (arg)));
	    }
	  else if (TYPE_CODE (type) == TYPE_CODE_FLT)
            {
	      /* Floating point value store, right aligned.  */
	      param_len = align_up (TYPE_LENGTH (type), 4);
	      memcpy (param_val, VALUE_CONTENTS (arg), param_len);
            }
	  else
	    {
	      param_len = align_up (TYPE_LENGTH (type), 4);

	      /* Small struct value are stored right-aligned.  */
	      memcpy (param_val + param_len - TYPE_LENGTH (type),
		      VALUE_CONTENTS (arg), TYPE_LENGTH (type));

	      /* Structures of size 5, 6 and 7 bytes are special in that
	         the higher-ordered word is stored in the lower-ordered
		 argument, and even though it is a 8-byte quantity the
		 registers need not be 8-byte aligned.  */
	      if (param_len > 4)
		small_struct = 1;
	    }

	  param_ptr += param_len;
	  if (param_len == 8 && !small_struct)
            param_ptr = align_up (param_ptr, 8);

	  /* First 4 non-FP arguments are passed in gr26-gr23.
	     First 4 32-bit FP arguments are passed in fr4L-fr7L.
	     First 2 64-bit FP arguments are passed in fr5 and fr7.

	     The rest go on the stack, starting at sp-36, towards lower
	     addresses.  8-byte arguments must be aligned to a 8-byte
	     stack boundary.  */
	  if (write_pass)
	    {
	      write_memory (param_end - param_ptr, param_val, param_len);

	      /* There are some cases when we don't know the type
		 expected by the callee (e.g. for variadic functions), so 
		 pass the parameters in both general and fp regs.  */
	      if (param_ptr <= 48)
		{
		  int grreg = 26 - (param_ptr - 36) / 4;
		  int fpLreg = 72 + (param_ptr - 36) / 4 * 2;
		  int fpreg = 74 + (param_ptr - 32) / 8 * 4;

		  regcache_cooked_write (regcache, grreg, param_val);
		  regcache_cooked_write (regcache, fpLreg, param_val);

		  if (param_len > 4)
		    {
		      regcache_cooked_write (regcache, grreg + 1, 
					     param_val + 4);

		      regcache_cooked_write (regcache, fpreg, param_val);
		      regcache_cooked_write (regcache, fpreg + 1, 
					     param_val + 4);
		    }
		}
	    }
	}

      /* Update the various stack pointers.  */
      if (!write_pass)
	{
	  struct_end = sp + align_up (struct_ptr, 64);
	  /* PARAM_PTR already accounts for all the arguments passed
	     by the user.  However, the ABI mandates minimum stack
	     space allocations for outgoing arguments.  The ABI also
	     mandates minimum stack alignments which we must
	     preserve.  */
	  param_end = struct_end + align_up (param_ptr, 64);
	}
    }

  /* If a structure has to be returned, set up register 28 to hold its
     address */
  if (struct_return)
    write_register (28, struct_addr);

  /* Set the return address.  */
  regcache_cooked_write_unsigned (regcache, HPPA_RP_REGNUM, bp_addr);

  /* Update the Stack Pointer.  */
  regcache_cooked_write_unsigned (regcache, HPPA_SP_REGNUM, param_end);

  return param_end;
}

/* This function pushes a stack frame with arguments as part of the
   inferior function calling mechanism.

   This is the version for the PA64, in which later arguments appear
   at higher addresses.  (The stack always grows towards higher
   addresses.)

   We simply allocate the appropriate amount of stack space and put
   arguments into their proper slots.

   This ABI also requires that the caller provide an argument pointer
   to the callee, so we do that too.  */
   
CORE_ADDR
hppa64_push_dummy_call (struct gdbarch *gdbarch, CORE_ADDR func_addr,
			struct regcache *regcache, CORE_ADDR bp_addr,
			int nargs, struct value **args, CORE_ADDR sp,
			int struct_return, CORE_ADDR struct_addr)
{
  /* NOTE: cagney/2004-02-27: This is a guess - its implemented by
     reverse engineering testsuite failures.  */

  /* Stack base address at which any pass-by-reference parameters are
     stored.  */
  CORE_ADDR struct_end = 0;
  /* Stack base address at which the first parameter is stored.  */
  CORE_ADDR param_end = 0;

  /* The inner most end of the stack after all the parameters have
     been pushed.  */
  CORE_ADDR new_sp = 0;

  /* Two passes.  First pass computes the location of everything,
     second pass writes the bytes out.  */
  int write_pass;
  for (write_pass = 0; write_pass < 2; write_pass++)
    {
      CORE_ADDR struct_ptr = 0;
      CORE_ADDR param_ptr = 0;
      int i;
      for (i = 0; i < nargs; i++)
	{
	  struct value *arg = args[i];
	  struct type *type = check_typedef (VALUE_TYPE (arg));
	  if ((TYPE_CODE (type) == TYPE_CODE_INT
	       || TYPE_CODE (type) == TYPE_CODE_ENUM)
	      && TYPE_LENGTH (type) <= 8)
	    {
	      /* Integer value store, right aligned.  "unpack_long"
		 takes care of any sign-extension problems.  */
	      param_ptr += 8;
	      if (write_pass)
		{
		  ULONGEST val = unpack_long (type, VALUE_CONTENTS (arg));
		  int reg = 27 - param_ptr / 8;
		  write_memory_unsigned_integer (param_end - param_ptr,
						 val, 8);
		  if (reg >= 19)
		    regcache_cooked_write_unsigned (regcache, reg, val);
		}
	    }
	  else
	    {
	      /* Small struct value, store left aligned?  */
	      int reg;
	      if (TYPE_LENGTH (type) > 8)
		{
		  param_ptr = align_up (param_ptr, 16);
		  reg = 26 - param_ptr / 8;
		  param_ptr += align_up (TYPE_LENGTH (type), 16);
		}
	      else
		{
		  param_ptr = align_up (param_ptr, 8);
		  reg = 26 - param_ptr / 8;
		  param_ptr += align_up (TYPE_LENGTH (type), 8);
		}
	      if (write_pass)
		{
		  int byte;
		  write_memory (param_end - param_ptr, VALUE_CONTENTS (arg),
				TYPE_LENGTH (type));
		  for (byte = 0; byte < TYPE_LENGTH (type); byte += 8)
		    {
		      if (reg >= 19)
			{
			  int len = min (8, TYPE_LENGTH (type) - byte);
			  regcache_cooked_write_part (regcache, reg, 0, len,
						      VALUE_CONTENTS (arg) + byte);
			}
		      reg--;
		    }
		}
	    }
	}
      /* Update the various stack pointers.  */
      if (!write_pass)
	{
	  struct_end = sp + struct_ptr;
	  /* PARAM_PTR already accounts for all the arguments passed
	     by the user.  However, the ABI mandates minimum stack
	     space allocations for outgoing arguments.  The ABI also
	     mandates minimum stack alignments which we must
	     preserve.  */
	  param_end = struct_end + max (align_up (param_ptr, 16), 64);
	}
    }

  /* If a structure has to be returned, set up register 28 to hold its
     address */
  if (struct_return)
    write_register (28, struct_addr);

  /* Set the return address.  */
  regcache_cooked_write_unsigned (regcache, HPPA_RP_REGNUM, bp_addr);

  /* Update the Stack Pointer.  */
  regcache_cooked_write_unsigned (regcache, HPPA_SP_REGNUM, param_end + 64);

  /* The stack will have 32 bytes of additional space for a frame marker.  */
  return param_end + 64;
}

static CORE_ADDR
hppa32_frame_align (struct gdbarch *gdbarch, CORE_ADDR addr)
{
  /* HP frames are 64-byte (or cache line) aligned (yes that's _byte_
     and not _bit_)!  */
  return align_up (addr, 64);
}

/* Force all frames to 16-byte alignment.  Better safe than sorry.  */

static CORE_ADDR
hppa64_frame_align (struct gdbarch *gdbarch, CORE_ADDR addr)
{
  /* Just always 16-byte align.  */
  return align_up (addr, 16);
}


/* Get the PC from %r31 if currently in a syscall.  Also mask out privilege
   bits.  */

static CORE_ADDR
hppa_target_read_pc (ptid_t ptid)
{
  int flags = read_register_pid (HPPA_FLAGS_REGNUM, ptid);

  /* The following test does not belong here.  It is OS-specific, and belongs
     in native code.  */
  /* Test SS_INSYSCALL */
  if (flags & 2)
    return read_register_pid (31, ptid) & ~0x3;

  return read_register_pid (HPPA_PCOQ_HEAD_REGNUM, ptid) & ~0x3;
}

/* Write out the PC.  If currently in a syscall, then also write the new
   PC value into %r31.  */

static void
hppa_target_write_pc (CORE_ADDR v, ptid_t ptid)
{
  int flags = read_register_pid (HPPA_FLAGS_REGNUM, ptid);

  /* The following test does not belong here.  It is OS-specific, and belongs
     in native code.  */
  /* If in a syscall, then set %r31.  Also make sure to get the 
     privilege bits set correctly.  */
  /* Test SS_INSYSCALL */
  if (flags & 2)
    write_register_pid (31, v | 0x3, ptid);

  write_register_pid (HPPA_PCOQ_HEAD_REGNUM, v, ptid);
  write_register_pid (HPPA_PCOQ_TAIL_REGNUM, v + 4, ptid);
}

/* return the alignment of a type in bytes. Structures have the maximum
   alignment required by their fields. */

static int
hppa_alignof (struct type *type)
{
  int max_align, align, i;
  CHECK_TYPEDEF (type);
  switch (TYPE_CODE (type))
    {
    case TYPE_CODE_PTR:
    case TYPE_CODE_INT:
    case TYPE_CODE_FLT:
      return TYPE_LENGTH (type);
    case TYPE_CODE_ARRAY:
      return hppa_alignof (TYPE_FIELD_TYPE (type, 0));
    case TYPE_CODE_STRUCT:
    case TYPE_CODE_UNION:
      max_align = 1;
      for (i = 0; i < TYPE_NFIELDS (type); i++)
	{
	  /* Bit fields have no real alignment. */
	  /* if (!TYPE_FIELD_BITPOS (type, i)) */
	  if (!TYPE_FIELD_BITSIZE (type, i))	/* elz: this should be bitsize */
	    {
	      align = hppa_alignof (TYPE_FIELD_TYPE (type, i));
	      max_align = max (max_align, align);
	    }
	}
      return max_align;
    default:
      return 4;
    }
}

/* For the given instruction (INST), return any adjustment it makes
   to the stack pointer or zero for no adjustment. 

   This only handles instructions commonly found in prologues.  */

static int
prologue_inst_adjust_sp (unsigned long inst)
{
  /* This must persist across calls.  */
  static int save_high21;

  /* The most common way to perform a stack adjustment ldo X(sp),sp */
  if ((inst & 0xffffc000) == 0x37de0000)
    return hppa_extract_14 (inst);

  /* stwm X,D(sp) */
  if ((inst & 0xffe00000) == 0x6fc00000)
    return hppa_extract_14 (inst);

  /* std,ma X,D(sp) */
  if ((inst & 0xffe00008) == 0x73c00008)
    return (inst & 0x1 ? -1 << 13 : 0) | (((inst >> 4) & 0x3ff) << 3);

  /* addil high21,%r1; ldo low11,(%r1),%r30)
     save high bits in save_high21 for later use.  */
  if ((inst & 0xffe00000) == 0x28200000)
    {
      save_high21 = hppa_extract_21 (inst);
      return 0;
    }

  if ((inst & 0xffff0000) == 0x343e0000)
    return save_high21 + hppa_extract_14 (inst);

  /* fstws as used by the HP compilers.  */
  if ((inst & 0xffffffe0) == 0x2fd01220)
    return hppa_extract_5_load (inst);

  /* No adjustment.  */
  return 0;
}

/* Return nonzero if INST is a branch of some kind, else return zero.  */

static int
is_branch (unsigned long inst)
{
  switch (inst >> 26)
    {
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x27:
    case 0x28:
    case 0x29:
    case 0x2a:
    case 0x2b:
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b:
      return 1;

    default:
      return 0;
    }
}

/* Return the register number for a GR which is saved by INST or
   zero it INST does not save a GR.  */

static int
inst_saves_gr (unsigned long inst)
{
  /* Does it look like a stw?  */
  if ((inst >> 26) == 0x1a || (inst >> 26) == 0x1b
      || (inst >> 26) == 0x1f
      || ((inst >> 26) == 0x1f
	  && ((inst >> 6) == 0xa)))
    return hppa_extract_5R_store (inst);

  /* Does it look like a std?  */
  if ((inst >> 26) == 0x1c
      || ((inst >> 26) == 0x03
	  && ((inst >> 6) & 0xf) == 0xb))
    return hppa_extract_5R_store (inst);

  /* Does it look like a stwm?  GCC & HPC may use this in prologues. */
  if ((inst >> 26) == 0x1b)
    return hppa_extract_5R_store (inst);

  /* Does it look like sth or stb?  HPC versions 9.0 and later use these
     too.  */
  if ((inst >> 26) == 0x19 || (inst >> 26) == 0x18
      || ((inst >> 26) == 0x3
	  && (((inst >> 6) & 0xf) == 0x8
	      || (inst >> 6) & 0xf) == 0x9))
    return hppa_extract_5R_store (inst);

  return 0;
}

/* Return the register number for a FR which is saved by INST or
   zero it INST does not save a FR.

   Note we only care about full 64bit register stores (that's the only
   kind of stores the prologue will use).

   FIXME: What about argument stores with the HP compiler in ANSI mode? */

static int
inst_saves_fr (unsigned long inst)
{
  /* is this an FSTD ? */
  if ((inst & 0xfc00dfc0) == 0x2c001200)
    return hppa_extract_5r_store (inst);
  if ((inst & 0xfc000002) == 0x70000002)
    return hppa_extract_5R_store (inst);
  /* is this an FSTW ? */
  if ((inst & 0xfc00df80) == 0x24001200)
    return hppa_extract_5r_store (inst);
  if ((inst & 0xfc000002) == 0x7c000000)
    return hppa_extract_5R_store (inst);
  return 0;
}

/* Advance PC across any function entry prologue instructions
   to reach some "real" code. 

   Use information in the unwind table to determine what exactly should
   be in the prologue.  */


CORE_ADDR
skip_prologue_hard_way (CORE_ADDR pc)
{
  char buf[4];
  CORE_ADDR orig_pc = pc;
  unsigned long inst, stack_remaining, save_gr, save_fr, save_rp, save_sp;
  unsigned long args_stored, status, i, restart_gr, restart_fr;
  struct unwind_table_entry *u;

  restart_gr = 0;
  restart_fr = 0;

restart:
  u = find_unwind_entry (pc);
  if (!u)
    return pc;

  /* If we are not at the beginning of a function, then return now. */
  if ((pc & ~0x3) != u->region_start)
    return pc;

  /* This is how much of a frame adjustment we need to account for.  */
  stack_remaining = u->Total_frame_size << 3;

  /* Magic register saves we want to know about.  */
  save_rp = u->Save_RP;
  save_sp = u->Save_SP;

  /* An indication that args may be stored into the stack.  Unfortunately
     the HPUX compilers tend to set this in cases where no args were
     stored too!.  */
  args_stored = 1;

  /* Turn the Entry_GR field into a bitmask.  */
  save_gr = 0;
  for (i = 3; i < u->Entry_GR + 3; i++)
    {
      /* Frame pointer gets saved into a special location.  */
      if (u->Save_SP && i == HPPA_FP_REGNUM)
	continue;

      save_gr |= (1 << i);
    }
  save_gr &= ~restart_gr;

  /* Turn the Entry_FR field into a bitmask too.  */
  save_fr = 0;
  for (i = 12; i < u->Entry_FR + 12; i++)
    save_fr |= (1 << i);
  save_fr &= ~restart_fr;

  /* Loop until we find everything of interest or hit a branch.

     For unoptimized GCC code and for any HP CC code this will never ever
     examine any user instructions.

     For optimzied GCC code we're faced with problems.  GCC will schedule
     its prologue and make prologue instructions available for delay slot
     filling.  The end result is user code gets mixed in with the prologue
     and a prologue instruction may be in the delay slot of the first branch
     or call.

     Some unexpected things are expected with debugging optimized code, so
     we allow this routine to walk past user instructions in optimized
     GCC code.  */
  while (save_gr || save_fr || save_rp || save_sp || stack_remaining > 0
	 || args_stored)
    {
      unsigned int reg_num;
      unsigned long old_stack_remaining, old_save_gr, old_save_fr;
      unsigned long old_save_rp, old_save_sp, next_inst;

      /* Save copies of all the triggers so we can compare them later
         (only for HPC).  */
      old_save_gr = save_gr;
      old_save_fr = save_fr;
      old_save_rp = save_rp;
      old_save_sp = save_sp;
      old_stack_remaining = stack_remaining;

      status = read_memory_nobpt (pc, buf, 4);
      inst = extract_unsigned_integer (buf, 4);

      /* Yow! */
      if (status != 0)
	return pc;

      /* Note the interesting effects of this instruction.  */
      stack_remaining -= prologue_inst_adjust_sp (inst);

      /* There are limited ways to store the return pointer into the
	 stack.  */
      if (inst == 0x6bc23fd9 || inst == 0x0fc212c1)
	save_rp = 0;

      /* These are the only ways we save SP into the stack.  At this time
         the HP compilers never bother to save SP into the stack.  */
      if ((inst & 0xffffc000) == 0x6fc10000
	  || (inst & 0xffffc00c) == 0x73c10008)
	save_sp = 0;

      /* Are we loading some register with an offset from the argument
         pointer?  */
      if ((inst & 0xffe00000) == 0x37a00000
	  || (inst & 0xffffffe0) == 0x081d0240)
	{
	  pc += 4;
	  continue;
	}

      /* Account for general and floating-point register saves.  */
      reg_num = inst_saves_gr (inst);
      save_gr &= ~(1 << reg_num);

      /* Ugh.  Also account for argument stores into the stack.
         Unfortunately args_stored only tells us that some arguments
         where stored into the stack.  Not how many or what kind!

         This is a kludge as on the HP compiler sets this bit and it
         never does prologue scheduling.  So once we see one, skip past
         all of them.   We have similar code for the fp arg stores below.

         FIXME.  Can still die if we have a mix of GR and FR argument
         stores!  */
      if (reg_num >= (TARGET_PTR_BIT == 64 ? 19 : 23) && reg_num <= 26)
	{
	  while (reg_num >= (TARGET_PTR_BIT == 64 ? 19 : 23) && reg_num <= 26)
	    {
	      pc += 4;
	      status = read_memory_nobpt (pc, buf, 4);
	      inst = extract_unsigned_integer (buf, 4);
	      if (status != 0)
		return pc;
	      reg_num = inst_saves_gr (inst);
	    }
	  args_stored = 0;
	  continue;
	}

      reg_num = inst_saves_fr (inst);
      save_fr &= ~(1 << reg_num);

      status = read_memory_nobpt (pc + 4, buf, 4);
      next_inst = extract_unsigned_integer (buf, 4);

      /* Yow! */
      if (status != 0)
	return pc;

      /* We've got to be read to handle the ldo before the fp register
         save.  */
      if ((inst & 0xfc000000) == 0x34000000
	  && inst_saves_fr (next_inst) >= 4
	  && inst_saves_fr (next_inst) <= (TARGET_PTR_BIT == 64 ? 11 : 7))
	{
	  /* So we drop into the code below in a reasonable state.  */
	  reg_num = inst_saves_fr (next_inst);
	  pc -= 4;
	}

      /* Ugh.  Also account for argument stores into the stack.
         This is a kludge as on the HP compiler sets this bit and it
         never does prologue scheduling.  So once we see one, skip past
         all of them.  */
      if (reg_num >= 4 && reg_num <= (TARGET_PTR_BIT == 64 ? 11 : 7))
	{
	  while (reg_num >= 4 && reg_num <= (TARGET_PTR_BIT == 64 ? 11 : 7))
	    {
	      pc += 8;
	      status = read_memory_nobpt (pc, buf, 4);
	      inst = extract_unsigned_integer (buf, 4);
	      if (status != 0)
		return pc;
	      if ((inst & 0xfc000000) != 0x34000000)
		break;
	      status = read_memory_nobpt (pc + 4, buf, 4);
	      next_inst = extract_unsigned_integer (buf, 4);
	      if (status != 0)
		return pc;
	      reg_num = inst_saves_fr (next_inst);
	    }
	  args_stored = 0;
	  continue;
	}

      /* Quit if we hit any kind of branch.  This can happen if a prologue
         instruction is in the delay slot of the first call/branch.  */
      if (is_branch (inst))
	break;

      /* What a crock.  The HP compilers set args_stored even if no
         arguments were stored into the stack (boo hiss).  This could
         cause this code to then skip a bunch of user insns (up to the
         first branch).

         To combat this we try to identify when args_stored was bogusly
         set and clear it.   We only do this when args_stored is nonzero,
         all other resources are accounted for, and nothing changed on
         this pass.  */
      if (args_stored
       && !(save_gr || save_fr || save_rp || save_sp || stack_remaining > 0)
	  && old_save_gr == save_gr && old_save_fr == save_fr
	  && old_save_rp == save_rp && old_save_sp == save_sp
	  && old_stack_remaining == stack_remaining)
	break;

      /* Bump the PC.  */
      pc += 4;
    }

  /* We've got a tenative location for the end of the prologue.  However
     because of limitations in the unwind descriptor mechanism we may
     have went too far into user code looking for the save of a register
     that does not exist.  So, if there registers we expected to be saved
     but never were, mask them out and restart.

     This should only happen in optimized code, and should be very rare.  */
  if (save_gr || (save_fr && !(restart_fr || restart_gr)))
    {
      pc = orig_pc;
      restart_gr = save_gr;
      restart_fr = save_fr;
      goto restart;
    }

  return pc;
}


/* Return the address of the PC after the last prologue instruction if
   we can determine it from the debug symbols.  Else return zero.  */

static CORE_ADDR
after_prologue (CORE_ADDR pc)
{
  struct symtab_and_line sal;
  CORE_ADDR func_addr, func_end;
  struct symbol *f;

  /* If we can not find the symbol in the partial symbol table, then
     there is no hope we can determine the function's start address
     with this code.  */
  if (!find_pc_partial_function (pc, NULL, &func_addr, &func_end))
    return 0;

  /* Get the line associated with FUNC_ADDR.  */
  sal = find_pc_line (func_addr, 0);

  /* There are only two cases to consider.  First, the end of the source line
     is within the function bounds.  In that case we return the end of the
     source line.  Second is the end of the source line extends beyond the
     bounds of the current function.  We need to use the slow code to
     examine instructions in that case. 

     Anything else is simply a bug elsewhere.  Fixing it here is absolutely
     the wrong thing to do.  In fact, it should be entirely possible for this
     function to always return zero since the slow instruction scanning code
     is supposed to *always* work.  If it does not, then it is a bug.  */
  if (sal.end < func_end)
    return sal.end;
  else
    return 0;
}

/* To skip prologues, I use this predicate.  Returns either PC itself
   if the code at PC does not look like a function prologue; otherwise
   returns an address that (if we're lucky) follows the prologue.  If
   LENIENT, then we must skip everything which is involved in setting
   up the frame (it's OK to skip more, just so long as we don't skip
   anything which might clobber the registers which are being saved.
   Currently we must not skip more on the alpha, but we might the lenient
   stuff some day.  */

static CORE_ADDR
hppa_skip_prologue (CORE_ADDR pc)
{
  unsigned long inst;
  int offset;
  CORE_ADDR post_prologue_pc;
  char buf[4];

  /* See if we can determine the end of the prologue via the symbol table.
     If so, then return either PC, or the PC after the prologue, whichever
     is greater.  */

  post_prologue_pc = after_prologue (pc);

  /* If after_prologue returned a useful address, then use it.  Else
     fall back on the instruction skipping code.

     Some folks have claimed this causes problems because the breakpoint
     may be the first instruction of the prologue.  If that happens, then
     the instruction skipping code has a bug that needs to be fixed.  */
  if (post_prologue_pc != 0)
    return max (pc, post_prologue_pc);
  else
    return (skip_prologue_hard_way (pc));
}

struct hppa_frame_cache
{
  CORE_ADDR base;
  struct trad_frame_saved_reg *saved_regs;
};

static struct hppa_frame_cache *
hppa_frame_cache (struct frame_info *next_frame, void **this_cache)
{
  struct hppa_frame_cache *cache;
  long saved_gr_mask;
  long saved_fr_mask;
  CORE_ADDR this_sp;
  long frame_size;
  struct unwind_table_entry *u;
  CORE_ADDR prologue_end;
  int i;

  if (hppa_debug)
    fprintf_unfiltered (gdb_stdlog, "{ hppa_frame_cache (frame=%d) -> ",
      frame_relative_level(next_frame));

  if ((*this_cache) != NULL)
    {
      if (hppa_debug)
        fprintf_unfiltered (gdb_stdlog, "base=0x%s (cached) }", 
          paddr_nz (((struct hppa_frame_cache *)*this_cache)->base));
      return (*this_cache);
    }
  cache = FRAME_OBSTACK_ZALLOC (struct hppa_frame_cache);
  (*this_cache) = cache;
  cache->saved_regs = trad_frame_alloc_saved_regs (next_frame);

  /* Yow! */
  u = find_unwind_entry (frame_func_unwind (next_frame));
  if (!u)
    {
      if (hppa_debug)
        fprintf_unfiltered (gdb_stdlog, "base=NULL (no unwind entry) }");
      return (*this_cache);
    }

  /* Turn the Entry_GR field into a bitmask.  */
  saved_gr_mask = 0;
  for (i = 3; i < u->Entry_GR + 3; i++)
    {
      /* Frame pointer gets saved into a special location.  */
      if (u->Save_SP && i == HPPA_FP_REGNUM)
	continue;
	
      saved_gr_mask |= (1 << i);
    }

  /* Turn the Entry_FR field into a bitmask too.  */
  saved_fr_mask = 0;
  for (i = 12; i < u->Entry_FR + 12; i++)
    saved_fr_mask |= (1 << i);

  /* Loop until we find everything of interest or hit a branch.

     For unoptimized GCC code and for any HP CC code this will never ever
     examine any user instructions.

     For optimized GCC code we're faced with problems.  GCC will schedule
     its prologue and make prologue instructions available for delay slot
     filling.  The end result is user code gets mixed in with the prologue
     and a prologue instruction may be in the delay slot of the first branch
     or call.

     Some unexpected things are expected with debugging optimized code, so
     we allow this routine to walk past user instructions in optimized
     GCC code.  */
  {
    int final_iteration = 0;
    CORE_ADDR pc, end_pc;
    int looking_for_sp = u->Save_SP;
    int looking_for_rp = u->Save_RP;
    int fp_loc = -1;

    /* We have to use hppa_skip_prologue instead of just 
       skip_prologue_using_sal, in case we stepped into a function without
       symbol information.  hppa_skip_prologue also bounds the returned
       pc by the passed in pc, so it will not return a pc in the next
       function.  */
    prologue_end = hppa_skip_prologue (frame_func_unwind (next_frame));
    end_pc = frame_pc_unwind (next_frame);

    if (prologue_end != 0 && end_pc > prologue_end)
      end_pc = prologue_end;

    frame_size = 0;

    for (pc = frame_func_unwind (next_frame);
	 ((saved_gr_mask || saved_fr_mask
	   || looking_for_sp || looking_for_rp
	   || frame_size < (u->Total_frame_size << 3))
	  && pc < end_pc);
	 pc += 4)
      {
	int reg;
	char buf4[4];
	long status = read_memory_nobpt (pc, buf4, sizeof buf4);
	long inst = extract_unsigned_integer (buf4, sizeof buf4);

	/* Note the interesting effects of this instruction.  */
	frame_size += prologue_inst_adjust_sp (inst);
	
	/* There are limited ways to store the return pointer into the
	   stack.  */
	if (inst == 0x6bc23fd9) /* stw rp,-0x14(sr0,sp) */
	  {
	    looking_for_rp = 0;
	    cache->saved_regs[HPPA_RP_REGNUM].addr = -20;
	  }
	else if (inst == 0x0fc212c1) /* std rp,-0x10(sr0,sp) */
	  {
	    looking_for_rp = 0;
	    cache->saved_regs[HPPA_RP_REGNUM].addr = -16;
	  }
	
	/* Check to see if we saved SP into the stack.  This also
	   happens to indicate the location of the saved frame
	   pointer.  */
	if ((inst & 0xffffc000) == 0x6fc10000  /* stw,ma r1,N(sr0,sp) */
	    || (inst & 0xffffc00c) == 0x73c10008) /* std,ma r1,N(sr0,sp) */
	  {
	    looking_for_sp = 0;
	    cache->saved_regs[HPPA_FP_REGNUM].addr = 0;
	  }
	
	/* Account for general and floating-point register saves.  */
	reg = inst_saves_gr (inst);
	if (reg >= 3 && reg <= 18
	    && (!u->Save_SP || reg != HPPA_FP_REGNUM))
	  {
	    saved_gr_mask &= ~(1 << reg);
	    if ((inst >> 26) == 0x1b && hppa_extract_14 (inst) >= 0)
	      /* stwm with a positive displacement is a _post_
		 _modify_.  */
	      cache->saved_regs[reg].addr = 0;
	    else if ((inst & 0xfc00000c) == 0x70000008)
	      /* A std has explicit post_modify forms.  */
	      cache->saved_regs[reg].addr = 0;
	    else
	      {
		CORE_ADDR offset;
		
		if ((inst >> 26) == 0x1c)
		  offset = (inst & 0x1 ? -1 << 13 : 0) | (((inst >> 4) & 0x3ff) << 3);
		else if ((inst >> 26) == 0x03)
		  offset = hppa_low_hppa_sign_extend (inst & 0x1f, 5);
		else
		  offset = hppa_extract_14 (inst);
		
		/* Handle code with and without frame pointers.  */
		if (u->Save_SP)
		  cache->saved_regs[reg].addr = offset;
		else
		  cache->saved_regs[reg].addr = (u->Total_frame_size << 3) + offset;
	      }
	  }

	/* GCC handles callee saved FP regs a little differently.  
	   
	   It emits an instruction to put the value of the start of
	   the FP store area into %r1.  It then uses fstds,ma with a
	   basereg of %r1 for the stores.

	   HP CC emits them at the current stack pointer modifying the
	   stack pointer as it stores each register.  */
	
	/* ldo X(%r3),%r1 or ldo X(%r30),%r1.  */
	if ((inst & 0xffffc000) == 0x34610000
	    || (inst & 0xffffc000) == 0x37c10000)
	  fp_loc = hppa_extract_14 (inst);
	
	reg = inst_saves_fr (inst);
	if (reg >= 12 && reg <= 21)
	  {
	    /* Note +4 braindamage below is necessary because the FP
	       status registers are internally 8 registers rather than
	       the expected 4 registers.  */
	    saved_fr_mask &= ~(1 << reg);
	    if (fp_loc == -1)
	      {
		/* 1st HP CC FP register store.  After this
		   instruction we've set enough state that the GCC and
		   HPCC code are both handled in the same manner.  */
		cache->saved_regs[reg + HPPA_FP4_REGNUM + 4].addr = 0;
		fp_loc = 8;
	      }
	    else
	      {
		cache->saved_regs[reg + HPPA_FP0_REGNUM + 4].addr = fp_loc;
		fp_loc += 8;
	      }
	  }
	
	/* Quit if we hit any kind of branch the previous iteration. */
	if (final_iteration)
	  break;
	/* We want to look precisely one instruction beyond the branch
	   if we have not found everything yet.  */
	if (is_branch (inst))
	  final_iteration = 1;
      }
  }

  {
    /* The frame base always represents the value of %sp at entry to
       the current function (and is thus equivalent to the "saved"
       stack pointer.  */
    CORE_ADDR this_sp = frame_unwind_register_unsigned (next_frame, HPPA_SP_REGNUM);
    CORE_ADDR fp;

    if (hppa_debug)
      fprintf_unfiltered (gdb_stdlog, " (this_sp=0x%s, pc=0x%s, "
		          "prologue_end=0x%s) ",
		          paddr_nz (this_sp),
			  paddr_nz (frame_pc_unwind (next_frame)),
			  paddr_nz (prologue_end));

     /* Check to see if a frame pointer is available, and use it for
        frame unwinding if it is.
 
        There are some situations where we need to rely on the frame
        pointer to do stack unwinding.  For example, if a function calls
        alloca (), the stack pointer can get adjusted inside the body of
        the function.  In this case, the ABI requires that the compiler
        maintain a frame pointer for the function.
 
        The unwind record has a flag (alloca_frame) that indicates that
        a function has a variable frame; unfortunately, gcc/binutils 
        does not set this flag.  Instead, whenever a frame pointer is used
        and saved on the stack, the Save_SP flag is set.  We use this to
        decide whether to use the frame pointer for unwinding.
	
	fp should never be zero here; checking just in case. 
	
        TODO: For the HP compiler, maybe we should use the alloca_frame flag 
	instead of Save_SP.  */
 
     fp = frame_unwind_register_unsigned (next_frame, HPPA_FP_REGNUM);
 
     if (frame_pc_unwind (next_frame) >= prologue_end
         && u->Save_SP && fp != 0)
      {
 	cache->base = fp;
 
 	if (hppa_debug)
	  fprintf_unfiltered (gdb_stdlog, " (base=0x%s) [frame pointer] }",
 	    paddr_nz (cache->base));
      }
     else if (frame_pc_unwind (next_frame) >= prologue_end)
      {
        if (u->Save_SP && trad_frame_addr_p (cache->saved_regs, HPPA_SP_REGNUM))
          {
            /* Both we're expecting the SP to be saved and the SP has been
	       saved.  The entry SP value is saved at this frame's SP
	       address.  */
            cache->base = read_memory_integer (this_sp, TARGET_PTR_BIT / 8);

	    if (hppa_debug)
	      fprintf_unfiltered (gdb_stdlog, " (base=0x%s) [saved] }",
			          paddr_nz (cache->base));
          }
        else
          {
            /* The prologue has been slowly allocating stack space.  Adjust
	     the SP back.  */
            cache->base = this_sp - frame_size;
	    if (hppa_debug)
	      fprintf_unfiltered (gdb_stdlog, " (base=0x%s) [unwind adjust] } ",
			          paddr_nz (cache->base));

          }
      }
    else
      {
	/* This frame has not yet been created. */
        cache->base = this_sp;

	if (hppa_debug)
	  fprintf_unfiltered (gdb_stdlog, " (base=0x%s) [before prologue] } ",
			      paddr_nz (cache->base));

      }

    trad_frame_set_value (cache->saved_regs, HPPA_SP_REGNUM, cache->base);
  }

  /* The PC is found in the "return register", "Millicode" uses "r31"
     as the return register while normal code uses "rp".  */
  if (u->Millicode)
    {
      if (trad_frame_addr_p (cache->saved_regs, 31))
        cache->saved_regs[HPPA_PCOQ_HEAD_REGNUM] = cache->saved_regs[31];
      else
	{
	  ULONGEST r31 = frame_unwind_register_unsigned (next_frame, 31);
	  trad_frame_set_value (cache->saved_regs, HPPA_PCOQ_HEAD_REGNUM, r31);
        }
    }
  else
    {
      if (trad_frame_addr_p (cache->saved_regs, HPPA_RP_REGNUM))
        cache->saved_regs[HPPA_PCOQ_HEAD_REGNUM] = cache->saved_regs[HPPA_RP_REGNUM];
      else
	{
	  ULONGEST rp = frame_unwind_register_unsigned (next_frame, HPPA_RP_REGNUM);
	  trad_frame_set_value (cache->saved_regs, HPPA_PCOQ_HEAD_REGNUM, rp);
	}
    }

  {
    /* Convert all the offsets into addresses.  */
    int reg;
    for (reg = 0; reg < NUM_REGS; reg++)
      {
	if (trad_frame_addr_p (cache->saved_regs, reg))
	  cache->saved_regs[reg].addr += cache->base;
      }
  }

  if (hppa_debug)
    fprintf_unfiltered (gdb_stdlog, "base=0x%s }", 
      paddr_nz (((struct hppa_frame_cache *)*this_cache)->base));
  return (*this_cache);
}

static void
hppa_frame_this_id (struct frame_info *next_frame, void **this_cache,
			   struct frame_id *this_id)
{
  struct hppa_frame_cache *info = hppa_frame_cache (next_frame, this_cache);
  (*this_id) = frame_id_build (info->base, frame_func_unwind (next_frame));
}

static void
hppa_frame_prev_register (struct frame_info *next_frame,
			  void **this_cache,
			  int regnum, int *optimizedp,
			  enum lval_type *lvalp, CORE_ADDR *addrp,
			  int *realnump, void *valuep)
{
  struct hppa_frame_cache *info = hppa_frame_cache (next_frame, this_cache);
  hppa_frame_prev_register_helper (next_frame, info->saved_regs, regnum,
		                   optimizedp, lvalp, addrp, realnump, valuep);
}

static const struct frame_unwind hppa_frame_unwind =
{
  NORMAL_FRAME,
  hppa_frame_this_id,
  hppa_frame_prev_register
};

static const struct frame_unwind *
hppa_frame_unwind_sniffer (struct frame_info *next_frame)
{
  CORE_ADDR pc = frame_pc_unwind (next_frame);

  if (find_unwind_entry (pc))
    return &hppa_frame_unwind;

  return NULL;
}

/* This is a generic fallback frame unwinder that kicks in if we fail all
   the other ones.  Normally we would expect the stub and regular unwinder
   to work, but in some cases we might hit a function that just doesn't
   have any unwind information available.  In this case we try to do
   unwinding solely based on code reading.  This is obviously going to be
   slow, so only use this as a last resort.  Currently this will only
   identify the stack and pc for the frame.  */

static struct hppa_frame_cache *
hppa_fallback_frame_cache (struct frame_info *next_frame, void **this_cache)
{
  struct hppa_frame_cache *cache;
  CORE_ADDR pc, start_pc, end_pc, cur_pc;

  cache = FRAME_OBSTACK_ZALLOC (struct hppa_frame_cache);
  (*this_cache) = cache;
  cache->saved_regs = trad_frame_alloc_saved_regs (next_frame);

  pc = frame_func_unwind (next_frame);
  cur_pc = frame_pc_unwind (next_frame);

  find_pc_partial_function (pc, NULL, &start_pc, &end_pc);

  if (start_pc == 0 || end_pc == 0)
    {
      error ("Cannot find bounds of current function (@0x%s), unwinding will "
	     "fail.", paddr_nz (pc));
      return cache;
    }

  if (end_pc > cur_pc)
    end_pc = cur_pc;

  for (pc = start_pc; pc < end_pc; pc += 4)
    {
      unsigned int insn;

      insn = read_memory_unsigned_integer (pc, 4);

      /* There are limited ways to store the return pointer into the
	 stack.  */
      if (insn == 0x6bc23fd9) /* stw rp,-0x14(sr0,sp) */
	{
	  cache->saved_regs[HPPA_RP_REGNUM].addr = -20;
	  break;
	}
      else if (insn == 0x0fc212c1) /* std rp,-0x10(sr0,sp) */
	{
	  cache->saved_regs[HPPA_RP_REGNUM].addr = -16;
	  break;
	}
    }

  cache->base = frame_unwind_register_unsigned (next_frame, HPPA_SP_REGNUM);

  if (trad_frame_addr_p (cache->saved_regs, HPPA_RP_REGNUM))
    {
      cache->saved_regs[HPPA_RP_REGNUM].addr += cache->base;
      cache->saved_regs[HPPA_PCOQ_HEAD_REGNUM] = cache->saved_regs[HPPA_RP_REGNUM];
    }
  else
    {
      ULONGEST rp = frame_unwind_register_unsigned (next_frame, HPPA_RP_REGNUM);
      trad_frame_set_value (cache->saved_regs, HPPA_PCOQ_HEAD_REGNUM, rp);
    }

  return cache;
}

static void
hppa_fallback_frame_this_id (struct frame_info *next_frame, void **this_cache,
			     struct frame_id *this_id)
{
  struct hppa_frame_cache *info = 
    hppa_fallback_frame_cache (next_frame, this_cache);
  (*this_id) = frame_id_build (info->base, frame_func_unwind (next_frame));
}

static void
hppa_fallback_frame_prev_register (struct frame_info *next_frame,
			  void **this_cache,
			  int regnum, int *optimizedp,
			  enum lval_type *lvalp, CORE_ADDR *addrp,
			  int *realnump, void *valuep)
{
  struct hppa_frame_cache *info = 
    hppa_fallback_frame_cache (next_frame, this_cache);
  hppa_frame_prev_register_helper (next_frame, info->saved_regs, regnum,
		                   optimizedp, lvalp, addrp, realnump, valuep);
}

static const struct frame_unwind hppa_fallback_frame_unwind =
{
  NORMAL_FRAME,
  hppa_fallback_frame_this_id,
  hppa_fallback_frame_prev_register
};

static const struct frame_unwind *
hppa_fallback_unwind_sniffer (struct frame_info *next_frame)
{
  return &hppa_fallback_frame_unwind;
}

static CORE_ADDR
hppa_frame_base_address (struct frame_info *next_frame,
				void **this_cache)
{
  struct hppa_frame_cache *info = hppa_frame_cache (next_frame,
							   this_cache);
  return info->base;
}

static const struct frame_base hppa_frame_base = {
  &hppa_frame_unwind,
  hppa_frame_base_address,
  hppa_frame_base_address,
  hppa_frame_base_address
};

static const struct frame_base *
hppa_frame_base_sniffer (struct frame_info *next_frame)
{
  return &hppa_frame_base;
}

/* Stub frames, used for all kinds of call stubs.  */
struct hppa_stub_unwind_cache
{
  CORE_ADDR base;
  struct trad_frame_saved_reg *saved_regs;
};

static struct hppa_stub_unwind_cache *
hppa_stub_frame_unwind_cache (struct frame_info *next_frame,
			      void **this_cache)
{
  struct gdbarch *gdbarch = get_frame_arch (next_frame);
  struct hppa_stub_unwind_cache *info;
  struct unwind_table_entry *u;

  if (*this_cache)
    return *this_cache;

  info = FRAME_OBSTACK_ZALLOC (struct hppa_stub_unwind_cache);
  *this_cache = info;
  info->saved_regs = trad_frame_alloc_saved_regs (next_frame);

  info->base = frame_unwind_register_unsigned (next_frame, HPPA_SP_REGNUM);

  if (gdbarch_osabi (gdbarch) == GDB_OSABI_HPUX_SOM)
    {
      /* HPUX uses export stubs in function calls; the export stub clobbers
         the return value of the caller, and, later restores it from the
	 stack.  */
      u = find_unwind_entry (frame_pc_unwind (next_frame));

      if (u && u->stub_unwind.stub_type == EXPORT)
	{
          info->saved_regs[HPPA_PCOQ_HEAD_REGNUM].addr = info->base - 24;

	  return info;
	}
    }

  /* By default we assume that stubs do not change the rp.  */
  info->saved_regs[HPPA_PCOQ_HEAD_REGNUM].realreg = HPPA_RP_REGNUM;

  return info;
}

static void
hppa_stub_frame_this_id (struct frame_info *next_frame,
			 void **this_prologue_cache,
			 struct frame_id *this_id)
{
  struct hppa_stub_unwind_cache *info
    = hppa_stub_frame_unwind_cache (next_frame, this_prologue_cache);
  *this_id = frame_id_build (info->base, frame_pc_unwind (next_frame));
}

static void
hppa_stub_frame_prev_register (struct frame_info *next_frame,
			       void **this_prologue_cache,
			       int regnum, int *optimizedp,
			       enum lval_type *lvalp, CORE_ADDR *addrp,
			       int *realnump, void *valuep)
{
  struct hppa_stub_unwind_cache *info
    = hppa_stub_frame_unwind_cache (next_frame, this_prologue_cache);
  hppa_frame_prev_register_helper (next_frame, info->saved_regs, regnum,
		                   optimizedp, lvalp, addrp, realnump, valuep);
}

static const struct frame_unwind hppa_stub_frame_unwind = {
  NORMAL_FRAME,
  hppa_stub_frame_this_id,
  hppa_stub_frame_prev_register
};

static const struct frame_unwind *
hppa_stub_unwind_sniffer (struct frame_info *next_frame)
{
  CORE_ADDR pc = frame_pc_unwind (next_frame);

  if (IN_SOLIB_CALL_TRAMPOLINE (pc, NULL)
      || IN_SOLIB_RETURN_TRAMPOLINE (pc, NULL))
    return &hppa_stub_frame_unwind;
  return NULL;
}

static struct frame_id
hppa_unwind_dummy_id (struct gdbarch *gdbarch, struct frame_info *next_frame)
{
  return frame_id_build (frame_unwind_register_unsigned (next_frame,
							 HPPA_SP_REGNUM),
			 frame_pc_unwind (next_frame));
}

static CORE_ADDR
hppa_unwind_pc (struct gdbarch *gdbarch, struct frame_info *next_frame)
{
  return frame_unwind_register_signed (next_frame, HPPA_PCOQ_HEAD_REGNUM) & ~3;
}

/* Instead of this nasty cast, add a method pvoid() that prints out a
   host VOID data type (remember %p isn't portable).  */

static CORE_ADDR
hppa_pointer_to_address_hack (void *ptr)
{
  gdb_assert (sizeof (ptr) == TYPE_LENGTH (builtin_type_void_data_ptr));
  return POINTER_TO_ADDRESS (builtin_type_void_data_ptr, &ptr);
}

static void
unwind_command (char *exp, int from_tty)
{
  CORE_ADDR address;
  struct unwind_table_entry *u;

  /* If we have an expression, evaluate it and use it as the address.  */

  if (exp != 0 && *exp != 0)
    address = parse_and_eval_address (exp);
  else
    return;

  u = find_unwind_entry (address);

  if (!u)
    {
      printf_unfiltered ("Can't find unwind table entry for %s\n", exp);
      return;
    }

  printf_unfiltered ("unwind_table_entry (0x%s):\n",
		     paddr_nz (hppa_pointer_to_address_hack (u)));

  printf_unfiltered ("\tregion_start = ");
  print_address (u->region_start, gdb_stdout);

  printf_unfiltered ("\n\tregion_end = ");
  print_address (u->region_end, gdb_stdout);

#define pif(FLD) if (u->FLD) printf_unfiltered (" "#FLD);

  printf_unfiltered ("\n\tflags =");
  pif (Cannot_unwind);
  pif (Millicode);
  pif (Millicode_save_sr0);
  pif (Entry_SR);
  pif (Args_stored);
  pif (Variable_Frame);
  pif (Separate_Package_Body);
  pif (Frame_Extension_Millicode);
  pif (Stack_Overflow_Check);
  pif (Two_Instruction_SP_Increment);
  pif (Ada_Region);
  pif (Save_SP);
  pif (Save_RP);
  pif (Save_MRP_in_frame);
  pif (extn_ptr_defined);
  pif (Cleanup_defined);
  pif (MPE_XL_interrupt_marker);
  pif (HP_UX_interrupt_marker);
  pif (Large_frame);

  putchar_unfiltered ('\n');

#define pin(FLD) printf_unfiltered ("\t"#FLD" = 0x%x\n", u->FLD);

  pin (Region_description);
  pin (Entry_FR);
  pin (Entry_GR);
  pin (Total_frame_size);
}

void
hppa_skip_permanent_breakpoint (void)
{
  /* To step over a breakpoint instruction on the PA takes some
     fiddling with the instruction address queue.

     When we stop at a breakpoint, the IA queue front (the instruction
     we're executing now) points at the breakpoint instruction, and
     the IA queue back (the next instruction to execute) points to
     whatever instruction we would execute after the breakpoint, if it
     were an ordinary instruction.  This is the case even if the
     breakpoint is in the delay slot of a branch instruction.

     Clearly, to step past the breakpoint, we need to set the queue
     front to the back.  But what do we put in the back?  What
     instruction comes after that one?  Because of the branch delay
     slot, the next insn is always at the back + 4.  */
  write_register (HPPA_PCOQ_HEAD_REGNUM, read_register (HPPA_PCOQ_TAIL_REGNUM));
  write_register (HPPA_PCSQ_HEAD_REGNUM, read_register (HPPA_PCSQ_TAIL_REGNUM));

  write_register (HPPA_PCOQ_TAIL_REGNUM, read_register (HPPA_PCOQ_TAIL_REGNUM) + 4);
  /* We can leave the tail's space the same, since there's no jump.  */
}

int
hppa_pc_requires_run_before_use (CORE_ADDR pc)
{
  /* Sometimes we may pluck out a minimal symbol that has a negative address.
  
     An example of this occurs when an a.out is linked against a foo.sl.
     The foo.sl defines a global bar(), and the a.out declares a signature
     for bar().  However, the a.out doesn't directly call bar(), but passes
     its address in another call.
  
     If you have this scenario and attempt to "break bar" before running,
     gdb will find a minimal symbol for bar() in the a.out.  But that
     symbol's address will be negative.  What this appears to denote is
     an index backwards from the base of the procedure linkage table (PLT)
     into the data linkage table (DLT), the end of which is contiguous
     with the start of the PLT.  This is clearly not a valid address for
     us to set a breakpoint on.
  
     Note that one must be careful in how one checks for a negative address.
     0xc0000000 is a legitimate address of something in a shared text
     segment, for example.  Since I don't know what the possible range
     is of these "really, truly negative" addresses that come from the
     minimal symbols, I'm resorting to the gross hack of checking the
     top byte of the address for all 1's.  Sigh.  */

  return (!target_has_stack && (pc & 0xFF000000));
}

int
hppa_instruction_nullified (void)
{
  /* brobecker 2002/11/07: Couldn't we use a ULONGEST here? It would
     avoid the type cast.  I'm leaving it as is for now as I'm doing
     semi-mechanical multiarching-related changes.  */
  const int ipsw = (int) read_register (HPPA_IPSW_REGNUM);
  const int flags = (int) read_register (HPPA_FLAGS_REGNUM);

  return ((ipsw & 0x00200000) && !(flags & 0x2));
}

/* Return the GDB type object for the "standard" data type of data
   in register N.  */

static struct type *
hppa32_register_type (struct gdbarch *gdbarch, int reg_nr)
{
   if (reg_nr < HPPA_FP4_REGNUM)
     return builtin_type_uint32;
   else
     return builtin_type_ieee_single_big;
}

/* Return the GDB type object for the "standard" data type of data
   in register N.  hppa64 version.  */

static struct type *
hppa64_register_type (struct gdbarch *gdbarch, int reg_nr)
{
   if (reg_nr < HPPA_FP4_REGNUM)
     return builtin_type_uint64;
   else
     return builtin_type_ieee_double_big;
}

/* Return True if REGNUM is not a register available to the user
   through ptrace().  */

static int
hppa_cannot_store_register (int regnum)
{
  return (regnum == 0
          || regnum == HPPA_PCSQ_HEAD_REGNUM
          || (regnum >= HPPA_PCSQ_TAIL_REGNUM && regnum < HPPA_IPSW_REGNUM)
          || (regnum > HPPA_IPSW_REGNUM && regnum < HPPA_FP4_REGNUM));

}

static CORE_ADDR
hppa_smash_text_address (CORE_ADDR addr)
{
  /* The low two bits of the PC on the PA contain the privilege level.
     Some genius implementing a (non-GCC) compiler apparently decided
     this means that "addresses" in a text section therefore include a
     privilege level, and thus symbol tables should contain these bits.
     This seems like a bonehead thing to do--anyway, it seems to work
     for our purposes to just ignore those bits.  */

  return (addr &= ~0x3);
}

/* Get the ith function argument for the current function.  */
CORE_ADDR
hppa_fetch_pointer_argument (struct frame_info *frame, int argi, 
			     struct type *type)
{
  CORE_ADDR addr;
  get_frame_register (frame, HPPA_R0_REGNUM + 26 - argi, &addr);
  return addr;
}

static void
hppa_pseudo_register_read (struct gdbarch *gdbarch, struct regcache *regcache,
			   int regnum, void *buf)
{
    ULONGEST tmp;

    regcache_raw_read_unsigned (regcache, regnum, &tmp);
    if (regnum == HPPA_PCOQ_HEAD_REGNUM || regnum == HPPA_PCOQ_TAIL_REGNUM)
      tmp &= ~0x3;
    store_unsigned_integer (buf, sizeof(tmp), tmp);
}

void
hppa_frame_prev_register_helper (struct frame_info *next_frame,
			         struct trad_frame_saved_reg saved_regs[],
				 int regnum, int *optimizedp,
				 enum lval_type *lvalp, CORE_ADDR *addrp,
				 int *realnump, void *valuep)
{
  int pcoqt = (regnum == HPPA_PCOQ_TAIL_REGNUM);
  struct gdbarch *gdbarch = get_frame_arch (next_frame);
  int regsize = register_size (gdbarch, HPPA_PCOQ_HEAD_REGNUM);

  if (pcoqt)
    regnum = HPPA_PCOQ_HEAD_REGNUM;

  trad_frame_prev_register (next_frame, saved_regs, regnum,
                            optimizedp, lvalp, addrp, realnump, valuep);

  if (pcoqt)
    store_unsigned_integer (valuep, regsize, 
		      	    extract_unsigned_integer (valuep, regsize) + 4);
}

/* Here is a table of C type sizes on hppa with various compiles
   and options.  I measured this on PA 9000/800 with HP-UX 11.11
   and these compilers:

     /usr/ccs/bin/cc    HP92453-01 A.11.01.21
     /opt/ansic/bin/cc  HP92453-01 B.11.11.28706.GP
     /opt/aCC/bin/aCC   B3910B A.03.45
     gcc                gcc 3.3.2 native hppa2.0w-hp-hpux11.11

     cc            : 1 2 4 4 8 : 4 8 -- : 4 4
     ansic +DA1.1  : 1 2 4 4 8 : 4 8 16 : 4 4
     ansic +DA2.0  : 1 2 4 4 8 : 4 8 16 : 4 4
     ansic +DA2.0W : 1 2 4 8 8 : 4 8 16 : 8 8
     acc   +DA1.1  : 1 2 4 4 8 : 4 8 16 : 4 4
     acc   +DA2.0  : 1 2 4 4 8 : 4 8 16 : 4 4
     acc   +DA2.0W : 1 2 4 8 8 : 4 8 16 : 8 8
     gcc           : 1 2 4 4 8 : 4 8 16 : 4 4

   Each line is:

     compiler and options
     char, short, int, long, long long
     float, double, long double
     char *, void (*)()

   So all these compilers use either ILP32 or LP64 model.
   TODO: gcc has more options so it needs more investigation.

   For floating point types, see:

     http://docs.hp.com/hpux/pdf/B3906-90006.pdf
     HP-UX floating-point guide, hpux 11.00

   -- chastain 2003-12-18  */

static struct gdbarch *
hppa_gdbarch_init (struct gdbarch_info info, struct gdbarch_list *arches)
{
  struct gdbarch_tdep *tdep;
  struct gdbarch *gdbarch;
  
  /* Try to determine the ABI of the object we are loading.  */
  if (info.abfd != NULL && info.osabi == GDB_OSABI_UNKNOWN)
    {
      /* If it's a SOM file, assume it's HP/UX SOM.  */
      if (bfd_get_flavour (info.abfd) == bfd_target_som_flavour)
	info.osabi = GDB_OSABI_HPUX_SOM;
    }

  /* find a candidate among the list of pre-declared architectures.  */
  arches = gdbarch_list_lookup_by_info (arches, &info);
  if (arches != NULL)
    return (arches->gdbarch);

  /* If none found, then allocate and initialize one.  */
  tdep = XZALLOC (struct gdbarch_tdep);
  gdbarch = gdbarch_alloc (&info, tdep);

  /* Determine from the bfd_arch_info structure if we are dealing with
     a 32 or 64 bits architecture.  If the bfd_arch_info is not available,
     then default to a 32bit machine.  */
  if (info.bfd_arch_info != NULL)
    tdep->bytes_per_address =
      info.bfd_arch_info->bits_per_address / info.bfd_arch_info->bits_per_byte;
  else
    tdep->bytes_per_address = 4;

  /* Some parts of the gdbarch vector depend on whether we are running
     on a 32 bits or 64 bits target.  */
  switch (tdep->bytes_per_address)
    {
      case 4:
        set_gdbarch_num_regs (gdbarch, hppa32_num_regs);
        set_gdbarch_register_name (gdbarch, hppa32_register_name);
        set_gdbarch_register_type (gdbarch, hppa32_register_type);
        break;
      case 8:
        set_gdbarch_num_regs (gdbarch, hppa64_num_regs);
        set_gdbarch_register_name (gdbarch, hppa64_register_name);
        set_gdbarch_register_type (gdbarch, hppa64_register_type);
        break;
      default:
        internal_error (__FILE__, __LINE__, "Unsupported address size: %d",
                        tdep->bytes_per_address);
    }

  set_gdbarch_long_bit (gdbarch, tdep->bytes_per_address * TARGET_CHAR_BIT);
  set_gdbarch_ptr_bit (gdbarch, tdep->bytes_per_address * TARGET_CHAR_BIT);

  /* The following gdbarch vector elements are the same in both ILP32
     and LP64, but might show differences some day.  */
  set_gdbarch_long_long_bit (gdbarch, 64);
  set_gdbarch_long_double_bit (gdbarch, 128);
  set_gdbarch_long_double_format (gdbarch, &floatformat_ia64_quad_big);

  /* The following gdbarch vector elements do not depend on the address
     size, or in any other gdbarch element previously set.  */
  set_gdbarch_skip_prologue (gdbarch, hppa_skip_prologue);
  set_gdbarch_inner_than (gdbarch, core_addr_greaterthan);
  set_gdbarch_sp_regnum (gdbarch, HPPA_SP_REGNUM);
  set_gdbarch_fp0_regnum (gdbarch, HPPA_FP0_REGNUM);
  set_gdbarch_cannot_store_register (gdbarch, hppa_cannot_store_register);
  set_gdbarch_cannot_fetch_register (gdbarch, hppa_cannot_store_register);
  set_gdbarch_addr_bits_remove (gdbarch, hppa_smash_text_address);
  set_gdbarch_smash_text_address (gdbarch, hppa_smash_text_address);
  set_gdbarch_believe_pcc_promotion (gdbarch, 1);
  set_gdbarch_read_pc (gdbarch, hppa_target_read_pc);
  set_gdbarch_write_pc (gdbarch, hppa_target_write_pc);

  /* Helper for function argument information.  */
  set_gdbarch_fetch_pointer_argument (gdbarch, hppa_fetch_pointer_argument);

  set_gdbarch_print_insn (gdbarch, print_insn_hppa);

  /* When a hardware watchpoint triggers, we'll move the inferior past
     it by removing all eventpoints; stepping past the instruction
     that caused the trigger; reinserting eventpoints; and checking
     whether any watched location changed.  */
  set_gdbarch_have_nonsteppable_watchpoint (gdbarch, 1);

  /* Inferior function call methods.  */
  switch (tdep->bytes_per_address)
    {
    case 4:
      set_gdbarch_push_dummy_call (gdbarch, hppa32_push_dummy_call);
      set_gdbarch_frame_align (gdbarch, hppa32_frame_align);
      break;
    case 8:
      set_gdbarch_push_dummy_call (gdbarch, hppa64_push_dummy_call);
      set_gdbarch_frame_align (gdbarch, hppa64_frame_align);
      break;
    default:
      internal_error (__FILE__, __LINE__, "bad switch");
    }
      
  /* Struct return methods.  */
  switch (tdep->bytes_per_address)
    {
    case 4:
      set_gdbarch_return_value (gdbarch, hppa32_return_value);
      break;
    case 8:
      set_gdbarch_return_value (gdbarch, hppa64_return_value);
      break;
    default:
      internal_error (__FILE__, __LINE__, "bad switch");
    }
      
  set_gdbarch_breakpoint_from_pc (gdbarch, hppa_breakpoint_from_pc);
  set_gdbarch_pseudo_register_read (gdbarch, hppa_pseudo_register_read);

  /* Frame unwind methods.  */
  set_gdbarch_unwind_dummy_id (gdbarch, hppa_unwind_dummy_id);
  set_gdbarch_unwind_pc (gdbarch, hppa_unwind_pc);

  /* Hook in ABI-specific overrides, if they have been registered.  */
  gdbarch_init_osabi (info, gdbarch);

  /* Hook in the default unwinders.  */
  frame_unwind_append_sniffer (gdbarch, hppa_stub_unwind_sniffer);
  frame_unwind_append_sniffer (gdbarch, hppa_frame_unwind_sniffer);
  frame_unwind_append_sniffer (gdbarch, hppa_fallback_unwind_sniffer);
  frame_base_append_sniffer (gdbarch, hppa_frame_base_sniffer);

  return gdbarch;
}

static void
hppa_dump_tdep (struct gdbarch *current_gdbarch, struct ui_file *file)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);

  fprintf_unfiltered (file, "bytes_per_address = %d\n", 
                      tdep->bytes_per_address);
  fprintf_unfiltered (file, "elf = %s\n", tdep->is_elf ? "yes" : "no");
}

void
_initialize_hppa_tdep (void)
{
  struct cmd_list_element *c;
  void break_at_finish_command (char *arg, int from_tty);
  void tbreak_at_finish_command (char *arg, int from_tty);
  void break_at_finish_at_depth_command (char *arg, int from_tty);

  gdbarch_register (bfd_arch_hppa, hppa_gdbarch_init, hppa_dump_tdep);

  hppa_objfile_priv_data = register_objfile_data ();

  add_cmd ("unwind", class_maintenance, unwind_command,
	   "Print unwind table entry at given address.",
	   &maintenanceprintlist);

  deprecate_cmd (add_com ("xbreak", class_breakpoint, 
			  break_at_finish_command,
			  concat ("Set breakpoint at procedure exit. \n\
Argument may be function name, or \"*\" and an address.\n\
If function is specified, break at end of code for that function.\n\
If an address is specified, break at the end of the function that contains \n\
that exact address.\n",
		   "With no arg, uses current execution address of selected stack frame.\n\
This is useful for breaking on return to a stack frame.\n\
\n\
Multiple breakpoints at one place are permitted, and useful if conditional.\n\
\n\
Do \"help breakpoints\" for info on other commands dealing with breakpoints.", NULL)), NULL);
  deprecate_cmd (add_com_alias ("xb", "xbreak", class_breakpoint, 1), NULL);
  deprecate_cmd (add_com_alias ("xbr", "xbreak", class_breakpoint, 1), NULL);
  deprecate_cmd (add_com_alias ("xbre", "xbreak", class_breakpoint, 1), NULL);
  deprecate_cmd (add_com_alias ("xbrea", "xbreak", class_breakpoint, 1), NULL);

  deprecate_cmd (c = add_com ("txbreak", class_breakpoint, 
			      tbreak_at_finish_command,
"Set temporary breakpoint at procedure exit.  Either there should\n\
be no argument or the argument must be a depth.\n"), NULL);
  set_cmd_completer (c, location_completer);
  
  if (xdb_commands)
    deprecate_cmd (add_com ("bx", class_breakpoint, 
			    break_at_finish_at_depth_command,
"Set breakpoint at procedure exit.  Either there should\n\
be no argument or the argument must be a depth.\n"), NULL);

  /* Debug this files internals. */
  add_show_from_set (add_set_cmd ("hppa", class_maintenance, var_zinteger,
				  &hppa_debug, "Set hppa debugging.\n\
When non-zero, hppa specific debugging is enabled.", &setdebuglist), &showdebuglist);
}

