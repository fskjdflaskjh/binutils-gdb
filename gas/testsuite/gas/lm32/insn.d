#as:
#objdump: -d
#name: insn

dump.o:     file format elf32-lm32.*

Disassembly of section .text:

00000000 <.text>:
   0:	b4 00 f8 00 	add ba,r0,r0
   4:	b7 e0 00 00 	add r0,ba,r0
   8:	b4 1f 00 00 	add r0,r0,ba
   c:	b4 43 08 00 	add r1,r2,r3
  10:	34 00 00 00 	nop
  14:	34 00 80 00 	mvi r0,-32768
  18:	34 00 7f ff 	mvi r0,32767
  1c:	37 e0 00 00 	addi r0,ba,0
  20:	37 e0 80 00 	addi r0,ba,-32768
  24:	37 e0 7f ff 	addi r0,ba,32767
  28:	34 1f 00 00 	mvi ba,0
  2c:	34 1f 80 00 	mvi ba,-32768
  30:	34 1f 7f ff 	mvi ba,32767
  34:	a0 00 f8 00 	and ba,r0,r0
  38:	a3 e0 00 00 	and r0,ba,r0
  3c:	a0 1f 00 00 	and r0,r0,ba
  40:	a0 43 08 00 	and r1,r2,r3
  44:	20 00 00 00 	andi r0,r0,0x0
  48:	20 00 ff ff 	andi r0,r0,0xffff
  4c:	23 e0 00 00 	andi r0,ba,0x0
  50:	23 e0 ff ff 	andi r0,ba,0xffff
  54:	20 1f 00 00 	andi ba,r0,0x0
  58:	20 1f ff ff 	andi ba,r0,0xffff
  5c:	60 00 00 00 	andhi r0,r0,0x0
  60:	60 00 ff ff 	andhi r0,r0,0xffff
  64:	63 e0 00 00 	andhi r0,ba,0x0
  68:	63 e0 ff ff 	andhi r0,ba,0xffff
  6c:	60 1f 00 00 	andhi ba,r0,0x0
  70:	60 1f ff ff 	andhi ba,r0,0xffff
  74:	60 00 00 00 	andhi r0,r0,0x0
  78:	60 00 ff ff 	andhi r0,r0,0xffff
  7c:	e0 00 00 00 	bi 0x7c
  80:	c0 00 00 00 	b r0
  84:	c3 e0 00 00 	bret
  88:	44 00 00 00 	be r0,r0,0x88
  8c:	44 22 00 00 	be r1,r2,0x8c
  90:	48 00 00 00 	bg r0,r0,0x90
  94:	48 22 00 00 	bg r1,r2,0x94
  98:	4c 00 00 00 	bge r0,r0,0x98
  9c:	4c 22 00 00 	bge r1,r2,0x9c
  a0:	50 00 00 00 	bgeu r0,r0,0xa0
  a4:	50 22 00 00 	bgeu r1,r2,0xa4
  a8:	54 00 00 00 	bgu r0,r0,0xa8
  ac:	54 22 00 00 	bgu r1,r2,0xac
  b0:	5c 00 00 00 	bne r0,r0,0xb0
  b4:	5c 22 00 00 	bne r1,r2,0xb4
  b8:	f8 00 00 00 	calli 0xb8
  bc:	d8 00 00 00 	call r0
  c0:	db e0 00 00 	call ba
  c4:	e4 00 f8 00 	cmpe ba,r0,r0
  c8:	e7 e0 00 00 	cmpe r0,ba,r0
  cc:	e4 1f 00 00 	cmpe r0,r0,ba
  d0:	e4 43 08 00 	cmpe r1,r2,r3
  d4:	64 00 00 00 	cmpei r0,r0,0
  d8:	64 00 80 00 	cmpei r0,r0,-32768
  dc:	64 00 7f ff 	cmpei r0,r0,32767
  e0:	67 e0 00 00 	cmpei r0,ba,0
  e4:	67 e0 80 00 	cmpei r0,ba,-32768
  e8:	67 e0 7f ff 	cmpei r0,ba,32767
  ec:	64 1f 00 00 	cmpei ba,r0,0
  f0:	64 1f 80 00 	cmpei ba,r0,-32768
  f4:	64 1f 7f ff 	cmpei ba,r0,32767
  f8:	e8 00 f8 00 	cmpg ba,r0,r0
  fc:	eb e0 00 00 	cmpg r0,ba,r0
 100:	e8 1f 00 00 	cmpg r0,r0,ba
 104:	e8 43 08 00 	cmpg r1,r2,r3
 108:	68 00 00 00 	cmpgi r0,r0,0
 10c:	68 00 80 00 	cmpgi r0,r0,-32768
 110:	68 00 7f ff 	cmpgi r0,r0,32767
 114:	6b e0 00 00 	cmpgi r0,ba,0
 118:	6b e0 80 00 	cmpgi r0,ba,-32768
 11c:	6b e0 7f ff 	cmpgi r0,ba,32767
 120:	68 1f 00 00 	cmpgi ba,r0,0
 124:	68 1f 80 00 	cmpgi ba,r0,-32768
 128:	68 1f 7f ff 	cmpgi ba,r0,32767
 12c:	ec 00 f8 00 	cmpge ba,r0,r0
 130:	ef e0 00 00 	cmpge r0,ba,r0
 134:	ec 1f 00 00 	cmpge r0,r0,ba
 138:	ec 43 08 00 	cmpge r1,r2,r3
 13c:	6c 00 00 00 	cmpgei r0,r0,0
 140:	6c 00 80 00 	cmpgei r0,r0,-32768
 144:	6c 00 7f ff 	cmpgei r0,r0,32767
 148:	6f e0 00 00 	cmpgei r0,ba,0
 14c:	6f e0 80 00 	cmpgei r0,ba,-32768
 150:	6f e0 7f ff 	cmpgei r0,ba,32767
 154:	6c 1f 00 00 	cmpgei ba,r0,0
 158:	6c 1f 80 00 	cmpgei ba,r0,-32768
 15c:	6c 1f 7f ff 	cmpgei ba,r0,32767
 160:	f0 00 f8 00 	cmpgeu ba,r0,r0
 164:	f3 e0 00 00 	cmpgeu r0,ba,r0
 168:	f0 1f 00 00 	cmpgeu r0,r0,ba
 16c:	f0 43 08 00 	cmpgeu r1,r2,r3
 170:	70 00 00 00 	cmpgeui r0,r0,0x0
 174:	70 00 ff ff 	cmpgeui r0,r0,0xffff
 178:	73 e0 00 00 	cmpgeui r0,ba,0x0
 17c:	73 e0 ff ff 	cmpgeui r0,ba,0xffff
 180:	70 1f 00 00 	cmpgeui ba,r0,0x0
 184:	70 1f ff ff 	cmpgeui ba,r0,0xffff
 188:	f4 00 f8 00 	cmpgu ba,r0,r0
 18c:	f7 e0 00 00 	cmpgu r0,ba,r0
 190:	f4 1f 00 00 	cmpgu r0,r0,ba
 194:	f4 43 08 00 	cmpgu r1,r2,r3
 198:	74 00 00 00 	cmpgui r0,r0,0x0
 19c:	74 00 ff ff 	cmpgui r0,r0,0xffff
 1a0:	77 e0 00 00 	cmpgui r0,ba,0x0
 1a4:	77 e0 ff ff 	cmpgui r0,ba,0xffff
 1a8:	74 1f 00 00 	cmpgui ba,r0,0x0
 1ac:	74 1f ff ff 	cmpgui ba,r0,0xffff
 1b0:	fc 00 f8 00 	cmpne ba,r0,r0
 1b4:	ff e0 00 00 	cmpne r0,ba,r0
 1b8:	fc 1f 00 00 	cmpne r0,r0,ba
 1bc:	fc 43 08 00 	cmpne r1,r2,r3
 1c0:	7c 00 00 00 	cmpnei r0,r0,0
 1c4:	7c 00 80 00 	cmpnei r0,r0,-32768
 1c8:	7c 00 7f ff 	cmpnei r0,r0,32767
 1cc:	7f e0 00 00 	cmpnei r0,ba,0
 1d0:	7f e0 80 00 	cmpnei r0,ba,-32768
 1d4:	7f e0 7f ff 	cmpnei r0,ba,32767
 1d8:	7c 1f 00 00 	cmpnei ba,r0,0
 1dc:	7c 1f 80 00 	cmpnei ba,r0,-32768
 1e0:	7c 1f 7f ff 	cmpnei ba,r0,32767
 1e4:	8c 00 f8 00 	divu ba,r0,r0
 1e8:	8f e0 00 00 	divu r0,ba,r0
 1ec:	8c 1f 00 00 	divu r0,r0,ba
 1f0:	8c 43 08 00 	divu r1,r2,r3
 1f4:	c4 00 f8 00 	modu ba,r0,r0
 1f8:	c7 e0 00 00 	modu r0,ba,r0
 1fc:	c4 1f 00 00 	modu r0,r0,ba
 200:	c4 43 08 00 	modu r1,r2,r3
 204:	88 00 f8 00 	mul ba,r0,r0
 208:	8b e0 00 00 	mul r0,ba,r0
 20c:	88 1f 00 00 	mul r0,r0,ba
 210:	88 43 08 00 	mul r1,r2,r3
 214:	08 00 00 00 	muli r0,r0,0
 218:	08 00 80 00 	muli r0,r0,-32768
 21c:	08 00 7f ff 	muli r0,r0,32767
 220:	0b e0 00 00 	muli r0,ba,0
 224:	0b e0 80 00 	muli r0,ba,-32768
 228:	0b e0 7f ff 	muli r0,ba,32767
 22c:	08 1f 00 00 	muli ba,r0,0
 230:	08 1f 80 00 	muli ba,r0,-32768
 234:	08 1f 7f ff 	muli ba,r0,32767
 238:	84 00 f8 00 	nor ba,r0,r0
 23c:	87 e0 00 00 	nor r0,ba,r0
 240:	84 1f 00 00 	nor r0,r0,ba
 244:	84 43 08 00 	nor r1,r2,r3
 248:	04 00 00 00 	nori r0,r0,0x0
 24c:	04 00 ff ff 	nori r0,r0,0xffff
 250:	07 e0 00 00 	nori r0,ba,0x0
 254:	07 e0 ff ff 	nori r0,ba,0xffff
 258:	04 1f 00 00 	nori ba,r0,0x0
 25c:	04 1f ff ff 	nori ba,r0,0xffff
 260:	b8 00 f8 00 	mv ba,r0
 264:	bb e0 00 00 	mv r0,ba
 268:	b8 1f 00 00 	or r0,r0,ba
 26c:	b8 43 08 00 	or r1,r2,r3
 270:	38 00 00 00 	mvu r0,0x0
 274:	38 00 ff ff 	mvu r0,0xffff
 278:	3b e0 00 00 	ori r0,ba,0x0
 27c:	3b e0 ff ff 	ori r0,ba,0xffff
 280:	38 1f 00 00 	mvu ba,0x0
 284:	38 1f ff ff 	mvu ba,0xffff
 288:	38 00 00 00 	mvu r0,0x0
 28c:	38 00 ff ff 	mvu r0,0xffff
 290:	78 00 00 00 	mvhi r0,0x0
 294:	78 00 ff ff 	mvhi r0,0xffff
 298:	7b e0 00 00 	orhi r0,ba,0x0
 29c:	7b e0 ff ff 	orhi r0,ba,0xffff
 2a0:	78 1f 00 00 	mvhi ba,0x0
 2a4:	78 1f ff ff 	mvhi ba,0xffff
 2a8:	78 00 00 00 	mvhi r0,0x0
 2ac:	78 00 ff ff 	mvhi r0,0xffff
 2b0:	bc 00 f8 00 	sl ba,r0,r0
 2b4:	bf e0 00 00 	sl r0,ba,r0
 2b8:	bc 1f 00 00 	sl r0,r0,ba
 2bc:	bc 43 08 00 	sl r1,r2,r3
 2c0:	94 00 f8 00 	sr ba,r0,r0
 2c4:	97 e0 00 00 	sr r0,ba,r0
 2c8:	94 1f 00 00 	sr r0,r0,ba
 2cc:	94 43 08 00 	sr r1,r2,r3
 2d0:	80 00 f8 00 	sru ba,r0,r0
 2d4:	83 e0 00 00 	sru r0,ba,r0
 2d8:	80 1f 00 00 	sru r0,r0,ba
 2dc:	80 43 08 00 	sru r1,r2,r3
 2e0:	3c 00 00 00 	sli r0,r0,0
 2e4:	3c 00 00 1f 	sli r0,r0,31
 2e8:	14 00 00 00 	sri r0,r0,0
 2ec:	14 00 00 1f 	sri r0,r0,31
 2f0:	00 00 00 00 	srui r0,r0,0
 2f4:	00 00 00 1f 	srui r0,r0,31
 2f8:	c8 00 f8 00 	sub ba,r0,r0
 2fc:	cb e0 00 00 	sub r0,ba,r0
 300:	c8 1f 00 00 	sub r0,r0,ba
 304:	c8 43 08 00 	sub r1,r2,r3
 308:	a4 00 f8 00 	not ba,r0
 30c:	a7 e0 00 00 	not r0,ba
 310:	a4 1f 00 00 	xnor r0,r0,ba
 314:	a4 43 08 00 	xnor r1,r2,r3
 318:	24 00 00 00 	xnori r0,r0,0x0
 31c:	24 00 ff ff 	xnori r0,r0,0xffff
 320:	27 e0 00 00 	xnori r0,ba,0x0
 324:	27 e0 ff ff 	xnori r0,ba,0xffff
 328:	24 1f 00 00 	xnori ba,r0,0x0
 32c:	24 1f ff ff 	xnori ba,r0,0xffff
 330:	98 00 f8 00 	xor ba,r0,r0
 334:	9b e0 00 00 	xor r0,ba,r0
 338:	98 1f 00 00 	xor r0,r0,ba
 33c:	98 43 08 00 	xor r1,r2,r3
 340:	18 00 00 00 	xori r0,r0,0x0
 344:	18 00 ff ff 	xori r0,r0,0xffff
 348:	1b e0 00 00 	xori r0,ba,0x0
 34c:	1b e0 ff ff 	xori r0,ba,0xffff
 350:	18 1f 00 00 	xori ba,r0,0x0
 354:	18 1f ff ff 	xori ba,r0,0xffff
 358:	b0 00 00 00 	sextb r0,r0
 35c:	b0 00 f8 00 	sextb ba,r0
 360:	b3 e0 00 00 	sextb r0,ba
 364:	b0 20 10 00 	sextb r2,r1
 368:	dc 00 00 00 	sexth r0,r0
 36c:	dc 00 f8 00 	sexth ba,r0
 370:	df e0 00 00 	sexth r0,ba
 374:	dc 20 10 00 	sexth r2,r1
 378:	10 00 00 00 	lb r0,\(r0\+0\)
 37c:	10 41 00 03 	lb r1,\(r2\+3\)
 380:	40 00 00 00 	lbu r0,\(r0\+0\)
 384:	40 41 00 03 	lbu r1,\(r2\+3\)
 388:	1c 00 00 00 	lh r0,\(r0\+0\)
 38c:	1c 41 00 03 	lh r1,\(r2\+3\)
 390:	2c 00 00 00 	lhu r0,\(r0\+0\)
 394:	2c 41 00 03 	lhu r1,\(r2\+3\)
 398:	28 00 00 00 	lw r0,\(r0\+0\)
 39c:	28 41 00 03 	lw r1,\(r2\+3\)
 3a0:	30 00 00 00 	sb \(r0\+0\),r0
 3a4:	30 23 00 02 	sb \(r1\+2\),r3
 3a8:	0c 00 00 00 	sh \(r0\+0\),r0
 3ac:	0c 23 00 02 	sh \(r1\+2\),r3
 3b0:	58 00 00 00 	sw \(r0\+0\),r0
 3b4:	58 23 00 02 	sw \(r1\+2\),r3
 3b8:	ac 00 00 02 	break
 3bc:	ac 00 00 07 	scall
 3c0:	c3 c0 00 00 	eret
 3c4:	c3 e0 00 00 	bret
 3c8:	c3 a0 00 00 	ret
 3cc:	34 00 00 00 	nop
 3d0:	b8 00 00 00 	mv r0,r0
 3d4:	78 00 00 00 	mvhi r0,0x0
 3d8:	78 00 00 00 	mvhi r0,0x0
 3dc:	a4 00 00 00 	not r0,r0
