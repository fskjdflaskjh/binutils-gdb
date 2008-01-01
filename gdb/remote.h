/* Remote target communications for serial-line targets in custom GDB protocol
   Copyright (C) 1999, 2003, 2004, 2005, 2006, 2007, 2008
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

#ifndef REMOTE_H
#define REMOTE_H

struct target_desc;

/* FIXME?: move this interface down to tgt vector) */

/* Read a packet from the remote machine, with error checking, and
   store it in *BUF.  Resize *BUF using xrealloc if necessary to hold
   the result, and update *SIZEOF_BUF.  If FOREVER, wait forever
   rather than timing out; this is used (in synchronous mode) to wait
   for a target that is is executing user code to stop.  */

extern void getpkt (char **buf, long *sizeof_buf, int forever);

/* Send a packet to the remote machine, with error checking.  The data
   of the packet is in BUF.  The string in BUF can be at most PBUFSIZ
   - 5 to account for the $, # and checksum, and for a possible /0 if
   we are debugging (remote_debug) and want to print the sent packet
   as a string */

extern int putpkt (char *buf);

/* Send HEX encoded string to the target console. (gdb_stdtarg) */

extern void remote_console_output (char *);


/* FIXME: cagney/1999-09-20: The remote cisco stuff in remote.c needs
   to be broken out into a separate file (remote-cisco.[hc]?).  Before
   that can happen, a remote protocol stack framework needs to be
   implemented. */

extern void remote_cisco_objfile_relocate (bfd_signed_vma text_off,
					   bfd_signed_vma data_off,
					   bfd_signed_vma bss_off);

extern void async_remote_interrupt_twice (void *arg);

extern int remote_write_bytes (CORE_ADDR memaddr, const gdb_byte *myaddr,
			       int len);

extern int remote_read_bytes (CORE_ADDR memaddr, gdb_byte *myaddr, int len);

extern void (*deprecated_target_resume_hook) (void);
extern void (*deprecated_target_wait_loop_hook) (void);

void register_remote_g_packet_guess (struct gdbarch *gdbarch, int bytes,
				     const struct target_desc *tdesc);

void remote_file_put (const char *local_file, const char *remote_file,
		      int from_tty);
void remote_file_get (const char *remote_file, const char *local_file,
		      int from_tty);
void remote_file_delete (const char *remote_file, int from_tty);

#endif
