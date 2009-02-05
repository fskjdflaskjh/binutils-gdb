/* C language support routines for GDB, the GNU debugger.

   Copyright (C) 1992, 1993, 1994, 1995, 1996, 1998, 1999, 2000, 2002, 2003,
   2004, 2005, 2007, 2008, 2009 Free Software Foundation, Inc.

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
#include "symtab.h"
#include "gdbtypes.h"
#include "expression.h"
#include "parser-defs.h"
#include "language.h"
#include "c-lang.h"
#include "valprint.h"
#include "macroscope.h"
#include "gdb_assert.h"
#include "charset.h"
#include "gdb_string.h"
#include "demangle.h"
#include "cp-abi.h"
#include "cp-support.h"

extern void _initialize_c_language (void);
static void c_emit_char (int c, struct ui_file * stream, int quoter);

/* Print the character C on STREAM as part of the contents of a literal
   string whose delimiter is QUOTER.  Note that that format for printing
   characters and strings is language specific. */

static void
c_emit_char (int c, struct ui_file *stream, int quoter)
{
  const char *escape;
  int host_char;

  c &= 0xFF;			/* Avoid sign bit follies */

  escape = c_target_char_has_backslash_escape (c);
  if (escape)
    {
      if (quoter == '"' && strcmp (escape, "0") == 0)
	/* Print nulls embedded in double quoted strings as \000 to
	   prevent ambiguity.  */
	fprintf_filtered (stream, "\\000");
      else
	fprintf_filtered (stream, "\\%s", escape);
    }
  else if (target_char_to_host (c, &host_char)
           && host_char_print_literally (host_char))
    {
      if (host_char == '\\' || host_char == quoter)
        fputs_filtered ("\\", stream);
      fprintf_filtered (stream, "%c", host_char);
    }
  else
    fprintf_filtered (stream, "\\%.3o", (unsigned int) c);
}

void
c_printchar (int c, struct ui_file *stream)
{
  fputc_filtered ('\'', stream);
  LA_EMIT_CHAR (c, stream, '\'');
  fputc_filtered ('\'', stream);
}

/* Print the character string STRING, printing at most LENGTH characters.
   LENGTH is -1 if the string is nul terminated.  Each character is WIDTH bytes
   long.  Printing stops early if the number hits print_max; repeat counts are
   printed as appropriate.  Print ellipses at the end if we had to stop before
   printing LENGTH characters, or if FORCE_ELLIPSES.  */

void
c_printstr (struct ui_file *stream, const gdb_byte *string,
	    unsigned int length, int width, int force_ellipses,
	    const struct value_print_options *options)
{
  unsigned int i;
  unsigned int things_printed = 0;
  int in_quotes = 0;
  int need_comma = 0;

  /* If the string was not truncated due to `set print elements', and
     the last byte of it is a null, we don't print that, in traditional C
     style.  */
  if (!force_ellipses
      && length > 0
      && (extract_unsigned_integer (string + (length - 1) * width, width)
          == '\0'))
    length--;

  if (length == 0)
    {
      fputs_filtered ("\"\"", stream);
      return;
    }

  for (i = 0; i < length && things_printed < options->print_max; ++i)
    {
      /* Position of the character we are examining
         to see whether it is repeated.  */
      unsigned int rep1;
      /* Number of repetitions we have detected so far.  */
      unsigned int reps;
      unsigned long current_char;

      QUIT;

      if (need_comma)
	{
	  fputs_filtered (", ", stream);
	  need_comma = 0;
	}

      current_char = extract_unsigned_integer (string + i * width, width);

      rep1 = i + 1;
      reps = 1;
      while (rep1 < length
	     && extract_unsigned_integer (string + rep1 * width, width)
	     == current_char)
	{
	  ++rep1;
	  ++reps;
	}

      if (reps > options->repeat_count_threshold)
	{
	  if (in_quotes)
	    {
	      if (options->inspect_it)
		fputs_filtered ("\\\", ", stream);
	      else
		fputs_filtered ("\", ", stream);
	      in_quotes = 0;
	    }
	  LA_PRINT_CHAR (current_char, stream);
	  fprintf_filtered (stream, _(" <repeats %u times>"), reps);
	  i = rep1 - 1;
	  things_printed += options->repeat_count_threshold;
	  need_comma = 1;
	}
      else
	{
	  if (!in_quotes)
	    {
	      if (options->inspect_it)
		fputs_filtered ("\\\"", stream);
	      else
		fputs_filtered ("\"", stream);
	      in_quotes = 1;
	    }
	  LA_EMIT_CHAR (current_char, stream, '"');
	  ++things_printed;
	}
    }

  /* Terminate the quotes if necessary.  */
  if (in_quotes)
    {
      if (options->inspect_it)
	fputs_filtered ("\\\"", stream);
      else
	fputs_filtered ("\"", stream);
    }

  if (force_ellipses || i < length)
    fputs_filtered ("...", stream);
}

