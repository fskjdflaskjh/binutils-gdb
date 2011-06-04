//Original:/testcases/core/c_dsp32mult_pair_u/c_dsp32mult_pair_u.dsp
// Spec Reference: dsp32mult pair u
# mach: bfin

.include "testutils.inc"
	start

imm32 r0, 0x8b235625;
imm32 r1, 0x93ba5127;
imm32 r2, 0xa3446725;
imm32 r3, 0x00050027;
imm32 r4, 0xb0ab6d29;
imm32 r5, 0x10ace72b;
imm32 r6, 0xc00c008d;
imm32 r7, 0xd2467029;
R1 = R0.L * R0.L, R0 = R0.L * R0.L (FU);
R3 = R0.L * R1.L, R2 = R0.L * R1.H (FU);
R5 = R1.L * R0.L, R4 = R1.H * R0.L (FU);
R7 = R1.L * R1.L, R6 = R1.H * R1.H (FU);
CHECKREG r0, 0x1CFCE159;
CHECKREG r1, 0x1CFCE159;
CHECKREG r2, 0x19838F9C;
CHECKREG r3, 0xC65D90F1;
CHECKREG r4, 0x19838F9C;
CHECKREG r5, 0xC65D90F1;
CHECKREG r6, 0x03481810;
CHECKREG r7, 0xC65D90F1;

imm32 r0, 0x5b33a635;
imm32 r1, 0x6fbe5137;
imm32 r2, 0x1324b735;
imm32 r3, 0x9006d037;
imm32 r4, 0x80abcb39;
imm32 r5, 0xb0acef3b;
imm32 r6, 0xa00c00dd;
imm32 r7, 0x12469003;
R1 = R2.L * R2.L, R0 = R2.L * R2.L (FU);
R3 = R2.L * R3.L, R2 = R2.L * R3.H (FU);
R5 = R3.L * R2.L, R4 = R3.H * R2.L (FU);
R7 = R3.L * R3.L, R6 = R3.H * R3.H (FU);
CHECKREG r0, 0x831CD0F9;
CHECKREG r1, 0x831CD0F9;
CHECKREG r2, 0x67121B3E;
CHECKREG r3, 0x95026C63;
CHECKREG r4, 0x0FDB4C7C;
CHECKREG r5, 0x0B88B0FA;
CHECKREG r6, 0x56BB5404;
CHECKREG r7, 0x2DE3AE49;

imm32 r0, 0x1b235655;
imm32 r1, 0xc4ba5157;
imm32 r2, 0x63246755;
imm32 r3, 0x00060055;
imm32 r4, 0x90abc509;
imm32 r5, 0x10acef5b;
imm32 r6, 0xb00c005d;
imm32 r7, 0x1246705f;
R1 = R4.L * R4.L, R0 = R4.L * R4.L (FU);
R3 = R4.L * R5.L, R2 = R4.L * R5.H (FU);
R5 = R5.L * R4.L, R4 = R5.H * R4.L (FU);
R7 = R5.L * R5.L, R6 = R5.H * R5.H (FU);
CHECKREG r0, 0x97A6DA51;
CHECKREG r1, 0x97A6DA51;
CHECKREG r2, 0x0CD4F20C;
CHECKREG r3, 0xB8397133;
CHECKREG r4, 0x0CD4F20C;
CHECKREG r5, 0xB8397133;
CHECKREG r6, 0x8491FCB1;
CHECKREG r7, 0x320E1029;

imm32 r0, 0xab235666;
imm32 r1, 0xeaba5166;
imm32 r2, 0x13d48766;
imm32 r3, 0xf00b0066;
imm32 r4, 0x90ab9d69;
imm32 r5, 0x10ac5f6b;
imm32 r6, 0x800cb66d;
imm32 r7, 0x1246707f;
R1 = R6.L * R6.L, R0 = R6.L * R6.L (FU);
R3 = R6.L * R7.L, R2 = R6.L * R7.H (FU);
R5 = R7.L * R6.L, R4 = R7.H * R6.L (FU);
R7 = R7.L * R7.L, R6 = R7.H * R7.H (FU);
CHECKREG r0, 0x81FF2A69;
CHECKREG r1, 0x81FF2A69;
CHECKREG r2, 0x0D058BCE;
CHECKREG r3, 0x502A3013;
CHECKREG r4, 0x0D058BCE;
CHECKREG r5, 0x502A3013;
CHECKREG r6, 0x014DEB24;
CHECKREG r7, 0x316F5F01;

