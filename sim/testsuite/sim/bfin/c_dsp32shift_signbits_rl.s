//Original:/testcases/core/c_dsp32shift_signbits_rl/c_dsp32shift_signbits_rl.dsp
// Spec Reference: dsp32shift signbits dregs_lo
# mach: bfin

.include "testutils.inc"
	start



imm32 r0, 0x00000000;
imm32 r1, 0x0000c001;
imm32 r2, 0x0000c002;
imm32 r3, 0x0000c003;
imm32 r4, 0x0000c004;
imm32 r5, 0x0000c005;
imm32 r6, 0x0000c006;
imm32 r7, 0x0000c007;
R7.L = SIGNBITS R0.L;
R1.L = SIGNBITS R0.L;
R2.L = SIGNBITS R0.L;
R3.L = SIGNBITS R0.L;
R4.L = SIGNBITS R0.L;
R5.L = SIGNBITS R0.L;
R6.L = SIGNBITS R0.L;
R0.L = SIGNBITS R0.L;
CHECKREG r1, 0x0000000F;
CHECKREG r0, 0x0000000F;
CHECKREG r2, 0x0000000F;
CHECKREG r3, 0x0000000F;
CHECKREG r4, 0x0000000F;
CHECKREG r5, 0x0000000F;
CHECKREG r6, 0x0000000F;
CHECKREG r7, 0x0000000F;

imm32 r0, 0x00000001;
imm32 r1, 0x00008001;
imm32 r2, 0x0000d002;
imm32 r3, 0x0000e003;
imm32 r4, 0x0000f004;
imm32 r5, 0x0000c005;
imm32 r6, 0x0000d006;
imm32 r7, 0x0000e007;
R0.L = SIGNBITS R1.L;
R7.L = SIGNBITS R1.L;
R2.L = SIGNBITS R1.L;
R3.L = SIGNBITS R1.L;
R4.L = SIGNBITS R1.L;
R5.L = SIGNBITS R1.L;
R6.L = SIGNBITS R1.L;
R1.L = SIGNBITS R1.L;
CHECKREG r0, 0x00000000;
CHECKREG r1, 0x00000000;
CHECKREG r2, 0x00000000;
CHECKREG r3, 0x00000000;
CHECKREG r4, 0x00000000;
CHECKREG r5, 0x00000000;
CHECKREG r6, 0x00000000;
CHECKREG r7, 0x00000000;


imm32 r0, 0x0000c001;
imm32 r1, 0x0000d001;
imm32 r2, 0x0000c00f;
imm32 r3, 0x0000e003;
imm32 r4, 0x0000f004;
imm32 r5, 0x0000f005;
imm32 r6, 0x0000f006;
imm32 r7, 0x0000f007;
R0.L = SIGNBITS R2.L;
R1.L = SIGNBITS R2.L;
R7.L = SIGNBITS R2.L;
R3.L = SIGNBITS R2.L;
R4.L = SIGNBITS R2.L;
R5.L = SIGNBITS R2.L;
R6.L = SIGNBITS R2.L;
R2.L = SIGNBITS R2.L;
CHECKREG r0, 0x00000001;
CHECKREG r1, 0x00000001;
CHECKREG r2, 0x00000001;
CHECKREG r3, 0x00000001;
CHECKREG r4, 0x00000001;
CHECKREG r5, 0x00000001;
CHECKREG r6, 0x00000001;
CHECKREG r7, 0x00000001;

imm32 r0, 0x00009001;
imm32 r1, 0x0000a001;
imm32 r2, 0x0000b002;
imm32 r3, 0x00000e10;
imm32 r4, 0x0000c004;
imm32 r5, 0x0000d005;
imm32 r6, 0x0000e006;
imm32 r7, 0x0000f007;
R0.L = SIGNBITS R3.L;
R1.L = SIGNBITS R3.L;
R2.L = SIGNBITS R3.L;
R7.L = SIGNBITS R3.L;
R4.L = SIGNBITS R3.L;
R5.L = SIGNBITS R3.L;
R6.L = SIGNBITS R3.L;
R3.L = SIGNBITS R3.L;
CHECKREG r0, 0x00000003;
CHECKREG r1, 0x00000003;
CHECKREG r2, 0x00000003;
CHECKREG r3, 0x00000003;
CHECKREG r4, 0x00000003;
CHECKREG r5, 0x00000003;
CHECKREG r6, 0x00000003;
CHECKREG r7, 0x00000003;