/* Obtain a C string from the inferior storing it in a newly allocated
   buffer in BUFFER, which should be freed by the caller.  The string is
   read until a null character is found. If VALUE is an array with known
   length, the function will not read past the end of the array.  LENGTH
   will contain the size of the string in bytes (not counting the null
   character).

   Assumes strings are terminated by a null character.  The size of a character
   is determined by the length of the target type of the pointer or array.
   This means that a null byte present in a multi-byte character will not
   terminate the string unless the whole character is null.

   CHARSET is always set to the target charset.  */

void
c_get_string (struct value *value, gdb_byte **buffer, int *length,
	      const char **charset)
{
  int err, width;
  unsigned int fetchlimit;
  struct type *type = check_typedef (value_type (value));
  struct type *element_type = TYPE_TARGET_TYPE (type);

  if (element_type == NULL)
    goto error;

  if (TYPE_CODE (type) == TYPE_CODE_ARRAY)
    {
      /* If we know the size of the array, we can use it as a limit on the
	 number of characters to be fetched.  */
      if (TYPE_NFIELDS (type) == 1
	  && TYPE_CODE (TYPE_FIELD_TYPE (type, 0)) == TYPE_CODE_RANGE)
	{
	  LONGEST low_bound, high_bound;

	  get_discrete_bounds (TYPE_FIELD_TYPE (type, 0),
			       &low_bound, &high_bound);
	  fetchlimit = high_bound - low_bound + 1;
	}
      else
	fetchlimit = UINT_MAX;
    }
  else if (TYPE_CODE (type) == TYPE_CODE_PTR)
    fetchlimit = UINT_MAX;
  else
    /* We work only with arrays and pointers.  */
    goto error;

  element_type = check_typedef (element_type);
  if (TYPE_CODE (element_type) != TYPE_CODE_INT
      && TYPE_CODE (element_type) != TYPE_CODE_CHAR)
    /* If the elements are not integers or characters, we don't consider it
       a string.  */
    goto error;

  width = TYPE_LENGTH (element_type);

  /* If the string lives in GDB's memory intead of the inferior's, then we
     just need to copy it to BUFFER.  Also, since such strings are arrays
     with known size, FETCHLIMIT will hold the size of the array.  */
  if ((VALUE_LVAL (value) == not_lval
       || VALUE_LVAL (value) == lval_internalvar)
      && fetchlimit != UINT_MAX)
    {
      int i;
      const gdb_byte *contents = value_contents (value);

      /* Look for a null character.  */
      for (i = 0; i < fetchlimit; i++)
	if (extract_unsigned_integer (contents + i * width, width) == 0)
	  break;

      /* I is now either the number of non-null characters, or FETCHLIMIT.  */
      *length = i * width;
      *buffer = xmalloc (*length);
      memcpy (*buffer, contents, *length);
      err = 0;
    }
  else
    {
      err = read_string (value_as_address (value), -1, width, fetchlimit,
			 buffer, length);
      if (err)
	{
	  xfree (buffer);
	  error (_("Error reading string from inferior: %s"),
		 safe_strerror (err));
	}
    }

  /* If the last character is null, subtract it from LENGTH.  */
  if (*length > 0
      && extract_unsigned_integer (*buffer + *length - width, width) == 0)
    *length -= width;

  *charset = target_charset ();

  return;

 error:
  {
    char *type_str;

    type_str = type_to_string (type);
    if (type_str)
      {
	make_cleanup (xfree, type_str);
	error (_("Trying to read string with inappropriate type `%s'."),
	       type_str);
      }
    else
      error (_("Trying to read string with inappropriate type."));
  }
}


