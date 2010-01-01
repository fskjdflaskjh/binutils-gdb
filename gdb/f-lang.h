/* Fortran language support definitions for GDB, the GNU debugger.

   Copyright (C) 1992, 1993, 1994, 1995, 1998, 2000, 2005, 2007, 2008, 2009,
   2010 Free Software Foundation, Inc.

   Contributed by Motorola.  Adapted from the C definitions by Farooq Butt
   (fmbutt@engage.sps.mot.com).

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

extern int f_parse (void);

extern void f_error (char *);	/* Defined in f-exp.y */

extern void f_print_type (struct type *, char *, struct ui_file *, int,
			  int);

extern int f_val_print (struct type *, const gdb_byte *, int, CORE_ADDR,
			struct ui_file *, int,
			const struct value_print_options *);

/* Language-specific data structures */

/* In F90 subrange expression, either bound could be empty, indicating that
   its value is by default that of the corresponding bound of the array or
   string.  So we have four sorts of subrange in F90.  This enumeration type
   is to identify this.  */
   
enum f90_range_type
  {
    BOTH_BOUND_DEFAULT,		/* "(:)"  */
    LOW_BOUND_DEFAULT,		/* "(:high)"  */
    HIGH_BOUND_DEFAULT,		/* "(low:)"  */
    NONE_BOUND_DEFAULT		/* "(low:high)"  */
  };

struct common_entry
  {
    struct symbol *symbol;	/* The symbol node corresponding
				   to this component */
    struct common_entry *next;	/* The next component */
  };

struct saved_f77_common
  {
    char *name;			/* Name of COMMON */
    char *owning_function;	/* Name of parent function */
    int secnum;			/* Section # of .bss */
    CORE_ADDR offset;		/* Offset from .bss for 
				   this block */
    struct common_entry *entries;	/* List of block's components */
    struct common_entry *end_of_entries;	/* ptr. to end of components */
    struct saved_f77_common *next;	/* Next saved COMMON block */
  };

typedef struct saved_f77_common SAVED_F77_COMMON, *SAVED_F77_COMMON_PTR;

typedef struct common_entry COMMON_ENTRY, *COMMON_ENTRY_PTR;

extern SAVED_F77_COMMON_PTR head_common_list;	/* Ptr to 1st saved COMMON  */
extern SAVED_F77_COMMON_PTR tail_common_list;	/* Ptr to last saved COMMON  */
extern SAVED_F77_COMMON_PTR current_common;	/* Ptr to current COMMON */

extern SAVED_F77_COMMON_PTR find_common_for_function (char *, char *);

#define UNINITIALIZED_SECNUM -1
#define COMMON_NEEDS_PATCHING(blk) ((blk)->secnum == UNINITIALIZED_SECNUM)

#define BLANK_COMMON_NAME_ORIGINAL "#BLNK_COM"	/* XLF assigned  */
#define BLANK_COMMON_NAME_MF77     "__BLNK__"	/* MF77 assigned  */
#define BLANK_COMMON_NAME_LOCAL    "__BLANK"	/* Local GDB */

/* When reasonable array bounds cannot be fetched, such as when 
   you ask to 'mt print symbols' and there is no stack frame and 
   therefore no way of knowing the bounds of stack-based arrays, 
   we have to assign default bounds, these are as good as any... */

#define DEFAULT_UPPER_BOUND 999999
#define DEFAULT_LOWER_BOUND -999999

extern char *real_main_name;	/* Name of main function */
extern int real_main_c_value;	/* C_value field of main function */

extern int f77_get_upperbound (struct type *);

extern int f77_get_lowerbound (struct type *);

extern void f77_get_dynamic_array_length (struct type *);

extern int calc_f77_array_dims (struct type *);


/* Fortran (F77) types */

struct builtin_f_type
{
  struct type *builtin_character;
  struct type *builtin_integer;
  struct type *builtin_integer_s2;
  struct type *builtin_logical;
  struct type *builtin_logical_s1;
  struct type *builtin_logical_s2;
  struct type *builtin_real;
  struct type *builtin_real_s8;
  struct type *builtin_real_s16;
  struct type *builtin_complex_s8;
  struct type *builtin_complex_s16;
  struct type *builtin_complex_s32;
  struct type *builtin_void;
};

/* Return the Fortran type table for the specified architecture.  */
extern const struct builtin_f_type *builtin_f_type (struct gdbarch *gdbarch);

