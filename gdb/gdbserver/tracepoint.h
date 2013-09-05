/* Tracepoint code for remote server for GDB.
   Copyright (C) 1993-2013 Free Software Foundation, Inc.

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

#ifndef TRACEPOINT_H
#define TRACEPOINT_H

/* Size for a small buffer to report problems from the in-process
   agent back to GDBserver.  */
#define IPA_BUFSIZ 100

void initialize_tracepoint (void);

extern int tracing;
extern int disconnected_tracing;

void tracepoint_look_up_symbols (void);

void stop_tracing (void);

int handle_tracepoint_general_set (char *own_buf);
int handle_tracepoint_query (char *own_buf);

int tracepoint_finished_step (struct thread_info *tinfo, CORE_ADDR stop_pc);
int tracepoint_was_hit (struct thread_info *tinfo, CORE_ADDR stop_pc);

void release_while_stepping_state_list (struct thread_info *tinfo);

extern int current_traceframe;

int in_readonly_region (CORE_ADDR addr, ULONGEST length);
int traceframe_read_mem (int tfnum, CORE_ADDR addr,
			 unsigned char *buf, ULONGEST length,
			 ULONGEST *nbytes);
int fetch_traceframe_registers (int tfnum,
				struct regcache *regcache,
				int regnum);

int traceframe_read_sdata (int tfnum, ULONGEST offset,
			   unsigned char *buf, ULONGEST length,
			   ULONGEST *nbytes);

int traceframe_read_info (int tfnum, struct buffer *buffer);

/* If a thread is determined to be collecting a fast tracepoint, this
   structure holds the collect status.  */

struct fast_tpoint_collect_status
{
  /* The tracepoint that is presently being collected.  */
  int tpoint_num;
  CORE_ADDR tpoint_addr;

  /* The address range in the jump pad of where the original
     instruction the tracepoint jump was inserted was relocated
     to.  */
  CORE_ADDR adjusted_insn_addr;
  CORE_ADDR adjusted_insn_addr_end;
};

int fast_tracepoint_collecting (CORE_ADDR thread_area,
				CORE_ADDR stop_pc,
				struct fast_tpoint_collect_status *status);
void force_unlock_trace_buffer (void);

int handle_tracepoint_bkpts (struct thread_info *tinfo, CORE_ADDR stop_pc);

#ifdef IN_PROCESS_AGENT
void initialize_low_tracepoint (void);
void supply_fast_tracepoint_registers (struct regcache *regcache,
				       const unsigned char *regs);
void supply_static_tracepoint_registers (struct regcache *regcache,
					 const unsigned char *regs,
					 CORE_ADDR pc);
void set_trampoline_buffer_space (CORE_ADDR begin, CORE_ADDR end,
				  char *errmsg);

extern const struct target_desc *ipa_tdesc;

#else
void stop_tracing (void);

int claim_trampoline_space (ULONGEST used, CORE_ADDR *trampoline);
int have_fast_tracepoint_trampoline_buffer (char *msgbuf);
void gdb_agent_about_to_close (int pid);
#endif

struct traceframe;
struct eval_agent_expr_context;

/* Do memory copies for bytecodes.  */
/* Do the recording of memory blocks for actions and bytecodes.  */

int agent_mem_read (struct eval_agent_expr_context *ctx,
		    unsigned char *to, CORE_ADDR from,
		    ULONGEST len);

LONGEST agent_get_trace_state_variable_value (int num);
void agent_set_trace_state_variable_value (int num, LONGEST val);

/* Record the value of a trace state variable.  */

int agent_tsv_read (struct eval_agent_expr_context *ctx, int n);
int agent_mem_read_string (struct eval_agent_expr_context *ctx,
			   unsigned char *to,
			   CORE_ADDR from,
			   ULONGEST len);

/* Returns the address of the get_raw_reg function in the IPA.  */
CORE_ADDR get_raw_reg_func_addr (void);
/* Returns the address of the get_trace_state_variable_value
   function in the IPA.  */
CORE_ADDR get_get_tsv_func_addr (void);
/* Returns the address of the set_trace_state_variable_value
   function in the IPA.  */
CORE_ADDR get_set_tsv_func_addr (void);

#endif /* TRACEPOINT_H */
