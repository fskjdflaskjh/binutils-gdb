# Blackfin testcase for Accumulator Rotates (ROT)
# mach: bfin

	.include "testutils.inc"

	.macro atest_setup acc:req, val_x:req, val_w:req, cc:req, shift:req
	imm32 R0, \val_w
	imm32 R1, \val_x
	R2 = \cc;
	R3 = \shift
	\acc\().W = R0;
	\acc\().X = R1;
	CC = R2;
	.endm

	.macro atest_check acc:req, exp_x:req, exp_w:req, expcc:req
	R7 = CC;
	CHECKREG R7, \expcc;

	R2 = \acc\().W;
	CHECKREG R2, \exp_w;

	R6 = \acc\().X;
	R6 = R6.B (z);
	CHECKREG R6, \exp_x;
	.endm

	.macro _atest acc:req, val_x:req, val_w:req, cc:req, shift:req, exp_x:req, exp_w:req, expcc:req
	atest_setup \acc, \val_x, \val_w, \cc, \shift
	_DBG \acc;
	\acc = ROT \acc BY \shift;
	atest_check \acc, \exp_x, \exp_w, \expcc

	atest_setup \acc, \val_x, \val_w, \cc, \shift
	\acc = ROT \acc BY R3.L;
	atest_check \acc, \exp_x, \exp_w, \expcc
	.endm

	.macro atest val_x:req, val_w:req, cc:req, shift:req, exp_x:req, exp_w:req, expcc:req
	_atest A0, \val_x, \val_w, \cc, \shift, \exp_x, \exp_w, \expcc
	_atest A1, \val_x, \val_w, \cc, \shift, \exp_x, \exp_w, \expcc
	.endm

	start

	atest 0x00, 0x00000000, 0,   0, 0x00, 0x00000000, 0
	atest 0xa5, 0xa5a5a5a5, 0,   0, 0xa5, 0xa5a5a5a5, 0
	atest 0x00, 0x00000000, 1,   0, 0x00, 0x00000000, 1
	atest 0xa5, 0xa5a5a5a5, 1,   0, 0xa5, 0xa5a5a5a5, 1
	atest 0x00, 0x00000000, 0,  10, 0x00, 0x00000000, 0

	atest 0x00, 0x0000000f, 0,   4, 0x00, 0x000000f0, 0
	atest 0x00, 0x0000000f, 1,   4, 0x00, 0x000000f8, 0
	atest 0x00, 0x0000000f, 0,  20, 0x00, 0x00f00000, 0
	atest 0x00, 0x0000000f, 1,  20, 0x00, 0x00f80000, 0
	atest 0x00, 0x0000000f, 0,  -5, 0xf0, 0x00000000, 0
	atest 0x00, 0x0000000f, 1,  -5, 0xf8, 0x00000000, 0
	atest 0x00, 0x0000000f, 0,  -1, 0x00, 0x00000007, 1
	atest 0x00, 0x0000000f, 1,  -1, 0x80, 0x00000007, 1

	atest 0xff, 0xffffffff, 1,  10, 0xff, 0xffffffff, 1
	atest 0x11, 0x11111110, 0,  -5, 0x00, 0x88888888, 1

	atest 0x1f, 0x2e3d4c5b, 1,   0, 0x1f, 0x2e3d4c5b, 1
	atest 0x1f, 0x2e3d4c5b, 1,   1, 0x3e, 0x5c7a98b7, 0
	atest 0x1f, 0x2e3d4c5b, 1,   2, 0x7c, 0xb8f5316e, 0
	atest 0x1f, 0x2e3d4c5b, 1,   3, 0xf9, 0x71ea62dc, 0
	atest 0x1f, 0x2e3d4c5b, 1,   4, 0xf2, 0xe3d4c5b8, 1
	atest 0x1f, 0x2e3d4c5b, 1,   5, 0xe5, 0xc7a98b71, 1
	atest 0x1f, 0x2e3d4c5b, 1,   6, 0xcb, 0x8f5316e3, 1
	atest 0x1f, 0x2e3d4c5b, 1,   7, 0x97, 0x1ea62dc7, 1
	atest 0x1f, 0x2e3d4c5b, 1,   8, 0x2e, 0x3d4c5b8f, 1
	atest 0x1f, 0x2e3d4c5b, 1,   9, 0x5c, 0x7a98b71f, 0
	atest 0x1f, 0x2e3d4c5b, 1,  10, 0xb8, 0xf5316e3e, 0
	atest 0x1f, 0x2e3d4c5b, 1,  11, 0x71, 0xea62dc7c, 1
	atest 0x1f, 0x2e3d4c5b, 1,  12, 0xe3, 0xd4c5b8f9, 0
	atest 0x1f, 0x2e3d4c5b, 1,  13, 0xc7, 0xa98b71f2, 1
	atest 0x1f, 0x2e3d4c5b, 1,  14, 0x8f, 0x5316e3e5, 1
	atest 0x1f, 0x2e3d4c5b, 1,  15, 0x1e, 0xa62dc7cb, 1
	atest 0x1f, 0x2e3d4c5b, 1,  16, 0x3d, 0x4c5b8f97, 0
	atest 0x1f, 0x2e3d4c5b, 1,  17, 0x7a, 0x98b71f2e, 0
	atest 0x1f, 0x2e3d4c5b, 1,  18, 0xf5, 0x316e3e5c, 0
	atest 0x1f, 0x2e3d4c5b, 1,  19, 0xea, 0x62dc7cb8, 1
	atest 0x1f, 0x2e3d4c5b, 1,  20, 0xd4, 0xc5b8f971, 1
	atest 0x1f, 0x2e3d4c5b, 1,  21, 0xa9, 0x8b71f2e3, 1
	atest 0x1f, 0x2e3d4c5b, 1,  22, 0x53, 0x16e3e5c7, 1
	atest 0x1f, 0x2e3d4c5b, 1,  23, 0xa6, 0x2dc7cb8f, 0
	atest 0x1f, 0x2e3d4c5b, 1,  24, 0x4c, 0x5b8f971e, 1
	atest 0x1f, 0x2e3d4c5b, 1,  25, 0x98, 0xb71f2e3d, 0
	atest 0x1f, 0x2e3d4c5b, 1,  26, 0x31, 0x6e3e5c7a, 1
	atest 0x1f, 0x2e3d4c5b, 1,  27, 0x62, 0xdc7cb8f5, 0
	atest 0x1f, 0x2e3d4c5b, 1,  28, 0xc5, 0xb8f971ea, 0
	atest 0x1f, 0x2e3d4c5b, 1,  29, 0x8b, 0x71f2e3d4, 1
	atest 0x1f, 0x2e3d4c5b, 1,  30, 0x16, 0xe3e5c7a9, 1
	atest 0x1f, 0x2e3d4c5b, 1,  31, 0x2d, 0xc7cb8f53, 0
	atest 0x1f, 0x2e3d4c5b, 1,  -1, 0x8f, 0x971ea62d, 1
	atest 0x1f, 0x2e3d4c5b, 1,  -2, 0xc7, 0xcb8f5316, 1
	atest 0x1f, 0x2e3d4c5b, 1,  -3, 0xe3, 0xe5c7a98b, 0
	atest 0x1f, 0x2e3d4c5b, 1,  -4, 0x71, 0xf2e3d4c5, 1
	atest 0x1f, 0x2e3d4c5b, 1,  -5, 0xb8, 0xf971ea62, 1
	atest 0x1f, 0x2e3d4c5b, 1,  -6, 0xdc, 0x7cb8f531, 0
	atest 0x1f, 0x2e3d4c5b, 1,  -7, 0x6e, 0x3e5c7a98, 1
	atest 0x1f, 0x2e3d4c5b, 1,  -8, 0xb7, 0x1f2e3d4c, 0
	atest 0x1f, 0x2e3d4c5b, 1,  -9, 0x5b, 0x8f971ea6, 0
	atest 0x1f, 0x2e3d4c5b, 1, -10, 0x2d, 0xc7cb8f53, 0
	atest 0x1f, 0x2e3d4c5b, 1, -11, 0x16, 0xe3e5c7a9, 1
	atest 0x1f, 0x2e3d4c5b, 1, -12, 0x8b, 0x71f2e3d4, 1
	atest 0x1f, 0x2e3d4c5b, 1, -13, 0xc5, 0xb8f971ea, 0
	atest 0x1f, 0x2e3d4c5b, 1, -14, 0x62, 0xdc7cb8f5, 0
	atest 0x1f, 0x2e3d4c5b, 1, -15, 0x31, 0x6e3e5c7a, 1
	atest 0x1f, 0x2e3d4c5b, 1, -16, 0x98, 0xb71f2e3d, 0
	atest 0x1f, 0x2e3d4c5b, 1, -17, 0x4c, 0x5b8f971e, 1
	atest 0x1f, 0x2e3d4c5b, 1, -18, 0xa6, 0x2dc7cb8f, 0
	atest 0x1f, 0x2e3d4c5b, 1, -19, 0x53, 0x16e3e5c7, 1
	atest 0x1f, 0x2e3d4c5b, 1, -20, 0xa9, 0x8b71f2e3, 1
	atest 0x1f, 0x2e3d4c5b, 1, -21, 0xd4, 0xc5b8f971, 1
	atest 0x1f, 0x2e3d4c5b, 1, -22, 0xea, 0x62dc7cb8, 1
	atest 0x1f, 0x2e3d4c5b, 1, -23, 0xf5, 0x316e3e5c, 0
	atest 0x1f, 0x2e3d4c5b, 1, -24, 0x7a, 0x98b71f2e, 0
	atest 0x1f, 0x2e3d4c5b, 1, -25, 0x3d, 0x4c5b8f97, 0
	atest 0x1f, 0x2e3d4c5b, 1, -26, 0x1e, 0xa62dc7cb, 1
	atest 0x1f, 0x2e3d4c5b, 1, -27, 0x8f, 0x5316e3e5, 1
	atest 0x1f, 0x2e3d4c5b, 1, -28, 0xc7, 0xa98b71f2, 1
	atest 0x1f, 0x2e3d4c5b, 1, -29, 0xe3, 0xd4c5b8f9, 0
	atest 0x1f, 0x2e3d4c5b, 1, -30, 0x71, 0xea62dc7c, 1
	atest 0x1f, 0x2e3d4c5b, 1, -31, 0xb8, 0xf5316e3e, 0
	atest 0x1f, 0x2e3d4c5b, 1, -32, 0x5c, 0x7a98b71f, 0

	pass
