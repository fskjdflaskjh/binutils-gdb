/* *INDENT-OFF* */ /* ATTR_FORMAT confuses indent, avoid running it for now */
/* Basic, host-specific, and target-specific definitions for GDB.
   Copyright 1986, 1988, 1989, 1990, 1991, 1992, 1993, 1994, 1995, 1996,
   1997, 1998, 1999, 2000, 2001, 2002
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

#ifndef DEFS_H
#define DEFS_H

#include "config.h"		/* Generated by configure */
#include <stdio.h>
#include <errno.h>		/* System call error return status */
#include <limits.h>

#ifdef HAVE_STDDEF_H
#include <stddef.h>
#else
#include <sys/types.h>		/* for size_t */
#endif

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

/* For ``enum target_signal''.  */
#include "gdb/signals.h"

/* Just in case they're not defined in stdio.h. */

#ifndef SEEK_SET
#define SEEK_SET 0
#endif
#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif

/* First include ansidecl.h so we can use the various macro definitions
   here and in all subsequent file inclusions.  */

#include "ansidecl.h"

#include <stdarg.h>		/* for va_list */

#include "libiberty.h"

#include "progress.h"

/* For BFD64 and bfd_vma.  */
#include "bfd.h"


/* The target is partially multi-arched.  Both "tm.h" and the
   multi-arch vector provide definitions.  "tm.h" normally overrides
   the multi-arch vector (but there are a few exceptions).  */

#define GDB_MULTI_ARCH_PARTIAL 1

/* The target is partially multi-arched. Both the multi-arch vector
   and "tm.h" provide definitions. "tm.h" cannot override a definition
   provided by the multi-arch vector.  It is detected as a compilation
   error.

   This setting is only useful during a multi-arch conversion. */

#define GDB_MULTI_ARCH_TM 2

/* The target is pure multi-arch.  The MULTI-ARCH vector provides all
   definitions.  "tm.h" is linked to an empty file. */

#define GDB_MULTI_ARCH_PURE 3



/* An address in the program being debugged.  Host byte order.  Rather
   than duplicate all the logic in BFD which figures out what type
   this is (long, long long, etc.) and whether it needs to be 64
   bits (the host/target interactions are subtle), we just use
   bfd_vma.  */

typedef bfd_vma CORE_ADDR;

/* This is to make sure that LONGEST is at least as big as CORE_ADDR.  */

#ifndef LONGEST

#ifdef BFD64

#define LONGEST BFD_HOST_64_BIT
#define ULONGEST BFD_HOST_U_64_BIT

#else /* No BFD64 */

#ifdef CC_HAS_LONG_LONG
#define LONGEST long long
#define ULONGEST unsigned long long
#else
#ifdef BFD_HOST_64_BIT
/* BFD_HOST_64_BIT is defined for some hosts that don't have long long
   (e.g. i386-windows) so try it.  */
#define LONGEST BFD_HOST_64_BIT
#define ULONGEST BFD_HOST_U_64_BIT
#else
#define LONGEST long
#define ULONGEST unsigned long
#endif
#endif

#endif /* No BFD64 */

#endif /* ! LONGEST */

#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

/* Macros to do string compares.

   NOTE: cagney/2000-03-14:

   While old code can continue to refer to these macros, new code is
   probably better off using strcmp() directly vis: ``strcmp() == 0''
   and ``strcmp() != 0''.

   This is because modern compilers can directly inline strcmp()
   making the original justification for these macros - avoid function
   call overhead by pre-testing the first characters
   (``*X==*Y?...:0'') - redundant.

   ``Even if [...] testing the first character does have a modest
   performance improvement, I'd rather that whenever a performance
   issue is found that we spend the effort on algorithmic
   optimizations than micro-optimizing.'' J.T. */

#define STREQ(a,b) (*(a) == *(b) ? !strcmp ((a), (b)) : 0)
#define STREQN(a,b,c) (*(a) == *(b) ? !strncmp ((a), (b), (c)) : 0)

/* The character GNU C++ uses to build identifiers that must be unique from
   the program's identifiers (such as $this and $$vptr).  */
#define CPLUS_MARKER '$'	/* May be overridden to '.' for SysV */

/* Check if a character is one of the commonly used C++ marker characters.  */
extern int is_cplus_marker (int);

/* use tui interface if non-zero */
extern int tui_version;

/* enable xdb commands if set */
extern int xdb_commands;

/* enable dbx commands if set */
extern int dbx_commands;

extern int quit_flag;
extern int immediate_quit;
extern int sevenbit_strings;

extern void quit (void);

