//Original:/proj/frio/dv/testcases/core/c_dsp32mac_pair_a0_s/c_dsp32mac_pair_a0_s.dsp
// Spec Reference: dsp32mac pair a0 S
# mach: bfin

.include "testutils.inc"
	start

	A1 = A0 = 0;

// The result accumulated in A       , and stored to a reg half
	imm32 r0, 0x63545abd;
	imm32 r1, 0x86bcfec7;
	imm32 r2, 0xa8645679;
	imm32 r3, 0x00860007;
	imm32 r4, 0xefb86569;
	imm32 r5, 0x1235860b;
	imm32 r6, 0x000c086d;
	imm32 r7, 0x678e0086;
	A1 += R1.L * R0.L, R6 = ( A0 -= R1.L * R0.L ) (S2RND);
	P1 = A0.w;
	A1 = R2.L * R3.L, R0 = ( A0 = R2.H * R3.L ) (S2RND);
	P2 = A0.w;
	A1 = R7.L * R4.L, R2 = ( A0 += R7.H * R4.H ) (S2RND);
	P3 = A0.w;
	A1 += R6.L * R5.L, R4 = ( A0 += R6.L * R5.H ) (S2RND);
	P4 = A0.w;
	CHECKREG r0, 0xFFF66AF0;
	CHECKREG r1, 0x86BCFEC7;
	CHECKREG r2, 0xE59E6B30;
	CHECKREG r3, 0x00860007;
	CHECKREG r4, 0xD4A4A0C0;
	CHECKREG r5, 0x1235860B;
	CHECKREG r6, 0x01BBC454;
	CHECKREG r7, 0x678E0086;
	CHECKREG p1, 0x00DDE22A;
	CHECKREG p2, 0xFFFB3578;
	CHECKREG p3, 0xF2CF3598;
	CHECKREG p4, 0xEA525060;

	imm32 r0, 0x98764abd;
	imm32 r1, 0xa1bcf4c7;
	imm32 r2, 0xa1145649;
	imm32 r3, 0x00010005;
	imm32 r4, 0xefbc1569;
	imm32 r5, 0x1235010b;
	imm32 r6, 0x000c001d;
	imm32 r7, 0x678e0001;
	A1 += R1.L * R0.H, R4 = ( A0 = R1.L * R0.L ) (S2RND);
	P1 = A0.w;
	A1 = R2.L * R3.H, R0 = ( A0 = R2.H * R3.L ) (S2RND);
	P2 = A0.w;
	A1 -= R4.L * R5.H, R2 = ( A0 += R4.H * R5.H ) (S2RND);
	P3 = A0.w;
	A1 += R6.L * R7.H, R0 = ( A0 += R6.L * R7.H ) (S2RND);
	P4 = A0.w;
	CHECKREG r0, 0xFC6CC6B8;
	CHECKREG r1, 0xA1BCF4C7;
	CHECKREG r2, 0xFC3DDA60;
	CHECKREG r3, 0x00010005;
	CHECKREG r4, 0xF2E4F3AC;
	CHECKREG r5, 0x1235010B;
	CHECKREG r6, 0x000C001D;
	CHECKREG r7, 0x678E0001;
	CHECKREG p1, 0xF97279D6;
	CHECKREG p2, 0xFFFC4AC8;
	CHECKREG p3, 0xFE1EED30;
	CHECKREG p4, 0xFE36635C;

	imm32 r0, 0x7136459d;
	imm32 r1, 0xabd69ec7;
	imm32 r2, 0x71145679;
	imm32 r3, 0x08010007;
	imm32 r4, 0xef9c1569;
	imm32 r5, 0x1225010b;
	imm32 r6, 0x0003401d;
	imm32 r7, 0x678e0561;
	A1 += R1.H * R0.L, R4 = ( A0 -= R1.L * R0.L ) (S2RND);
	P1 = A0.w;
	A1 = R2.H * R3.L, R6 = ( A0 = R2.H * R3.L ) (S2RND);
	P2 = A0.w;
	A1 = R4.H * R5.L, R0 = ( A0 -= R4.H * R5.H ) (S2RND);
	P3 = A0.w;
	A1 += R6.H * R7.L, R4 = ( A0 += R6.L * R7.H ) (S2RND);
	P4 = A0.w;
	CHECKREG r0, 0xE314ECC0;
	CHECKREG r1, 0xABD69EC7;
	CHECKREG r2, 0x71145679;
	CHECKREG r3, 0x08010007;
	CHECKREG r4, 0x7B7B2740;
	CHECKREG r5, 0x1225010B;
	CHECKREG r6, 0x000C5E30;
	CHECKREG r7, 0x678E0561;
	CHECKREG p1, 0x33165D46;
	CHECKREG p2, 0x00062F18;
	CHECKREG p3, 0xF18A7660;
	CHECKREG p4, 0x3DBD93A0;

	imm32 r0, 0x123489bd;
	imm32 r1, 0x91bcfec7;
	imm32 r2, 0xa9145679;
	imm32 r3, 0xd0910007;
	imm32 r4, 0xedb91569;
	imm32 r5, 0xd235910b;
	imm32 r6, 0x0d0c0999;
	imm32 r7, 0x67de0009;
	A1 += R5.H * R3.H, R0 = ( A0 = R5.L * R3.L ) (S2RND);
	P1 = A0.w;
	A1 -= R2.H * R1.H, R2 = ( A0 = R2.H * R1.L ) (S2RND);
	P2 = A0.w;
	A1 = R7.H * R0.H, R4 = ( A0 += R7.H * R0.H ) (S2RND);
	P3 = A0.w;
	A1 += R4.H * R6.H, R6 = ( A0 += R4.L * R6.H ) (S2RND);
	P4 = A0.w;
	CHECKREG r0, 0xFFF3DD34;
	CHECKREG r1, 0x91BCFEC7;
	CHECKREG r2, 0x01A91A30;
	CHECKREG r3, 0xD0910007;
	CHECKREG r4, 0x01940118;
	CHECKREG r5, 0xD235910B;
	CHECKREG r6, 0x01CD1598;
	CHECKREG r7, 0x67DE0009;
	CHECKREG p1, 0xFFF9EE9A;
	CHECKREG p2, 0x00D48D18;
	CHECKREG p3, 0x00CA008C;
	CHECKREG p4, 0x00E68ACC;

	imm32 r0, 0x63545abd;
	imm32 r1, 0x86bcfec7;
	imm32 r2, 0xa8645679;
	imm32 r3, 0x00860007;
	imm32 r4, 0xefb86569;
	imm32 r5, 0x1235860b;
	imm32 r6, 0x000c086d;
	imm32 r7, 0x678e0086;
	A1 += R1.L * R0.L (M), R6 = ( A0 = R1.L * R0.L ) (S2RND);
	P5 = A1.w;
	P1 = A0.w;
	A1 -= R2.L * R3.L (M), R0 = ( A0 = R2.H * R3.L ) (S2RND);
	P2 = A0.w;
	A1 = R7.L * R4.L (M), R2 = ( A0 += R7.H * R4.H ) (S2RND);
	P3 = A0.w;
	A1 += R6.L * R5.L (M), R4 = ( A0 += R6.L * R5.H ) (S2RND);
	P4 = A0.w;
	CHECKREG r0, 0xFFF66AF0;
	CHECKREG r1, 0x86BCFEC7;
	CHECKREG r2, 0xE59E6B30;
	CHECKREG r3, 0x00860007;
	CHECKREG r4, 0xF69835A0;
	CHECKREG r5, 0x1235860B;
	CHECKREG r6, 0xFE443BAC;
	CHECKREG r7, 0x678E0086;
	CHECKREG p1, 0xFF221DD6;
	CHECKREG p2, 0xFFFB3578;
	CHECKREG p3, 0xF2CF3598;
	CHECKREG p4, 0xFB4C1AD0;
	CHECKREG p5, 0xFFAFB03F;

	imm32 r0, 0x98764abd;
	imm32 r1, 0xa1bcf4c7;
	imm32 r2, 0xa1145649;
	imm32 r3, 0x00010005;
	imm32 r4, 0xefbc1569;
	imm32 r5, 0x1235010b;
	imm32 r6, 0x000c001d;
	imm32 r7, 0x678e0001;
	R4 = ( A0 = R1.L * R0.L ) (S2RND);
	P1 = A0.w;
	R0 = ( A0 = R2.H * R3.L ) (S2RND);
	P2 = A0.w;
	R2 = ( A0 -= R4.H * R5.H ) (S2RND);
	P3 = A0.w;
	R0 = ( A0 += R6.L * R7.H ) (S2RND);
	P4 = A0.w;
	CHECKREG r0, 0x03E23D18;
	CHECKREG r1, 0xA1BCF4C7;
	CHECKREG r2, 0x03B350C0;
	CHECKREG r3, 0x00010005;
	CHECKREG r4, 0xF2E4F3AC;
	CHECKREG r5, 0x1235010B;
	CHECKREG r6, 0x000C001D;
	CHECKREG r7, 0x678E0001;
	CHECKREG p1, 0xF97279D6;
	CHECKREG p2, 0xFFFC4AC8;
	CHECKREG p3, 0x01D9A860;
	CHECKREG p4, 0x01F11E8C;

	imm32 r0, 0x7136459d;
	imm32 r1, 0xabd69ec7;
	imm32 r2, 0x71145679;
	imm32 r3, 0x08010007;
	imm32 r4, 0xef9c1569;
	imm32 r5, 0x1225010b;
	imm32 r6, 0x0003401d;
	imm32 r7, 0x678e0561;
	A1 += R1.H * R0.L (M), R4 = ( A0 = R1.L * R0.L ) (S2RND);
	P1 = A0.w;
	R6 = ( A0 = R2.H * R3.L ) (S2RND);
	P2 = A0.w;
	A1 = R4.H * R5.L (M), R0 = ( A0 += R4.H * R5.H ) (S2RND);
	P3 = A0.w;
	R4 = ( A0 += R6.L * R7.H ) (S2RND);
	P4 = A0.w;
	CHECKREG r0, 0xE2113B30;
	CHECKREG r1, 0xABD69EC7;
	CHECKREG r2, 0x71145679;
	CHECKREG r3, 0x08010007;
	CHECKREG r4, 0x7A7775B0;
	CHECKREG r5, 0x1225010B;
	CHECKREG r6, 0x000C5E30;
	CHECKREG r7, 0x678E0561;
	CHECKREG p1, 0xCB200616;
	CHECKREG p2, 0x00062F18;
	CHECKREG p3, 0xF1089D98;
	CHECKREG p4, 0x3D3BBAD8;

	imm32 r0, 0x123489bd;
	imm32 r1, 0x91bcfec7;
	imm32 r2, 0xa9145679;
	imm32 r3, 0xd0910007;
	imm32 r4, 0xedb91569;
	imm32 r5, 0xd235910b;
	imm32 r6, 0x0d0c0999;
	imm32 r7, 0x67de0009;
	R0 = ( A0 -= R5.L * R3.L ) (S2RND);
	P1 = A0.w;
	A1 = R2.H * R1.H (M), R2 = ( A0 = R2.H * R1.L ) (S2RND);
	P2 = A0.w;
	A1 = R7.H * R0.H (M), R4 = ( A0 -= R7.H * R0.H ) (S2RND);
	P3 = A0.w;
	R6 = ( A0 += R4.L * R6.H ) (S2RND);
	P4 = A0.w;
	CHECKREG r0, 0x7A83987C;
	CHECKREG r1, 0x91BCFEC7;
	CHECKREG r2, 0x01A91A30;
	CHECKREG r3, 0xD0910007;
	CHECKREG r4, 0x80000000;
	CHECKREG r5, 0xD235910B;
	CHECKREG r6, 0x80000000;
	CHECKREG r7, 0x67DE0009;
	CHECKREG p1, 0x3D41CC3E;
	CHECKREG p2, 0x00D48D18;
	CHECKREG p3, 0x9D6AA7E4;
	CHECKREG p4, 0x9D6AA7E4;

	pass
