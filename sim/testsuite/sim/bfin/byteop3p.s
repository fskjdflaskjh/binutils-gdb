# Blackfin testcase for BYTEOP3P
# mach: bfin

	.include "testutils.inc"

	start

	.macro check_it res:req
	imm32 R7, \res
	CC = R6 == R7;
	IF !CC JUMP 1f;
	.endm
	.macro test_byteop3p i0:req, i1:req, resL:req, resH:req, resLR:req, resHR:req
	dmm32 I0, \i0
	dmm32 I1, \i1

	R6 = BYTEOP3P (R1:0, R3:2) (LO);
	check_it \resL
	R6 = BYTEOP3P (R1:0, R3:2) (HI);
	check_it \resH
	R6 = BYTEOP3P (R1:0, R3:2) (LO, R);
	check_it \resLR
	R6 = BYTEOP3P (R1:0, R3:2) (HI, R);
	check_it \resHR

	jump 2f;
1:	fail
2:
	.endm

	imm32 R0, 0x01020304
	imm32 R1, 0x10203040
	imm32 R2, 0x0a0b0c0d
	imm32 R3, 0xa0b0c0d0

	test_byteop3p 0, 0, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 0, 1, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 0, 2, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 0, 3, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 1, 0, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 1, 1, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 1, 2, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 1, 3, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 2, 0, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 2, 1, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 2, 2, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 2, 3, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 3, 0, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 3, 1, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 3, 2, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 3, 3, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00

	imm32 R0, ~0x01020304
	imm32 R1, ~0x10203040
	imm32 R2, ~0x0a0b0c0d
	imm32 R3, ~0xa0b0c0d0

	test_byteop3p 0, 0, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 0, 1, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 0, 2, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 0, 3, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 1, 0, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 1, 1, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 1, 2, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 1, 3, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 2, 0, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 2, 1, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 2, 2, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 2, 3, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 3, 0, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 3, 1, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 3, 2, 0x00000000, 0x00000000, 0x00000000, 0x00000000
	test_byteop3p 3, 3, 0x00000000, 0x00000000, 0x00000000, 0x00000000

	imm32 R0, 0x00010002
	imm32 R1, 0x00030004
	imm32 R2, 0x10203040
	imm32 R3, 0x50607080

	test_byteop3p 0, 0, 0x00110032, 0x21004200, 0x00530074, 0x63008400
	test_byteop3p 0, 1, 0x00810022, 0x11003200, 0x00430064, 0x53007400
	test_byteop3p 0, 2, 0x00710012, 0x81002200, 0x00330054, 0x43006400
	test_byteop3p 0, 3, 0x00610082, 0x71001200, 0x00230044, 0x33005400
	test_byteop3p 1, 0, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 1, 1, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 1, 2, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 1, 3, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 2, 0, 0x00140031, 0x24004100, 0x00520073, 0x62008300
	test_byteop3p 2, 1, 0x00840021, 0x14003100, 0x00420063, 0x52007300
	test_byteop3p 2, 2, 0x00740011, 0x84002100, 0x00320053, 0x42006300
	test_byteop3p 2, 3, 0x00640081, 0x74001100, 0x00220043, 0x32005300
	test_byteop3p 3, 0, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 3, 1, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 3, 2, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 3, 3, 0x00ff00ff, 0xff00ff00, 0x00ff00ff, 0xff00ff00

	imm32 R0, 0x00100200
	imm32 R1, 0x30000040
	imm32 R2, 0x1a2b3c4d
	imm32 R3, 0x5e6f7a8b

	test_byteop3p 0, 0, 0x002a00ff, 0x3b00ff00, 0x00ff00ba, 0xff00cb00
	test_byteop3p 0, 1, 0x009b00ff, 0x2a00ff00, 0x00ff00af, 0xff00ba00
	test_byteop3p 0, 2, 0x008a00ff, 0x9b00ff00, 0x00ff009e, 0xff00af00
	test_byteop3p 0, 3, 0x007f00ff, 0x8a00ff00, 0x00ff008d, 0xff009e00
	test_byteop3p 1, 0, 0x00ff00ff, 0xff00ff00, 0x008e007a, 0x9f008b00
	test_byteop3p 1, 1, 0x00ff00ff, 0xff00ff00, 0x007d006f, 0x8e007a00
	test_byteop3p 1, 2, 0x00ff00ff, 0xff00ff00, 0x006c005e, 0x7d006f00
	test_byteop3p 1, 3, 0x00ff00ff, 0xff00ff00, 0x005b004d, 0x6c005e00
	test_byteop3p 2, 0, 0x005a004c, 0x6b005d00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 2, 1, 0x00cb003b, 0x5a004c00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 2, 2, 0x00ba002a, 0xcb003b00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 2, 3, 0x00af009b, 0xba002a00, 0x00ff00ff, 0xff00ff00
	test_byteop3p 3, 0, 0x001a00ff, 0x2b00ff00, 0x00ff00aa, 0xff00bb00
	test_byteop3p 3, 1, 0x008b00ff, 0x1a00ff00, 0x00ff009f, 0xff00aa00
	test_byteop3p 3, 2, 0x007a00ff, 0x8b00ff00, 0x00ff008e, 0xff009f00
	test_byteop3p 3, 3, 0x006f00ff, 0x7a00ff00, 0x00ff007d, 0xff008e00

	pass