/* FIXME: cagney/2000-03-13: It has been suggested that the peformance
   benefits of having a ``QUIT'' macro rather than a function are
   marginal.  If the overhead of a QUIT function call is proving
   significant then its calling frequency should probably be reduced
   [kingdon].  A profile analyzing the current situtation is
   needed. */

#ifdef QUIT
/* do twice to force compiler warning */
#define QUIT_FIXME "FIXME"
#define QUIT_FIXME "ignoring redefinition of QUIT"
#else
#define QUIT { \
  if (quit_flag) quit (); \
  if (interactive_hook) interactive_hook (); \
  PROGRESS (1); \
}
#endif

/* Languages represented in the symbol table and elsewhere.
   This should probably be in language.h, but since enum's can't
   be forward declared to satisfy opaque references before their
   actual definition, needs to be here. */

enum language
  {
    language_unknown,		/* Language not known */
    language_auto,		/* Placeholder for automatic setting */
    language_c,			/* C */
    language_cplus,		/* C++ */
    language_java,		/* Java */
    language_chill,		/* Chill */
    language_fortran,		/* Fortran */
    language_m2,		/* Modula-2 */
    language_asm,		/* Assembly language */
    language_scm,    		/* Scheme / Guile */
    language_pascal		/* Pascal */
  };

enum precision_type
  {
    single_precision,
    double_precision,
    unspecified_precision
  };

/* the cleanup list records things that have to be undone
   if an error happens (descriptors to be closed, memory to be freed, etc.)
   Each link in the chain records a function to call and an
   argument to give it.

   Use make_cleanup to add an element to the cleanup chain.
   Use do_cleanups to do all cleanup actions back to a given
   point in the chain.  Use discard_cleanups to remove cleanups
   from the chain back to a given point, not doing them.  */

struct cleanup
  {
    struct cleanup *next;
    void (*function) (PTR);
    PTR arg;
  };


/* The ability to declare that a function never returns is useful, but
   not really required to compile GDB successfully, so the NORETURN and
   ATTR_NORETURN macros normally expand into nothing.  */

/* If compiling with older versions of GCC, a function may be declared
   "volatile" to indicate that it does not return.  */

#ifndef NORETURN
#if defined(__GNUC__) \
     && (__GNUC__ == 1 || (__GNUC__ == 2 && __GNUC_MINOR__ < 7))
#define NORETURN volatile
#else
#define NORETURN		/* nothing */
#endif
#endif

/* GCC 2.5 and later versions define a function attribute "noreturn",
   which is the preferred way to declare that a function never returns.
   However GCC 2.7 appears to be the first version in which this fully
   works everywhere we use it. */

#ifndef ATTR_NORETURN
#if defined(__GNUC__) && (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7))
#define ATTR_NORETURN __attribute__ ((noreturn))
#else
#define ATTR_NORETURN		/* nothing */
#endif
#endif

#ifndef ATTR_FORMAT
#if defined(__GNUC__) && (__GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 4))
#define ATTR_FORMAT(type, x, y) __attribute__ ((format(type, x, y)))
#else
#define ATTR_FORMAT(type, x, y)	/* nothing */
#endif
#endif

/* Needed for various prototypes */

struct symtab;
struct breakpoint;

/* From blockframe.c */

extern int inside_entry_func (CORE_ADDR);

extern int inside_entry_file (CORE_ADDR addr);

extern int inside_main_func (CORE_ADDR pc);

/* From ch-lang.c, for the moment. (FIXME) */

extern char *chill_demangle (const char *);

/* From utils.c */

extern void initialize_utils (void);

extern void notice_quit (void);

extern int strcmp_iw (const char *, const char *);

extern int subset_compare (char *, char *);

extern char *safe_strerror (int);

extern void init_malloc (void *);

extern void request_quit (int);

extern void do_cleanups (struct cleanup *);
extern void do_final_cleanups (struct cleanup *);
extern void do_my_cleanups (struct cleanup **, struct cleanup *);
extern void do_run_cleanups (struct cleanup *);
extern void do_exec_cleanups (struct cleanup *);
extern void do_exec_error_cleanups (struct cleanup *);

extern void discard_cleanups (struct cleanup *);
extern void discard_final_cleanups (struct cleanup *);
extern void discard_exec_error_cleanups (struct cleanup *);
extern void discard_my_cleanups (struct cleanup **, struct cleanup *);

/* NOTE: cagney/2000-03-04: This typedef is strictly for the
   make_cleanup function declarations below. Do not use this typedef
   as a cast when passing functions into the make_cleanup() code.
   Instead either use a bounce function or add a wrapper function.
   Calling a f(char*) function with f(void*) is non-portable. */
typedef void (make_cleanup_ftype) (void *);

extern struct cleanup *make_cleanup (make_cleanup_ftype *, void *);

extern struct cleanup *make_cleanup_freeargv (char **);