imm32 r0, 0x00000000;
imm32 r1, 0x00010000;
imm32 r2, 0x00020000;
imm32 r3, 0x00030000;
imm32 r4, 0x0000f000;
imm32 r5, 0x00050000;
imm32 r6, 0x00060000;
imm32 r7, 0x00070000;
R0.L = SIGNBITS R4.L;
R1.L = SIGNBITS R4.L;
R2.L = SIGNBITS R4.L;
R3.L = SIGNBITS R4.L;
R7.L = SIGNBITS R4.L;
R5.L = SIGNBITS R4.L;
R6.L = SIGNBITS R4.L;
R4.L = SIGNBITS R4.L;
CHECKREG r0, 0x00000003;
CHECKREG r1, 0x00010003;
CHECKREG r2, 0x00020003;
CHECKREG r3, 0x00030003;
CHECKREG r4, 0x00000003;
CHECKREG r5, 0x00050003;
CHECKREG r6, 0x00060003;
CHECKREG r7, 0x00070003;

imm32 r0, 0x90010000;
imm32 r1, 0x00010001;
imm32 r2, 0x90020000;
imm32 r3, 0x90030000;
imm32 r4, 0x90040000;
imm32 r5, 0x9008f000;
imm32 r6, 0x90060000;
imm32 r7, 0x90070000;
R0.L = SIGNBITS R5.L;
R1.L = SIGNBITS R5.L;
R2.L = SIGNBITS R5.L;
R3.L = SIGNBITS R5.L;
R4.L = SIGNBITS R5.L;
R7.L = SIGNBITS R5.L;
R6.L = SIGNBITS R5.L;
R5.L = SIGNBITS R5.L;
CHECKREG r0, 0x90010003;
CHECKREG r1, 0x00010003;
CHECKREG r2, 0x90020003;
CHECKREG r3, 0x90030003;
CHECKREG r4, 0x90040003;
CHECKREG r5, 0x90080003;
CHECKREG r6, 0x90060003;
CHECKREG r7, 0x90070003;

imm32 r1, 0xa0010000;
imm32 r2, 0xa002000f;
imm32 r3, 0xa0030000;
imm32 r4, 0xa0040000;
imm32 r5, 0xa0050000;
imm32 r6, 0xa000fc00;
imm32 r7, 0xa0070000;
R0.L = SIGNBITS R6.L;
R1.L = SIGNBITS R6.L;
R2.L = SIGNBITS R6.L;
R3.L = SIGNBITS R6.L;
R4.L = SIGNBITS R6.L;
R5.L = SIGNBITS R6.L;
R7.L = SIGNBITS R6.L;
R6.L = SIGNBITS R6.L;
CHECKREG r0, 0x90010005;
CHECKREG r1, 0xA0010005;
CHECKREG r2, 0xA0020005;
CHECKREG r3, 0xA0030005;
CHECKREG r4, 0xA0040005;
CHECKREG r5, 0xA0050005;
CHECKREG r6, 0xA0000005;
CHECKREG r7, 0xA0070005;

imm32 r0, 0xc0010001;
imm32 r1, 0xc0010001;
imm32 r2, 0xc0020002;
imm32 r3, 0xc0030010;
imm32 r4, 0xc0040004;
imm32 r5, 0xc0050005;
imm32 r6, 0xc0060006;
imm32 r7, 0xc007e007;
R0.L = SIGNBITS R7.L;
R1.L = SIGNBITS R7.L;
R2.L = SIGNBITS R7.L;
R3.L = SIGNBITS R7.L;
R4.L = SIGNBITS R7.L;
R5.L = SIGNBITS R7.L;
R6.L = SIGNBITS R7.L;
R7.L = SIGNBITS R7.L;
CHECKREG r0, 0xC0010002;
CHECKREG r1, 0xC0010002;
CHECKREG r2, 0xC0020002;
CHECKREG r3, 0xC0030002;
CHECKREG r4, 0xC0040002;
CHECKREG r5, 0xC0050002;
CHECKREG r6, 0xC0060002;
CHECKREG r7, 0xC0070002;

pass