/* Preprocessing and parsing C and C++ expressions.  */



/* Table mapping opcodes into strings for printing operators
   and precedences of the operators.  */

const struct op_print c_op_print_tab[] =
{
  {",", BINOP_COMMA, PREC_COMMA, 0},
  {"=", BINOP_ASSIGN, PREC_ASSIGN, 1},
  {"||", BINOP_LOGICAL_OR, PREC_LOGICAL_OR, 0},
  {"&&", BINOP_LOGICAL_AND, PREC_LOGICAL_AND, 0},
  {"|", BINOP_BITWISE_IOR, PREC_BITWISE_IOR, 0},
  {"^", BINOP_BITWISE_XOR, PREC_BITWISE_XOR, 0},
  {"&", BINOP_BITWISE_AND, PREC_BITWISE_AND, 0},
  {"==", BINOP_EQUAL, PREC_EQUAL, 0},
  {"!=", BINOP_NOTEQUAL, PREC_EQUAL, 0},
  {"<=", BINOP_LEQ, PREC_ORDER, 0},
  {">=", BINOP_GEQ, PREC_ORDER, 0},
  {">", BINOP_GTR, PREC_ORDER, 0},
  {"<", BINOP_LESS, PREC_ORDER, 0},
  {">>", BINOP_RSH, PREC_SHIFT, 0},
  {"<<", BINOP_LSH, PREC_SHIFT, 0},
  {"+", BINOP_ADD, PREC_ADD, 0},
  {"-", BINOP_SUB, PREC_ADD, 0},
  {"*", BINOP_MUL, PREC_MUL, 0},
  {"/", BINOP_DIV, PREC_MUL, 0},
  {"%", BINOP_REM, PREC_MUL, 0},
  {"@", BINOP_REPEAT, PREC_REPEAT, 0},
  {"-", UNOP_NEG, PREC_PREFIX, 0},
  {"!", UNOP_LOGICAL_NOT, PREC_PREFIX, 0},
  {"~", UNOP_COMPLEMENT, PREC_PREFIX, 0},
  {"*", UNOP_IND, PREC_PREFIX, 0},
  {"&", UNOP_ADDR, PREC_PREFIX, 0},
  {"sizeof ", UNOP_SIZEOF, PREC_PREFIX, 0},
  {"++", UNOP_PREINCREMENT, PREC_PREFIX, 0},
  {"--", UNOP_PREDECREMENT, PREC_PREFIX, 0},
  {NULL, 0, 0, 0}
};

enum c_primitive_types {
  c_primitive_type_int,
  c_primitive_type_long,
  c_primitive_type_short,
  c_primitive_type_char,
  c_primitive_type_float,
  c_primitive_type_double,
  c_primitive_type_void,
  c_primitive_type_long_long,
  c_primitive_type_signed_char,
  c_primitive_type_unsigned_char,
  c_primitive_type_unsigned_short,
  c_primitive_type_unsigned_int,
  c_primitive_type_unsigned_long,
  c_primitive_type_unsigned_long_long,
  c_primitive_type_long_double,
  c_primitive_type_complex,
  c_primitive_type_double_complex,
  c_primitive_type_decfloat,
  c_primitive_type_decdouble,
  c_primitive_type_declong,
  nr_c_primitive_types
};

