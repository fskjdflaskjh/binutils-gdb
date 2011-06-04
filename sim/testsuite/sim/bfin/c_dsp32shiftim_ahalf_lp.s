//Original:/testcases/core/c_dsp32shiftim_ahalf_lp/c_dsp32shiftim_ahalf_lp.dsp
// Spec Reference: dspshiftimm dreg_lo(hi) = ashift (dreg_lo(hi) by imm5)
# mach: bfin

.include "testutils.inc"
	start

// Ashift : positive data, count (+)=left (half reg)
// d_lo = ashift (d_lo BY d_lo)
// RLx by RLx
imm32 r0, 0x01010100;
imm32 r1, 0x01020101;
imm32 r2, 0x01030102;
imm32 r3, 0x01040103;
imm32 r4, 0x01050104;
imm32 r5, 0x01060105;
imm32 r6, 0x01070106;
imm32 r7, 0x01080107;
R0.L = R0.L << 0;
R1.L = R1.L << 1;
R2.L = R2.L << 2;
R3.L = R3.L << 3;
R4.L = R4.L << 4;
R5.L = R5.L << 5;
R6.L = R6.L << 6;
R7.L = R7.L << 7;
CHECKREG r0, 0x01010100;
CHECKREG r1, 0x01020202;
CHECKREG r2, 0x01030408;
CHECKREG r3, 0x01040818;
CHECKREG r4, 0x01051040;
CHECKREG r5, 0x010620A0;
CHECKREG r6, 0x01074180;
CHECKREG r7, 0x01088380;

imm32 r0, 0x00090201;
imm32 r1, 0x00100201;
imm32 r2, 0x00110202;
imm32 r3, 0x00120203;
imm32 r4, 0x00130204;
imm32 r5, 0x00140205;
imm32 r6, 0x00150206;
imm32 r7, 0x00160207;
R7.L = R0.L << 8;
R6.L = R1.L << 9;
R5.L = R2.L << 10;
R4.L = R3.L << 11;
R3.L = R4.L << 12;
R2.L = R5.L << 13;
R1.L = R6.L << 14;
R0.L = R7.L << 15;
CHECKREG r1, 0x00100000;
CHECKREG r0, 0x00090000;
CHECKREG r2, 0x00110000;
CHECKREG r3, 0x00120000;
CHECKREG r4, 0x00131800;
CHECKREG r5, 0x00140800;
CHECKREG r6, 0x00150200;
CHECKREG r7, 0x00160100;


imm32 r0, 0x00170401;
imm32 r1, 0x00180401;
imm32 r2, 0x0019040f;
imm32 r3, 0x00200403;
imm32 r4, 0x00210404;
imm32 r5, 0x00220405;
imm32 r6, 0x00230406;
imm32 r7, 0x00244407;
R6.L = R0.L << 15;
R5.L = R1.L << 15;
R4.L = R2.L << 15;
R3.L = R3.L << 15;
R2.L = R4.L << 15;
R1.L = R5.L << 15;
R0.L = R6.L << 15;
R7.L = R7.L << 15;
CHECKREG r0, 0x00170000;
CHECKREG r1, 0x00180000;
CHECKREG r2, 0x00190000;
CHECKREG r3, 0x00208000;
CHECKREG r4, 0x00218000;
CHECKREG r5, 0x00228000;
CHECKREG r6, 0x00238000;
CHECKREG r7, 0x00248000;

imm32 r0, 0x00005001;
imm32 r1, 0x00005001;
imm32 r2, 0x00005002;
imm32 r3, 0x00005010;
imm32 r4, 0x00005004;
imm32 r5, 0x00005005;
imm32 r6, 0x00000506;
imm32 r7, 0x00000507;
R5.L = R0.L << 13;
R6.L = R1.L << 13;
R7.L = R2.L << 13;
R0.L = R3.L << 13;
R1.L = R4.L << 13;
R2.L = R5.L << 13;
R3.L = R6.L << 13;
R4.L = R7.L << 13;
CHECKREG r0, 0x00000000;
CHECKREG r1, 0x00008000;
CHECKREG r2, 0x00000000;
CHECKREG r3, 0x00000000;
CHECKREG r4, 0x00000000;
CHECKREG r5, 0x00002000;
CHECKREG r6, 0x00002000;
CHECKREG r7, 0x00004000;

