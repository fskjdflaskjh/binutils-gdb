/* Assembler interface for targets using CGEN. -*- C -*-
   CGEN: Cpu tools GENerator

THIS FILE IS MACHINE GENERATED WITH CGEN.
- the resultant file is machine generated, cgen-asm.in isn't

Copyright (C) 1996, 1997, 1998, 1999 Free Software Foundation, Inc.

This file is part of the GNU Binutils and GDB, the GNU debugger.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation, Inc.,
59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

/* ??? Eventually more and more of this stuff can go to cpu-independent files.
   Keep that in mind.  */

#include "sysdep.h"
#include <ctype.h>
#include <stdio.h>
#include "ansidecl.h"
#include "bfd.h"
#include "symcat.h"
#include "m32r-desc.h"
#include "m32r-opc.h"
#include "opintl.h"

#undef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#undef max
#define max(a,b) ((a) > (b) ? (a) : (b))

static const char * parse_insn_normal
     PARAMS ((CGEN_CPU_DESC, const CGEN_INSN *, const char **, CGEN_FIELDS *));

/* -- assembler routines inserted here */

/* -- asm.c */

/* Handle '#' prefixes (i.e. skip over them).  */

static const char *
parse_hash (cd, strp, opindex, valuep)
     CGEN_CPU_DESC cd;
     const char **strp;
     int opindex;
     unsigned long *valuep;
{
  if (**strp == '#')
    ++*strp;
  return NULL;
}

/* Handle shigh(), high().  */

static const char *
parse_hi16 (cd, strp, opindex, valuep)
     CGEN_CPU_DESC cd;
     const char **strp;
     int opindex;
     unsigned long *valuep;
{
  const char *errmsg;
  enum cgen_parse_operand_result result_type;
  bfd_vma value;

  if (**strp == '#')
    ++*strp;

  if (strncasecmp (*strp, "high(", 5) == 0)
    {
      *strp += 5;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_M32R_HI16_ULO,
				   &result_type, &value);
      if (**strp != ')')
	return "missing `)'";
      ++*strp;
      if (errmsg == NULL
  	  && result_type == CGEN_PARSE_OPERAND_RESULT_NUMBER)
	value >>= 16;
      *valuep = value;
      return errmsg;
    }
  else if (strncasecmp (*strp, "shigh(", 6) == 0)
    {
      *strp += 6;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_M32R_HI16_SLO,
 				   &result_type, &value);
      if (**strp != ')')
	return "missing `)'";
      ++*strp;
      if (errmsg == NULL
	  && result_type == CGEN_PARSE_OPERAND_RESULT_NUMBER)
	value = (value >> 16) + (value & 0x8000 ? 1 : 0);
      *valuep = value;
      return errmsg;
    }

  return cgen_parse_unsigned_integer (cd, strp, opindex, valuep);
}

/* Handle low() in a signed context.  Also handle sda().
   The signedness of the value doesn't matter to low(), but this also
   handles the case where low() isn't present.  */

static const char *
parse_slo16 (cd, strp, opindex, valuep)
     CGEN_CPU_DESC cd;
     const char **strp;
     int opindex;
     long *valuep;
{
  const char *errmsg;
  enum cgen_parse_operand_result result_type;
  bfd_vma value;

  if (**strp == '#')
    ++*strp;

  if (strncasecmp (*strp, "low(", 4) == 0)
    {
      *strp += 4;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_M32R_LO16,
				   &result_type, &value);
      if (**strp != ')')
	return "missing `)'";
      ++*strp;
      if (errmsg == NULL
	  && result_type == CGEN_PARSE_OPERAND_RESULT_NUMBER)
	value &= 0xffff;
      *valuep = value;
      return errmsg;
    }

  if (strncasecmp (*strp, "sda(", 4) == 0)
    {
      *strp += 4;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_M32R_SDA16,
				   NULL, &value);
      if (**strp != ')')
	return "missing `)'";
      ++*strp;
      *valuep = value;
      return errmsg;
    }

  return cgen_parse_signed_integer (cd, strp, opindex, valuep);
}

/* Handle low() in an unsigned context.
   The signedness of the value doesn't matter to low(), but this also
   handles the case where low() isn't present.  */

