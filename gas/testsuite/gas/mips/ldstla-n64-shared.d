#objdump: -d
#as: -KPIC -64
#name: MIPS ld-st-la constants (ABI n64, shared)
#source: ldstla-n64.s

.*: +file format elf64-.*mips

Disassembly of section \.text:

0000000000000000 <\.text>:
   0:	3c020123 	lui	v0,0x123
   4:	34424567 	ori	v0,v0,0x4567
   8:	00021438 	dsll	v0,v0,0x10
   c:	344289ac 	ori	v0,v0,0x89ac
  10:	00021438 	dsll	v0,v0,0x10
  14:	0043102d 	daddu	v0,v0,v1
  18:	dc42cdef 	ld	v0,-12817\(v0\)
  1c:	3c02abcd 	lui	v0,0xabcd
  20:	3442ef01 	ori	v0,v0,0xef01
  24:	00021438 	dsll	v0,v0,0x10
  28:	34422345 	ori	v0,v0,0x2345
  2c:	00021438 	dsll	v0,v0,0x10
  30:	0043102d 	daddu	v0,v0,v1
  34:	dc426789 	ld	v0,26505\(v0\)
  38:	3c028000 	lui	v0,0x8000
  3c:	0043102d 	daddu	v0,v0,v1
  40:	dc420000 	ld	v0,0\(v0\)
  44:	2402ffff 	li	v0,-1
  48:	0002103c 	dsll32	v0,v0,0x0
  4c:	0043102d 	daddu	v0,v0,v1
  50:	dc420000 	ld	v0,0\(v0\)
  54:	3c028000 	lui	v0,0x8000
  58:	0043102d 	daddu	v0,v0,v1
  5c:	dc42ffff 	ld	v0,-1\(v0\)
  60:	3402abce 	li	v0,0xabce
  64:	00021438 	dsll	v0,v0,0x10
  68:	0043102d 	daddu	v0,v0,v1
  6c:	dc42ef01 	ld	v0,-4351\(v0\)
  70:	3c020123 	lui	v0,0x123
  74:	0043102d 	daddu	v0,v0,v1
  78:	dc424567 	ld	v0,17767\(v0\)
  7c:	3c010123 	lui	at,0x123
  80:	34214567 	ori	at,at,0x4567
  84:	00010c38 	dsll	at,at,0x10
  88:	342189ac 	ori	at,at,0x89ac
  8c:	00010c38 	dsll	at,at,0x10
  90:	0023082d 	daddu	at,at,v1
  94:	fc22cdef 	sd	v0,-12817\(at\)
  98:	3c01abcd 	lui	at,0xabcd
  9c:	3421ef01 	ori	at,at,0xef01
  a0:	00010c38 	dsll	at,at,0x10
  a4:	34212345 	ori	at,at,0x2345
  a8:	00010c38 	dsll	at,at,0x10
  ac:	0023082d 	daddu	at,at,v1
  b0:	fc226789 	sd	v0,26505\(at\)
  b4:	3c018000 	lui	at,0x8000
  b8:	0023082d 	daddu	at,at,v1
  bc:	fc220000 	sd	v0,0\(at\)
  c0:	2401ffff 	li	at,-1
  c4:	0001083c 	dsll32	at,at,0x0
  c8:	0023082d 	daddu	at,at,v1
  cc:	fc220000 	sd	v0,0\(at\)
  d0:	3c018000 	lui	at,0x8000
  d4:	0023082d 	daddu	at,at,v1
  d8:	fc22ffff 	sd	v0,-1\(at\)
  dc:	3401abce 	li	at,0xabce
  e0:	00010c38 	dsll	at,at,0x10
  e4:	0023082d 	daddu	at,at,v1
  e8:	fc22ef01 	sd	v0,-4351\(at\)
  ec:	3c010123 	lui	at,0x123
  f0:	0023082d 	daddu	at,at,v1
  f4:	fc224567 	sd	v0,17767\(at\)
  f8:	3c020123 	lui	v0,0x123
  fc:	34424567 	ori	v0,v0,0x4567
 100:	00021438 	dsll	v0,v0,0x10
 104:	344289ac 	ori	v0,v0,0x89ac
 108:	00021438 	dsll	v0,v0,0x10
 10c:	0043102d 	daddu	v0,v0,v1
 110:	8c42cdef 	lw	v0,-12817\(v0\)
 114:	3c02abcd 	lui	v0,0xabcd
 118:	3442ef01 	ori	v0,v0,0xef01
 11c:	00021438 	dsll	v0,v0,0x10
 120:	34422345 	ori	v0,v0,0x2345
 124:	00021438 	dsll	v0,v0,0x10
 128:	0043102d 	daddu	v0,v0,v1
 12c:	8c426789 	lw	v0,26505\(v0\)
 130:	3c028000 	lui	v0,0x8000
 134:	0043102d 	daddu	v0,v0,v1
 138:	8c420000 	lw	v0,0\(v0\)
 13c:	2402ffff 	li	v0,-1
 140:	0002103c 	dsll32	v0,v0,0x0
 144:	0043102d 	daddu	v0,v0,v1
 148:	8c420000 	lw	v0,0\(v0\)
 14c:	3c028000 	lui	v0,0x8000
 150:	0043102d 	daddu	v0,v0,v1
 154:	8c42ffff 	lw	v0,-1\(v0\)
 158:	3402abce 	li	v0,0xabce
 15c:	00021438 	dsll	v0,v0,0x10
 160:	0043102d 	daddu	v0,v0,v1
 164:	8c42ef01 	lw	v0,-4351\(v0\)
 168:	3c020123 	lui	v0,0x123
 16c:	0043102d 	daddu	v0,v0,v1
 170:	8c424567 	lw	v0,17767\(v0\)
 174:	3c010123 	lui	at,0x123
 178:	34214567 	ori	at,at,0x4567
 17c:	00010c38 	dsll	at,at,0x10
 180:	342189ac 	ori	at,at,0x89ac
 184:	00010c38 	dsll	at,at,0x10
 188:	0023082d 	daddu	at,at,v1
 18c:	ac22cdef 	sw	v0,-12817\(at\)
 190:	3c01abcd 	lui	at,0xabcd
 194:	3421ef01 	ori	at,at,0xef01
 198:	00010c38 	dsll	at,at,0x10
 19c:	34212345 	ori	at,at,0x2345
 1a0:	00010c38 	dsll	at,at,0x10
 1a4:	0023082d 	daddu	at,at,v1
 1a8:	ac226789 	sw	v0,26505\(at\)
 1ac:	3c018000 	lui	at,0x8000
 1b0:	0023082d 	daddu	at,at,v1
 1b4:	ac220000 	sw	v0,0\(at\)
 1b8:	2401ffff 	li	at,-1
 1bc:	0001083c 	dsll32	at,at,0x0
 1c0:	0023082d 	daddu	at,at,v1
 1c4:	ac220000 	sw	v0,0\(at\)
 1c8:	3c018000 	lui	at,0x8000
 1cc:	0023082d 	daddu	at,at,v1
 1d0:	ac22ffff 	sw	v0,-1\(at\)
 1d4:	3401abce 	li	at,0xabce
 1d8:	00010c38 	dsll	at,at,0x10
 1dc:	0023082d 	daddu	at,at,v1
 1e0:	ac22ef01 	sw	v0,-4351\(at\)
 1e4:	3c010123 	lui	at,0x123
 1e8:	0023082d 	daddu	at,at,v1
 1ec:	ac224567 	sw	v0,17767\(at\)
 1f0:	3c020123 	lui	v0,0x123
 1f4:	34424567 	ori	v0,v0,0x4567
 1f8:	00021438 	dsll	v0,v0,0x10
 1fc:	344289ab 	ori	v0,v0,0x89ab
 200:	00021438 	dsll	v0,v0,0x10
 204:	3442cdef 	ori	v0,v0,0xcdef
 208:	3c02abcd 	lui	v0,0xabcd
 20c:	3442ef01 	ori	v0,v0,0xef01
 210:	00021438 	dsll	v0,v0,0x10
 214:	34422345 	ori	v0,v0,0x2345
 218:	00021438 	dsll	v0,v0,0x10
 21c:	34426789 	ori	v0,v0,0x6789
 220:	3c028000 	lui	v0,0x8000
 224:	2402ffff 	li	v0,-1
 228:	0002103c 	dsll32	v0,v0,0x0
 22c:	3402abcd 	li	v0,0xabcd
 230:	00021438 	dsll	v0,v0,0x10
 234:	3442ef01 	ori	v0,v0,0xef01
 238:	3c027fff 	lui	v0,0x7fff
 23c:	3442ffff 	ori	v0,v0,0xffff
 240:	3c020123 	lui	v0,0x123
 244:	34424567 	ori	v0,v0,0x4567
	\.\.\.