struct ui_file;
extern struct cleanup *make_cleanup_ui_file_delete (struct ui_file *);

extern struct cleanup *make_cleanup_close (int fd);

extern struct cleanup *make_cleanup_bfd_close (bfd *abfd);

extern struct cleanup *make_final_cleanup (make_cleanup_ftype *, void *);

extern struct cleanup *make_my_cleanup (struct cleanup **,
					make_cleanup_ftype *, void *);

extern struct cleanup *make_run_cleanup (make_cleanup_ftype *, void *);

extern struct cleanup *make_exec_cleanup (make_cleanup_ftype *, void *);
extern struct cleanup *make_exec_error_cleanup (make_cleanup_ftype *, void *);

extern struct cleanup *save_cleanups (void);
extern struct cleanup *save_final_cleanups (void);
extern struct cleanup *save_my_cleanups (struct cleanup **);

extern void restore_cleanups (struct cleanup *);
extern void restore_final_cleanups (struct cleanup *);
extern void restore_my_cleanups (struct cleanup **, struct cleanup *);

extern void free_current_contents (void *);

extern void null_cleanup (void *);

extern int myread (int, char *, int);

extern int query (const char *, ...) ATTR_FORMAT (printf, 1, 2);

extern void init_page_info (void);

extern CORE_ADDR host_pointer_to_address (void *ptr);
extern void *address_to_host_pointer (CORE_ADDR addr);

extern char *gdb_realpath (const char *);
extern char *xfullpath (const char *);

/* From demangle.c */

extern void set_demangling_style (char *);

/* From tm.h */

struct type;
typedef int (use_struct_convention_fn) (int gcc_p, struct type * value_type);
extern use_struct_convention_fn generic_use_struct_convention;

typedef unsigned char *(breakpoint_from_pc_fn) (CORE_ADDR * pcptr, int *lenptr);

/* Annotation stuff.  */

extern int annotation_level;	/* in stack.c */

extern void begin_line (void);

extern void wrap_here (char *);

extern void reinitialize_more_filter (void);

/* Normal results */
extern struct ui_file *gdb_stdout;
/* Serious error notifications */
extern struct ui_file *gdb_stderr;
/* Log/debug/trace messages that should bypass normal stdout/stderr
   filtering.  For momement, always call this stream using
   *_unfiltered. In the very near future that restriction shall be
   removed - either call shall be unfiltered. (cagney 1999-06-13). */
extern struct ui_file *gdb_stdlog;
/* Target output that should bypass normal stdout/stderr filtering.
   For momement, always call this stream using *_unfiltered. In the
   very near future that restriction shall be removed - either call
   shall be unfiltered. (cagney 1999-07-02). */
extern struct ui_file *gdb_stdtarg;

#if defined(TUI)
#include "tui.h"
#endif

#include "ui-file.h"

/* More generic printf like operations.  Filtered versions may return
   non-locally on error.  */

extern void fputs_filtered (const char *, struct ui_file *);

extern void fputs_unfiltered (const char *, struct ui_file *);

extern int fputc_filtered (int c, struct ui_file *);

extern int fputc_unfiltered (int c, struct ui_file *);

extern int putchar_filtered (int c);

extern int putchar_unfiltered (int c);

extern void puts_filtered (const char *);

extern void puts_unfiltered (const char *);

extern void puts_debug (char *prefix, char *string, char *suffix);

extern void vprintf_filtered (const char *, va_list) ATTR_FORMAT (printf, 1, 0);

extern void vfprintf_filtered (struct ui_file *, const char *, va_list) ATTR_FORMAT (printf, 2, 0);

extern void fprintf_filtered (struct ui_file *, const char *, ...) ATTR_FORMAT (printf, 2, 3);

extern void fprintfi_filtered (int, struct ui_file *, const char *, ...) ATTR_FORMAT (printf, 3, 4);

extern void printf_filtered (const char *, ...) ATTR_FORMAT (printf, 1, 2);

extern void printfi_filtered (int, const char *, ...) ATTR_FORMAT (printf, 2, 3);

extern void vprintf_unfiltered (const char *, va_list) ATTR_FORMAT (printf, 1, 0);

extern void vfprintf_unfiltered (struct ui_file *, const char *, va_list) ATTR_FORMAT (printf, 2, 0);

extern void fprintf_unfiltered (struct ui_file *, const char *, ...) ATTR_FORMAT (printf, 2, 3);

extern void printf_unfiltered (const char *, ...) ATTR_FORMAT (printf, 1, 2);

extern void print_spaces (int, struct ui_file *);

extern void print_spaces_filtered (int, struct ui_file *);

extern char *n_spaces (int);

