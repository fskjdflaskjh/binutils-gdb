#as: -mtitan
#objdump: -dr -Mtitan
#name: AppliedMicro Titan tests

.*: +file format elf(32)?(64)?-powerpc.*

Disassembly of section \.text:

0+0000000 <start>:
   0:	4e 80 00 20 	blr
   4:	0c 81 00 00 	tweqi   r1,0
   8:	10 41 01 58 	macchw  r2,r1,r0
   c:	10 41 01 59 	macchw\. r2,r1,r0
  10:	10 41 05 58 	macchwo r2,r1,r0
  14:	10 41 05 59 	macchwo\. r2,r1,r0
  18:	10 41 01 d8 	macchws r2,r1,r0
  1c:	10 41 01 d9 	macchws\. r2,r1,r0
  20:	10 41 05 d8 	macchwso r2,r1,r0
  24:	10 41 05 d9 	macchwso\. r2,r1,r0
  28:	10 41 01 98 	macchwsu r2,r1,r0
  2c:	10 41 01 99 	macchwsu\. r2,r1,r0
  30:	10 41 05 98 	macchwsuo r2,r1,r0
  34:	10 41 05 99 	macchwsuo\. r2,r1,r0
  38:	10 41 01 18 	macchwu r2,r1,r0
  3c:	10 41 01 19 	macchwu\. r2,r1,r0
  40:	10 41 05 18 	macchwuo r2,r1,r0
  44:	10 41 05 19 	macchwuo\. r2,r1,r0
  48:	10 41 00 58 	machhw  r2,r1,r0
  4c:	10 41 00 59 	machhw\. r2,r1,r0
  50:	10 41 04 58 	machhwo r2,r1,r0
  54:	10 41 04 59 	machhwo\. r2,r1,r0
  58:	10 41 00 d8 	machhws r2,r1,r0
  5c:	10 41 00 d9 	machhws\. r2,r1,r0
  60:	10 41 04 d8 	machhwso r2,r1,r0
  64:	10 41 04 d9 	machhwso\. r2,r1,r0
  68:	10 41 00 98 	machhwsu r2,r1,r0
  6c:	10 41 00 99 	machhwsu\. r2,r1,r0
  70:	10 41 04 98 	machhwsuo r2,r1,r0
  74:	10 41 04 99 	machhwsuo\. r2,r1,r0
  78:	10 41 00 18 	machhwu r2,r1,r0
  7c:	10 41 00 19 	machhwu\. r2,r1,r0
  80:	10 41 04 18 	machhwuo r2,r1,r0
  84:	10 41 04 19 	machhwuo\. r2,r1,r0
  88:	10 41 03 58 	maclhw  r2,r1,r0
  8c:	10 41 03 59 	maclhw\. r2,r1,r0
  90:	10 41 07 58 	maclhwo r2,r1,r0
  94:	10 41 07 59 	maclhwo\. r2,r1,r0
  98:	10 41 03 d8 	maclhws r2,r1,r0
  9c:	10 41 03 d9 	maclhws\. r2,r1,r0
  a0:	10 41 07 d8 	maclhwso r2,r1,r0
  a4:	10 41 07 d9 	maclhwso\. r2,r1,r0
  a8:	10 41 03 98 	maclhwsu r2,r1,r0
  ac:	10 41 03 99 	maclhwsu\. r2,r1,r0
  b0:	10 41 07 98 	maclhwsuo r2,r1,r0
  b4:	10 41 07 99 	maclhwsuo\. r2,r1,r0
  b8:	10 41 03 18 	maclhwu r2,r1,r0
  bc:	10 41 03 19 	maclhwu\. r2,r1,r0
  c0:	10 41 07 18 	maclhwuo r2,r1,r0
  c4:	10 41 07 19 	maclhwuo\. r2,r1,r0
  c8:	10 41 01 5c 	nmacchw r2,r1,r0
  cc:	10 41 01 5d 	nmacchw\. r2,r1,r0
  d0:	10 41 05 5c 	nmacchwo r2,r1,r0
  d4:	10 41 05 5d 	nmacchwo\. r2,r1,r0
  d8:	10 41 01 dc 	nmacchws r2,r1,r0
  dc:	10 41 01 dd 	nmacchws\. r2,r1,r0
  e0:	10 41 05 dc 	nmacchwso r2,r1,r0
  e4:	10 41 05 dd 	nmacchwso\. r2,r1,r0
  e8:	10 41 00 5c 	nmachhw r2,r1,r0
  ec:	10 41 00 5d 	nmachhw\. r2,r1,r0
  f0:	10 41 04 5c 	nmachhwo r2,r1,r0
  f4:	10 41 04 5d 	nmachhwo\. r2,r1,r0
  f8:	10 41 00 dc 	nmachhws r2,r1,r0
  fc:	10 41 00 dd 	nmachhws\. r2,r1,r0
 100:	10 41 04 dc 	nmachhwso r2,r1,r0
 104:	10 41 04 dd 	nmachhwso\. r2,r1,r0
 108:	10 41 03 5c 	nmaclhw r2,r1,r0
 10c:	10 41 03 5d 	nmaclhw\. r2,r1,r0
 110:	10 41 07 5c 	nmaclhwo r2,r1,r0
 114:	10 41 07 5d 	nmaclhwo\. r2,r1,r0
 118:	10 41 03 dc 	nmaclhws r2,r1,r0
 11c:	10 41 03 dd 	nmaclhws\. r2,r1,r0
 120:	10 41 07 dc 	nmaclhwso r2,r1,r0
 124:	10 41 07 dd 	nmaclhwso\. r2,r1,r0
 128:	10 41 01 50 	mulchw  r2,r1,r0
 12c:	10 41 01 51 	mulchw\. r2,r1,r0
 130:	10 41 01 10 	mulchwu r2,r1,r0
 134:	10 41 01 11 	mulchwu\. r2,r1,r0
 138:	10 41 00 50 	mulhhw  r2,r1,r0
 13c:	10 41 00 51 	mulhhw\. r2,r1,r0
 140:	10 41 00 10 	mulhhwu r2,r1,r0
 144:	10 41 00 11 	mulhhwu\. r2,r1,r0
 148:	10 41 03 50 	mullhw  r2,r1,r0
 14c:	10 41 03 51 	mullhw\. r2,r1,r0
 150:	10 41 03 10 	mullhwu r2,r1,r0
 154:	10 41 03 11 	mullhwu\. r2,r1,r0
 158:	7c 22 00 9c 	dlmzb   r2,r1,r0
 15c:	7c 22 00 9d 	dlmzb\.  r2,r1,r0
 160:	7c 02 0b 8c 	dccci   r2,r1
 164:	7c 02 0f 8c 	iccci   r2,r1
 168:	7c 02 0b 0c 	dcblc   r2,r1
 16c:	7c 02 0b 0c 	dcblc   r2,r1
 170:	7c 22 0b 0c 	dcblc   1,r2,r1
 174:	7c 02 09 4c 	dcbtls  r2,r1
 178:	7c 02 09 4c 	dcbtls  r2,r1
 17c:	7c 22 09 4c 	dcbtls  1,r2,r1
 180:	7c 02 09 0c 	dcbtstls r2,r1
 184:	7c 02 09 0c 	dcbtstls r2,r1
 188:	7c 22 09 0c 	dcbtstls 1,r2,r1
 18c:	7c 02 09 cc 	icblc   r2,r1
 190:	7c 02 09 cc 	icblc   r2,r1
 194:	7c 22 09 cc 	icblc   1,r2,r1
 198:	7c 02 0b cc 	icbtls  r2,r1
 19c:	7c 02 0b cc 	icbtls  r2,r1
 1a0:	7c 22 0b cc 	icbtls  1,r2,r1
 1a4:	7c 41 02 8c 	dcread  r2,r1,r0
 1a8:	7c 02 0f cc 	icread  r2,r1
 1ac:	7c 41 02 9c 	mfpmr   r2,1
 1b0:	7c 22 02 9c 	mfpmr   r1,2
 1b4:	7c 81 02 a6 	mfxer   r4
 1b8:	7c 81 02 a6 	mfxer   r4
 1bc:	7c 88 02 a6 	mflr    r4
 1c0:	7c 88 02 a6 	mflr    r4
 1c4:	7c 89 02 a6 	mfctr   r4
 1c8:	7c 89 02 a6 	mfctr   r4
 1cc:	7c 96 02 a6 	mfdec   r4
 1d0:	7c 96 02 a6 	mfdec   r4
 1d4:	7c 9a 02 a6 	mfsrr0  r4
 1d8:	7c 9a 02 a6 	mfsrr0  r4
 1dc:	7c 9b 02 a6 	mfsrr1  r4
 1e0:	7c 9b 02 a6 	mfsrr1  r4
 1e4:	7c 90 0a a6 	mfpid   r4
 1e8:	7c 90 0a a6 	mfpid   r4
 1ec:	7c 9a 0a a6 	mfcsrr0 r4
 1f0:	7c 9a 0a a6 	mfcsrr0 r4
 1f4:	7c 9b 0a a6 	mfcsrr1 r4
 1f8:	7c 9b 0a a6 	mfcsrr1 r4
 1fc:	7c 9d 0a a6 	mfdear  r4
 200:	7c 9d 0a a6 	mfdear  r4
 204:	7c 9e 0a a6 	mfesr   r4
 208:	7c 9e 0a a6 	mfesr   r4
 20c:	7c 9f 0a a6 	mfivpr  r4
 210:	7c 9f 0a a6 	mfivpr  r4
 214:	7c 80 42 a6 	mfusprg0 r4
 218:	7c 80 42 a6 	mfusprg0 r4
 21c:	7c 84 42 a6 	mfsprg  r4,4
 220:	7c 84 42 a6 	mfsprg  r4,4
 224:	7c 85 42 a6 	mfsprg  r4,5
 228:	7c 85 42 a6 	mfsprg  r4,5
 22c:	7c 86 42 a6 	mfsprg  r4,6
 230:	7c 86 42 a6 	mfsprg  r4,6
 234:	7c 87 42 a6 	mfsprg  r4,7
 238:	7c 87 42 a6 	mfsprg  r4,7
 23c:	7c 8c 42 a6 	mftb    r4
 240:	7c 8c 42 a6 	mftb    r4
 244:	7c 8c 42 a6 	mftb    r4
 248:	7c 8d 42 a6 	mftbu   r4
 24c:	7c 8d 42 a6 	mftbu   r4
 250:	7c 90 42 a6 	mfsprg  r4,0
 254:	7c 90 42 a6 	mfsprg  r4,0
 258:	7c 91 42 a6 	mfsprg  r4,1
 25c:	7c 91 42 a6 	mfsprg  r4,1
 260:	7c 92 42 a6 	mfsprg  r4,2
 264:	7c 92 42 a6 	mfsprg  r4,2
 268:	7c 93 42 a6 	mfsprg  r4,3
 26c:	7c 93 42 a6 	mfsprg  r4,3
 270:	7c 9e 42 a6 	mfpir   r4
 274:	7c 9e 42 a6 	mfpir   r4
 278:	7c 9f 42 a6 	mfpvr   r4
 27c:	7c 9f 42 a6 	mfpvr   r4
 280:	7c 90 4a a6 	mfdbsr  r4
 284:	7c 90 4a a6 	mfdbsr  r4
 288:	7c 94 4a a6 	mfdbcr0 r4
 28c:	7c 94 4a a6 	mfdbcr0 r4
 290:	7c 95 4a a6 	mfdbcr1 r4
 294:	7c 95 4a a6 	mfdbcr1 r4
 298:	7c 96 4a a6 	mfdbcr2 r4
 29c:	7c 96 4a a6 	mfdbcr2 r4
 2a0:	7c 98 4a a6 	mfiac1  r4
 2a4:	7c 98 4a a6 	mfiac1  r4
 2a8:	7c 99 4a a6 	mfiac2  r4
 2ac:	7c 99 4a a6 	mfiac2  r4
 2b0:	7c 9a 4a a6 	mfiac3  r4
 2b4:	7c 9a 4a a6 	mfiac3  r4
 2b8:	7c 9b 4a a6 	mfiac4  r4
 2bc:	7c 9b 4a a6 	mfiac4  r4
 2c0:	7c 9c 4a a6 	mfdac1  r4
 2c4:	7c 9c 4a a6 	mfdac1  r4
 2c8:	7c 9d 4a a6 	mfdac2  r4
 2cc:	7c 9d 4a a6 	mfdac2  r4
 2d0:	7c 9e 4a a6 	mfdvc1  r4
 2d4:	7c 9e 4a a6 	mfdvc1  r4
 2d8:	7c 9f 4a a6 	mfdvc2  r4
 2dc:	7c 9f 4a a6 	mfdvc2  r4
 2e0:	7c 90 52 a6 	mftsr   r4
 2e4:	7c 90 52 a6 	mftsr   r4
 2e8:	7c 94 52 a6 	mftcr   r4
 2ec:	7c 94 52 a6 	mftcr   r4
 2f0:	7c 90 62 a6 	mfivor0 r4
 2f4:	7c 90 62 a6 	mfivor0 r4
 2f8:	7c 91 62 a6 	mfivor1 r4
 2fc:	7c 91 62 a6 	mfivor1 r4
 300:	7c 92 62 a6 	mfivor2 r4
 304:	7c 92 62 a6 	mfivor2 r4
 308:	7c 93 62 a6 	mfivor3 r4
 30c:	7c 93 62 a6 	mfivor3 r4
 310:	7c 94 62 a6 	mfivor4 r4
 314:	7c 94 62 a6 	mfivor4 r4
 318:	7c 95 62 a6 	mfivor5 r4
 31c:	7c 95 62 a6 	mfivor5 r4
 320:	7c 96 62 a6 	mfivor6 r4
 324:	7c 96 62 a6 	mfivor6 r4
 328:	7c 97 62 a6 	mfivor7 r4
 32c:	7c 97 62 a6 	mfivor7 r4
 330:	7c 98 62 a6 	mfivor8 r4
 334:	7c 98 62 a6 	mfivor8 r4
 338:	7c 99 62 a6 	mfivor9 r4
 33c:	7c 99 62 a6 	mfivor9 r4
 340:	7c 9a 62 a6 	mfivor10 r4
 344:	7c 9a 62 a6 	mfivor10 r4
 348:	7c 9b 62 a6 	mfivor11 r4
 34c:	7c 9b 62 a6 	mfivor11 r4
 350:	7c 9c 62 a6 	mfivor12 r4
 354:	7c 9c 62 a6 	mfivor12 r4
 358:	7c 9d 62 a6 	mfivor13 r4
 35c:	7c 9d 62 a6 	mfivor13 r4
 360:	7c 9e 62 a6 	mfivor14 r4
 364:	7c 9e 62 a6 	mfivor14 r4
 368:	7c 9f 62 a6 	mfivor15 r4
 36c:	7c 9f 62 a6 	mfivor15 r4
 370:	7c 93 82 a6 	mfivor35 r4
 374:	7c 93 82 a6 	mfivor35 r4
 378:	7c 9a 8a a6 	mfdc_dat r4
 37c:	7c 9a 8a a6 	mfdc_dat r4
 380:	7c 9b 8a a6 	mfmcsrr1 r4
 384:	7c 9b 8a a6 	mfmcsrr1 r4
 388:	7c 9c 8a a6 	mfmcsr  r4
 38c:	7c 9c 8a a6 	mfmcsr  r4
 390:	7c 90 da a6 	mfivndx r4
 394:	7c 90 da a6 	mfivndx r4
 398:	7c 91 da a6 	mfdvndx r4
 39c:	7c 91 da a6 	mfdvndx r4
 3a0:	7c 92 da a6 	mfivlim r4
 3a4:	7c 92 da a6 	mfivlim r4
 3a8:	7c 93 da a6 	mfdvlim r4
 3ac:	7c 93 da a6 	mfdvlim r4
 3b0:	7c 94 da a6 	mfclcsr r4
 3b4:	7c 94 da a6 	mfclcsr r4
 3b8:	7c 98 da a6 	mfccr1  r4
 3bc:	7c 98 da a6 	mfccr1  r4
 3c0:	7c 9b e2 a6 	mfrstcfg r4
 3c4:	7c 9b e2 a6 	mfrstcfg r4
 3c8:	7c 9c e2 a6 	mfdcdbtrl r4
 3cc:	7c 9c e2 a6 	mfdcdbtrl r4
 3d0:	7c 9d e2 a6 	mfdcdbtrh r4
 3d4:	7c 9d e2 a6 	mfdcdbtrh r4
 3d8:	7c 9f e2 a6 	mficdbtr r4
 3dc:	7c 9f e2 a6 	mficdbtr r4
 3e0:	7c 92 ea a6 	mfmmucr r4
 3e4:	7c 92 ea a6 	mfmmucr r4
 3e8:	7c 93 ea a6 	mfccr0  r4
 3ec:	7c 93 ea a6 	mfccr0  r4
 3f0:	7c 93 f2 a6 	mficdbdr r4
 3f4:	7c 93 f2 a6 	mficdbdr r4
 3f8:	7c 93 fa a6 	mfdbdr  r4
 3fc:	7c 93 fa a6 	mfdbdr  r4
 400:	7c 96 0b a6 	mtdecar r4
 404:	7c 96 0b a6 	mtdecar r4