void
c_language_arch_info (struct gdbarch *gdbarch,
		      struct language_arch_info *lai)
{
  const struct builtin_type *builtin = builtin_type (gdbarch);
  lai->string_char_type = builtin->builtin_char;
  lai->primitive_type_vector
    = GDBARCH_OBSTACK_CALLOC (gdbarch, nr_c_primitive_types + 1,
			      struct type *);
  lai->primitive_type_vector [c_primitive_type_int] = builtin->builtin_int;
  lai->primitive_type_vector [c_primitive_type_long] = builtin->builtin_long;
  lai->primitive_type_vector [c_primitive_type_short] = builtin->builtin_short;
  lai->primitive_type_vector [c_primitive_type_char] = builtin->builtin_char;
  lai->primitive_type_vector [c_primitive_type_float] = builtin->builtin_float;
  lai->primitive_type_vector [c_primitive_type_double] = builtin->builtin_double;
  lai->primitive_type_vector [c_primitive_type_void] = builtin->builtin_void;
  lai->primitive_type_vector [c_primitive_type_long_long] = builtin->builtin_long_long;
  lai->primitive_type_vector [c_primitive_type_signed_char] = builtin->builtin_signed_char;
  lai->primitive_type_vector [c_primitive_type_unsigned_char] = builtin->builtin_unsigned_char;
  lai->primitive_type_vector [c_primitive_type_unsigned_short] = builtin->builtin_unsigned_short;
  lai->primitive_type_vector [c_primitive_type_unsigned_int] = builtin->builtin_unsigned_int;
  lai->primitive_type_vector [c_primitive_type_unsigned_long] = builtin->builtin_unsigned_long;
  lai->primitive_type_vector [c_primitive_type_unsigned_long_long] = builtin->builtin_unsigned_long_long;
  lai->primitive_type_vector [c_primitive_type_long_double] = builtin->builtin_long_double;
  lai->primitive_type_vector [c_primitive_type_complex] = builtin->builtin_complex;
  lai->primitive_type_vector [c_primitive_type_double_complex] = builtin->builtin_double_complex;
  lai->primitive_type_vector [c_primitive_type_decfloat] = builtin->builtin_decfloat;
  lai->primitive_type_vector [c_primitive_type_decdouble] = builtin->builtin_decdouble;
  lai->primitive_type_vector [c_primitive_type_declong] = builtin->builtin_declong;

  lai->bool_type_default = builtin->builtin_int;
}

const struct language_defn c_language_defn =
{
  "c",				/* Language name */
  language_c,
  range_check_off,
  type_check_off,
  case_sensitive_on,
  array_row_major,
  macro_expansion_c,
  &exp_descriptor_standard,
  c_parse,
  c_error,
  null_post_parser,
  c_printchar,			/* Print a character constant */
  c_printstr,			/* Function to print string constant */
  c_emit_char,			/* Print a single char */
  c_print_type,			/* Print a type using appropriate syntax */
  c_print_typedef,		/* Print a typedef using appropriate syntax */
  c_val_print,			/* Print a value using appropriate syntax */
  c_value_print,		/* Print a top-level value */
  NULL,				/* Language specific skip_trampoline */
  NULL,				/* name_of_this */
  basic_lookup_symbol_nonlocal,	/* lookup_symbol_nonlocal */
  basic_lookup_transparent_type,/* lookup_transparent_type */
  NULL,				/* Language specific symbol demangler */
  NULL,				/* Language specific class_name_from_physname */
  c_op_print_tab,		/* expression operators for printing */
  1,				/* c-style arrays */
  0,				/* String lower bound */
  default_word_break_characters,
  default_make_symbol_completion_list,
  c_language_arch_info,
  default_print_array_index,
  default_pass_by_reference,
  c_get_string,
  LANG_MAGIC
};