extern void fputstr_filtered (const char *str, int quotr, struct ui_file * stream);

extern void fputstr_unfiltered (const char *str, int quotr, struct ui_file * stream);

extern void fputstrn_unfiltered (const char *str, int n, int quotr, struct ui_file * stream);

/* Display the host ADDR on STREAM formatted as ``0x%x''. */
extern void gdb_print_host_address (void *addr, struct ui_file *stream);

/* Convert a CORE_ADDR into a HEX string.  paddr() is like %08lx.
   paddr_nz() is like %lx.  paddr_u() is like %lu. paddr_width() is
   for ``%*''. */
extern int strlen_paddr (void);
extern char *paddr (CORE_ADDR addr);
extern char *paddr_nz (CORE_ADDR addr);
extern char *paddr_u (CORE_ADDR addr);
extern char *paddr_d (LONGEST addr);

extern char *phex (ULONGEST l, int sizeof_l);
extern char *phex_nz (ULONGEST l, int sizeof_l);

/* Like paddr() only print/scan raw CORE_ADDR.  The output from
   core_addr_to_string() can be passed direct to
   string_to_core_addr().  */
extern const char *core_addr_to_string (const CORE_ADDR addr);
extern const char *core_addr_to_string_nz (const CORE_ADDR addr);
extern CORE_ADDR string_to_core_addr (const char *my_string);

extern void fprintf_symbol_filtered (struct ui_file *, char *,
				     enum language, int);

extern NORETURN void perror_with_name (const char *) ATTR_NORETURN;

extern void print_sys_errmsg (const char *, int);

/* From regex.c or libc.  BSD 4.4 declares this with the argument type as
   "const char *" in unistd.h, so we can't declare the argument
   as "char *".  */

extern char *re_comp (const char *);

/* From symfile.c */

extern void symbol_file_command (char *, int);

/* Remote targets may wish to use this as their load function.  */
extern void generic_load (char *name, int from_tty);

/* Summarise a download */
extern void print_transfer_performance (struct ui_file *stream,
					unsigned long data_count,
					unsigned long write_count,
					unsigned long time_count);

/* From top.c */

typedef void initialize_file_ftype (void);

extern char *skip_quoted (char *);

extern char *gdb_readline (char *);

extern char *command_line_input (char *, int, char *);

extern void print_prompt (void);

extern int input_from_terminal_p (void);

extern int info_verbose;

/* From printcmd.c */

extern void set_next_address (CORE_ADDR);

extern void print_address_symbolic (CORE_ADDR, struct ui_file *, int,
				    char *);

extern int build_address_symbolic (CORE_ADDR addr,
				   int do_demangle, 
				   char **name, 
				   int *offset, 
				   char **filename, 
				   int *line, 	
				   int *unmapped);

extern void print_address_numeric (CORE_ADDR, int, struct ui_file *);

extern void print_address (CORE_ADDR, struct ui_file *);

/* From source.c */

extern int openp (const char *, int, const char *, int, int, char **);

extern int source_full_path_of (char *, char **);

extern void mod_path (char *, char **);

extern void directory_command (char *, int);

extern void init_source_path (void);

extern char *symtab_to_filename (struct symtab *);

/* From exec.c */

extern void exec_set_section_offsets (bfd_signed_vma text_off,
				      bfd_signed_vma data_off,
				      bfd_signed_vma bss_off);

/* Take over the 'find_mapped_memory' vector from exec.c. */
extern void exec_set_find_memory_regions (int (*) (int (*) (CORE_ADDR, 
							    unsigned long, 
							    int, int, int, 
							    void *),
						   void *));

/* Possible lvalue types.  Like enum language, this should be in
   value.h, but needs to be here for the same reason. */

enum lval_type
  {
    /* Not an lval. */
    not_lval,
    /* In memory.  Could be a saved register.  */
    lval_memory,
    /* In a register.  */
    lval_register,
    /* In a gdb internal variable.  */
    lval_internalvar,
    /* Part of a gdb internal variable (structure field).  */
    lval_internalvar_component,
    /* In a register series in a frame not the current one, which may have been
       partially saved or saved in different places (otherwise would be
       lval_register or lval_memory).  */
    lval_reg_frame_relative
  };

struct frame_info;

/* From readline (but not in any readline .h files).  */

extern char *tilde_expand (char *);

/* Control types for commands */

enum misc_command_type
  {
    ok_command,
    end_command,
    else_command,
    nop_command
  };

enum command_control_type
  {
    simple_control,
    break_control,
    continue_control,
    while_control,
    if_control,
    invalid_control
  };

/* Structure for saved commands lines
   (for breakpoints, defined commands, etc).  */

struct command_line
  {
    struct command_line *next;
    char *line;
    enum command_control_type control_type;
    int body_count;
    struct command_line **body_list;
  };

