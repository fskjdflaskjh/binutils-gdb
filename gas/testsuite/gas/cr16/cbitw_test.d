#as:
#objdump:  -dr
#name:  cbitw_test

.*: +file format .*

Disassembly of section .text:

00000000 <main>:
   0:	40 6f cd 0b 	cbitw	\$0x4:s,0xbcd <main\+0xbcd>:m
   4:	5a 6f cd ab 	cbitw	\$0x5:s,0xaabcd <main\+0xaabcd>:m
   8:	11 00 3f 7a 	cbitw	\$0x3:s,0xfaabcd <main\+0xfaabcd>:l
   c:	cd ab 
   e:	a0 6f cd 0b 	cbitw	\$0xa:s,0xbcd <main\+0xbcd>:m
  12:	fa 6f cd ab 	cbitw	\$0xf:s,0xaabcd <main\+0xaabcd>:m
  16:	11 00 ef 7a 	cbitw	\$0xe:s,0xfaabcd <main\+0xfaabcd>:l
  1a:	cd ab 
  1c:	50 6c 14 00 	cbitw	\$0x5:s,\[r13\]0x14:m
  20:	40 6d fc ab 	cbitw	\$0x4:s,\[r13\]0xabfc:m
  24:	30 6c 34 12 	cbitw	\$0x3:s,\[r12\]0x1234:m
  28:	30 6d 34 12 	cbitw	\$0x3:s,\[r12\]0x1234:m
  2c:	30 6c 34 00 	cbitw	\$0x3:s,\[r12\]0x34:m
  30:	f0 6c 14 00 	cbitw	\$0xf:s,\[r13\]0x14:m
  34:	e0 6d fc ab 	cbitw	\$0xe:s,\[r13\]0xabfc:m
  38:	d0 6c 34 12 	cbitw	\$0xd:s,\[r13\]0x1234:m
  3c:	d0 6d 34 12 	cbitw	\$0xd:s,\[r13\]0x1234:m
  40:	b0 6c 34 00 	cbitw	\$0xb:s,\[r12\]0x34:m
  44:	f0 6a 3a 4a 	cbitw	\$0x3:s,\[r12\]0xa7a:m\(r1,r0\)
  48:	f1 6a 3a 4a 	cbitw	\$0x3:s,\[r12\]0xa7a:m\(r3,r2\)
  4c:	f6 6a 3a 4a 	cbitw	\$0x3:s,\[r12\]0xa7a:m\(r4,r3\)
  50:	f2 6a 3a 4a 	cbitw	\$0x3:s,\[r12\]0xa7a:m\(r5,r4\)
  54:	f7 6a 3a 4a 	cbitw	\$0x3:s,\[r12\]0xa7a:m\(r6,r5\)
  58:	f3 6a 3a 4a 	cbitw	\$0x3:s,\[r12\]0xa7a:m\(r7,r6\)
  5c:	f4 6a 3a 4a 	cbitw	\$0x3:s,\[r12\]0xa7a:m\(r9,r8\)
  60:	f5 6a 3a 4a 	cbitw	\$0x3:s,\[r12\]0xa7a:m\(r11,r10\)
  64:	f8 6a 3a 4a 	cbitw	\$0x3:s,\[r13\]0xa7a:m\(r1,r0\)
  68:	f9 6a 3a 4a 	cbitw	\$0x3:s,\[r13\]0xa7a:m\(r3,r2\)
  6c:	fe 6a 3a 4a 	cbitw	\$0x3:s,\[r13\]0xa7a:m\(r4,r3\)
  70:	fa 6a 3a 4a 	cbitw	\$0x3:s,\[r13\]0xa7a:m\(r5,r4\)
  74:	ff 6a 3a 4a 	cbitw	\$0x3:s,\[r13\]0xa7a:m\(r6,r5\)
  78:	fb 6a 3a 4a 	cbitw	\$0x3:s,\[r13\]0xa7a:m\(r7,r6\)
  7c:	fc 6a 3a 4a 	cbitw	\$0x3:s,\[r13\]0xa7a:m\(r9,r8\)
  80:	fd 6a 3a 4a 	cbitw	\$0x3:s,\[r13\]0xa7a:m\(r11,r10\)
  84:	fe 6a 5a 4b 	cbitw	\$0x5:s,\[r13\]0xb7a:m\(r4,r3\)
  88:	f7 6a 1a 41 	cbitw	\$0x1:s,\[r12\]0x17a:m\(r6,r5\)
  8c:	ff 6a 14 01 	cbitw	\$0x1:s,\[r13\]0x134:m\(r6,r5\)
  90:	11 00 36 6a 	cbitw	\$0x3:s,\[r12\]0xabcde:l\(r4,r3\)
  94:	de bc 
  96:	11 00 5e 60 	cbitw	\$0x5:s,\[r13\]0xabcd:l\(r4,r3\)
  9a:	cd ab 
  9c:	11 00 37 60 	cbitw	\$0x3:s,\[r12\]0xabcd:l\(r6,r5\)
  a0:	cd ab 
  a2:	11 00 3f 60 	cbitw	\$0x3:s,\[r13\]0xbcde:l\(r6,r5\)
  a6:	de bc 
  a8:	f0 6a da 4a 	cbitw	\$0xd:s,\[r12\]0xafa:m\(r1,r0\)
  ac:	f1 6a da 4a 	cbitw	\$0xd:s,\[r12\]0xafa:m\(r3,r2\)
  b0:	f6 6a da 4a 	cbitw	\$0xd:s,\[r12\]0xafa:m\(r4,r3\)
  b4:	f2 6a da 4a 	cbitw	\$0xd:s,\[r12\]0xafa:m\(r5,r4\)
  b8:	f7 6a da 4a 	cbitw	\$0xd:s,\[r12\]0xafa:m\(r6,r5\)
  bc:	f3 6a da 4a 	cbitw	\$0xd:s,\[r12\]0xafa:m\(r7,r6\)
  c0:	f4 6a da 4a 	cbitw	\$0xd:s,\[r12\]0xafa:m\(r9,r8\)
  c4:	f5 6a da 4a 	cbitw	\$0xd:s,\[r12\]0xafa:m\(r11,r10\)
  c8:	f8 6a da 4a 	cbitw	\$0xd:s,\[r13\]0xafa:m\(r1,r0\)
  cc:	f9 6a da 4a 	cbitw	\$0xd:s,\[r13\]0xafa:m\(r3,r2\)
  d0:	fe 6a da 4a 	cbitw	\$0xd:s,\[r13\]0xafa:m\(r4,r3\)
  d4:	fa 6a da 4a 	cbitw	\$0xd:s,\[r13\]0xafa:m\(r5,r4\)
  d8:	ff 6a da 4a 	cbitw	\$0xd:s,\[r13\]0xafa:m\(r6,r5\)
  dc:	fb 6a da 4a 	cbitw	\$0xd:s,\[r13\]0xafa:m\(r7,r6\)
  e0:	fc 6a da 4a 	cbitw	\$0xd:s,\[r13\]0xafa:m\(r9,r8\)
  e4:	fd 6a da 4a 	cbitw	\$0xd:s,\[r13\]0xafa:m\(r11,r10\)
  e8:	fe 6a fa 4b 	cbitw	\$0xf:s,\[r13\]0xbfa:m\(r4,r3\)
  ec:	f7 6a ba 41 	cbitw	\$0xb:s,\[r12\]0x1fa:m\(r6,r5\)
  f0:	ff 6a b4 01 	cbitw	\$0xb:s,\[r13\]0x1b4:m\(r6,r5\)
  f4:	11 00 d6 6a 	cbitw	\$0xd:s,\[r12\]0xabcde:l\(r4,r3\)
  f8:	de bc 
  fa:	11 00 fe 60 	cbitw	\$0xf:s,\[r13\]0xabcd:l\(r4,r3\)
  fe:	cd ab 
 100:	11 00 d7 60 	cbitw	\$0xd:s,\[r12\]0xabcd:l\(r6,r5\)
 104:	cd ab 
 106:	11 00 df 60 	cbitw	\$0xd:s,\[r13\]0xbcde:l\(r6,r5\)
 10a:	de bc 
 10c:	11 00 52 40 	cbitw	\$0x5:s,0x0:l\(r2\)
 110:	00 00 
 112:	3c 69 34 00 	cbitw	\$0x3:s,0x34:m\(r12\)
 116:	3d 69 ab 00 	cbitw	\$0x3:s,0xab:m\(r13\)
 11a:	11 00 51 40 	cbitw	\$0x5:s,0xad:l\(r1\)
 11e:	ad 00 
 120:	11 00 52 40 	cbitw	\$0x5:s,0xcd:l\(r2\)
 124:	cd 00 
 126:	11 00 50 40 	cbitw	\$0x5:s,0xfff:l\(r0\)
 12a:	ff 0f 
 12c:	11 00 34 40 	cbitw	\$0x3:s,0xbcd:l\(r4\)
 130:	cd 0b 
 132:	3c 69 ff 0f 	cbitw	\$0x3:s,0xfff:m\(r12\)
 136:	3d 69 ff 0f 	cbitw	\$0x3:s,0xfff:m\(r13\)
 13a:	3d 69 ff ff 	cbitw	\$0x3:s,0xffff:m\(r13\)
 13e:	3c 69 43 23 	cbitw	\$0x3:s,0x2343:m\(r12\)
 142:	11 00 32 41 	cbitw	\$0x3:s,0x2345:l\(r2\)
 146:	45 23 
 148:	11 00 38 44 	cbitw	\$0x3:s,0xabcd:l\(r8\)
 14c:	cd ab 
 14e:	11 00 3d 5f 	cbitw	\$0x3:s,0xfabcd:l\(r13\)
 152:	cd ab 
 154:	11 00 38 4f 	cbitw	\$0x3:s,0xabcd:l\(r8\)
 158:	cd ab 
 15a:	11 00 39 4f 	cbitw	\$0x3:s,0xabcd:l\(r9\)
 15e:	cd ab 
 160:	11 00 39 44 	cbitw	\$0x3:s,0xabcd:l\(r9\)
 164:	cd ab 
 166:	11 00 f2 40 	cbitw	\$0xf:s,0x0:l\(r2\)
 16a:	00 00 
 16c:	dc 69 34 00 	cbitw	\$0xd:s,0x34:m\(r12\)
 170:	dd 69 ab 00 	cbitw	\$0xd:s,0xab:m\(r13\)
 174:	11 00 f1 40 	cbitw	\$0xf:s,0xad:l\(r1\)
 178:	ad 00 
 17a:	11 00 f2 40 	cbitw	\$0xf:s,0xcd:l\(r2\)
 17e:	cd 00 
 180:	11 00 f0 40 	cbitw	\$0xf:s,0xfff:l\(r0\)
 184:	ff 0f 
 186:	11 00 d4 40 	cbitw	\$0xd:s,0xbcd:l\(r4\)
 18a:	cd 0b 
 18c:	dc 69 ff 0f 	cbitw	\$0xd:s,0xfff:m\(r12\)
 190:	dd 69 ff 0f 	cbitw	\$0xd:s,0xfff:m\(r13\)
 194:	dd 69 ff ff 	cbitw	\$0xd:s,0xffff:m\(r13\)
 198:	dc 69 43 23 	cbitw	\$0xd:s,0x2343:m\(r12\)
 19c:	11 00 d2 41 	cbitw	\$0xd:s,0x2345:l\(r2\)
 1a0:	45 23 
 1a2:	11 00 d8 44 	cbitw	\$0xd:s,0xabcd:l\(r8\)
 1a6:	cd ab 
 1a8:	11 00 dd 5f 	cbitw	\$0xd:s,0xfabcd:l\(r13\)
 1ac:	cd ab 
 1ae:	11 00 d8 4f 	cbitw	\$0xd:s,0xabcd:l\(r8\)
 1b2:	cd ab 
 1b4:	11 00 d9 4f 	cbitw	\$0xd:s,0xabcd:l\(r9\)
 1b8:	cd ab 
 1ba:	11 00 d9 44 	cbitw	\$0xd:s,0xabcd:l\(r9\)
 1be:	cd ab 
 1c0:	31 6e       	cbitw	\$0x3:s,0x0:s\(r2,r1\)
 1c2:	51 69 01 00 	cbitw	\$0x5:s,0x1:m\(r2,r1\)
 1c6:	41 69 34 12 	cbitw	\$0x4:s,0x1234:m\(r2,r1\)
 1ca:	31 69 34 12 	cbitw	\$0x3:s,0x1234:m\(r2,r1\)
 1ce:	11 00 31 51 	cbitw	\$0x3:s,0x12345:l\(r2,r1\)
 1d2:	45 23 
 1d4:	31 69 23 01 	cbitw	\$0x3:s,0x123:m\(r2,r1\)
 1d8:	11 00 31 51 	cbitw	\$0x3:s,0x12345:l\(r2,r1\)
 1dc:	45 23 
 1de:	d1 6e       	cbitw	\$0xd:s,0x0:s\(r2,r1\)
 1e0:	f1 69 01 00 	cbitw	\$0xf:s,0x1:m\(r2,r1\)
 1e4:	e1 69 34 12 	cbitw	\$0xe:s,0x1234:m\(r2,r1\)
 1e8:	d1 69 34 12 	cbitw	\$0xd:s,0x1234:m\(r2,r1\)
 1ec:	11 00 d1 51 	cbitw	\$0xd:s,0x12345:l\(r2,r1\)
 1f0:	45 23 
 1f2:	d1 69 23 01 	cbitw	\$0xd:s,0x123:m\(r2,r1\)
 1f6:	11 00 d1 51 	cbitw	\$0xd:s,0x12345:l\(r2,r1\)
 1fa:	45 23 
