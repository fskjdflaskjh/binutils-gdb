//Original:/proj/frio/dv/testcases/core/c_dsp32mac_pair_a1a0_i/c_dsp32mac_pair_a1a0_i.dsp
// Spec Reference: dsp32mac pair a1a0 I
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
	R7 = ( A1 += R1.L * R0.L ),  R6 = ( A0 = R1.L * R0.L )  (IS);
	P1 = A1.w;
	P2 = A0.w;
	R1 = ( A1 = R2.L * R3.L ),  R0 = ( A0 = R2.H * R3.L )  (IS);
	P3 = A1.w;
	P4 = A0.w;
	R3 = ( A1 = R7.L * R4.L ),  R2 = ( A0 += R7.H * R4.H )  (IS);
	P5 = A1.w;
	SP = A0.w;
	R5 = ( A1 += R6.L * R5.L ),  R4 = ( A0 += R6.L * R5.H )  (IS);
	FP = A1.w;
	CHECKREG r0, 0xFFFD9ABC;
	CHECKREG r1, 0x00025D4F;
	CHECKREG r2, 0x0004A9F4;
	CHECKREG r3, 0x05E8D563;
	CHECKREG r4, 0x0114469B;
	CHECKREG r5, 0xFECD7B7C;
	CHECKREG r6, 0xFF910EEB;
	CHECKREG r7, 0xFF910EEB;
	CHECKREG p1, 0xFF910EEB;
	CHECKREG p2, 0xFF910EEB;
	CHECKREG p3, 0x00025D4F;
	CHECKREG p4, 0xFFFD9ABC;
	CHECKREG p5, 0x05E8D563;
	CHECKREG sp, 0x0004A9F4;
	CHECKREG fp, 0xFECD7B7C;

	imm32 r0, 0x98764abd;
	imm32 r1, 0xa1bcf4c7;
	imm32 r2, 0xa1145649;
	imm32 r3, 0x00010005;
	imm32 r4, 0xefbc1569;
	imm32 r5, 0x1235010b;
	imm32 r6, 0x000c001d;
	imm32 r7, 0x678e0001;
	R5 = ( A1 += R1.L * R0.H ),  R4 = ( A0 = R1.L * R0.L )  (IS);
	P1 = A1.w;
	P2 = A0.w;
	R1 = ( A1 = R2.L * R3.H ),  R0 = ( A0 -= R2.H * R3.L )  (IS);
	P2 = A0.w;
	P3 = A1.w;
	P4 = A0.w;
	R3 = ( A1 -= R4.L * R5.H ),  R2 = ( A0 += R4.H * R5.H )  (IS);
	P5 = A1.w;
	SP = A0.w;
	R1 = ( A1 += R6.L * R7.H ),  R0 = ( A0 += R6.L * R7.H )  (IS);
	FP = A0.w;
	CHECKREG r0, 0xFCBBE07C;
	CHECKREG r1, 0xFF409C82;
	CHECKREG r2, 0xFCB02566;
	CHECKREG r3, 0xFF34E16C;
	CHECKREG r4, 0xFCB93CEB;
	CHECKREG r5, 0x03577736;
	CHECKREG r6, 0x000C001D;
	CHECKREG r7, 0x678E0001;
	CHECKREG p1, 0x03577736;
	CHECKREG p2, 0xFCBB1787;
	CHECKREG p3, 0x00005649;
	CHECKREG p4, 0xFCBB1787;
	CHECKREG p5, 0xFF34E16C;
	CHECKREG sp, 0xFCB02566;
	CHECKREG fp, 0xFCBBE07C;

	imm32 r0, 0x7136459d;
	imm32 r1, 0xabd69ec7;
	imm32 r2, 0x71145679;
	imm32 r3, 0x08010007;
	imm32 r4, 0xef9c1569;
	imm32 r5, 0x1225010b;
	imm32 r6, 0x0003401d;
	imm32 r7, 0x678e0561;
	R5 = ( A1 += R1.H * R0.L ),  R4 = ( A0 = R1.L * R0.L )  (IS);
	P1 = A1.w;
	P2 = A0.w;
	R7 = ( A1 = R2.H * R3.L ),  R6 = ( A0 = R2.H * R3.L )  (IS);
	P3 = A1.w;
	P4 = A0.w;
	R1 = ( A1 -= R4.H * R5.L ),  R0 = ( A0 += R4.H * R5.H )  (IS);
	P5 = A1.w;
	SP = A0.w;
	R5 = ( A1 += R6.H * R7.L ),  R4 = ( A0 += R6.L * R7.H )  (IS);
	FP = A0.w;
	CHECKREG r0, 0x0273FCDC;
	CHECKREG r1, 0xF76A2B8C;
	CHECKREG r2, 0x71145679;
	CHECKREG r3, 0x08010007;
	CHECKREG r4, 0x02744380;
	CHECKREG r5, 0xF76A7230;
	CHECKREG r6, 0x0003178C;
	CHECKREG r7, 0x0003178C;
	CHECKREG p1, 0xE85DACC0;
	CHECKREG p2, 0xE590030B;
	CHECKREG p3, 0x0003178C;
	CHECKREG p5, 0xF76A2B8C;
	CHECKREG p4, 0x0003178C;
	CHECKREG sp, 0x0273FCDC;
	CHECKREG fp, 0x02744380;

	imm32 r0, 0x123489bd;
	imm32 r1, 0x91bcfec7;
	imm32 r2, 0xa9145679;
	imm32 r3, 0xd0910007;
	imm32 r4, 0xedb91569;
	imm32 r5, 0xd235910b;
	imm32 r6, 0x0d0c0999;
	imm32 r7, 0x67de0009;
	R1 = ( A1 += R5.H * R3.H ),  R0 = ( A0 = R5.L * R3.L )  (IS);
	P1 = A1.w;
	P2 = A0.w;
	R3 = ( A1 = R2.H * R1.H ),  R2 = ( A0 -= R2.H * R1.L )  (IS);
	P3 = A1.w;
	P4 = A0.w;
	R5 = ( A1 = R7.H * R0.H ),  R4 = ( A0 += R7.H * R0.H )  (IS);
	P5 = A1.w;
	SP = A0.w;
	R7 = ( A1 += R4.H * R6.H ),  R6 = ( A0 += R4.L * R6.H )  (IS);
	FP = A0.w;
	CHECKREG r0, 0xFFFCF74D;
	CHECKREG r1, 0xFFE69235;
	CHECKREG r2, 0xDAB58E29;
	CHECKREG r3, 0x0008D3F8;
	CHECKREG r4, 0xDAB3EEB1;
	CHECKREG r5, 0xFFFE6088;
	CHECKREG r6, 0xD9D21BFD;
	CHECKREG r7, 0xFE17B7EC;
	CHECKREG p1, 0xFFE69235;
	CHECKREG p2, 0xFFFCF74D;
	CHECKREG p3, 0x0008D3F8;
	CHECKREG p4, 0xDAB58E29;
	CHECKREG p5, 0xFFFE6088;
	CHECKREG sp, 0xDAB3EEB1;
	CHECKREG fp, 0xD9D21BFD;

	imm32 r0, 0x63545abd;
	imm32 r1, 0x86bcfec7;
	imm32 r2, 0xa8645679;
	imm32 r3, 0x00860007;
	imm32 r4, 0xefb86569;
	imm32 r5, 0x1235860b;
	imm32 r6, 0x000c086d;
	imm32 r7, 0x678e0086;
	R7 = ( A1 += R1.L * R0.L ) (M),  R6 = ( A0 = R1.L * R0.L )  (IS);
	P1 = A1.w;
	P2 = A0.w;
	R1 = ( A1 = R2.L * R3.L ) (M),  R0 = ( A0 = R2.H * R3.L )  (IS);
	P3 = A1.w;
	P4 = A0.w;
	R3 = ( A1 -= R7.L * R4.L ) (M),  R2 = ( A0 -= R7.H * R4.H )  (IS);
	P5 = A1.w;
	SP = A0.w;
	R5 = ( A1 += R6.L * R5.L ) (M),  R4 = ( A0 += R6.L * R5.H )  (IS);
	FP = A0.w;
	CHECKREG r0, 0xFFFD9ABC;
	CHECKREG r1, 0x00025D4F;
	CHECKREG r2, 0xFFD771FC;
	CHECKREG r3, 0x16A6FC20;
	CHECKREG r4, 0x00E70EA3;
	CHECKREG r5, 0x1E76A239;
	CHECKREG r6, 0xFF910EEB;
	CHECKREG r7, 0xFDA8C6D7;
	CHECKREG p1, 0xFDA8C6D7;
	CHECKREG p2, 0xFF910EEB;
	CHECKREG p3, 0x00025D4F;
	CHECKREG p4, 0xFFFD9ABC;
	CHECKREG p5, 0x16A6FC20;
	CHECKREG sp, 0xFFD771FC;
	CHECKREG fp, 0x00E70EA3;

	imm32 r0, 0x98764abd;
	imm32 r1, 0xa1bcf4c7;
	imm32 r2, 0xa1145649;
	imm32 r3, 0x00010005;
	imm32 r4, 0xefbc1569;
	imm32 r5, 0x1235010b;
	imm32 r6, 0x000c001d;
	imm32 r7, 0x678e0001;
	R5 = A1,  R4 = ( A0 = R1.L * R0.L )  (IS);
	P1 = A1.w;
	P2 = A0.w;
	R1 = A1,  R0 = ( A0 = R2.H * R3.L )  (IS);
	P3 = A1.w;
	P4 = A0.w;
	R3 = A1,  R2 = ( A0 -= R4.H * R5.H )  (IS);
	P5 = A1.w;
	SP = A0.w;
	R1 = A1,  R0 = ( A0 += R6.L * R7.H )  (IS);
	FP = A1.w;
	CHECKREG r0, 0x006DB534;
	CHECKREG r1, 0x1E76A239;
	CHECKREG r2, 0x0061FA1E;
	CHECKREG r3, 0x1E76A239;
	CHECKREG r4, 0xFCB93CEB;
	CHECKREG r5, 0x1E76A239;
	CHECKREG r6, 0x000C001D;
	CHECKREG r7, 0x678E0001;
	CHECKREG p1, 0x1E76A239;
	CHECKREG p2, 0xFCB93CEB;
	CHECKREG p3, 0x1E76A239;
	CHECKREG p4, 0xFFFE2564;
	CHECKREG p5, 0x1E76A239;
	CHECKREG sp, 0x0061FA1E;
	CHECKREG fp, 0x1E76A239;

	imm32 r0, 0x7136459d;
	imm32 r1, 0xabd69ec7;
	imm32 r2, 0x71145679;
	imm32 r3, 0x08010007;
	imm32 r4, 0xef9c1569;
	imm32 r5, 0x1225010b;
	imm32 r6, 0x0003401d;
	imm32 r7, 0x678e0561;
	R5 = ( A1 += R1.H * R0.L ) (M),  R4 = ( A0 = R1.L * R0.L )  (IS);
	P1 = A1.w;
	P2 = A0.w;
	R7 = A1,  R6 = ( A0 = R2.H * R3.L )  (IS);
	P3 = A1.w;
	P4 = A0.w;
	R1 = ( A1 = R4.H * R5.L ) (M),  R0 = ( A0 += R4.H * R5.H )  (IS);
	P5 = A1.w;
	SP = A0.w;
	R5 = A1,  R4 = ( A0 -= R6.L * R7.H )  (IS);
	FP = A1.w;
	CHECKREG r0, 0xFF3AD93C;
	CHECKREG r1, 0xED91D5F0;
	CHECKREG r2, 0x71145679;
	CHECKREG r3, 0x08010007;
	CHECKREG r4, 0xFE887FD8;
	CHECKREG r5, 0xED91D5F0;
	CHECKREG r6, 0x0003178C;
	CHECKREG r7, 0x0793B277;
	CHECKREG p1, 0x0793B277;
	CHECKREG p2, 0xE590030B;
	CHECKREG p3, 0x0793B277;
	CHECKREG p4, 0x0003178C;
	CHECKREG p5, 0xED91D5F0;
	CHECKREG sp, 0xFF3AD93C;
	CHECKREG fp, 0xED91D5F0;

	imm32 r0, 0x123489bd;
	imm32 r1, 0x91bcfec7;
	imm32 r2, 0xa9145679;
	imm32 r3, 0xd0910007;
	imm32 r4, 0xedb91569;
	imm32 r5, 0xd235910b;
	imm32 r6, 0x0d0c0999;
	imm32 r7, 0x67de0009;
	R1 = A1,  R0 = ( A0 = R5.L * R3.L )  (IS);
	P1 = A1.w;
	P2 = A0.w;
	R3 = ( A1 = R2.H * R1.H ) (M),  R2 = ( A0 = R2.H * R1.L )  (IS);
	P3 = A1.w;
	P4 = A0.w;
	R5 = ( A1 = R7.H * R0.H ) (M),  R4 = ( A0 += R7.H * R0.H )  (IS);
	P5 = A0.w;
	SP = A1.w;
	R7 = A1,  R6 = ( A0 += R4.L * R6.H )  (IS);
	FP = A0.w;
	CHECKREG r0, 0xFFFCF74D;
	CHECKREG r1, 0xED91D5F0;
	CHECKREG r2, 0x0E4826C0;
	CHECKREG r3, 0xAF564854;
	CHECKREG r4, 0x0E468748;
	CHECKREG r5, 0x67DC6088;
	CHECKREG r6, 0x081F86A8;
	CHECKREG r7, 0x67DC6088;
	CHECKREG p1, 0xED91D5F0;
	CHECKREG p2, 0xFFFCF74D;
	CHECKREG p3, 0xAF564854;
	CHECKREG p4, 0x0E4826C0;
	CHECKREG p5, 0x0E468748;
	CHECKREG sp, 0x67DC6088;
	CHECKREG fp, 0x081F86A8;

	pass