// RHx by RLx
imm32 r0, 0x00006010;
imm32 r1, 0x00016020;
imm32 r2, 0x00026030;
imm32 r3, 0x00036040;
imm32 r4, 0x00046050;
imm32 r5, 0x00056060;
imm32 r6, 0x00066070;
imm32 r7, 0x00076080;
R0.L = R0.H << 10;
R1.L = R1.H << 10;
R2.L = R2.H << 10;
R3.L = R3.H << 10;
R4.L = R4.H << 10;
R5.L = R5.H << 10;
R6.L = R6.H << 10;
R7.L = R7.H << 10;
CHECKREG r0, 0x00000000;
CHECKREG r1, 0x00010400;
CHECKREG r2, 0x00020800;
CHECKREG r3, 0x00030C00;
CHECKREG r4, 0x00041000;
CHECKREG r5, 0x00051400;
CHECKREG r6, 0x00061800;
CHECKREG r7, 0x00071C00;

imm32 r0, 0x00010090;
imm32 r1, 0x00010111;
imm32 r2, 0x00020120;
imm32 r3, 0x00030130;
imm32 r4, 0x00040140;
imm32 r5, 0x00050150;
imm32 r6, 0x00060160;
imm32 r7, 0x00070170;
R1.L = R0.H << 1;
R2.L = R1.H << 1;
R3.L = R2.H << 1;
R4.L = R3.H << 1;
R5.L = R4.H << 1;
R6.L = R5.H << 1;
R7.L = R6.H << 1;
R0.L = R7.H << 1;
CHECKREG r1, 0x00010002;
CHECKREG r2, 0x00020002;
CHECKREG r3, 0x00030004;
CHECKREG r4, 0x00040006;
CHECKREG r5, 0x00050008;
CHECKREG r6, 0x0006000A;
CHECKREG r7, 0x0007000C;
CHECKREG r0, 0x0001000E;


imm32 r0, 0x0a010000;
imm32 r1, 0x0b010000;
imm32 r2, 0x0c02000f;
imm32 r3, 0x0d030000;
imm32 r4, 0x0e040000;
imm32 r5, 0x0f050000;
imm32 r6, 0x01060000;
imm32 r7, 0x02070000;
R2.L = R0.H << 12;
R3.L = R1.H << 12;
R4.L = R2.H << 12;
R5.L = R3.H << 12;
R6.L = R4.H << 12;
R7.L = R5.H << 12;
R0.L = R6.H << 12;
R1.L = R7.H << 12;
CHECKREG r0, 0x0A016000;
CHECKREG r1, 0x0B017000;
CHECKREG r2, 0x0C021000;
CHECKREG r3, 0x0D031000;
CHECKREG r4, 0x0E042000;
CHECKREG r5, 0x0F053000;
CHECKREG r6, 0x01064000;
CHECKREG r7, 0x02075000;

imm32 r0, 0x01010001;
imm32 r1, 0x02010001;
imm32 r2, 0x03020002;
imm32 r3, 0x04030010;
imm32 r4, 0x05040004;
imm32 r5, 0x06050005;
imm32 r6, 0x07060006;
imm32 r7, 0x08070007;
R3.L = R0.H << 13;
R4.L = R1.H << 13;
R5.L = R2.H << 13;
R6.L = R3.H << 13;
R7.L = R4.H << 13;
R0.L = R5.H << 13;
R1.L = R6.H << 13;
R2.L = R7.H << 13;
CHECKREG r0, 0x0101A000;
CHECKREG r1, 0x0201C000;
CHECKREG r2, 0x0302E000;
CHECKREG r3, 0x04032000;
CHECKREG r4, 0x05042000;
CHECKREG r5, 0x06054000;
CHECKREG r6, 0x07066000;
CHECKREG r7, 0x08078000;