static const char *
parse_ulo16 (cd, strp, opindex, valuep)
     CGEN_CPU_DESC cd;
     const char **strp;
     int opindex;
     unsigned long *valuep;
{
  const char *errmsg;
  enum cgen_parse_operand_result result_type;
  bfd_vma value;

  if (**strp == '#')
    ++*strp;

  if (strncasecmp (*strp, "low(", 4) == 0)
    {
      *strp += 4;
      errmsg = cgen_parse_address (cd, strp, opindex, BFD_RELOC_M32R_LO16,
				   &result_type, &value);
      if (**strp != ')')
	return "missing `)'";
      ++*strp;
      if (errmsg == NULL
	  && result_type == CGEN_PARSE_OPERAND_RESULT_NUMBER)
	value &= 0xffff;
      *valuep = value;
      return errmsg;
    }

  return cgen_parse_unsigned_integer (cd, strp, opindex, valuep);
}

/* -- */

/* Main entry point for operand parsing.

   This function is basically just a big switch statement.  Earlier versions
   used tables to look up the function to use, but
   - if the table contains both assembler and disassembler functions then
     the disassembler contains much of the assembler and vice-versa,
   - there's a lot of inlining possibilities as things grow,
   - using a switch statement avoids the function call overhead.

   This function could be moved into `parse_insn_normal', but keeping it
   separate makes clear the interface between `parse_insn_normal' and each of
   the handlers.
*/

const char *
m32r_cgen_parse_operand (cd, opindex, strp, fields)
     CGEN_CPU_DESC cd;
     int opindex;
     const char ** strp;
     CGEN_FIELDS * fields;
{
  const char * errmsg;

  switch (opindex)
    {
    case M32R_OPERAND_DCR :
      errmsg = cgen_parse_keyword (cd, strp, & m32r_cgen_opval_cr_names, & fields->f_r1);
      break;
    case M32R_OPERAND_DISP16 :
      {
        bfd_vma value;
        errmsg = cgen_parse_address (cd, strp, M32R_OPERAND_DISP16, 0, NULL,  & value);
        fields->f_disp16 = value;
      }
      break;
    case M32R_OPERAND_DISP24 :
      {
        bfd_vma value;
        errmsg = cgen_parse_address (cd, strp, M32R_OPERAND_DISP24, 0, NULL,  & value);
        fields->f_disp24 = value;
      }
      break;
    case M32R_OPERAND_DISP8 :
      {
        bfd_vma value;
        errmsg = cgen_parse_address (cd, strp, M32R_OPERAND_DISP8, 0, NULL,  & value);
        fields->f_disp8 = value;
      }
      break;
    case M32R_OPERAND_DR :
      errmsg = cgen_parse_keyword (cd, strp, & m32r_cgen_opval_gr_names, & fields->f_r1);
      break;
    case M32R_OPERAND_HASH :
      errmsg = parse_hash (cd, strp, M32R_OPERAND_HASH, &fields->f_nil);
      break;
    case M32R_OPERAND_HI16 :
      errmsg = parse_hi16 (cd, strp, M32R_OPERAND_HI16, &fields->f_hi16);
      break;
    case M32R_OPERAND_SCR :
      errmsg = cgen_parse_keyword (cd, strp, & m32r_cgen_opval_cr_names, & fields->f_r2);
      break;
    case M32R_OPERAND_SIMM16 :
      errmsg = cgen_parse_signed_integer (cd, strp, M32R_OPERAND_SIMM16, &fields->f_simm16);
      break;
    case M32R_OPERAND_SIMM8 :
      errmsg = cgen_parse_signed_integer (cd, strp, M32R_OPERAND_SIMM8, &fields->f_simm8);
      break;
    case M32R_OPERAND_SLO16 :
      errmsg = parse_slo16 (cd, strp, M32R_OPERAND_SLO16, &fields->f_simm16);
      break;
    case M32R_OPERAND_SR :
      errmsg = cgen_parse_keyword (cd, strp, & m32r_cgen_opval_gr_names, & fields->f_r2);
      break;
    case M32R_OPERAND_SRC1 :
      errmsg = cgen_parse_keyword (cd, strp, & m32r_cgen_opval_gr_names, & fields->f_r1);
      break;
    case M32R_OPERAND_SRC2 :
      errmsg = cgen_parse_keyword (cd, strp, & m32r_cgen_opval_gr_names, & fields->f_r2);
      break;
    case M32R_OPERAND_UIMM16 :
      errmsg = cgen_parse_unsigned_integer (cd, strp, M32R_OPERAND_UIMM16, &fields->f_uimm16);
      break;
    case M32R_OPERAND_UIMM24 :
      {
        bfd_vma value;
        errmsg = cgen_parse_address (cd, strp, M32R_OPERAND_UIMM24, 0, NULL,  & value);
        fields->f_uimm24 = value;
      }
      break;
    case M32R_OPERAND_UIMM4 :
      errmsg = cgen_parse_unsigned_integer (cd, strp, M32R_OPERAND_UIMM4, &fields->f_uimm4);
      break;
    case M32R_OPERAND_UIMM5 :
      errmsg = cgen_parse_unsigned_integer (cd, strp, M32R_OPERAND_UIMM5, &fields->f_uimm5);
      break;
    case M32R_OPERAND_ULO16 :
      errmsg = parse_ulo16 (cd, strp, M32R_OPERAND_ULO16, &fields->f_uimm16);
      break;

    default :
      /* xgettext:c-format */
      fprintf (stderr, _("Unrecognized field %d while parsing.\n"), opindex);
      abort ();
  }

  return errmsg;
}

