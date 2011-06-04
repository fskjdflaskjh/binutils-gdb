//Original:/testcases/core/c_ldst_st_p_d_h/c_ldst_st_p_d_h.dsp
// Spec Reference: c_ldst st_p d h
# mach: bfin

.include "testutils.inc"
	start

	INIT_R_REGS 0;

	imm32 r0, 0x0a231507;
	imm32 r1, 0x1b342618;
	imm32 r2, 0x2c453729;
	imm32 r3, 0x3d56483a;
	imm32 r4, 0x4e67594b;
	imm32 r5, 0x5f786a5c;
	imm32 r6, 0x60897b6d;
	imm32 r7, 0x719a8c7e;

	loadsym p5, DATA_ADDR_1;
	loadsym p1, DATA_ADDR_2;
	loadsym p2, DATA_ADDR_3;
	loadsym p4, DATA_ADDR_5;
	loadsym fp, DATA_ADDR_6;

	W [ P5 ] = R0;
	W [ P1 ] = R1;
	W [ P2 ] = R2;
	W [ P4 ] = R4;
	W [ FP ] = R5;
	R0 = [ P1 ];
	R1 = [ P2 ];
	R3 = [ P4 ];
	R4 = [ P5 ];
	R5 = [ FP ];
	CHECKREG r0, 0x20212618;
	CHECKREG r1, 0x40413729;
	CHECKREG r3, 0x8081594B;
	CHECKREG r4, 0x00011507;
	CHECKREG r5, 0xA0A16A5C;
	CHECKREG r7, 0x719A8C7E;

	imm32 r0, 0x1a231507;
	imm32 r1, 0x11342618;
	imm32 r2, 0x2c153729;
	imm32 r3, 0x3d51483a;
	imm32 r4, 0x4e67194b;
	imm32 r5, 0x5f78615c;
	imm32 r6, 0x60897b1d;
	imm32 r7, 0x719a8c71;
	W [ P5 ] = R1;
	W [ P1 ] = R2;
	W [ P2 ] = R3;
	W [ P4 ] = R5;
	W [ FP ] = R6;
	R0 = [ P1 ];
	R1 = [ P2 ];
	R3 = [ P4 ];
	R4 = [ P5 ];
	R5 = [ FP ];
	CHECKREG r0, 0x20213729;
	CHECKREG r1, 0x4041483A;
	CHECKREG r3, 0x8081615C;
	CHECKREG r4, 0x00012618;
	CHECKREG r5, 0xA0A17B1D;
	CHECKREG r6, 0x60897b1d;

	imm32 r0, 0x2a231507;
	imm32 r1, 0x12342618;
	imm32 r2, 0x2c253729;
	imm32 r3, 0x3d52483a;
	imm32 r4, 0x4e67294b;
	imm32 r5, 0x5f78625c;
	imm32 r6, 0x60897b2d;
	imm32 r7, 0x719a8c72;
	W [ P5 ] = R2;
	W [ P1 ] = R3;
	W [ P2 ] = R4;
	W [ P4 ] = R6;
	W [ FP ] = R7;
	R0 = [ P1 ];
	R1 = [ P2 ];
	R3 = [ P4 ];
	R4 = [ P5 ];
	R5 = [ FP ];
	CHECKREG r0, 0x2021483A;
	CHECKREG r1, 0x4041294B;
	CHECKREG r3, 0x80817B2D;
	CHECKREG r4, 0x00013729;
	CHECKREG r5, 0xA0A18C72;
	CHECKREG r7, 0x719A8C72;

	imm32 r0, 0x3a231507;
	imm32 r1, 0x13342618;
	imm32 r2, 0x2c353729;
	imm32 r3, 0x3d53483a;
	imm32 r4, 0x4e67394b;
	imm32 r5, 0x5f78635c;
	imm32 r6, 0x60897b3d;
	imm32 r7, 0x719a8c73;
	W [ P5 ] = R3;
	W [ P1 ] = R4;
	W [ P2 ] = R5;
	W [ P4 ] = R7;
	W [ FP ] = R0;
	R0 = [ P1 ];
	R1 = [ P2 ];
	R3 = [ P4 ];
	R4 = [ P5 ];
	R5 = [ FP ];
	CHECKREG r0, 0x2021394B;
	CHECKREG r1, 0x4041635C;
	CHECKREG r3, 0x80818C73;
	CHECKREG r4, 0x0001483A;
	CHECKREG r5, 0xA0A11507;
	CHECKREG r7, 0x719A8C73;

	imm32 r0, 0x4a231507;
	imm32 r1, 0x14342618;
	imm32 r2, 0x2c453729;
	imm32 r3, 0x3d54483a;
	imm32 r4, 0x4e67494b;
	imm32 r5, 0x5f78645c;
	imm32 r6, 0x60897b4d;
	imm32 r7, 0x719a8c74;
	W [ P5 ] = R4;
	W [ P1 ] = R5;
	W [ P2 ] = R6;
	W [ P4 ] = R0;
	W [ FP ] = R1;

	W [ P5 ] = R5;
	W [ P1 ] = R6;
	W [ P2 ] = R7;
	W [ P4 ] = R1;
	W [ FP ] = R2;
	R0 = [ P1 ];
	R1 = [ P2 ];
	R3 = [ P4 ];
	R4 = [ P5 ];
	R5 = [ FP ];
	CHECKREG r0, 0x20217B4D;
	CHECKREG r1, 0x40418C74;
	CHECKREG r3, 0x80812618;
	CHECKREG r4, 0x0001645C;
	CHECKREG r5, 0xA0A13729;
	CHECKREG r7, 0x719A8C74;

	imm32 r0, 0x5a231507;
	imm32 r1, 0x15342618;
	imm32 r2, 0x2c553729;
	imm32 r3, 0x3d55483a;
	imm32 r4, 0x4e67594b;
	imm32 r5, 0x5f78655c;
	imm32 r6, 0x60897b5d;
	imm32 r7, 0x719a8c75;
	W [ P5 ] = R6;
	W [ P1 ] = R7;
	W [ P2 ] = R0;
	W [ P4 ] = R2;
	W [ FP ] = R3;
	R0 = [ P1 ];
	R1 = [ P2 ];
	R3 = [ P4 ];
	R4 = [ P5 ];
	R5 = [ FP ];
	CHECKREG r0, 0x20218C75;
	CHECKREG r1, 0x40411507;
	CHECKREG r3, 0x80813729;
	CHECKREG r4, 0x00017B5D;
	CHECKREG r5, 0xA0A1483A;
	CHECKREG r7, 0x719A8C75;

	imm32 r0, 0x6a231507;
	imm32 r1, 0x16342618;
	imm32 r2, 0x2c653729;
	imm32 r3, 0x3d56483a;
	imm32 r4, 0x4e67694b;
	imm32 r5, 0x5f78665c;
	imm32 r6, 0x60897b6d;
	imm32 r7, 0x719a8c76;
	W [ P5 ] = R7;
	W [ P1 ] = R0;
	W [ P2 ] = R1;
	W [ P4 ] = R3;
	W [ FP ] = R4;
	R0 = [ P1 ];
	R1 = [ P2 ];
	R3 = [ P4 ];
	R4 = [ P5 ];
	R5 = [ FP ];
	CHECKREG r0, 0x20211507;
	CHECKREG r1, 0x40412618;
	CHECKREG r3, 0x8081483A;
	CHECKREG r4, 0x00018C76;
	CHECKREG r5, 0xA0A1694B;
	CHECKREG r7, 0x719A8C76;

	pass