enum cplus_primitive_types {
  cplus_primitive_type_int,
  cplus_primitive_type_long,
  cplus_primitive_type_short,
  cplus_primitive_type_char,
  cplus_primitive_type_float,
  cplus_primitive_type_double,
  cplus_primitive_type_void,
  cplus_primitive_type_long_long,
  cplus_primitive_type_signed_char,
  cplus_primitive_type_unsigned_char,
  cplus_primitive_type_unsigned_short,
  cplus_primitive_type_unsigned_int,
  cplus_primitive_type_unsigned_long,
  cplus_primitive_type_unsigned_long_long,
  cplus_primitive_type_long_double,
  cplus_primitive_type_complex,
  cplus_primitive_type_double_complex,
  cplus_primitive_type_bool,
  cplus_primitive_type_decfloat,
  cplus_primitive_type_decdouble,
  cplus_primitive_type_declong,
  nr_cplus_primitive_types
};

static void
cplus_language_arch_info (struct gdbarch *gdbarch,
			  struct language_arch_info *lai)
{
  const struct builtin_type *builtin = builtin_type (gdbarch);
  lai->string_char_type = builtin->builtin_char;
  lai->primitive_type_vector
    = GDBARCH_OBSTACK_CALLOC (gdbarch, nr_cplus_primitive_types + 1,
			      struct type *);
  lai->primitive_type_vector [cplus_primitive_type_int]
    = builtin->builtin_int;
  lai->primitive_type_vector [cplus_primitive_type_long]
    = builtin->builtin_long;
  lai->primitive_type_vector [cplus_primitive_type_short]
    = builtin->builtin_short;
  lai->primitive_type_vector [cplus_primitive_type_char]
    = builtin->builtin_char;
  lai->primitive_type_vector [cplus_primitive_type_float]
    = builtin->builtin_float;
  lai->primitive_type_vector [cplus_primitive_type_double]
    = builtin->builtin_double;
  lai->primitive_type_vector [cplus_primitive_type_void]
    = builtin->builtin_void;
  lai->primitive_type_vector [cplus_primitive_type_long_long]
    = builtin->builtin_long_long;
  lai->primitive_type_vector [cplus_primitive_type_signed_char]
    = builtin->builtin_signed_char;
  lai->primitive_type_vector [cplus_primitive_type_unsigned_char]
    = builtin->builtin_unsigned_char;
  lai->primitive_type_vector [cplus_primitive_type_unsigned_short]
    = builtin->builtin_unsigned_short;
  lai->primitive_type_vector [cplus_primitive_type_unsigned_int]
    = builtin->builtin_unsigned_int;
  lai->primitive_type_vector [cplus_primitive_type_unsigned_long]
    = builtin->builtin_unsigned_long;
  lai->primitive_type_vector [cplus_primitive_type_unsigned_long_long]
    = builtin->builtin_unsigned_long_long;
  lai->primitive_type_vector [cplus_primitive_type_long_double]
    = builtin->builtin_long_double;
  lai->primitive_type_vector [cplus_primitive_type_complex]
    = builtin->builtin_complex;
  lai->primitive_type_vector [cplus_primitive_type_double_complex]
    = builtin->builtin_double_complex;
  lai->primitive_type_vector [cplus_primitive_type_bool]
    = builtin->builtin_bool;
  lai->primitive_type_vector [cplus_primitive_type_decfloat]
    = builtin->builtin_decfloat;
  lai->primitive_type_vector [cplus_primitive_type_decdouble]
    = builtin->builtin_decdouble;
  lai->primitive_type_vector [cplus_primitive_type_declong]
    = builtin->builtin_declong;

  lai->bool_type_symbol = "bool";
  lai->bool_type_default = builtin->builtin_bool;
}