extern struct command_line *read_command_lines (char *, int);

extern void free_command_lines (struct command_line **);

/* To continue the execution commands when running gdb asynchronously. 
   A continuation structure contains a pointer to a function to be called 
   to finish the command, once the target has stopped. Such mechanism is
   used bt the finish and until commands, and in the remote protocol
   when opening an extended-remote connection. */

struct continuation_arg
  {
    struct continuation_arg *next;
    union continuation_data {
      void *pointer;
      int   integer;
      long  longint;
    } data;
  };

struct continuation
  {
    void (*continuation_hook) (struct continuation_arg *);
    struct continuation_arg *arg_list;
    struct continuation *next;
  };

/* In infrun.c. */
extern struct continuation *cmd_continuation;
/* Used only by the step_1 function. */
extern struct continuation *intermediate_continuation;

/* From utils.c */
extern void add_continuation (void (*)(struct continuation_arg *),
			      struct continuation_arg *);
extern void do_all_continuations (void);
extern void discard_all_continuations (void);

extern void add_intermediate_continuation (void (*)(struct continuation_arg *),
			      struct continuation_arg *);
extern void do_all_intermediate_continuations (void);
extern void discard_all_intermediate_continuations (void);

/* String containing the current directory (what getwd would return).  */

extern char *current_directory;

/* Default radixes for input and output.  Only some values supported.  */
extern unsigned input_radix;
extern unsigned output_radix;

/* Possibilities for prettyprint parameters to routines which print
   things.  Like enum language, this should be in value.h, but needs
   to be here for the same reason.  FIXME:  If we can eliminate this
   as an arg to LA_VAL_PRINT, then we can probably move it back to
   value.h. */

enum val_prettyprint
  {
    Val_no_prettyprint = 0,
    Val_prettyprint,
    /* Use the default setting which the user has specified.  */
    Val_pretty_default
  };

/* The ptid struct is a collection of the various "ids" necessary
   for identifying the inferior.  This consists of the process id
   (pid), thread id (tid), and other fields necessary for uniquely
   identifying the inferior process/thread being debugged.  When
   manipulating ptids, the constructors, accessors, and predicate
   declared in inferior.h should be used.  These are as follows:

      ptid_build	- Make a new ptid from a pid, lwp, and tid.
      pid_to_ptid	- Make a new ptid from just a pid.
      ptid_get_pid	- Fetch the pid component of a ptid.
      ptid_get_lwp	- Fetch the lwp component of a ptid.
      ptid_get_tid	- Fetch the tid component of a ptid.
      ptid_equal	- Test to see if two ptids are equal.

   Please do NOT access the struct ptid members directly (except, of
   course, in the implementation of the above ptid manipulation
   functions).  */

struct ptid
  {
    /* Process id */
    int pid;

    /* Lightweight process id */
    long lwp;

    /* Thread id */
    long tid;
  };

typedef struct ptid ptid_t;



/* Optional host machine definition.  Pure autoconf targets will not
   need a "xm.h" file.  This will be a symlink to one of the xm-*.h
   files, built by the `configure' script.  */

#ifdef GDB_XM_FILE
#include "xm.h"
#endif

/* Optional native machine support.  Non-native (and possibly pure
   multi-arch) targets do not need a "nm.h" file.  This will be a
   symlink to one of the nm-*.h files, built by the `configure'
   script.  */

#ifdef GDB_NM_FILE
#include "nm.h"
#endif

/* Optional target machine definition.  Pure multi-arch configurations
   do not need a "tm.h" file.  This will be a symlink to one of the
   tm-*.h files, built by the `configure' script.  */

#ifdef GDB_TM_FILE
#include "tm.h"
#endif

/* GDB_MULTI_ARCH is normally set by configure.in using information
   from configure.tgt or the config/%/%.mt Makefile fragment.  Since
   some targets have defined it in their "tm.h" file, delay providing
   a default definition until after "tm.h" has been included.. */

#ifndef GDB_MULTI_ARCH
#define GDB_MULTI_ARCH 0
#endif


/* If the xm.h file did not define the mode string used to open the
   files, assume that binary files are opened the same way as text
   files */
#ifndef FOPEN_RB
#include "fopen-same.h"
#endif

/* Defaults for system-wide constants (if not defined by xm.h, we fake it).
   FIXME: Assumes 2's complement arithmetic */

#if !defined (UINT_MAX)
#define	UINT_MAX ((unsigned int)(~0))	/* 0xFFFFFFFF for 32-bits */
#endif

#if !defined (INT_MAX)
#define	INT_MAX ((int)(UINT_MAX >> 1))	/* 0x7FFFFFFF for 32-bits */
#endif

