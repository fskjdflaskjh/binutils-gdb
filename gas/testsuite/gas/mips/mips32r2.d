#objdump: -dr --prefix-addresses --show-raw-insn -M reg-names=numeric
#name: MIPS MIPS32r2 instructions
#as: -32

# Check MIPS32 Release 2 (mips32r2) instruction assembly

.*: +file format .*mips.*

Disassembly of section .text:
0+0000 <[^>]*> 000000c0 	ehb
0+0004 <[^>]*> 7ca43980 	ext	\$4,\$5,0x6,0x8
0+0008 <[^>]*> 7ca46984 	ins	\$4,\$5,0x6,0x8
0+000c <[^>]*> 0100fc09 	jalr.hb	\$8
0+0010 <[^>]*> 0120a409 	jalr.hb	\$20,\$9
0+0014 <[^>]*> 01000408 	jr.hb	\$8
0+0018 <[^>]*> 7c0a003b 	rdhwr	\$10,\$0
0+001c <[^>]*> 7c0b083b 	rdhwr	\$11,\$1
0+0020 <[^>]*> 7c0c103b 	rdhwr	\$12,\$2
0+0024 <[^>]*> 7c0d183b 	rdhwr	\$13,\$3
0+0028 <[^>]*> 7c0e203b 	rdhwr	\$14,\$4
0+002c <[^>]*> 7c0f283b 	rdhwr	\$15,\$5
0+0030 <[^>]*> 002acf02 	ror	\$25,\$10,0x1c
0+0034 <[^>]*> 002ac902 	ror	\$25,\$10,0x4
0+0038 <[^>]*> 0004c823 	negu	\$25,\$4
0+003c <[^>]*> 032ac846 	rorv	\$25,\$10,\$25
0+0040 <[^>]*> 008ac846 	rorv	\$25,\$10,\$4
0+0044 <[^>]*> 008ac846 	rorv	\$25,\$10,\$4
0+0048 <[^>]*> 7c073c20 	seb	\$7,\$7
0+004c <[^>]*> 7c0a4420 	seb	\$8,\$10
0+0050 <[^>]*> 7c073e20 	seh	\$7,\$7
0+0054 <[^>]*> 7c0a4620 	seh	\$8,\$10
0+0058 <[^>]*> 055f5555 	synci	21845\(\$10\)
0+005c <[^>]*> 7c0738a0 	wsbh	\$7,\$7
0+0060 <[^>]*> 7c0a40a0 	wsbh	\$8,\$10
0+0064 <[^>]*> 41606000 	di
0+0068 <[^>]*> 41606000 	di
0+006c <[^>]*> 416a6000 	di	\$10
0+0070 <[^>]*> 41606020 	ei
0+0074 <[^>]*> 41606020 	ei
0+0078 <[^>]*> 416a6020 	ei	\$10
0+007c <[^>]*> 41595000 	rdpgpr	\$10,\$25
0+0080 <[^>]*> 41d95000 	wrpgpr	\$10,\$25
0+0084 <[^>]*> 44710000 	mfhc1	\$17,\$f0
0+0088 <[^>]*> 44f10000 	mthc1	\$17,\$f0
0+008c <[^>]*> 48715555 	mfhc2	\$17,0x5555
0+0090 <[^>]*> 48f15555 	mthc2	\$17,0x5555
	...