cgen_parse_fn * const m32r_cgen_parse_handlers[] = 
{
  parse_insn_normal,
};

void
m32r_cgen_init_asm (cd)
     CGEN_CPU_DESC cd;
{
  m32r_cgen_init_opcode_table (cd);
  m32r_cgen_init_ibld_table (cd);
  cd->parse_handlers = & m32r_cgen_parse_handlers[0];
  cd->parse_operand = m32r_cgen_parse_operand;
}


/* Default insn parser.

   The syntax string is scanned and operands are parsed and stored in FIELDS.
   Relocs are queued as we go via other callbacks.

   ??? Note that this is currently an all-or-nothing parser.  If we fail to
   parse the instruction, we return 0 and the caller will start over from
   the beginning.  Backtracking will be necessary in parsing subexpressions,
   but that can be handled there.  Not handling backtracking here may get
   expensive in the case of the m68k.  Deal with later.

   Returns NULL for success, an error message for failure.
*/

static const char *
parse_insn_normal (cd, insn, strp, fields)
     CGEN_CPU_DESC cd;
     const CGEN_INSN *insn;
     const char **strp;
     CGEN_FIELDS *fields;
{
  /* ??? Runtime added insns not handled yet.  */
  const CGEN_SYNTAX *syntax = CGEN_INSN_SYNTAX (insn);
  const char *str = *strp;
  const char *errmsg;
  const char *p;
  const unsigned char * syn;
#ifdef CGEN_MNEMONIC_OPERANDS
  /* FIXME: wip */
  int past_opcode_p;
#endif

  /* For now we assume the mnemonic is first (there are no leading operands).
     We can parse it without needing to set up operand parsing.
     GAS's input scrubber will ensure mnemonics are lowercase, but we may
     not be called from GAS.  */
  p = CGEN_INSN_MNEMONIC (insn);
  while (*p && tolower (*p) == tolower (*str))
    ++p, ++str;
  
  if (* p || (* str && !isspace (* str)))
    return _("unrecognized instruction");

  CGEN_INIT_PARSE (cd);
  cgen_init_parse_operand (cd);
#ifdef CGEN_MNEMONIC_OPERANDS
  past_opcode_p = 0;
#endif

  /* We don't check for (*str != '\0') here because we want to parse
     any trailing fake arguments in the syntax string.  */
  syn = CGEN_SYNTAX_STRING (syntax);

  /* Mnemonics come first for now, ensure valid string.  */
  if (! CGEN_SYNTAX_MNEMONIC_P (* syn))
    abort ();

  ++syn;

  while (* syn != 0)
    {
      /* Non operand chars must match exactly.  */
      if (CGEN_SYNTAX_CHAR_P (* syn))
	{
	  if (*str == CGEN_SYNTAX_CHAR (* syn))
	    {
#ifdef CGEN_MNEMONIC_OPERANDS
	      if (* syn == ' ')
		past_opcode_p = 1;
#endif
	      ++ syn;
	      ++ str;
	    }
	  else
	    {
	      /* Syntax char didn't match.  Can't be this insn.  */
	      /* FIXME: would like to return something like
		 "expected char `c'" */
	      return _("syntax error");
	    }
	  continue;
	}

      /* We have an operand of some sort.  */
      errmsg = m32r_cgen_parse_operand (cd, CGEN_SYNTAX_FIELD (*syn),
					  &str, fields);
      if (errmsg)
	return errmsg;

      /* Done with this operand, continue with next one.  */
      ++ syn;
    }

  /* If we're at the end of the syntax string, we're done.  */
  if (* syn == '\0')
    {
      /* FIXME: For the moment we assume a valid `str' can only contain
	 blanks now.  IE: We needn't try again with a longer version of
	 the insn and it is assumed that longer versions of insns appear
	 before shorter ones (eg: lsr r2,r3,1 vs lsr r2,r3).  */
      while (isspace (* str))
	++ str;

      if (* str != '\0')
	return _("junk at end of line"); /* FIXME: would like to include `str' */

      return NULL;
    }

  /* We couldn't parse it.  */
  return _("unrecognized instruction");
}