// RLx by RLx
imm32 r0, 0xa0000400;
imm32 r1, 0xbb000401;
imm32 r2, 0xc0000402;
imm32 r3, 0xd0000403;
imm32 r4, 0xe0000404;
imm32 r5, 0xf0000405;
imm32 r6, 0x10000406;
imm32 r7, 0x20000407;
R0.H = R0.L << 14;
R1.H = R1.L << 14;
R2.H = R2.L << 14;
R3.H = R3.L << 14;
R4.H = R4.L << 14;
R5.H = R5.L << 14;
R6.H = R6.L << 14;
R7.H = R7.L << 14;
CHECKREG r0, 0x00000400;
CHECKREG r1, 0x40000401;
CHECKREG r2, 0x80000402;
CHECKREG r3, 0xC0000403;
CHECKREG r4, 0x00000404;
CHECKREG r5, 0x40000405;
CHECKREG r6, 0x80000406;
CHECKREG r7, 0xC0000407;

imm32 r0, 0x0a000001;
imm32 r1, 0x0b000001;
imm32 r2, 0x0cd00002;
imm32 r3, 0x0d000003;
imm32 r4, 0x0e000004;
imm32 r5, 0x0f000005;
imm32 r6, 0x03000006;
imm32 r7, 0x04000007;
R1.H = R0.L << 15;
R2.H = R1.L << 15;
R3.H = R2.L << 15;
R4.H = R3.L << 15;
R5.H = R4.L << 15;
R6.H = R5.L << 15;
R7.H = R6.L << 15;
R0.H = R7.L << 15;
CHECKREG r1, 0x80000001;
CHECKREG r2, 0x80000002;
CHECKREG r3, 0x00000003;
CHECKREG r4, 0x80000004;
CHECKREG r5, 0x00000005;
CHECKREG r6, 0x80000006;
CHECKREG r7, 0x00000007;
CHECKREG r0, 0x80000001;


imm32 r0, 0x10000001;
imm32 r1, 0x02000001;
imm32 r2, 0x0300000f;
imm32 r3, 0x04000003;
imm32 r4, 0x05000004;
imm32 r5, 0x06000005;
imm32 r6, 0x07000006;
imm32 r7, 0x00800007;
R2.H = R0.L << 2;
R3.H = R1.L << 2;
R4.H = R2.L << 2;
R5.H = R3.L << 2;
R6.H = R4.L << 2;
R7.H = R5.L << 2;
R0.H = R6.L << 2;
R1.H = R7.L << 2;
CHECKREG r0, 0x00180001;
CHECKREG r1, 0x001C0001;
CHECKREG r2, 0x0004000F;
CHECKREG r3, 0x00040003;
CHECKREG r4, 0x003C0004;
CHECKREG r5, 0x000C0005;
CHECKREG r6, 0x00100006;
CHECKREG r7, 0x00140007;

imm32 r0, 0x00000801;
imm32 r1, 0x00000801;
imm32 r2, 0x00000802;
imm32 r3, 0x00000810;
imm32 r4, 0x00000804;
imm32 r5, 0x00000805;
imm32 r6, 0x00000806;
imm32 r7, 0x00000807;
R3.H = R0.L << 3;
R4.H = R1.L << 3;
R5.H = R2.L << 3;
R6.H = R3.L << 3;
R7.H = R4.L << 3;
R0.H = R5.L << 3;
R1.H = R6.L << 3;
R2.H = R7.L << 3;
CHECKREG r0, 0x40280801;
CHECKREG r1, 0x40300801;
CHECKREG r2, 0x40380802;
CHECKREG r3, 0x40080810;
CHECKREG r4, 0x40080804;
CHECKREG r5, 0x40100805;
CHECKREG r6, 0x40800806;
CHECKREG r7, 0x40200807;