#if !defined (INT_MIN)
#define INT_MIN ((int)((int) ~0 ^ INT_MAX))	/* 0x80000000 for 32-bits */
#endif

#if !defined (ULONG_MAX)
#define	ULONG_MAX ((unsigned long)(~0L))	/* 0xFFFFFFFF for 32-bits */
#endif

#if !defined (LONG_MAX)
#define	LONG_MAX ((long)(ULONG_MAX >> 1))	/* 0x7FFFFFFF for 32-bits */
#endif

#if !defined (ULONGEST_MAX)
#define	ULONGEST_MAX (~(ULONGEST)0)        /* 0xFFFFFFFFFFFFFFFF for 64-bits */
#endif

#if !defined (LONGEST_MAX)                 /* 0x7FFFFFFFFFFFFFFF for 64-bits */
#define	LONGEST_MAX ((LONGEST)(ULONGEST_MAX >> 1))
#endif

/* Convert a LONGEST to an int.  This is used in contexts (e.g. number of
   arguments to a function, number in a value history, register number, etc.)
   where the value must not be larger than can fit in an int.  */

extern int longest_to_int (LONGEST);

/* Assorted functions we can declare, now that const and volatile are 
   defined.  */

extern char *savestring (const char *, size_t);

extern char *msavestring (void *, const char *, size_t);

extern char *mstrsave (void *, const char *);

/* Robust versions of same.  Throw an internal error when no memory,
   guard against stray NULL arguments. */
extern void *xmmalloc (void *md, size_t size);
extern void *xmrealloc (void *md, void *ptr, size_t size);
extern void *xmcalloc (void *md, size_t number, size_t size);
extern void xmfree (void *md, void *ptr);

/* xmalloc(), xrealloc() and xcalloc() have already been declared in
   "libiberty.h". */
extern void xfree (void *);

/* Utility macro to allocate typed memory.  Avoids errors like
   ``struct foo *foo = xmalloc (sizeof bar)'' and ``struct foo *foo =
   (struct foo *) xmalloc (sizeof bar)''.  */
#define XMALLOC(TYPE) ((TYPE*) xmalloc (sizeof (TYPE)))

/* Like asprintf/vasprintf but get an internal_error if the call
   fails. */
extern void xasprintf (char **ret, const char *format, ...) ATTR_FORMAT (printf, 2, 3);
extern void xvasprintf (char **ret, const char *format, va_list ap);

extern int parse_escape (char **);

/* Message to be printed before the error message, when an error occurs.  */

extern char *error_pre_print;

/* Message to be printed before the error message, when an error occurs.  */

extern char *quit_pre_print;

/* Message to be printed before the warning message, when a warning occurs.  */

extern char *warning_pre_print;

extern NORETURN void verror (const char *fmt, va_list ap) ATTR_NORETURN;

extern NORETURN void error (const char *fmt, ...) ATTR_NORETURN ATTR_FORMAT (printf, 1, 2);

extern NORETURN void error_stream (struct ui_file *) ATTR_NORETURN;

/* Returns a freshly allocate buffer containing the last error
   message.  */
extern char *error_last_message (void);

extern NORETURN void internal_verror (const char *file, int line,
				      const char *, va_list ap) ATTR_NORETURN;

extern NORETURN void internal_error (const char *file, int line,
				     const char *, ...) ATTR_NORETURN ATTR_FORMAT (printf, 3, 4);

extern NORETURN void nomem (long) ATTR_NORETURN;

/* Reasons for calling throw_exception().  NOTE: all reason values
   must be less than zero.  enum value 0 is reserved for internal use
   as the return value from an initial setjmp().  The function
   catch_exceptions() reserves values >= 0 as legal results from its
   wrapped function.  */

enum return_reason
  {
    /* User interrupt.  */
    RETURN_QUIT = -2,
    /* Any other error.  */
    RETURN_ERROR
  };

#define	ALL_CLEANUPS	((struct cleanup *)0)

#define RETURN_MASK(reason)	(1 << (int)(-reason))
#define RETURN_MASK_QUIT	RETURN_MASK (RETURN_QUIT)
#define RETURN_MASK_ERROR	RETURN_MASK (RETURN_ERROR)
#define RETURN_MASK_ALL		(RETURN_MASK_QUIT | RETURN_MASK_ERROR)
typedef int return_mask;

/* Throw an exception of type RETURN_REASON.  Will execute a LONG JUMP
   to the inner most containing exception handler established using
   catch_exceptions() (or the legacy catch_errors()).

   Code normally throws an exception using error() et.al.  For various
   reaons, GDB also contains code that throws an exception directly.
   For instance, the remote*.c targets contain CNTRL-C signal handlers
   that propogate the QUIT event up the exception chain.  ``This could
   be a good thing or a dangerous thing.'' -- the Existential Wombat.  */

