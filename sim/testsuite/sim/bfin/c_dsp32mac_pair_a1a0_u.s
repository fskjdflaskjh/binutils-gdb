//Original:/proj/frio/dv/testcases/core/c_dsp32mac_pair_a1a0_u/c_dsp32mac_pair_a1a0_u.dsp
// Spec Reference: dsp32mac pair a1a0 U
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
	R7 = ( A1 += R1.L * R0.L ),  R6 = ( A0 = R1.L * R0.L )  (FU);
	P1 = A1.w;
	P2 = A0.w;
	R1 = ( A1 = R2.L * R3.L ),  R0 = ( A0 = R2.H * R3.L )  (FU);
	P3 = A1.w;
	P4 = A0.w;
	R3 = ( A1 -= R7.L * R4.L ),  R2 = ( A0 += R7.H * R4.H )  (FU);
	P5 = A1.w;
	SP = A0.w;
	R5 = ( A1 += R6.L * R5.L ),  R4 = ( A0 += R6.L * R5.H )  (FU);
	FP = A1.w;
	CHECKREG r0, 0x00049ABC;
	CHECKREG r1, 0x00025D4F;
	CHECKREG r2, 0x549454CC;
	CHECKREG r3, 0x00000000;
	CHECKREG r4, 0x55A3F173;
	CHECKREG r5, 0x07CFA619;
	CHECKREG r6, 0x5A4E0EEB;
	CHECKREG r7, 0x5A4E0EEB;
	CHECKREG p1, 0x5A4E0EEB;
	CHECKREG p2, 0x5A4E0EEB;
	CHECKREG p3, 0x00025D4F;
	CHECKREG p4, 0x00049ABC;
	CHECKREG p5, 0x00000000;
	CHECKREG sp, 0x549454CC;
	CHECKREG fp, 0x07CFA619;

	imm32 r0, 0x98764abd;
	imm32 r1, 0xa1bcf4c7;
	imm32 r2, 0xa1145649;
	imm32 r3, 0x00010005;
	imm32 r4, 0xefbc1569;
	imm32 r5, 0x1235010b;
	imm32 r6, 0x000c001d;
	imm32 r7, 0x678e0001;
	R5 = ( A1 += R1.L * R0.H ),  R4 = ( A0 -= R1.L * R0.L )  (FU);
	P1 = A1.w;
	P2 = A0.w;
	R1 = ( A1 -= R2.L * R3.H ),  R0 = ( A0 = R2.H * R3.L )  (FU);
	P2 = A0.w;
	P3 = A1.w;
	P4 = A0.w;
	R3 = ( A1 = R4.L * R5.H ),  R2 = ( A0 += R4.H * R5.H )  (FU);
	P5 = A1.w;
	SP = A0.w;
	R1 = ( A1 += R6.L * R7.H ),  R0 = ( A0 += R6.L * R7.H )  (FU);
	FP = A0.w;
	CHECKREG r0, 0x089013D8;
	CHECKREG r1, 0x6C5ACAC6;
	CHECKREG r2, 0x088458C2;
	CHECKREG r3, 0x6C4F0FB0;
	CHECKREG r4, 0x0E2DB488;
	CHECKREG r5, 0x9996A1D3;
	CHECKREG r6, 0x000C001D;
	CHECKREG r7, 0x678E0001;
	CHECKREG p1, 0x9996A1D3;
	CHECKREG p2, 0x00032564;
	CHECKREG p3, 0x99964B8A;
	CHECKREG p4, 0x00032564;
	CHECKREG p5, 0x6C4F0FB0;
	CHECKREG sp, 0x088458C2;
	CHECKREG fp, 0x089013D8;

	imm32 r0, 0x7136459d;
	imm32 r1, 0xabd69ec7;
	imm32 r2, 0x71145679;
	imm32 r3, 0x08010007;
	imm32 r4, 0xef9c1569;
	imm32 r5, 0x1225010b;
	imm32 r6, 0x0003401d;
	imm32 r7, 0x678e0561;
	R5 = ( A1 += R1.H * R0.L ),  R4 = ( A0 = R1.L * R0.L )  (FU);
	P1 = A1.w;
	P2 = A0.w;
	R7 = ( A1 -= R2.H * R3.L ),  R6 = ( A0 = R2.H * R3.L )  (FU);
	P3 = A1.w;
	P4 = A0.w;
	R1 = ( A1 = R4.H * R5.L ),  R0 = ( A0 += R4.H * R5.H )  (FU);
	P5 = A1.w;
	SP = A0.w;
	R5 = ( A1 += R6.H * R7.L ),  R4 = ( A0 -= R6.L * R7.H )  (FU);
	FP = A0.w;
	CHECKREG r0, 0x1A2AB610;
	CHECKREG r1, 0x24F02BB4;
	CHECKREG r2, 0x71145679;
	CHECKREG r3, 0x08010007;
	CHECKREG r4, 0x0BE761C4;
	CHECKREG r5, 0x24F2761C;
	CHECKREG r6, 0x0003178C;
	CHECKREG r7, 0x9B11C378;
	CHECKREG p1, 0x9B14DB04;
	CHECKREG p2, 0x2B2D030B;
	CHECKREG p3, 0x9B11C378;
	CHECKREG p5, 0x24F02BB4;
	CHECKREG p4, 0x0003178C;
	CHECKREG sp, 0x1A2AB610;
	CHECKREG fp, 0x0BE761C4;

	imm32 r0, 0x123489bd;
	imm32 r1, 0x91bcfec7;
	imm32 r2, 0xa9145679;
	imm32 r3, 0xd0910007;
	imm32 r4, 0xedb91569;
	imm32 r5, 0xd235910b;
	imm32 r6, 0x0d0c0999;
	imm32 r7, 0x67de0009;
	R1 = ( A1 += R5.H * R3.H ),  R0 = ( A0 = R5.L * R3.L )  (FU);
	P1 = A1.w;
	P2 = A0.w;
	R3 = ( A1 -= R2.H * R1.H ),  R2 = ( A0 = R2.H * R1.L )  (FU);
	P3 = A1.w;
	P4 = A0.w;
	R5 = ( A1 -= R7.H * R0.H ),  R4 = ( A0 += R7.H * R0.H )  (FU);
	P5 = A1.w;
	SP = A0.w;
	R7 = ( A1 += R4.H * R6.H ),  R6 = ( A0 += R4.L * R6.H )  (FU);
	FP = A0.w;
	CHECKREG r0, 0x0003F74D;
	CHECKREG r1, 0xD0349621;
	CHECKREG r2, 0x63278394;
	CHECKREG r3, 0x46B1FE11;
	CHECKREG r4, 0x6328BB2E;
	CHECKREG r5, 0x46B0C677;
	CHECKREG r6, 0x6CB2D756;
	CHECKREG r7, 0x4BBE7457;
	CHECKREG p1, 0xD0349621;
	CHECKREG p2, 0x0003F74D;
	CHECKREG p3, 0x46B1FE11;
	CHECKREG p4, 0x63278394;
	CHECKREG p5, 0x46B0C677;
	CHECKREG sp, 0x6328BB2E;
	CHECKREG fp, 0x6CB2D756;

	imm32 r0, 0x63545abd;
	imm32 r1, 0x86bcfec7;
	imm32 r2, 0xa8645679;
	imm32 r3, 0x00860007;
	imm32 r4, 0xefb86569;
	imm32 r5, 0x1235860b;
	imm32 r6, 0x000c086d;
	imm32 r7, 0x678e0086;
	R7 = ( A1 += R1.L * R0.L ) (M),  R6 = ( A0 = R1.L * R0.L )  (FU);
	P1 = A1.w;
	P2 = A0.w;
	R1 = ( A1 = R2.L * R3.L ) (M),  R0 = ( A0 = R2.H * R3.L )  (FU);
	P3 = A1.w;
	P4 = A0.w;
	R3 = ( A1 -= R7.L * R4.L ) (M),  R2 = ( A0 += R7.H * R4.H )  (FU);
	P5 = A1.w;
	SP = A0.w;
	R5 = ( A1 -= R6.L * R5.L ) (M),  R4 = ( A0 -= R6.L * R5.H )  (FU);
	FP = A0.w;
	CHECKREG r0, 0x00049ABC;
	CHECKREG r1, 0x00025D4F;
	CHECKREG r2, 0x46897C84;
	CHECKREG r3, 0x316C7D3D;
	CHECKREG r4, 0x4579DFDD;
	CHECKREG r5, 0x299CD724;
	CHECKREG r6, 0x5A4E0EEB;
	CHECKREG r7, 0x4B4F8342;
	CHECKREG p1, 0x4B4F8342;
	CHECKREG p2, 0x5A4E0EEB;
	CHECKREG p3, 0x00025D4F;
	CHECKREG p4, 0x00049ABC;
	CHECKREG p5, 0x316C7D3D;
	CHECKREG sp, 0x46897C84;
	CHECKREG fp, 0x4579DFDD;

	imm32 r0, 0x98764abd;
	imm32 r1, 0xa1bcf4c7;
	imm32 r2, 0xa1145649;
	imm32 r3, 0x00010005;
	imm32 r4, 0xefbc1569;
	imm32 r5, 0x1235010b;
	imm32 r6, 0x000c001d;
	imm32 r7, 0x678e0001;
	R5 = A1,  R4 = ( A0 = R1.L * R0.L )  (FU);
	P1 = A1.w;
	P2 = A0.w;
	R1 = A1,  R0 = ( A0 -= R2.H * R3.L )  (FU);
	P3 = A1.w;
	P4 = A0.w;
	R3 = A1,  R2 = ( A0 += R4.H * R5.H )  (FU);
	P5 = A1.w;
	SP = A0.w;
	R1 = A1,  R0 = ( A0 -= R6.L * R7.H )  (FU);
	FP = A1.w;
	CHECKREG r0, 0x5304CE59;
	CHECKREG r1, 0x299CD724;
	CHECKREG r2, 0x5310896F;
	CHECKREG r3, 0x299CD724;
	CHECKREG r4, 0x47763CEB;
	CHECKREG r5, 0x299CD724;
	CHECKREG r6, 0x000C001D;
	CHECKREG r7, 0x678E0001;
	CHECKREG p1, 0x299CD724;
	CHECKREG p2, 0x47763CEB;
	CHECKREG p3, 0x299CD724;
	CHECKREG p4, 0x47731787;
	CHECKREG p5, 0x299CD724;
	CHECKREG sp, 0x5310896F;
	CHECKREG fp, 0x299CD724;

	imm32 r0, 0x7136459d;
	imm32 r1, 0xabd69ec7;
	imm32 r2, 0x71145679;
	imm32 r3, 0x08010007;
	imm32 r4, 0xef9c1569;
	imm32 r5, 0x1225010b;
	imm32 r6, 0x0003401d;
	imm32 r7, 0x678e0561;
	R5 = ( A1 += R1.H * R0.L ) (M),  R4 = ( A0 = R1.L * R0.L )  (FU);
	P1 = A1.w;
	P2 = A0.w;
	R7 = A1,  R6 = ( A0 = R2.H * R3.L )  (FU);
	P3 = A1.w;
	P4 = A0.w;
	R1 = ( A1 = R4.H * R5.L ) (M),  R0 = ( A0 -= R4.H * R5.H )  (FU);
	P5 = A1.w;
	SP = A0.w;
	R5 = A1,  R4 = ( A0 += R6.L * R7.H )  (FU);
	FP = A1.w;
	CHECKREG r0, 0x00000000;
	CHECKREG r1, 0x2706223A;
	CHECKREG r2, 0x71145679;
	CHECKREG r3, 0x08010007;
	CHECKREG r4, 0x01B8DC2C;
	CHECKREG r5, 0x2706223A;
	CHECKREG r6, 0x0003178C;
	CHECKREG r7, 0x12B9E762;
	CHECKREG p1, 0x12B9E762;
	CHECKREG p2, 0x2B2D030B;
	CHECKREG p3, 0x12B9E762;
	CHECKREG p4, 0x0003178C;
	CHECKREG p5, 0x2706223A;
	CHECKREG sp, 0x00000000;
	CHECKREG fp, 0x2706223A;

	imm32 r0, 0x123489bd;
	imm32 r1, 0x91bcfec7;
	imm32 r2, 0xa9145679;
	imm32 r3, 0xd0910007;
	imm32 r4, 0xedb91569;
	imm32 r5, 0xd235910b;
	imm32 r6, 0x0d0c0999;
	imm32 r7, 0x67de0009;
	R1 = A1,  R0 = ( A0 -= R5.L * R3.L )  (FU);
	P1 = A1.w;
	P2 = A0.w;
	R3 = ( A1 = R2.H * R1.H ) (M),  R2 = ( A0 = R2.H * R1.L )  (FU);
	P3 = A1.w;
	P4 = A0.w;
	R5 = ( A1 = R7.H * R0.H ) (M),  R4 = ( A0 += R7.H * R0.H )  (FU);
	P5 = A0.w;
	SP = A1.w;
	R7 = A1,  R6 = ( A0 += R4.L * R6.H )  (FU);
	FP = A0.w;
	CHECKREG r0, 0x01B4E4DF;
	CHECKREG r1, 0x2706223A;
	CHECKREG r2, 0x169AF688;
	CHECKREG r3, 0xF2C00278;
	CHECKREG r4, 0x174BDCA0;
	CHECKREG r5, 0x00B0E618;
	CHECKREG r6, 0x228A5420;
	CHECKREG r7, 0x00B0E618;
	CHECKREG p1, 0x2706223A;
	CHECKREG p2, 0x01B4E4DF;
	CHECKREG p3, 0xF2C00278;
	CHECKREG p4, 0x169AF688;
	CHECKREG p5, 0x174BDCA0;
	CHECKREG sp, 0x00B0E618;
	CHECKREG fp, 0x228A5420;

	pass
