#objdump: -dr 

.*:     file format .*

Disassembly of section \.text:

0000000000000000 <.*>:
   0:	0cdf7000 	ld1	{v0.8b}, \[x0\], #8
   4:	0cdfa000 	ld1	{v0.8b, v1.8b}, \[x0\], #16
   8:	0cdf6000 	ld1	{v0.8b-v2.8b}, \[x0\], #24
   c:	0cdf2000 	ld1	{v0.8b-v3.8b}, \[x0\], #32
  10:	0cdf7400 	ld1	{v0.4h}, \[x0\], #8
  14:	0cdfa400 	ld1	{v0.4h, v1.4h}, \[x0\], #16
  18:	0cdf6400 	ld1	{v0.4h-v2.4h}, \[x0\], #24
  1c:	0cdf2400 	ld1	{v0.4h-v3.4h}, \[x0\], #32
  20:	0cdf7800 	ld1	{v0.2s}, \[x0\], #8
  24:	0cdfa800 	ld1	{v0.2s, v1.2s}, \[x0\], #16
  28:	0cdf6800 	ld1	{v0.2s-v2.2s}, \[x0\], #24
  2c:	0cdf2800 	ld1	{v0.2s-v3.2s}, \[x0\], #32
  30:	0cdf7c00 	ld1	{v0.1d}, \[x0\], #8
  34:	0cdfac00 	ld1	{v0.1d, v1.1d}, \[x0\], #16
  38:	0cdf6c00 	ld1	{v0.1d-v2.1d}, \[x0\], #24
  3c:	0cdf2c00 	ld1	{v0.1d-v3.1d}, \[x0\], #32
  40:	0c9f7000 	st1	{v0.8b}, \[x0\], #8
  44:	0c9fa000 	st1	{v0.8b, v1.8b}, \[x0\], #16
  48:	0c9f6000 	st1	{v0.8b-v2.8b}, \[x0\], #24
  4c:	0c9f2000 	st1	{v0.8b-v3.8b}, \[x0\], #32
  50:	0c9f7400 	st1	{v0.4h}, \[x0\], #8
  54:	0c9fa400 	st1	{v0.4h, v1.4h}, \[x0\], #16
  58:	0c9f6400 	st1	{v0.4h-v2.4h}, \[x0\], #24
  5c:	0c9f2400 	st1	{v0.4h-v3.4h}, \[x0\], #32
  60:	0c9f7800 	st1	{v0.2s}, \[x0\], #8
  64:	0c9fa800 	st1	{v0.2s, v1.2s}, \[x0\], #16
  68:	0c9f6800 	st1	{v0.2s-v2.2s}, \[x0\], #24
  6c:	0c9f2800 	st1	{v0.2s-v3.2s}, \[x0\], #32
  70:	0c9f7c00 	st1	{v0.1d}, \[x0\], #8
  74:	0c9fac00 	st1	{v0.1d, v1.1d}, \[x0\], #16
  78:	0c9f6c00 	st1	{v0.1d-v2.1d}, \[x0\], #24
  7c:	0c9f2c00 	st1	{v0.1d-v3.1d}, \[x0\], #32
  80:	4cdf7000 	ld1	{v0.16b}, \[x0\], #16
  84:	4cdfa000 	ld1	{v0.16b, v1.16b}, \[x0\], #32
  88:	4cdf6000 	ld1	{v0.16b-v2.16b}, \[x0\], #48
  8c:	4cdf2000 	ld1	{v0.16b-v3.16b}, \[x0\], #64
  90:	4cdf7400 	ld1	{v0.8h}, \[x0\], #16
  94:	4cdfa400 	ld1	{v0.8h, v1.8h}, \[x0\], #32
  98:	4cdf6400 	ld1	{v0.8h-v2.8h}, \[x0\], #48
  9c:	4cdf2400 	ld1	{v0.8h-v3.8h}, \[x0\], #64
  a0:	4cdf7800 	ld1	{v0.4s}, \[x0\], #16
  a4:	4cdfa800 	ld1	{v0.4s, v1.4s}, \[x0\], #32
  a8:	4cdf6800 	ld1	{v0.4s-v2.4s}, \[x0\], #48
  ac:	4cdf2800 	ld1	{v0.4s-v3.4s}, \[x0\], #64
  b0:	4cdf7c00 	ld1	{v0.2d}, \[x0\], #16
  b4:	4cdfac00 	ld1	{v0.2d, v1.2d}, \[x0\], #32
  b8:	4cdf6c00 	ld1	{v0.2d-v2.2d}, \[x0\], #48
  bc:	4cdf2c00 	ld1	{v0.2d-v3.2d}, \[x0\], #64
  c0:	4c9f7000 	st1	{v0.16b}, \[x0\], #16
  c4:	4c9fa000 	st1	{v0.16b, v1.16b}, \[x0\], #32
  c8:	4c9f6000 	st1	{v0.16b-v2.16b}, \[x0\], #48
  cc:	4c9f2000 	st1	{v0.16b-v3.16b}, \[x0\], #64
  d0:	4c9f7400 	st1	{v0.8h}, \[x0\], #16
  d4:	4c9fa400 	st1	{v0.8h, v1.8h}, \[x0\], #32
  d8:	4c9f6400 	st1	{v0.8h-v2.8h}, \[x0\], #48
  dc:	4c9f2400 	st1	{v0.8h-v3.8h}, \[x0\], #64
  e0:	4c9f7800 	st1	{v0.4s}, \[x0\], #16
  e4:	4c9fa800 	st1	{v0.4s, v1.4s}, \[x0\], #32
  e8:	4c9f6800 	st1	{v0.4s-v2.4s}, \[x0\], #48
  ec:	4c9f2800 	st1	{v0.4s-v3.4s}, \[x0\], #64
  f0:	4c9f7c00 	st1	{v0.2d}, \[x0\], #16
  f4:	4c9fac00 	st1	{v0.2d, v1.2d}, \[x0\], #32
  f8:	4c9f6c00 	st1	{v0.2d-v2.2d}, \[x0\], #48
  fc:	4c9f2c00 	st1	{v0.2d-v3.2d}, \[x0\], #64
 100:	0cc77000 	ld1	{v0.8b}, \[x0\], x7
 104:	0cc7a000 	ld1	{v0.8b, v1.8b}, \[x0\], x7
 108:	0cc76000 	ld1	{v0.8b-v2.8b}, \[x0\], x7
 10c:	0cc72000 	ld1	{v0.8b-v3.8b}, \[x0\], x7
 110:	0cc77400 	ld1	{v0.4h}, \[x0\], x7
 114:	0cc7a400 	ld1	{v0.4h, v1.4h}, \[x0\], x7
 118:	0cc76400 	ld1	{v0.4h-v2.4h}, \[x0\], x7
 11c:	0cc72400 	ld1	{v0.4h-v3.4h}, \[x0\], x7
 120:	0cc77800 	ld1	{v0.2s}, \[x0\], x7
 124:	0cc7a800 	ld1	{v0.2s, v1.2s}, \[x0\], x7
 128:	0cc76800 	ld1	{v0.2s-v2.2s}, \[x0\], x7
 12c:	0cc72800 	ld1	{v0.2s-v3.2s}, \[x0\], x7
 130:	0cc77c00 	ld1	{v0.1d}, \[x0\], x7
 134:	0cc7ac00 	ld1	{v0.1d, v1.1d}, \[x0\], x7
 138:	0cc76c00 	ld1	{v0.1d-v2.1d}, \[x0\], x7
 13c:	0cc72c00 	ld1	{v0.1d-v3.1d}, \[x0\], x7
 140:	4cc77000 	ld1	{v0.16b}, \[x0\], x7
 144:	4cc7a000 	ld1	{v0.16b, v1.16b}, \[x0\], x7
 148:	4cc76000 	ld1	{v0.16b-v2.16b}, \[x0\], x7
 14c:	4cc72000 	ld1	{v0.16b-v3.16b}, \[x0\], x7
 150:	4cc77400 	ld1	{v0.8h}, \[x0\], x7
 154:	4cc7a400 	ld1	{v0.8h, v1.8h}, \[x0\], x7
 158:	4cc76400 	ld1	{v0.8h-v2.8h}, \[x0\], x7
 15c:	4cc72400 	ld1	{v0.8h-v3.8h}, \[x0\], x7
 160:	4cc77800 	ld1	{v0.4s}, \[x0\], x7
 164:	4cc7a800 	ld1	{v0.4s, v1.4s}, \[x0\], x7
 168:	4cc76800 	ld1	{v0.4s-v2.4s}, \[x0\], x7
 16c:	4cc72800 	ld1	{v0.4s-v3.4s}, \[x0\], x7
 170:	4cc77c00 	ld1	{v0.2d}, \[x0\], x7
 174:	4cc7ac00 	ld1	{v0.2d, v1.2d}, \[x0\], x7
 178:	4cc76c00 	ld1	{v0.2d-v2.2d}, \[x0\], x7
 17c:	4cc72c00 	ld1	{v0.2d-v3.2d}, \[x0\], x7
 180:	0c877000 	st1	{v0.8b}, \[x0\], x7
 184:	0c87a000 	st1	{v0.8b, v1.8b}, \[x0\], x7
 188:	0c876000 	st1	{v0.8b-v2.8b}, \[x0\], x7
 18c:	0c872000 	st1	{v0.8b-v3.8b}, \[x0\], x7
 190:	0c877400 	st1	{v0.4h}, \[x0\], x7
 194:	0c87a400 	st1	{v0.4h, v1.4h}, \[x0\], x7
 198:	0c876400 	st1	{v0.4h-v2.4h}, \[x0\], x7
 19c:	0c872400 	st1	{v0.4h-v3.4h}, \[x0\], x7
 1a0:	0c877800 	st1	{v0.2s}, \[x0\], x7
 1a4:	0c87a800 	st1	{v0.2s, v1.2s}, \[x0\], x7
 1a8:	0c876800 	st1	{v0.2s-v2.2s}, \[x0\], x7
 1ac:	0c872800 	st1	{v0.2s-v3.2s}, \[x0\], x7
 1b0:	0c877c00 	st1	{v0.1d}, \[x0\], x7
 1b4:	0c87ac00 	st1	{v0.1d, v1.1d}, \[x0\], x7
 1b8:	0c876c00 	st1	{v0.1d-v2.1d}, \[x0\], x7
 1bc:	0c872c00 	st1	{v0.1d-v3.1d}, \[x0\], x7
 1c0:	4c877000 	st1	{v0.16b}, \[x0\], x7
 1c4:	4c87a000 	st1	{v0.16b, v1.16b}, \[x0\], x7
 1c8:	4c876000 	st1	{v0.16b-v2.16b}, \[x0\], x7
 1cc:	4c872000 	st1	{v0.16b-v3.16b}, \[x0\], x7
 1d0:	4c877400 	st1	{v0.8h}, \[x0\], x7
 1d4:	4c87a400 	st1	{v0.8h, v1.8h}, \[x0\], x7
 1d8:	4c876400 	st1	{v0.8h-v2.8h}, \[x0\], x7
 1dc:	4c872400 	st1	{v0.8h-v3.8h}, \[x0\], x7
 1e0:	4c877800 	st1	{v0.4s}, \[x0\], x7
 1e4:	4c87a800 	st1	{v0.4s, v1.4s}, \[x0\], x7
 1e8:	4c876800 	st1	{v0.4s-v2.4s}, \[x0\], x7
 1ec:	4c872800 	st1	{v0.4s-v3.4s}, \[x0\], x7
 1f0:	4c877c00 	st1	{v0.2d}, \[x0\], x7
 1f4:	4c87ac00 	st1	{v0.2d, v1.2d}, \[x0\], x7
 1f8:	4c876c00 	st1	{v0.2d-v2.2d}, \[x0\], x7
 1fc:	4c872c00 	st1	{v0.2d-v3.2d}, \[x0\], x7
 200:	0cdf8000 	ld2	{v0.8b, v1.8b}, \[x0\], #16
 204:	0cc78000 	ld2	{v0.8b, v1.8b}, \[x0\], x7
 208:	0cdf8400 	ld2	{v0.4h, v1.4h}, \[x0\], #16
 20c:	0cc78400 	ld2	{v0.4h, v1.4h}, \[x0\], x7
 210:	0cdf8800 	ld2	{v0.2s, v1.2s}, \[x0\], #16
 214:	0cc78800 	ld2	{v0.2s, v1.2s}, \[x0\], x7
 218:	0c9f8000 	st2	{v0.8b, v1.8b}, \[x0\], #16
 21c:	0c878000 	st2	{v0.8b, v1.8b}, \[x0\], x7
 220:	0c9f8400 	st2	{v0.4h, v1.4h}, \[x0\], #16
 224:	0c878400 	st2	{v0.4h, v1.4h}, \[x0\], x7
 228:	0c9f8800 	st2	{v0.2s, v1.2s}, \[x0\], #16
 22c:	0c878800 	st2	{v0.2s, v1.2s}, \[x0\], x7
 230:	4cdf8000 	ld2	{v0.16b, v1.16b}, \[x0\], #32
 234:	4cc78000 	ld2	{v0.16b, v1.16b}, \[x0\], x7
 238:	4cdf8400 	ld2	{v0.8h, v1.8h}, \[x0\], #32
 23c:	4cc78400 	ld2	{v0.8h, v1.8h}, \[x0\], x7
 240:	4cdf8800 	ld2	{v0.4s, v1.4s}, \[x0\], #32
 244:	4cc78800 	ld2	{v0.4s, v1.4s}, \[x0\], x7
 248:	4cdf8c00 	ld2	{v0.2d, v1.2d}, \[x0\], #32
 24c:	4cc78c00 	ld2	{v0.2d, v1.2d}, \[x0\], x7
 250:	4c9f8000 	st2	{v0.16b, v1.16b}, \[x0\], #32
 254:	4c878000 	st2	{v0.16b, v1.16b}, \[x0\], x7
 258:	4c9f8400 	st2	{v0.8h, v1.8h}, \[x0\], #32
 25c:	4c878400 	st2	{v0.8h, v1.8h}, \[x0\], x7
 260:	4c9f8800 	st2	{v0.4s, v1.4s}, \[x0\], #32
 264:	4c878800 	st2	{v0.4s, v1.4s}, \[x0\], x7
 268:	4c9f8c00 	st2	{v0.2d, v1.2d}, \[x0\], #32
 26c:	4c878c00 	st2	{v0.2d, v1.2d}, \[x0\], x7
 270:	0cdf4000 	ld3	{v0.8b-v2.8b}, \[x0\], #24
 274:	0cdf0000 	ld4	{v0.8b-v3.8b}, \[x0\], #32
 278:	0cc74000 	ld3	{v0.8b-v2.8b}, \[x0\], x7
 27c:	0cc70000 	ld4	{v0.8b-v3.8b}, \[x0\], x7
 280:	0cdf4400 	ld3	{v0.4h-v2.4h}, \[x0\], #24
 284:	0cdf0400 	ld4	{v0.4h-v3.4h}, \[x0\], #32
 288:	0cc74400 	ld3	{v0.4h-v2.4h}, \[x0\], x7
 28c:	0cc70400 	ld4	{v0.4h-v3.4h}, \[x0\], x7
 290:	0cdf4800 	ld3	{v0.2s-v2.2s}, \[x0\], #24
 294:	0cdf0800 	ld4	{v0.2s-v3.2s}, \[x0\], #32
 298:	0cc74800 	ld3	{v0.2s-v2.2s}, \[x0\], x7
 29c:	0cc70800 	ld4	{v0.2s-v3.2s}, \[x0\], x7
 2a0:	0c9f4000 	st3	{v0.8b-v2.8b}, \[x0\], #24
 2a4:	0c9f0000 	st4	{v0.8b-v3.8b}, \[x0\], #32
 2a8:	0c874000 	st3	{v0.8b-v2.8b}, \[x0\], x7
 2ac:	0c870000 	st4	{v0.8b-v3.8b}, \[x0\], x7
 2b0:	0c9f4400 	st3	{v0.4h-v2.4h}, \[x0\], #24
 2b4:	0c9f0400 	st4	{v0.4h-v3.4h}, \[x0\], #32
 2b8:	0c874400 	st3	{v0.4h-v2.4h}, \[x0\], x7
 2bc:	0c870400 	st4	{v0.4h-v3.4h}, \[x0\], x7
 2c0:	0c9f4800 	st3	{v0.2s-v2.2s}, \[x0\], #24
 2c4:	0c9f0800 	st4	{v0.2s-v3.2s}, \[x0\], #32
 2c8:	0c874800 	st3	{v0.2s-v2.2s}, \[x0\], x7
 2cc:	0c870800 	st4	{v0.2s-v3.2s}, \[x0\], x7
 2d0:	4cdf4000 	ld3	{v0.16b-v2.16b}, \[x0\], #48
 2d4:	4cdf0000 	ld4	{v0.16b-v3.16b}, \[x0\], #64
 2d8:	4cc74000 	ld3	{v0.16b-v2.16b}, \[x0\], x7
 2dc:	4cc70000 	ld4	{v0.16b-v3.16b}, \[x0\], x7
 2e0:	4cdf4400 	ld3	{v0.8h-v2.8h}, \[x0\], #48
 2e4:	4cdf0400 	ld4	{v0.8h-v3.8h}, \[x0\], #64
 2e8:	4cc74400 	ld3	{v0.8h-v2.8h}, \[x0\], x7
 2ec:	4cc70400 	ld4	{v0.8h-v3.8h}, \[x0\], x7
 2f0:	4cdf4800 	ld3	{v0.4s-v2.4s}, \[x0\], #48
 2f4:	4cdf0800 	ld4	{v0.4s-v3.4s}, \[x0\], #64
 2f8:	4cc74800 	ld3	{v0.4s-v2.4s}, \[x0\], x7
 2fc:	4cc70800 	ld4	{v0.4s-v3.4s}, \[x0\], x7
 300:	4cdf4c00 	ld3	{v0.2d-v2.2d}, \[x0\], #48
 304:	4cdf0c00 	ld4	{v0.2d-v3.2d}, \[x0\], #64
 308:	4cc74c00 	ld3	{v0.2d-v2.2d}, \[x0\], x7
 30c:	4cc70c00 	ld4	{v0.2d-v3.2d}, \[x0\], x7
 310:	4c9f4000 	st3	{v0.16b-v2.16b}, \[x0\], #48
 314:	4c9f0000 	st4	{v0.16b-v3.16b}, \[x0\], #64
 318:	4c874000 	st3	{v0.16b-v2.16b}, \[x0\], x7
 31c:	4c870000 	st4	{v0.16b-v3.16b}, \[x0\], x7
 320:	4c9f4400 	st3	{v0.8h-v2.8h}, \[x0\], #48
 324:	4c9f0400 	st4	{v0.8h-v3.8h}, \[x0\], #64
 328:	4c874400 	st3	{v0.8h-v2.8h}, \[x0\], x7
 32c:	4c870400 	st4	{v0.8h-v3.8h}, \[x0\], x7
 330:	4c9f4800 	st3	{v0.4s-v2.4s}, \[x0\], #48
 334:	4c9f0800 	st4	{v0.4s-v3.4s}, \[x0\], #64
 338:	4c874800 	st3	{v0.4s-v2.4s}, \[x0\], x7
 33c:	4c870800 	st4	{v0.4s-v3.4s}, \[x0\], x7
 340:	4c9f4c00 	st3	{v0.2d-v2.2d}, \[x0\], #48
 344:	4c9f0c00 	st4	{v0.2d-v3.2d}, \[x0\], #64
 348:	4c874c00 	st3	{v0.2d-v2.2d}, \[x0\], x7
 34c:	4c870c00 	st4	{v0.2d-v3.2d}, \[x0\], x7
 350:	0ddf0400 	ld1	{v0.b}\[1\], \[x0\], #1
 354:	0dff0400 	ld2	{v0.b, v1.b}\[1\], \[x0\], #2
 358:	0ddf2400 	ld3	{v0.b-v2.b}\[1\], \[x0\], #3
 35c:	0dff2400 	ld4	{v0.b-v3.b}\[1\], \[x0\], #4
 360:	0ddfc000 	ld1r	{v0.8b}, \[x0\], #1
 364:	0dffc000 	ld2r	{v0.8b, v1.8b}, \[x0\], #2
 368:	0ddfe000 	ld3r	{v0.8b-v2.8b}, \[x0\], #3
 36c:	0dffe000 	ld4r	{v0.8b-v3.8b}, \[x0\], #4
 370:	4ddfc000 	ld1r	{v0.16b}, \[x0\], #1
 374:	4dffc000 	ld2r	{v0.16b, v1.16b}, \[x0\], #2
 378:	4ddfe000 	ld3r	{v0.16b-v2.16b}, \[x0\], #3
 37c:	4dffe000 	ld4r	{v0.16b-v3.16b}, \[x0\], #4
 380:	0d9f0400 	st1	{v0.b}\[1\], \[x0\], #1
 384:	0dbf0400 	st2	{v0.b, v1.b}\[1\], \[x0\], #2
 388:	0d9f2400 	st3	{v0.b-v2.b}\[1\], \[x0\], #3
 38c:	0dbf2400 	st4	{v0.b-v3.b}\[1\], \[x0\], #4
 390:	0ddf4800 	ld1	{v0.h}\[1\], \[x0\], #2
 394:	0dff4800 	ld2	{v0.h, v1.h}\[1\], \[x0\], #4
 398:	0ddf6800 	ld3	{v0.h-v2.h}\[1\], \[x0\], #6
 39c:	0dff6800 	ld4	{v0.h-v3.h}\[1\], \[x0\], #8
 3a0:	0ddfc400 	ld1r	{v0.4h}, \[x0\], #2
 3a4:	0dffc400 	ld2r	{v0.4h, v1.4h}, \[x0\], #4
 3a8:	0ddfe400 	ld3r	{v0.4h-v2.4h}, \[x0\], #6
 3ac:	0dffe400 	ld4r	{v0.4h-v3.4h}, \[x0\], #8
 3b0:	4ddfc400 	ld1r	{v0.8h}, \[x0\], #2
 3b4:	4dffc400 	ld2r	{v0.8h, v1.8h}, \[x0\], #4
 3b8:	4ddfe400 	ld3r	{v0.8h-v2.8h}, \[x0\], #6
 3bc:	4dffe400 	ld4r	{v0.8h-v3.8h}, \[x0\], #8
 3c0:	0d9f4800 	st1	{v0.h}\[1\], \[x0\], #2
 3c4:	0dbf4800 	st2	{v0.h, v1.h}\[1\], \[x0\], #4
 3c8:	0d9f6800 	st3	{v0.h-v2.h}\[1\], \[x0\], #6
 3cc:	0dbf6800 	st4	{v0.h-v3.h}\[1\], \[x0\], #8
 3d0:	0ddf9000 	ld1	{v0.s}\[1\], \[x0\], #4
 3d4:	0dff9000 	ld2	{v0.s, v1.s}\[1\], \[x0\], #8
 3d8:	0ddfb000 	ld3	{v0.s-v2.s}\[1\], \[x0\], #12
 3dc:	0dffb000 	ld4	{v0.s-v3.s}\[1\], \[x0\], #16
 3e0:	0ddfc800 	ld1r	{v0.2s}, \[x0\], #4
 3e4:	0dffc800 	ld2r	{v0.2s, v1.2s}, \[x0\], #8
 3e8:	0ddfe800 	ld3r	{v0.2s-v2.2s}, \[x0\], #12
 3ec:	0dffe800 	ld4r	{v0.2s-v3.2s}, \[x0\], #16
 3f0:	4ddfc800 	ld1r	{v0.4s}, \[x0\], #4
 3f4:	4dffc800 	ld2r	{v0.4s, v1.4s}, \[x0\], #8
 3f8:	4ddfe800 	ld3r	{v0.4s-v2.4s}, \[x0\], #12
 3fc:	4dffe800 	ld4r	{v0.4s-v3.4s}, \[x0\], #16
 400:	0d9f9000 	st1	{v0.s}\[1\], \[x0\], #4
 404:	0dbf9000 	st2	{v0.s, v1.s}\[1\], \[x0\], #8
 408:	0d9fb000 	st3	{v0.s-v2.s}\[1\], \[x0\], #12
 40c:	0dbfb000 	st4	{v0.s-v3.s}\[1\], \[x0\], #16
 410:	4ddf8400 	ld1	{v0.d}\[1\], \[x0\], #8
 414:	4dff8400 	ld2	{v0.d, v1.d}\[1\], \[x0\], #16
 418:	4ddfa400 	ld3	{v0.d-v2.d}\[1\], \[x0\], #24
 41c:	4dffa400 	ld4	{v0.d-v3.d}\[1\], \[x0\], #32
 420:	0ddfcc00 	ld1r	{v0.1d}, \[x0\], #8
 424:	0dffcc00 	ld2r	{v0.1d, v1.1d}, \[x0\], #16
 428:	0ddfec00 	ld3r	{v0.1d-v2.1d}, \[x0\], #24
 42c:	0dffec00 	ld4r	{v0.1d-v3.1d}, \[x0\], #32
 430:	4ddfcc00 	ld1r	{v0.2d}, \[x0\], #8
 434:	4dffcc00 	ld2r	{v0.2d, v1.2d}, \[x0\], #16
 438:	4ddfec00 	ld3r	{v0.2d-v2.2d}, \[x0\], #24
 43c:	4dffec00 	ld4r	{v0.2d-v3.2d}, \[x0\], #32
 440:	4d9f8400 	st1	{v0.d}\[1\], \[x0\], #8
 444:	4dbf8400 	st2	{v0.d, v1.d}\[1\], \[x0\], #16
 448:	4d9fa400 	st3	{v0.d-v2.d}\[1\], \[x0\], #24
 44c:	4dbfa400 	st4	{v0.d-v3.d}\[1\], \[x0\], #32
 450:	0dc70400 	ld1	{v0.b}\[1\], \[x0\], x7
 454:	0de70400 	ld2	{v0.b, v1.b}\[1\], \[x0\], x7
 458:	0dc72400 	ld3	{v0.b-v2.b}\[1\], \[x0\], x7
 45c:	0de72400 	ld4	{v0.b-v3.b}\[1\], \[x0\], x7
 460:	0dc74800 	ld1	{v0.h}\[1\], \[x0\], x7
 464:	0de74800 	ld2	{v0.h, v1.h}\[1\], \[x0\], x7
 468:	0dc76800 	ld3	{v0.h-v2.h}\[1\], \[x0\], x7
 46c:	0de76800 	ld4	{v0.h-v3.h}\[1\], \[x0\], x7
 470:	0dc79000 	ld1	{v0.s}\[1\], \[x0\], x7
 474:	0de79000 	ld2	{v0.s, v1.s}\[1\], \[x0\], x7
 478:	0dc7b000 	ld3	{v0.s-v2.s}\[1\], \[x0\], x7
 47c:	0de7b000 	ld4	{v0.s-v3.s}\[1\], \[x0\], x7
 480:	4dc78400 	ld1	{v0.d}\[1\], \[x0\], x7
 484:	4de78400 	ld2	{v0.d, v1.d}\[1\], \[x0\], x7
 488:	4dc7a400 	ld3	{v0.d-v2.d}\[1\], \[x0\], x7
 48c:	4de7a400 	ld4	{v0.d-v3.d}\[1\], \[x0\], x7
 490:	0dc7c000 	ld1r	{v0.8b}, \[x0\], x7
 494:	0de7c000 	ld2r	{v0.8b, v1.8b}, \[x0\], x7
 498:	0dc7e000 	ld3r	{v0.8b-v2.8b}, \[x0\], x7
 49c:	0de7e000 	ld4r	{v0.8b-v3.8b}, \[x0\], x7
 4a0:	4dc7c000 	ld1r	{v0.16b}, \[x0\], x7
 4a4:	4de7c000 	ld2r	{v0.16b, v1.16b}, \[x0\], x7
 4a8:	4dc7e000 	ld3r	{v0.16b-v2.16b}, \[x0\], x7
 4ac:	4de7e000 	ld4r	{v0.16b-v3.16b}, \[x0\], x7
 4b0:	0dc7c400 	ld1r	{v0.4h}, \[x0\], x7
 4b4:	0de7c400 	ld2r	{v0.4h, v1.4h}, \[x0\], x7
 4b8:	0dc7e400 	ld3r	{v0.4h-v2.4h}, \[x0\], x7
 4bc:	0de7e400 	ld4r	{v0.4h-v3.4h}, \[x0\], x7
 4c0:	4dc7c400 	ld1r	{v0.8h}, \[x0\], x7
 4c4:	4de7c400 	ld2r	{v0.8h, v1.8h}, \[x0\], x7
 4c8:	4dc7e400 	ld3r	{v0.8h-v2.8h}, \[x0\], x7
 4cc:	4de7e400 	ld4r	{v0.8h-v3.8h}, \[x0\], x7
 4d0:	0dc7c800 	ld1r	{v0.2s}, \[x0\], x7
 4d4:	0de7c800 	ld2r	{v0.2s, v1.2s}, \[x0\], x7
 4d8:	0dc7e800 	ld3r	{v0.2s-v2.2s}, \[x0\], x7
 4dc:	0de7e800 	ld4r	{v0.2s-v3.2s}, \[x0\], x7
 4e0:	4dc7c800 	ld1r	{v0.4s}, \[x0\], x7
 4e4:	4de7c800 	ld2r	{v0.4s, v1.4s}, \[x0\], x7
 4e8:	4dc7e800 	ld3r	{v0.4s-v2.4s}, \[x0\], x7
 4ec:	4de7e800 	ld4r	{v0.4s-v3.4s}, \[x0\], x7
 4f0:	0dc7cc00 	ld1r	{v0.1d}, \[x0\], x7
 4f4:	0de7cc00 	ld2r	{v0.1d, v1.1d}, \[x0\], x7
 4f8:	0dc7ec00 	ld3r	{v0.1d-v2.1d}, \[x0\], x7
 4fc:	0de7ec00 	ld4r	{v0.1d-v3.1d}, \[x0\], x7
 500:	4dc7cc00 	ld1r	{v0.2d}, \[x0\], x7
 504:	4de7cc00 	ld2r	{v0.2d, v1.2d}, \[x0\], x7
 508:	4dc7ec00 	ld3r	{v0.2d-v2.2d}, \[x0\], x7
 50c:	4de7ec00 	ld4r	{v0.2d-v3.2d}, \[x0\], x7
 510:	0d870400 	st1	{v0.b}\[1\], \[x0\], x7
 514:	0da70400 	st2	{v0.b, v1.b}\[1\], \[x0\], x7
 518:	0d872400 	st3	{v0.b-v2.b}\[1\], \[x0\], x7
 51c:	0da72400 	st4	{v0.b-v3.b}\[1\], \[x0\], x7
 520:	0d874800 	st1	{v0.h}\[1\], \[x0\], x7
 524:	0da74800 	st2	{v0.h, v1.h}\[1\], \[x0\], x7
 528:	0d876800 	st3	{v0.h-v2.h}\[1\], \[x0\], x7
 52c:	0da76800 	st4	{v0.h-v3.h}\[1\], \[x0\], x7
 530:	0d879000 	st1	{v0.s}\[1\], \[x0\], x7
 534:	0da79000 	st2	{v0.s, v1.s}\[1\], \[x0\], x7
 538:	0d87b000 	st3	{v0.s-v2.s}\[1\], \[x0\], x7
 53c:	0da7b000 	st4	{v0.s-v3.s}\[1\], \[x0\], x7
 540:	4d878400 	st1	{v0.d}\[1\], \[x0\], x7
 544:	4da78400 	st2	{v0.d, v1.d}\[1\], \[x0\], x7
 548:	4d87a400 	st3	{v0.d-v2.d}\[1\], \[x0\], x7
 54c:	4da7a400 	st4	{v0.d-v3.d}\[1\], \[x0\], x7