extern NORETURN void throw_exception (enum return_reason) ATTR_NORETURN;

/* Call FUNC(UIOUT, FUNC_ARGS) but wrapped within an exception
   handler.  If an exception (enum return_reason) is thrown using
   throw_exception() than all cleanups installed since
   catch_exceptions() was entered are invoked, the (-ve) exception
   value is then returned by catch_exceptions.  If FUNC() returns
   normally (with a postive or zero return value) then that value is
   returned by catch_exceptions().  It is an internal_error() for
   FUNC() to return a negative value.

   For the period of the FUNC() call: UIOUT is installed as the output
   builder; ERRSTRING is installed as the error/quit message; and a
   new cleanup_chain is established.  The old values are restored
   before catch_exceptions() returns.

   FIXME; cagney/2001-08-13: The need to override the global UIOUT
   builder variable should just go away.

   This function superseeds catch_errors().

   This function uses SETJMP() and LONGJUMP().  */

struct ui_out;
typedef int (catch_exceptions_ftype) (struct ui_out *ui_out, void *args);
extern int catch_exceptions (struct ui_out *uiout,
			     catch_exceptions_ftype *func, void *func_args,
			     char *errstring, return_mask mask);

/* If CATCH_ERRORS_FTYPE throws an error, catch_errors() returns zero
   otherwize the result from CATCH_ERRORS_FTYPE is returned. It is
   probably useful for CATCH_ERRORS_FTYPE to always return a non-zero
   value. It's unfortunate that, catch_errors() does not return an
   indication of the exact exception that it caught - quit_flag might
   help.

   This function is superseeded by catch_exceptions().  */

typedef int (catch_errors_ftype) (PTR);
extern int catch_errors (catch_errors_ftype *, void *, char *, return_mask);

/* Template to catch_errors() that wraps calls to command
   functions. */

typedef void (catch_command_errors_ftype) (char *, int);
extern int catch_command_errors (catch_command_errors_ftype *func, char *command, int from_tty, return_mask);

extern void warning (const char *, ...) ATTR_FORMAT (printf, 1, 2);

extern void vwarning (const char *, va_list args);

/* Global functions from other, non-gdb GNU thingies.
   Libiberty thingies are no longer declared here.  We include libiberty.h
   above, instead.  */

#ifndef GETENV_PROVIDED
extern char *getenv (const char *);
#endif

/* From other system libraries */

#ifdef HAVE_STDDEF_H
#include <stddef.h>
#endif

#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif


/* We take the address of fclose later, but some stdio's forget
   to declare this.  We can't always declare it since there's
   no way to declare the parameters without upsetting some compiler
   somewhere. */

#ifndef FCLOSE_PROVIDED
extern int fclose (FILE *);
#endif

#ifndef atof
extern double atof (const char *);	/* X3.159-1989  4.10.1.1 */
#endif

/* Various possibilities for alloca.  */
#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* Not GNU C */
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#else
#ifdef _AIX
#pragma alloca
#else

/* We need to be careful not to declare this in a way which conflicts with
   bison.  Bison never declares it as char *, but under various circumstances
   (like __hpux) we need to use void *.  */
extern void *alloca ();
#endif /* Not _AIX */
#endif /* Not HAVE_ALLOCA_H */
#endif /* Not GNU C */
#endif /* alloca not defined */

/* Dynamic target-system-dependent parameters for GDB. */
#include "gdbarch.h"
#if (GDB_MULTI_ARCH == 0)
/* Multi-arch targets _should_ be including "arch-utils.h" directly
   into their *-tdep.c file.  This is a prop to help old non-
   multi-arch targets to continue to compile. */
#include "arch-utils.h"
#endif

/* Static target-system-dependent parameters for GDB. */

/* Number of bits in a char or unsigned char for the target machine.
   Just like CHAR_BIT in <limits.h> but describes the target machine.  */
#if !defined (TARGET_CHAR_BIT)
#define TARGET_CHAR_BIT 8
#endif

/* If we picked up a copy of CHAR_BIT from a configuration file
   (which may get it by including <limits.h>) then use it to set
   the number of bits in a host char.  If not, use the same size
   as the target. */

#if defined (CHAR_BIT)
#define HOST_CHAR_BIT CHAR_BIT
#else
#define HOST_CHAR_BIT TARGET_CHAR_BIT
#endif

/* The bit byte-order has to do just with numbering of bits in
   debugging symbols and such.  Conceptually, it's quite separate
   from byte/word byte order.  */

#if !defined (BITS_BIG_ENDIAN)
#define BITS_BIG_ENDIAN (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
#endif