// Pre-load memory with known data
// More data is defined than will actually be used
	.data

DATA_ADDR_1:
	.dd 0x00010203
	.dd 0x04050607
	.dd 0x08090A0B
	.dd 0x0C0D0E0F
	.dd 0x10111213
	.dd 0x14151617
	.dd 0x18191A1B
	.dd 0x1C1D1E1F

DATA_ADDR_2:
	.dd 0x20212223
	.dd 0x24252627
	.dd 0x28292A2B
	.dd 0x2C2D2E2F
	.dd 0x30313233
	.dd 0x34353637
	.dd 0x38393A3B
	.dd 0x3C3D3E3F

DATA_ADDR_3:
	.dd 0x40414243
	.dd 0x44454647
	.dd 0x48494A4B
	.dd 0x4C4D4E4F
	.dd 0x50515253
	.dd 0x54555657
	.dd 0x58595A5B
	.dd 0x5C5D5E5F

DATA_ADDR_4:
	.dd 0x60616263
	.dd 0x64656667
	.dd 0x68696A6B
	.dd 0x6C6D6E6F
	.dd 0x70717273
	.dd 0x74757677
	.dd 0x78797A7B
	.dd 0x7C7D7E7F

DATA_ADDR_5:
	.dd 0x80818283
	.dd 0x84858687
	.dd 0x88898A8B
	.dd 0x8C8D8E8F
	.dd 0x90919293
	.dd 0x94959697
	.dd 0x98999A9B
	.dd 0x9C9D9E9F

DATA_ADDR_6:
	.dd 0xA0A1A2A3
	.dd 0xA4A5A6A7
	.dd 0xA8A9AAAB
	.dd 0xACADAEAF
	.dd 0xB0B1B2B3
	.dd 0xB4B5B6B7
	.dd 0xB8B9BABB
	.dd 0xBCBDBEBF

DATA_ADDR_7:
	.dd 0xC0C1C2C3
	.dd 0xC4C5C6C7
	.dd 0xC8C9CACB
	.dd 0xCCCDCECF
	.dd 0xD0D1D2D3
	.dd 0xD4D5D6D7
	.dd 0xD8D9DADB
	.dd 0xDCDDDEDF
	.dd 0xE0E1E2E3
	.dd 0xE4E5E6E7
	.dd 0xE8E9EAEB
	.dd 0xECEDEEEF
	.dd 0xF0F1F2F3
	.dd 0xF4F5F6F7
	.dd 0xF8F9FAFB
	.dd 0xFCFDFEFF