/* Main entry point.
   This routine is called for each instruction to be assembled.
   STR points to the insn to be assembled.
   We assume all necessary tables have been initialized.
   The assembled instruction, less any fixups, is stored in BUF.
   Remember that if CGEN_INT_INSN_P then BUF is an int and thus the value
   still needs to be converted to target byte order, otherwise BUF is an array
   of bytes in target byte order.
   The result is a pointer to the insn's entry in the opcode table,
   or NULL if an error occured (an error message will have already been
   printed).

   Note that when processing (non-alias) macro-insns,
   this function recurses.

   ??? It's possible to make this cpu-independent.
   One would have to deal with a few minor things.
   At this point in time doing so would be more of a curiosity than useful
   [for example this file isn't _that_ big], but keeping the possibility in
   mind helps keep the design clean.  */

const CGEN_INSN *
m32r_cgen_assemble_insn (cd, str, fields, buf, errmsg)
     CGEN_CPU_DESC cd;
     const char *str;
     CGEN_FIELDS *fields;
     CGEN_INSN_BYTES_PTR buf;
     char **errmsg;
{
  const char *start;
  CGEN_INSN_LIST *ilist;

  /* Skip leading white space.  */
  while (isspace (* str))
    ++ str;

  /* The instructions are stored in hashed lists.
     Get the first in the list.  */
  ilist = CGEN_ASM_LOOKUP_INSN (cd, str);

  /* Keep looking until we find a match.  */

  start = str;
  for ( ; ilist != NULL ; ilist = CGEN_ASM_NEXT_INSN (ilist))
    {
      const CGEN_INSN *insn = ilist->insn;

#if 0 /* not needed as unsupported opcodes shouldn't be in the hash lists */
      /* Is this insn supported by the selected cpu?  */
      if (! m32r_cgen_insn_supported (cd, insn))
	continue;
#endif

      /* If the RELAX attribute is set, this is an insn that shouldn't be
	 chosen immediately.  Instead, it is used during assembler/linker
	 relaxation if possible.  */
      if (CGEN_INSN_ATTR_VALUE (insn, CGEN_INSN_RELAX) != 0)
	continue;

      str = start;

      /* Allow parse/insert handlers to obtain length of insn.  */
      CGEN_FIELDS_BITSIZE (fields) = CGEN_INSN_BITSIZE (insn);

      if (! CGEN_PARSE_FN (cd, insn) (cd, insn, & str, fields))
	{
	  /* ??? 0 is passed for `pc' */
	  if (CGEN_INSERT_FN (cd, insn) (cd, insn, fields, buf, (bfd_vma) 0)
	      != NULL)
	    continue;
	  /* It is up to the caller to actually output the insn and any
	     queued relocs.  */
	  return insn;
	}

      /* Try the next entry.  */
    }

  /* FIXME: We can return a better error message than this.
     Need to track why it failed and pick the right one.  */
  {
    static char errbuf[100];
    if (strlen (start) > 50)
      /* xgettext:c-format */
      sprintf (errbuf, _("bad instruction `%.50s...'"), start);
    else 
      /* xgettext:c-format */
      sprintf (errbuf, _("bad instruction `%.50s'"), start);
      
    *errmsg = errbuf;
    return NULL;
  }
}

#if 0 /* This calls back to GAS which we can't do without care.  */

/* Record each member of OPVALS in the assembler's symbol table.
   This lets GAS parse registers for us.
   ??? Interesting idea but not currently used.  */

/* Record each member of OPVALS in the assembler's symbol table.
   FIXME: Not currently used.  */

void
m32r_cgen_asm_hash_keywords (cd, opvals)
     CGEN_CPU_DESC cd;
     CGEN_KEYWORD *opvals;
{
  CGEN_KEYWORD_SEARCH search = cgen_keyword_search_init (opvals, NULL);
  const CGEN_KEYWORD_ENTRY * ke;

  while ((ke = cgen_keyword_search_next (& search)) != NULL)
    {
#if 0 /* Unnecessary, should be done in the search routine.  */
      if (! m32r_cgen_opval_supported (ke))
	continue;
#endif
      cgen_asm_record_register (cd, ke->name, ke->value);
    }
}

#endif /* 0 */