/* In findvar.c.  */

extern LONGEST extract_signed_integer (void *, int);

extern ULONGEST extract_unsigned_integer (void *, int);

extern int extract_long_unsigned_integer (void *, int, LONGEST *);

extern CORE_ADDR extract_address (void *, int);

extern CORE_ADDR extract_typed_address (void *buf, struct type *type);

extern void store_signed_integer (void *, int, LONGEST);

extern void store_unsigned_integer (void *, int, ULONGEST);

extern void store_address (void *, int, LONGEST);

extern void store_typed_address (void *buf, struct type *type, CORE_ADDR addr);


/* From valops.c */

extern CORE_ADDR push_bytes (CORE_ADDR, char *, int);

extern CORE_ADDR push_word (CORE_ADDR, ULONGEST);

extern int watchdog;

/* Hooks for alternate command interfaces.  */

/* The name of the interpreter if specified on the command line. */
extern char *interpreter_p;

/* If a given interpreter matches INTERPRETER_P then it should update
   command_loop_hook and init_ui_hook with the per-interpreter
   implementation. */
/* FIXME: command_loop_hook and init_ui_hook should be moved here. */

struct target_waitstatus;
struct cmd_list_element;

/* Should the asynchronous variant of the interpreter (using the
   event-loop) be enabled? */
extern int event_loop_p;

extern void (*init_ui_hook) (char *argv0);
extern void (*command_loop_hook) (void);
extern void (*show_load_progress) (const char *section,
				   unsigned long section_sent, 
				   unsigned long section_size, 
				   unsigned long total_sent, 
				   unsigned long total_size);
extern void (*print_frame_info_listing_hook) (struct symtab * s,
					      int line, int stopline,
					      int noerror);
extern struct frame_info *parse_frame_specification (char *frame_exp);
extern int (*query_hook) (const char *, va_list);
extern void (*warning_hook) (const char *, va_list);
extern void (*flush_hook) (struct ui_file * stream);
extern void (*create_breakpoint_hook) (struct breakpoint * b);
extern void (*delete_breakpoint_hook) (struct breakpoint * bpt);
extern void (*modify_breakpoint_hook) (struct breakpoint * bpt);
extern void (*interactive_hook) (void);
extern void (*registers_changed_hook) (void);
extern void (*readline_begin_hook) (char *,...);
extern char *(*readline_hook) (char *);
extern void (*readline_end_hook) (void);
extern void (*register_changed_hook) (int regno);
extern void (*memory_changed_hook) (CORE_ADDR addr, int len);
extern void (*context_hook) (int);
extern ptid_t (*target_wait_hook) (ptid_t ptid,
                                         struct target_waitstatus * status);

extern void (*attach_hook) (void);
extern void (*detach_hook) (void);
extern void (*call_command_hook) (struct cmd_list_element * c,
				  char *cmd, int from_tty);

extern void (*set_hook) (struct cmd_list_element * c);

extern NORETURN void (*error_hook) (void) ATTR_NORETURN;

extern void (*error_begin_hook) (void);

extern int (*ui_load_progress_hook) (const char *section, unsigned long num);


/* Inhibit window interface if non-zero. */

extern int use_windows;

/* Symbolic definitions of filename-related things.  */
/* FIXME, this doesn't work very well if host and executable
   filesystems conventions are different.  */

#ifndef DIRNAME_SEPARATOR
#define DIRNAME_SEPARATOR ':'
#endif

#ifndef SLASH_STRING
#define SLASH_STRING "/"
#endif

#ifdef __MSDOS__
# define CANT_FORK
# define GLOBAL_CURDIR
#endif

/* Provide default definitions of PIDGET, TIDGET, and MERGEPID.
   The name ``TIDGET'' is a historical accident.  Many uses of TIDGET
   in the code actually refer to a lightweight process id, i.e,
   something that can be considered a process id in its own right for
   certain purposes.  */

#ifndef PIDGET
#define PIDGET(PTID) (ptid_get_pid (PTID))
#define TIDGET(PTID) (ptid_get_lwp (PTID))
#define MERGEPID(PID, TID) ptid_build (PID, TID, 0)
#endif

/* Define well known filenos if the system does not define them.  */
#ifndef STDIN_FILENO
#define STDIN_FILENO   0
#endif
#ifndef STDOUT_FILENO
#define STDOUT_FILENO  1
#endif
#ifndef STDERR_FILENO
#define STDERR_FILENO  2
#endif

/* If this definition isn't overridden by the header files, assume
   that isatty and fileno exist on this system.  */
#ifndef ISATTY
#define ISATTY(FP)	(isatty (fileno (FP)))
#endif

#endif /* #ifndef DEFS_H */