const struct language_defn cplus_language_defn =
{
  "c++",			/* Language name */
  language_cplus,
  range_check_off,
  type_check_off,
  case_sensitive_on,
  array_row_major,
  macro_expansion_c,
  &exp_descriptor_standard,
  c_parse,
  c_error,
  null_post_parser,
  c_printchar,			/* Print a character constant */
  c_printstr,			/* Function to print string constant */
  c_emit_char,			/* Print a single char */
  c_print_type,			/* Print a type using appropriate syntax */
  c_print_typedef,		/* Print a typedef using appropriate syntax */
  c_val_print,			/* Print a value using appropriate syntax */
  c_value_print,		/* Print a top-level value */
  cplus_skip_trampoline,	/* Language specific skip_trampoline */
  "this",                       /* name_of_this */
  cp_lookup_symbol_nonlocal,	/* lookup_symbol_nonlocal */
  cp_lookup_transparent_type,   /* lookup_transparent_type */
  cplus_demangle,		/* Language specific symbol demangler */
  cp_class_name_from_physname,  /* Language specific class_name_from_physname */
  c_op_print_tab,		/* expression operators for printing */
  1,				/* c-style arrays */
  0,				/* String lower bound */
  default_word_break_characters,
  default_make_symbol_completion_list,
  cplus_language_arch_info,
  default_print_array_index,
  cp_pass_by_reference,
  c_get_string,
  LANG_MAGIC
};

const struct language_defn asm_language_defn =
{
  "asm",			/* Language name */
  language_asm,
  range_check_off,
  type_check_off,
  case_sensitive_on,
  array_row_major,
  macro_expansion_c,
  &exp_descriptor_standard,
  c_parse,
  c_error,
  null_post_parser,
  c_printchar,			/* Print a character constant */
  c_printstr,			/* Function to print string constant */
  c_emit_char,			/* Print a single char */
  c_print_type,			/* Print a type using appropriate syntax */
  c_print_typedef,		/* Print a typedef using appropriate syntax */
  c_val_print,			/* Print a value using appropriate syntax */
  c_value_print,		/* Print a top-level value */
  NULL,				/* Language specific skip_trampoline */
  NULL,				/* name_of_this */
  basic_lookup_symbol_nonlocal,	/* lookup_symbol_nonlocal */
  basic_lookup_transparent_type,/* lookup_transparent_type */
  NULL,				/* Language specific symbol demangler */
  NULL,				/* Language specific class_name_from_physname */
  c_op_print_tab,		/* expression operators for printing */
  1,				/* c-style arrays */
  0,				/* String lower bound */
  default_word_break_characters,
  default_make_symbol_completion_list,
  c_language_arch_info, /* FIXME: la_language_arch_info.  */
  default_print_array_index,
  default_pass_by_reference,
  c_get_string,
  LANG_MAGIC
};

/* The following language_defn does not represent a real language.
   It just provides a minimal support a-la-C that should allow users
   to do some simple operations when debugging applications that use
   a language currently not supported by GDB.  */

const struct language_defn minimal_language_defn =
{
  "minimal",			/* Language name */
  language_minimal,
  range_check_off,
  type_check_off,
  case_sensitive_on,
  array_row_major,
  macro_expansion_c,
  &exp_descriptor_standard,
  c_parse,
  c_error,
  null_post_parser,
  c_printchar,			/* Print a character constant */
  c_printstr,			/* Function to print string constant */
  c_emit_char,			/* Print a single char */
  c_print_type,			/* Print a type using appropriate syntax */
  c_print_typedef,		/* Print a typedef using appropriate syntax */
  c_val_print,			/* Print a value using appropriate syntax */
  c_value_print,		/* Print a top-level value */
  NULL,				/* Language specific skip_trampoline */
  NULL,				/* name_of_this */
  basic_lookup_symbol_nonlocal,	/* lookup_symbol_nonlocal */
  basic_lookup_transparent_type,/* lookup_transparent_type */
  NULL,				/* Language specific symbol demangler */
  NULL,				/* Language specific class_name_from_physname */
  c_op_print_tab,		/* expression operators for printing */
  1,				/* c-style arrays */
  0,				/* String lower bound */
  default_word_break_characters,
  default_make_symbol_completion_list,
  c_language_arch_info,
  default_print_array_index,
  default_pass_by_reference,
  c_get_string,
  LANG_MAGIC
};

void
_initialize_c_language (void)
{
  add_language (&c_language_defn);
  add_language (&cplus_language_defn);
  add_language (&asm_language_defn);
  add_language (&minimal_language_defn);
}