// RHx by RLx
imm32 r0, 0x00000400;
imm32 r1, 0x00010500;
imm32 r2, 0x00020060;
imm32 r3, 0x00030070;
imm32 r4, 0x00040800;
imm32 r5, 0x00050090;
imm32 r6, 0x00060d00;
imm32 r7, 0x00070a00;
R7.H = R0.H << 10;
R6.H = R1.H << 10;
R5.H = R2.H << 10;
R4.H = R3.H << 10;
R3.H = R4.H << 10;
R2.H = R5.H << 10;
R1.H = R6.H << 10;
R0.H = R7.H << 10;
CHECKREG r1, 0x00000500;
CHECKREG r2, 0x00000060;
CHECKREG r3, 0x00000070;
CHECKREG r4, 0x0C000800;
CHECKREG r5, 0x08000090;
CHECKREG r6, 0x04000D00;
CHECKREG r7, 0x00000A00;
CHECKREG r0, 0x00000400;

imm32 r0, 0x00010000;
imm32 r1, 0x00010001;
imm32 r2, 0x00020001;
imm32 r3, 0x00030002;
imm32 r4, 0x00040003;
imm32 r5, 0x00050004;
imm32 r6, 0x00060005;
imm32 r7, 0x00070006;
R6.H = R0.H << 11;
R5.H = R1.H << 11;
R4.H = R2.H << 11;
R3.H = R3.H << 11;
R2.H = R4.H << 11;
R1.H = R5.H << 11;
R7.H = R6.H << 11;
R0.H = R7.H << 11;
CHECKREG r1, 0x00000001;
CHECKREG r2, 0x00000001;
CHECKREG r3, 0x18000002;
CHECKREG r4, 0x10000003;
CHECKREG r5, 0x08000004;
CHECKREG r6, 0x08000005;
CHECKREG r7, 0x00000006;
CHECKREG r0, 0x00000000;


imm32 r0, 0x00010060;
imm32 r1, 0x00010060;
imm32 r2, 0x0002006f;
imm32 r3, 0x00030060;
imm32 r4, 0x00040060;
imm32 r5, 0x00050060;
imm32 r6, 0x00060060;
imm32 r7, 0x00070060;
R4.H = R0.H << 12;
R5.H = R1.H << 12;
R6.H = R2.H << 12;
R7.H = R3.H << 12;
R0.H = R4.H << 12;
R1.H = R5.H << 12;
R2.H = R6.H << 12;
R3.H = R7.H << 12;
CHECKREG r0, 0x00000060;
CHECKREG r1, 0x00000060;
CHECKREG r2, 0x0000006F;
CHECKREG r3, 0x00000060;
CHECKREG r4, 0x10000060;
CHECKREG r5, 0x10000060;
CHECKREG r6, 0x20000060;
CHECKREG r7, 0x30000060;

imm32 r0, 0x12010070;
imm32 r1, 0x23010070;
imm32 r2, 0x34020070;
imm32 r3, 0x45030070;
imm32 r4, 0x56040070;
imm32 r5, 0x67050070;
imm32 r6, 0x78060070;
imm32 r7, 0x09070070;
R4.H = R0.H << 3;
R5.H = R1.H << 3;
R6.H = R2.H << 3;
R7.H = R3.H << 3;
R0.H = R4.H << 3;
R1.H = R5.H << 3;
R2.H = R6.H << 3;
R3.H = R7.H << 3;
CHECKREG r0, 0x80400070;
CHECKREG r1, 0xC0400070;
CHECKREG r2, 0x00800070;
CHECKREG r3, 0x40C00070;
CHECKREG r4, 0x90080070;
CHECKREG r5, 0x18080070;
CHECKREG r6, 0xA0100070;
CHECKREG r7, 0x28180070;

pass
