#objdump: -d
#as: -n64
#name: MIPS ld-st-la constants (ABI n64)
#source: ldstla-n64.s

.*: +file format elf64-.*mips

Disassembly of section \.text:

0000000000000000 <\.text>:
   0:	3c020123 	lui	v0,0x123
   4:	3c0189ac 	lui	at,0x89ac
   8:	64424568 	daddiu	v0,v0,17768
   c:	0023082d 	daddu	at,at,v1
  10:	0002103c 	dsll32	v0,v0,0x0
  14:	0041102d 	daddu	v0,v0,at
  18:	dc42cdef 	ld	v0,-12817\(v0\)
  1c:	3c02abce 	lui	v0,0xabce
  20:	3c012345 	lui	at,0x2345
  24:	6442ef01 	daddiu	v0,v0,-4351
  28:	0023082d 	daddu	at,at,v1
  2c:	0002103c 	dsll32	v0,v0,0x0
  30:	0041102d 	daddu	v0,v0,at
  34:	dc426789 	ld	v0,26505\(v0\)
  38:	3c028000 	lui	v0,0x8000
  3c:	0043102d 	daddu	v0,v0,v1
  40:	dc420000 	ld	v0,0\(v0\)
  44:	3c020000 	lui	v0,0x0
  48:	3c010000 	lui	at,0x0
  4c:	6442ffff 	daddiu	v0,v0,-1
  50:	0023082d 	daddu	at,at,v1
  54:	0002103c 	dsll32	v0,v0,0x0
  58:	0041102d 	daddu	v0,v0,at
  5c:	dc420000 	ld	v0,0\(v0\)
  60:	3c028000 	lui	v0,0x8000
  64:	0043102d 	daddu	v0,v0,v1
  68:	dc42ffff 	ld	v0,-1\(v0\)
  6c:	3c020000 	lui	v0,0x0
  70:	3c01abce 	lui	at,0xabce
  74:	64420001 	daddiu	v0,v0,1
  78:	0023082d 	daddu	at,at,v1
  7c:	0002103c 	dsll32	v0,v0,0x0
  80:	0041102d 	daddu	v0,v0,at
  84:	dc42ef01 	ld	v0,-4351\(v0\)
  88:	3c020123 	lui	v0,0x123
  8c:	0043102d 	daddu	v0,v0,v1
  90:	dc424567 	ld	v0,17767\(v0\)
  94:	3c010123 	lui	at,0x123
  98:	64214568 	daddiu	at,at,17768
  9c:	00010c38 	dsll	at,at,0x10
  a0:	642189ac 	daddiu	at,at,-30292
  a4:	00010c38 	dsll	at,at,0x10
  a8:	0023082d 	daddu	at,at,v1
  ac:	fc22cdef 	sd	v0,-12817\(at\)
  b0:	3c01abce 	lui	at,0xabce
  b4:	6421ef01 	daddiu	at,at,-4351
  b8:	00010c38 	dsll	at,at,0x10
  bc:	64212345 	daddiu	at,at,9029
  c0:	00010c38 	dsll	at,at,0x10
  c4:	0023082d 	daddu	at,at,v1
  c8:	fc226789 	sd	v0,26505\(at\)
  cc:	3c018000 	lui	at,0x8000
  d0:	0023082d 	daddu	at,at,v1
  d4:	fc220000 	sd	v0,0\(at\)
  d8:	3c010000 	lui	at,0x0
  dc:	6421ffff 	daddiu	at,at,-1
  e0:	00010c38 	dsll	at,at,0x10
  e4:	64210000 	daddiu	at,at,0
  e8:	00010c38 	dsll	at,at,0x10
  ec:	0023082d 	daddu	at,at,v1
  f0:	fc220000 	sd	v0,0\(at\)
  f4:	3c018000 	lui	at,0x8000
  f8:	0023082d 	daddu	at,at,v1
  fc:	fc22ffff 	sd	v0,-1\(at\)
 100:	3c010000 	lui	at,0x0
 104:	64210001 	daddiu	at,at,1
 108:	00010c38 	dsll	at,at,0x10
 10c:	6421abce 	daddiu	at,at,-21554
 110:	00010c38 	dsll	at,at,0x10
 114:	0023082d 	daddu	at,at,v1
 118:	fc22ef01 	sd	v0,-4351\(at\)
 11c:	3c010123 	lui	at,0x123
 120:	0023082d 	daddu	at,at,v1
 124:	fc224567 	sd	v0,17767\(at\)
 128:	3c020123 	lui	v0,0x123
 12c:	3c0189ac 	lui	at,0x89ac
 130:	64424568 	daddiu	v0,v0,17768
 134:	0023082d 	daddu	at,at,v1
 138:	0002103c 	dsll32	v0,v0,0x0
 13c:	0041102d 	daddu	v0,v0,at
 140:	8c42cdef 	lw	v0,-12817\(v0\)
 144:	3c02abce 	lui	v0,0xabce
 148:	3c012345 	lui	at,0x2345
 14c:	6442ef01 	daddiu	v0,v0,-4351
 150:	0023082d 	daddu	at,at,v1
 154:	0002103c 	dsll32	v0,v0,0x0
 158:	0041102d 	daddu	v0,v0,at
 15c:	8c426789 	lw	v0,26505\(v0\)
 160:	3c028000 	lui	v0,0x8000
 164:	0043102d 	daddu	v0,v0,v1
 168:	8c420000 	lw	v0,0\(v0\)
 16c:	3c020000 	lui	v0,0x0
 170:	3c010000 	lui	at,0x0
 174:	6442ffff 	daddiu	v0,v0,-1
 178:	0023082d 	daddu	at,at,v1
 17c:	0002103c 	dsll32	v0,v0,0x0
 180:	0041102d 	daddu	v0,v0,at
 184:	8c420000 	lw	v0,0\(v0\)
 188:	3c028000 	lui	v0,0x8000
 18c:	0043102d 	daddu	v0,v0,v1
 190:	8c42ffff 	lw	v0,-1\(v0\)
 194:	3c020000 	lui	v0,0x0
 198:	3c01abce 	lui	at,0xabce
 19c:	64420001 	daddiu	v0,v0,1
 1a0:	0023082d 	daddu	at,at,v1
 1a4:	0002103c 	dsll32	v0,v0,0x0
 1a8:	0041102d 	daddu	v0,v0,at
 1ac:	8c42ef01 	lw	v0,-4351\(v0\)
 1b0:	3c020123 	lui	v0,0x123
 1b4:	0043102d 	daddu	v0,v0,v1
 1b8:	8c424567 	lw	v0,17767\(v0\)
 1bc:	3c010123 	lui	at,0x123
 1c0:	64214568 	daddiu	at,at,17768
 1c4:	00010c38 	dsll	at,at,0x10
 1c8:	642189ac 	daddiu	at,at,-30292
 1cc:	00010c38 	dsll	at,at,0x10
 1d0:	0023082d 	daddu	at,at,v1
 1d4:	ac22cdef 	sw	v0,-12817\(at\)
 1d8:	3c01abce 	lui	at,0xabce
 1dc:	6421ef01 	daddiu	at,at,-4351
 1e0:	00010c38 	dsll	at,at,0x10
 1e4:	64212345 	daddiu	at,at,9029
 1e8:	00010c38 	dsll	at,at,0x10
 1ec:	0023082d 	daddu	at,at,v1
 1f0:	ac226789 	sw	v0,26505\(at\)
 1f4:	3c018000 	lui	at,0x8000
 1f8:	0023082d 	daddu	at,at,v1
 1fc:	ac220000 	sw	v0,0\(at\)
 200:	3c010000 	lui	at,0x0
 204:	6421ffff 	daddiu	at,at,-1
 208:	00010c38 	dsll	at,at,0x10
 20c:	64210000 	daddiu	at,at,0
 210:	00010c38 	dsll	at,at,0x10
 214:	0023082d 	daddu	at,at,v1
 218:	ac220000 	sw	v0,0\(at\)
 21c:	3c018000 	lui	at,0x8000
 220:	0023082d 	daddu	at,at,v1
 224:	ac22ffff 	sw	v0,-1\(at\)
 228:	3c010000 	lui	at,0x0
 22c:	64210001 	daddiu	at,at,1
 230:	00010c38 	dsll	at,at,0x10
 234:	6421abce 	daddiu	at,at,-21554
 238:	00010c38 	dsll	at,at,0x10
 23c:	0023082d 	daddu	at,at,v1
 240:	ac22ef01 	sw	v0,-4351\(at\)
 244:	3c010123 	lui	at,0x123
 248:	0023082d 	daddu	at,at,v1
 24c:	ac224567 	sw	v0,17767\(at\)
 250:	3c020123 	lui	v0,0x123
 254:	34424567 	ori	v0,v0,0x4567
 258:	00021438 	dsll	v0,v0,0x10
 25c:	344289ab 	ori	v0,v0,0x89ab
 260:	00021438 	dsll	v0,v0,0x10
 264:	3442cdef 	ori	v0,v0,0xcdef
 268:	3c02abcd 	lui	v0,0xabcd
 26c:	3442ef01 	ori	v0,v0,0xef01
 270:	00021438 	dsll	v0,v0,0x10
 274:	34422345 	ori	v0,v0,0x2345
 278:	00021438 	dsll	v0,v0,0x10
 27c:	34426789 	ori	v0,v0,0x6789
 280:	3c028000 	lui	v0,0x8000
 284:	2402ffff 	li	v0,-1
 288:	0002103c 	dsll32	v0,v0,0x0
 28c:	3402abcd 	li	v0,0xabcd
 290:	00021438 	dsll	v0,v0,0x10
 294:	3442ef01 	ori	v0,v0,0xef01
 298:	3c027fff 	lui	v0,0x7fff
 29c:	3442ffff 	ori	v0,v0,0xffff
 2a0:	3c020123 	lui	v0,0x123
 2a4:	34424567 	ori	v0,v0,0x4567
	\.\.\.
