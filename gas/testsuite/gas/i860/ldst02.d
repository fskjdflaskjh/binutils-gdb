#as:
#objdump: -dr
#name: ldst02 (ld.s)

.*: +file format .*

Disassembly of section \.text:

00000000 <\.text>:
   0:	00 00 00 14 	ld.s	0\(%r0\),%r0
   4:	7a 00 3f 14 	ld.s	122\(%r1\),%r31
   8:	02 01 5e 14 	ld.s	258\(%sp\),%r30
   c:	00 02 7d 14 	ld.s	512\(%fp\),%r29
  10:	04 04 9c 14 	ld.s	1028\(%r4\),%r28
  14:	fa 0f bb 14 	ld.s	4090\(%r5\),%r27
  18:	fe 1f da 14 	ld.s	8190\(%r6\),%r26
  1c:	00 40 f9 14 	ld.s	16384\(%r7\),%r25
  20:	00 c0 18 15 	ld.s	-16384\(%r8\),%r24
  24:	00 e0 37 15 	ld.s	-8192\(%r9\),%r23
  28:	00 f0 56 15 	ld.s	-4096\(%r10\),%r22
  2c:	00 fc 75 15 	ld.s	-1024\(%r11\),%r21
  30:	04 fe 94 15 	ld.s	-508\(%r12\),%r20
  34:	0e ff b3 15 	ld.s	-242\(%r13\),%r19
  38:	fe ff d2 15 	ld.s	-2\(%r14\),%r18
  3c:	00 28 00 10 	ld.s	%r5\(%r0\),%r0
  40:	00 30 3f 10 	ld.s	%r6\(%r1\),%r31
  44:	00 38 5e 10 	ld.s	%r7\(%sp\),%r30
  48:	00 40 7d 10 	ld.s	%r8\(%fp\),%r29
  4c:	00 48 9c 10 	ld.s	%r9\(%r4\),%r28
  50:	00 00 bb 10 	ld.s	%r0\(%r5\),%r27
  54:	00 08 da 10 	ld.s	%r1\(%r6\),%r26
  58:	00 60 f9 10 	ld.s	%r12\(%r7\),%r25
  5c:	00 68 18 11 	ld.s	%r13\(%r8\),%r24
  60:	00 70 37 11 	ld.s	%r14\(%r9\),%r23
  64:	00 78 56 11 	ld.s	%r15\(%r10\),%r22
  68:	00 80 75 11 	ld.s	%r16\(%r11\),%r21
  6c:	00 88 94 11 	ld.s	%r17\(%r12\),%r20
  70:	00 e0 b3 11 	ld.s	%r28\(%r13\),%r19
  74:	00 f8 d2 11 	ld.s	%r31\(%r14\),%r18