// mix order
imm32 r0, 0xab23a675;
imm32 r1, 0xcfba5127;
imm32 r2, 0x13246705;
imm32 r3, 0x00060007;
imm32 r4, 0x90abcd09;
imm32 r5, 0x10acdfdb;
imm32 r6, 0x000c000d;
imm32 r7, 0x1246f00f;
R1 = R3.L * R2.L (M), R0 = R3.L * R2.H (FU);
R3 = R1.L * R0.H, R2 = R1.H * R0.L (FU);
R5 = R7.H * R4.L, R4 = R7.H * R4.L (FU);
R7 = R5.L * R6.L (M), R6 = R5.H * R6.L (FU);
CHECKREG r0, 0x000085FC;
CHECKREG r1, 0x0002D123;
CHECKREG r2, 0x00010BF8;
CHECKREG r3, 0x00000000;
CHECKREG r4, 0x0EA2B276;
CHECKREG r5, 0x0EA2B276;
CHECKREG r6, 0x0000BE3A;
CHECKREG r7, 0xFFFC0FFE;

imm32 r0, 0x9b235a75;
imm32 r1, 0xc9ba5127;
imm32 r2, 0x13946905;
imm32 r3, 0x00090007;
imm32 r4, 0x90ab9d09;
imm32 r5, 0x10ace9db;
imm32 r6, 0x000c0d9d;
imm32 r7, 0x12467009;
R3 = R6.L * R5.L, R2 = R6.L * R5.H (FU);
R1 = R3.L * R0.H (M), R0 = R3.H * R0.L (FU);
R5 = R1.L * R4.L (M), R4 = R1.H * R4.L (FU);
R7 = R2.H * R7.L, R6 = R2.H * R7.L (FU);
CHECKREG r0, 0x0464B4BB;
CHECKREG r1, 0xB8ADBDCD;
CHECKREG r2, 0x00E2F57C;
CHECKREG r3, 0x0C6F8A4F;
CHECKREG r4, 0x71489715;
CHECKREG r5, 0xD7646535;
CHECKREG r6, 0x0062E7F2;
CHECKREG r7, 0x0062E7F2;

imm32 r0, 0x8b235675;
imm32 r1, 0xc8ba5127;
imm32 r2, 0x13846705;
imm32 r3, 0x00080007;
imm32 r4, 0x90ab8d09;
imm32 r5, 0x10ace8db;
imm32 r6, 0x000c008d;
imm32 r7, 0x12467008;
R3 = R6.H * R5.L, R2 = R6.L * R5.H (FU);
R7 = R2.L * R0.H (M), R6 = R2.H * R0.L (FU);
R5 = R1.L * R3.L (M), R4 = R1.H * R3.L (FU);
R1 = R2.H * R7.L, R0 = R2.L * R7.H (FU);
CHECKREG r0, 0x04A2FAE8;
CHECKREG r1, 0x00043554;
CHECKREG r2, 0x00092EBC;
CHECKREG r3, 0x000AEA44;
CHECKREG r4, 0xB7AF5568;
CHECKREG r5, 0x4A43345C;
CHECKREG r6, 0x00030A1D;
CHECKREG r7, 0x196677B4;

imm32 r0, 0xeb235675;
imm32 r1, 0xceba5127;
imm32 r2, 0x13e46705;
imm32 r3, 0x000e0007;
imm32 r4, 0x90abed09;
imm32 r5, 0x10aceedb;
imm32 r6, 0x000c00ed;
imm32 r7, 0x1246700e;
R1 = R1.H * R4.L, R0 = R1.H * R4.L (FU);
R3 = R2.L * R5.L, R2 = R2.L * R5.H (FU);
R5 = R3.H * R6.L, R4 = R3.L * R6.L (FU);
R7 = R4.L * R0.H, R6 = R4.H * R0.L (FU);
CHECKREG r0, 0xBF69768A;
CHECKREG r1, 0xBF69768A;
CHECKREG r2, 0x06B5875C;
CHECKREG r3, 0x601EC747;
CHECKREG r4, 0x00B87CBB;
CHECKREG r5, 0x0058FBC6;
CHECKREG r6, 0x00553330;
CHECKREG r7, 0x5D42ADB3;



pass
