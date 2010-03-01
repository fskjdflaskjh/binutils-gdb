/* Target-dependent code for GNU/Linux AMD64.

   Copyright (C) 2006, 2007, 2008, 2009, 2010 Free Software Foundation, Inc.

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

#ifndef AMD64_LINUX_TDEP_H
#define AMD64_LINUX_TDEP_H

/* Like for i386 GNU/Linux, there is an extra "register"
   used to control syscall restarting.  */

/* Register number for the "orig_rax" register.  If this register
   contains a value >= 0 it is interpreted as the system call number
   that the kernel is supposed to restart.  */
#define AMD64_LINUX_ORIG_RAX_REGNUM (AMD64_MXCSR_REGNUM + 1)

/* Total number of registers for GNU/Linux.  */
#define AMD64_LINUX_NUM_REGS (AMD64_LINUX_ORIG_RAX_REGNUM + 1)

/* Linux target description.  */
extern struct target_desc *tdesc_amd64_linux;

/* Enum that defines the syscall identifiers for amd64 linux.
   Used for process record/replay, these will be translated into
   a gdb-canonical set of syscall ids in linux-record.c.  */

enum amd64_syscall {
  amd64_sys_read = 0,
  amd64_sys_write = 1,
  amd64_sys_open = 2,
  amd64_sys_close = 3,
  amd64_sys_newstat = 4,
  amd64_sys_newfstat = 5,
  amd64_sys_newlstat = 6,
  amd64_sys_poll = 7,
  amd64_sys_lseek = 8,
  amd64_sys_mmap = 9,
  amd64_sys_mprotect = 10,
  amd64_sys_munmap = 11,
  amd64_sys_brk = 12,
  amd64_sys_rt_sigaction = 13,
  amd64_sys_rt_sigprocmask = 14,
  amd64_sys_rt_sigreturn = 15,
  amd64_sys_ioctl = 16,
  amd64_sys_pread64 = 17,
  amd64_sys_pwrite64 = 18,
  amd64_sys_readv = 19,
  amd64_sys_writev = 20,
  amd64_sys_access = 21,
  amd64_sys_pipe = 22,
  amd64_sys_select = 23,
  amd64_sys_sched_yield = 24,
  amd64_sys_mremap = 25,
  amd64_sys_msync = 26,
  amd64_sys_mincore = 27,
  amd64_sys_madvise = 28,
  amd64_sys_shmget = 29,
  amd64_sys_shmat = 30,
  amd64_sys_shmctl = 31,
  amd64_sys_dup = 32,
  amd64_sys_dup2 = 33,
  amd64_sys_pause = 34,
  amd64_sys_nanosleep = 35,
  amd64_sys_getitimer = 36,
  amd64_sys_alarm = 37,
  amd64_sys_setitimer = 38,
  amd64_sys_getpid = 39,
  amd64_sys_sendfile64 = 40,
  amd64_sys_socket = 41,
  amd64_sys_connect = 42,
  amd64_sys_accept = 43,
  amd64_sys_sendto = 44,
  amd64_sys_recvfrom = 45,
  amd64_sys_sendmsg = 46,
  amd64_sys_recvmsg = 47,
  amd64_sys_shutdown = 48,
  amd64_sys_bind = 49,
  amd64_sys_listen = 50,
  amd64_sys_getsockname = 51,
  amd64_sys_getpeername = 52,
  amd64_sys_socketpair = 53,
  amd64_sys_setsockopt = 54,
  amd64_sys_getsockopt = 55,
  amd64_sys_clone = 56,
  amd64_sys_fork = 57,
  amd64_sys_vfork = 58,
  amd64_sys_execve = 59,
  amd64_sys_exit = 60,
  amd64_sys_wait4 = 61,
  amd64_sys_kill = 62,
  amd64_sys_uname = 63,
  amd64_sys_semget = 64,
  amd64_sys_semop = 65,
  amd64_sys_semctl = 66,
  amd64_sys_shmdt = 67,
  amd64_sys_msgget = 68,
  amd64_sys_msgsnd = 69,
  amd64_sys_msgrcv = 70,
  amd64_sys_msgctl = 71,
  amd64_sys_fcntl = 72,
  amd64_sys_flock = 73,
  amd64_sys_fsync = 74,
  amd64_sys_fdatasync = 75,
  amd64_sys_truncate = 76,
  amd64_sys_ftruncate = 77,
  amd64_sys_getdents = 78,
  amd64_sys_getcwd = 79,
  amd64_sys_chdir = 80,
  amd64_sys_fchdir = 81,
  amd64_sys_rename = 82,
  amd64_sys_mkdir = 83,
  amd64_sys_rmdir = 84,
  amd64_sys_creat = 85,
  amd64_sys_link = 86,
  amd64_sys_unlink = 87,
  amd64_sys_symlink = 88,
  amd64_sys_readlink = 89,
  amd64_sys_chmod = 90,
  amd64_sys_fchmod = 91,
  amd64_sys_chown = 92,
  amd64_sys_fchown = 93,
  amd64_sys_lchown = 94,
  amd64_sys_umask = 95,
  amd64_sys_gettimeofday = 96,
  amd64_sys_getrlimit = 97,
  amd64_sys_getrusage = 98,
  amd64_sys_sysinfo = 99,
  amd64_sys_times = 100,
  amd64_sys_ptrace = 101,
  amd64_sys_getuid = 102,
  amd64_sys_syslog = 103,
  amd64_sys_getgid = 104,
  amd64_sys_setuid = 105,
  amd64_sys_setgid = 106,
  amd64_sys_geteuid = 107,
  amd64_sys_getegid = 108,
  amd64_sys_setpgid = 109,
  amd64_sys_getppid = 110,
  amd64_sys_getpgrp = 111,
  amd64_sys_setsid = 112,
  amd64_sys_setreuid = 113,
  amd64_sys_setregid = 114,
  amd64_sys_getgroups = 115,
  amd64_sys_setgroups = 116,
  amd64_sys_setresuid = 117,
  amd64_sys_getresuid = 118,
  amd64_sys_setresgid = 119,
  amd64_sys_getresgid = 120,
  amd64_sys_getpgid = 121,
  amd64_sys_setfsuid = 122,
  amd64_sys_setfsgid = 123,
  amd64_sys_getsid = 124,
  amd64_sys_capget = 125,
  amd64_sys_capset = 126,
  amd64_sys_rt_sigpending = 127,
  amd64_sys_rt_sigtimedwait = 128,
  amd64_sys_rt_sigqueueinfo = 129,
  amd64_sys_rt_sigsuspend = 130,
  amd64_sys_sigaltstack = 131,
  amd64_sys_utime = 132,
  amd64_sys_mknod = 133,
  amd64_sys_personality = 135,
  amd64_sys_ustat = 136,
  amd64_sys_statfs = 137,
  amd64_sys_fstatfs = 138,
  amd64_sys_sysfs = 139,
  amd64_sys_getpriority = 140,
  amd64_sys_setpriority = 141,
  amd64_sys_sched_setparam = 142,
  amd64_sys_sched_getparam = 143,
  amd64_sys_sched_setscheduler = 144,
  amd64_sys_sched_getscheduler = 145,
  amd64_sys_sched_get_priority_max = 146,
  amd64_sys_sched_get_priority_min = 147,
  amd64_sys_sched_rr_get_interval = 148,
  amd64_sys_mlock = 149,
  amd64_sys_munlock = 150,
  amd64_sys_mlockall = 151,
  amd64_sys_munlockall = 152,
  amd64_sys_vhangup = 153,
  amd64_sys_modify_ldt = 154,
  amd64_sys_pivot_root = 155,
  amd64_sys_sysctl = 156,
  amd64_sys_prctl = 157,
  amd64_sys_arch_prctl = 158,
  amd64_sys_adjtimex = 159,
  amd64_sys_setrlimit = 160,
  amd64_sys_chroot = 161,
  amd64_sys_sync = 162,
  amd64_sys_acct = 163,
  amd64_sys_settimeofday = 164,
  amd64_sys_mount = 165,
  amd64_sys_umount = 166,
  amd64_sys_swapon = 167,
  amd64_sys_swapoff = 168,
  amd64_sys_reboot = 169,
  amd64_sys_sethostname = 170,
  amd64_sys_setdomainname = 171,
  amd64_sys_iopl = 172,
  amd64_sys_ioperm = 173,
  amd64_sys_init_module = 175,
  amd64_sys_delete_module = 176,
  amd64_sys_quotactl = 179,
  amd64_sys_nfsservctl = 180,
  amd64_sys_gettid = 186,
  amd64_sys_readahead = 187,
  amd64_sys_setxattr = 188,
  amd64_sys_lsetxattr = 189,
  amd64_sys_fsetxattr = 190,
  amd64_sys_getxattr = 191,
  amd64_sys_lgetxattr = 192,
  amd64_sys_fgetxattr = 193,
  amd64_sys_listxattr = 194,
  amd64_sys_llistxattr = 195,
  amd64_sys_flistxattr = 196,
  amd64_sys_removexattr = 197,
  amd64_sys_lremovexattr = 198,
  amd64_sys_fremovexattr = 199,
  amd64_sys_tkill = 200,
  amd64_sys_time = 201,
  amd64_sys_futex = 202,
  amd64_sys_sched_setaffinity = 203,
  amd64_sys_sched_getaffinity = 204,
  amd64_sys_io_setup = 206,
  amd64_sys_io_destroy = 207,
  amd64_sys_io_getevents = 208,
  amd64_sys_io_submit = 209,
  amd64_sys_io_cancel = 210,
  amd64_sys_lookup_dcookie = 212,
  amd64_sys_epoll_create = 213,
  amd64_sys_remap_file_pages = 216,
  amd64_sys_getdents64 = 217,
  amd64_sys_set_tid_address = 218,
  amd64_sys_restart_syscall = 219,
  amd64_sys_semtimedop = 220,
  amd64_sys_fadvise64 = 221,
  amd64_sys_timer_create = 222,
  amd64_sys_timer_settime = 223,
  amd64_sys_timer_gettime = 224,
  amd64_sys_timer_getoverrun = 225,
  amd64_sys_timer_delete = 226,
  amd64_sys_clock_settime = 227,
  amd64_sys_clock_gettime = 228,
  amd64_sys_clock_getres = 229,
  amd64_sys_clock_nanosleep = 230,
  amd64_sys_exit_group = 231,
  amd64_sys_epoll_wait = 232,
  amd64_sys_epoll_ctl = 233,
  amd64_sys_tgkill = 234,
  amd64_sys_utimes = 235,
  amd64_sys_mbind = 237,
  amd64_sys_set_mempolicy = 238,
  amd64_sys_get_mempolicy = 239,
  amd64_sys_mq_open = 240,
  amd64_sys_mq_unlink = 241,
  amd64_sys_mq_timedsend = 242,
  amd64_sys_mq_timedreceive = 243,
  amd64_sys_mq_notify = 244,
  amd64_sys_mq_getsetattr = 245,
  amd64_sys_kexec_load = 246,
  amd64_sys_waitid = 247,
  amd64_sys_add_key = 248,
  amd64_sys_request_key = 249,
  amd64_sys_keyctl = 250,
  amd64_sys_ioprio_set = 251,
  amd64_sys_ioprio_get = 252,
  amd64_sys_inotify_init = 253,
  amd64_sys_inotify_add_watch = 254,
  amd64_sys_inotify_rm_watch = 255,
  amd64_sys_migrate_pages = 256,
  amd64_sys_openat = 257,
  amd64_sys_mkdirat = 258,
  amd64_sys_mknodat = 259,
  amd64_sys_fchownat = 260,
  amd64_sys_futimesat = 261,
  amd64_sys_newfstatat = 262,
  amd64_sys_unlinkat = 263,
  amd64_sys_renameat = 264,
  amd64_sys_linkat = 265,
  amd64_sys_symlinkat = 266,
  amd64_sys_readlinkat = 267,
  amd64_sys_fchmodat = 268,
  amd64_sys_faccessat = 269,
  amd64_sys_pselect6 = 270,
  amd64_sys_ppoll = 271,
  amd64_sys_unshare = 272,
  amd64_sys_set_robust_list = 273,
  amd64_sys_get_robust_list = 274,
  amd64_sys_splice = 275,
  amd64_sys_tee = 276,
  amd64_sys_sync_file_range = 277,
  amd64_sys_vmsplice = 278,
  amd64_sys_move_pages = 279,
};

#endif /* amd64-linux-tdep.h */
