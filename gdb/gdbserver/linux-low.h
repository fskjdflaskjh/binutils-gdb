/* Internal interfaces for the GNU/Linux specific target code for gdbserver.
   Copyright (C) 2002, 2004, 2005, 2007, 2008, 2009
   Free Software Foundation, Inc.

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

#ifdef HAVE_THREAD_DB_H
#include <thread_db.h>
#endif

#ifdef HAVE_LINUX_REGSETS
typedef void (*regset_fill_func) (void *);
typedef void (*regset_store_func) (const void *);
enum regset_type {
  GENERAL_REGS,
  FP_REGS,
  EXTENDED_REGS,
};

struct regset_info
{
  int get_request, set_request;
  int size;
  enum regset_type type;
  regset_fill_func fill_function;
  regset_store_func store_function;
};
extern struct regset_info target_regsets[];
#endif

struct linux_target_ops
{
  /* Architecture-specific setup.  */
  void (*arch_setup) (void);

  int num_regs;
  int *regmap;
  int (*cannot_fetch_register) (int);

  /* Returns 0 if we can store the register, 1 if we can not
     store the register, and 2 if failure to store the register
     is acceptable.  */
  int (*cannot_store_register) (int);
  CORE_ADDR (*get_pc) (void);
  void (*set_pc) (CORE_ADDR newpc);
  const unsigned char *breakpoint;
  int breakpoint_len;
  CORE_ADDR (*breakpoint_reinsert_addr) (void);


  int decr_pc_after_break;
  int (*breakpoint_at) (CORE_ADDR pc);

  /* Watchpoint related functions.  See target.h for comments.  */
  int (*insert_watchpoint) (char type, CORE_ADDR addr, int len);
  int (*remove_watchpoint) (char type, CORE_ADDR addr, int len);
  int (*stopped_by_watchpoint) (void);
  CORE_ADDR (*stopped_data_address) (void);

  /* Hooks to reformat register data for PEEKUSR/POKEUSR (in particular
     for registers smaller than an xfer unit).  */
  void (*collect_ptrace_register) (int regno, char *buf);
  void (*supply_ptrace_register) (int regno, const char *buf);
};

extern struct linux_target_ops the_low_target;

#define get_lwp(inf) ((struct lwp_info *)(inf))
#define get_thread_lwp(thr) (get_lwp (inferior_target_data (thr)))
#define get_lwp_thread(proc) ((struct thread_info *)			\
			      find_inferior_id (&all_threads,		\
						get_lwp (proc)->lwpid))

struct lwp_info
{
  struct inferior_list_entry head;
  unsigned long lwpid;

  /* If this flag is set, the next SIGSTOP will be ignored (the
     process will be immediately resumed).  This means that either we
     sent the SIGSTOP to it ourselves and got some other pending event
     (so the SIGSTOP is still pending), or that we stopped the
     inferior implicitly via PTRACE_ATTACH and have not waited for it
     yet.  */
  int stop_expected;

  /* If this flag is set, the process is known to be stopped right now (stop
     event already received in a wait()).  */
  int stopped;

  /* When stopped is set, the last wait status recorded for this process.  */
  int last_status;

  /* If this flag is set, STATUS_PENDING is a waitstatus that has not yet
     been reported.  */
  int status_pending_p;
  int status_pending;

  /* If this flag is set, the pending status is a (GDB-placed) breakpoint.  */
  int pending_is_breakpoint;
  CORE_ADDR pending_stop_pc;

  /* If this is non-zero, it is a breakpoint to be reinserted at our next
     stop (SIGTRAP stops only).  */
  CORE_ADDR bp_reinsert;

  /* If this flag is set, the last continue operation on this process
     was a single-step.  */
  int stepping;

  /* If this is non-zero, it points to a chain of signals which need to
     be delivered to this process.  */
  struct pending_signals *pending_signals;

  /* A link used when resuming.  It is initialized from the resume request,
     and then processed and cleared in linux_resume_one_lwp.  */

  struct thread_resume *resume;

  int thread_known;
#ifdef HAVE_THREAD_DB_H
  /* The thread handle, used for e.g. TLS access.  Only valid if
     THREAD_KNOWN is set.  */
  td_thrhandle_t th;
#endif
};

extern struct inferior_list all_lwps;

void linux_attach_lwp (unsigned long pid);

int thread_db_init (int use_events);
int thread_db_get_tls_address (struct thread_info *thread, CORE_ADDR offset,
			       CORE_ADDR load_module, CORE_ADDR *address);
