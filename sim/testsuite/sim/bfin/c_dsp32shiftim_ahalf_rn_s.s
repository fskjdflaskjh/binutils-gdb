//Original:/testcases/core/c_dsp32shiftim_ahalf_rn_s/c_dsp32shiftim_ahalf_rn_s.dsp
// Spec Reference: dsp32shift ashift
# mach: bfin

.include "testutils.inc"
	start



imm32 r0, 0x00000000;
R0.L = -1;
imm32 r1, 0x00008001;
imm32 r2, 0x00008002;
imm32 r3, 0x00008003;
imm32 r4, 0x00008004;
imm32 r5, 0x00008005;
imm32 r6, 0x00008006;
imm32 r7, 0x00008007;
R0.L = R0.L >>> 10;
R1.L = R1.L >>> 10;
R2.L = R2.L >>> 10;
R3.L = R3.L >>> 10;
R4.L = R4.L >>> 10;
R5.L = R5.L >>> 10;
R6.L = R6.L >>> 10;
R7.L = R7.L >>> 10;
CHECKREG r0, 0x0000FFFF;
CHECKREG r1, 0x0000FFE0;
CHECKREG r2, 0x0000FFE0;
CHECKREG r3, 0x0000FFE0;
CHECKREG r4, 0x0000FFE0;
CHECKREG r5, 0x0000FFE0;
CHECKREG r6, 0x0000FFE0;
CHECKREG r7, 0x0000FFE0;

imm32 r0, 0x02008020;
imm32 r0, 0x02008021;
imm32 r2, 0x02008022;
imm32 r3, 0x02008023;
imm32 r4, 0x02008024;
imm32 r5, 0x02008025;
imm32 r6, 0x02008026;
imm32 r7, 0x02008027;
R0.L = R0.L >>> 11;
R1.L = R1.L >>> 11;
R2.L = R2.L >>> 11;
R3.L = R3.L >>> 11;
R4.L = R4.L >>> 11;
R5.L = R5.L >>> 11;
R6.L = R6.L >>> 11;
R7.L = R7.L >>> 11;
CHECKREG r0, 0x0200FFF0;
CHECKREG r1, 0x0000FFFF;
CHECKREG r2, 0x0200FFF0;
CHECKREG r3, 0x0200FFF0;
CHECKREG r4, 0x0200FFF0;
CHECKREG r5, 0x0200FFF0;
CHECKREG r6, 0x0200FFF0;
CHECKREG r7, 0x0200FFF0;


imm32 r0, 0x00308001;
imm32 r1, 0x00308001;
R2.L = -15;
imm32 r3, 0x00308003;
imm32 r4, 0x00308004;
imm32 r5, 0x00308005;
imm32 r6, 0x00308006;
imm32 r7, 0x00308007;
R0.L = R0.L >>> 12;
R1.L = R1.L >>> 12;
R2.L = R2.L >>> 12;
R3.L = R3.L >>> 12;
R4.L = R4.L >>> 12;
R5.L = R5.L >>> 12;
R6.L = R6.L >>> 12;
R7.L = R7.L >>> 12;
CHECKREG r0, 0x0030FFF8;
CHECKREG r1, 0x0030FFF8;
CHECKREG r2, 0x0200FFFF;
CHECKREG r3, 0x0030FFF8;
CHECKREG r4, 0x0030FFF8;
CHECKREG r5, 0x0030FFF8;
CHECKREG r6, 0x0030FFF8;
CHECKREG r7, 0x0030FFF8;

imm32 r0, 0x00008401;
imm32 r1, 0x00008401;
imm32 r2, 0x00008402;
R3.L = -16;
imm32 r4, 0x00008404;
imm32 r5, 0x00008405;
imm32 r6, 0x00008406;
imm32 r7, 0x00008407;
R0.L = R0.L >>> 3;
R1.L = R1.L >>> 3;
R2.L = R2.L >>> 3;
R3.L = R3.L >>> 3;
R4.L = R4.L >>> 3;
R5.L = R5.L >>> 3;
R6.L = R6.L >>> 3;
R7.L = R7.L >>> 3;
CHECKREG r0, 0x0000F080;
CHECKREG r1, 0x0000F080;
CHECKREG r2, 0x0000F080;
CHECKREG r3, 0x0030FFFE;
CHECKREG r4, 0x0000F080;
CHECKREG r5, 0x0000F080;
CHECKREG r6, 0x0000F080;
CHECKREG r7, 0x0000F080;

// d_lo = ashift (d_hi BY d_lo)
// RHx by RLx
imm32 r0, 0x05000500;
imm32 r1, 0x85010500;
imm32 r2, 0x85020500;
imm32 r3, 0x85030500;
imm32 r4, 0x85040500;
imm32 r5, 0x85050500;
imm32 r6, 0x85060500;
imm32 r7, 0x85070500;
R0.L = R0.H >>> 10;
R1.L = R1.H >>> 10;
R2.L = R2.H >>> 10;
R3.L = R3.H >>> 10;
R4.L = R4.H >>> 10;
R5.L = R5.H >>> 10;
R6.L = R6.H >>> 10;
R7.L = R7.H >>> 10;
CHECKREG r0, 0x05000001;
CHECKREG r1, 0x8501FFE1;
CHECKREG r2, 0x8502FFE1;
CHECKREG r3, 0x8503FFE1;
CHECKREG r4, 0x8504FFE1;
CHECKREG r5, 0x8505FFE1;
CHECKREG r6, 0x8506FFE1;
CHECKREG r7, 0x8507FFE1;

imm32 r0, 0x80610000;
R1.L = -1;
imm32 r2, 0x80620000;
imm32 r3, 0x80630000;
imm32 r4, 0x80640000;
imm32 r5, 0x80650000;
imm32 r6, 0x80660000;
imm32 r7, 0x80670000;
R0.L = R0.H >>> 11;
R1.L = R1.H >>> 11;
R2.L = R2.H >>> 11;
R3.L = R3.H >>> 11;
R4.L = R4.H >>> 11;
R5.L = R5.H >>> 11;
R6.L = R6.H >>> 11;
R7.L = R7.H >>> 11;
CHECKREG r0, 0x8061FFF0;
CHECKREG r1, 0x8501FFF0;
CHECKREG r2, 0x8062FFF0;
CHECKREG r3, 0x8063FFF0;
CHECKREG r4, 0x8064FFF0;
CHECKREG r5, 0x8065FFF0;
CHECKREG r6, 0x8066FFF0;
CHECKREG r7, 0x8067FFF0;


imm32 r0, 0xa0010070;
imm32 r1, 0xa0010070;
R2.L = -15;
imm32 r3, 0xa0030070;
imm32 r4, 0xa0040070;
imm32 r5, 0xa0050070;
imm32 r6, 0xa0060070;
imm32 r7, 0xa0070070;
R0.L = R0.H >>> 12;
R1.L = R1.H >>> 12;
R2.L = R2.H >>> 12;
R3.L = R3.H >>> 12;
R4.L = R4.H >>> 12;
R5.L = R5.H >>> 12;
R6.L = R6.H >>> 12;
R7.L = R7.H >>> 12;
CHECKREG r0, 0xA001FFFA;
CHECKREG r1, 0xA001FFFA;
CHECKREG r2, 0x8062FFF8;
CHECKREG r3, 0xA003FFFA;
CHECKREG r4, 0xA004FFFA;
CHECKREG r5, 0xA005FFFA;
CHECKREG r6, 0xA006FFFA;
CHECKREG r7, 0xA007FFFA;

imm32 r0, 0xb8010001;
imm32 r1, 0xb8010001;
imm32 r2, 0xb8020002;
R3.L = -16;
imm32 r4, 0xb8040004;
imm32 r5, 0xb8050005;
imm32 r6, 0xb8060006;
imm32 r7, 0xb8070007;
R0.L = R0.H >>> 13;
R1.L = R1.H >>> 13;
R2.L = R2.H >>> 13;
R3.L = R3.H >>> 13;
R4.L = R4.H >>> 13;
R5.L = R5.H >>> 13;
R6.L = R6.H >>> 13;
R7.L = R7.H >>> 13;
CHECKREG r0, 0xB801FFFD;
CHECKREG r1, 0xB801FFFD;
CHECKREG r2, 0xB802FFFD;
CHECKREG r3, 0xA003FFFD;
CHECKREG r4, 0xB804FFFD;
CHECKREG r5, 0xB805FFFD;
CHECKREG r6, 0xB806FFFD;
CHECKREG r7, 0xB807FFFD;

// d_hi = ashft (d_lo BY d_lo)
// RLx by RLx
imm32 r0, 0x00009001;
imm32 r1, 0x00009001;
imm32 r2, 0x00009002;
imm32 r3, 0x00009003;
imm32 r4, 0x00009000;
imm32 r5, 0x00009005;
imm32 r6, 0x00009006;
imm32 r7, 0x00009007;
R0.H = R0.L >>> 14;
R1.H = R1.L >>> 14;
R2.H = R2.L >>> 14;
R3.H = R3.L >>> 14;
R4.H = R4.L >>> 14;
R5.H = R5.L >>> 14;
R6.H = R6.L >>> 14;
R7.H = R7.L >>> 14;
CHECKREG r0, 0xFFFE9001;
CHECKREG r1, 0xFFFE9001;
CHECKREG r2, 0xFFFE9002;
CHECKREG r3, 0xFFFE9003;
CHECKREG r4, 0xFFFE9000;
CHECKREG r5, 0xFFFE9005;
CHECKREG r6, 0xFFFE9006;
CHECKREG r7, 0xFFFE9007;

imm32 r0, 0xa0008001;
imm32 r1, 0xa0008001;
imm32 r2, 0xa0008002;
imm32 r3, 0xa0008003;
imm32 r4, 0xa0008004;
R5.L = -1;
imm32 r6, 0xa0008006;
imm32 r7, 0xa0008007;
R0.H = R0.L >>> 5;
R1.H = R1.L >>> 5;
R2.H = R2.L >>> 5;
R3.H = R3.L >>> 5;
R4.H = R4.L >>> 5;
R5.H = R5.L >>> 5;
R6.H = R6.L >>> 5;
R7.H = R7.L >>> 5;
CHECKREG r0, 0xFC008001;
CHECKREG r1, 0xFC008001;
CHECKREG r2, 0xFC008002;
CHECKREG r3, 0xFC008003;
CHECKREG r4, 0xFC008004;
CHECKREG r5, 0xFFFFFFFF;
CHECKREG r6, 0xFC008006;
CHECKREG r7, 0xFC008007;


imm32 r0, 0x00009b01;
imm32 r1, 0x00009b01;
imm32 r2, 0x00009b02;
imm32 r3, 0x00009b03;
imm32 r4, 0x00009b04;
imm32 r5, 0x00009b05;
R6.L = -15;
imm32 r7, 0x00009007;
R0.H = R0.L >>> 6;
R1.H = R1.L >>> 6;
R2.H = R2.L >>> 6;
R3.H = R3.L >>> 6;
R4.H = R4.L >>> 6;
R5.H = R5.L >>> 6;
R6.H = R6.L >>> 6;
R7.H = R7.L >>> 6;
CHECKREG r0, 0xFE6C9B01;
CHECKREG r1, 0xFE6C9B01;
CHECKREG r2, 0xFE6C9B02;
CHECKREG r3, 0xFE6C9B03;
CHECKREG r4, 0xFE6C9B04;
CHECKREG r5, 0xFE6C9B05;
CHECKREG r6, 0xFFFFFFF1;
CHECKREG r7, 0xFE409007;

imm32 r0, 0x0000a0c1;
imm32 r1, 0x0000a0c1;
imm32 r2, 0x0000a0c2;
imm32 r3, 0x0000a0c3;
imm32 r4, 0x0000a0c4;
imm32 r5, 0x0000a0c5;
imm32 r6, 0x0000a0c6;
R7.L = -16;
R0.H = R0.L >>> 7;
R1.H = R1.L >>> 7;
R2.H = R2.L >>> 7;
R3.H = R3.L >>> 7;
R4.H = R4.L >>> 7;
R5.H = R5.L >>> 7;
R6.H = R6.L >>> 7;
R7.H = R7.L >>> 7;
CHECKREG r0, 0xFF41A0C1;
CHECKREG r1, 0xFF41A0C1;
CHECKREG r2, 0xFF41A0C2;
CHECKREG r3, 0xFF41A0C3;
CHECKREG r4, 0xFF41A0C4;
CHECKREG r5, 0xFF41A0C5;
CHECKREG r6, 0xFF41A0C6;
CHECKREG r7, 0xFFFFFFF0;

imm32 r0, 0x80010d00;
imm32 r1, 0x80010d00;
imm32 r2, 0x80020d00;
imm32 r3, 0x80030d00;
R4.L = -1;
imm32 r5, 0x80050d00;
imm32 r6, 0x80060d00;
imm32 r7, 0x80070d00;
R0.H = R0.H >>> 14;
R1.H = R1.H >>> 14;
R2.H = R2.H >>> 14;
R3.H = R3.H >>> 14;
R4.H = R4.H >>> 14;
R5.H = R5.H >>> 14;
R6.H = R6.H >>> 14;
R7.H = R7.H >>> 14;
CHECKREG r0, 0xFFFE0D00;
CHECKREG r1, 0xFFFE0D00;
CHECKREG r2, 0xFFFE0D00;
CHECKREG r3, 0xFFFE0D00;
CHECKREG r4, 0xFFFFFFFF;
CHECKREG r5, 0xFFFE0D00;
CHECKREG r6, 0xFFFE0D00;
CHECKREG r7, 0xFFFE0D00;

imm32 r0, 0x8d010000;
imm32 r1, 0x8d010000;
imm32 r2, 0x8d020000;
imm32 r3, 0x8d030000;
imm32 r4, 0x8d040000;
R5.L = -1;
imm32 r6, 0x8d060000;
imm32 r7, 0x8d070000;
R0.H = R0.H >>> 15;
R1.H = R1.H >>> 15;
R2.H = R2.H >>> 15;
R3.H = R3.H >>> 15;
R4.H = R4.H >>> 15;
R5.H = R5.H >>> 15;
R6.H = R6.H >>> 15;
R7.H = R7.H >>> 15;
CHECKREG r0, 0xFFFF0000;
CHECKREG r1, 0xFFFF0000;
CHECKREG r2, 0xFFFF0000;
CHECKREG r3, 0xFFFF0000;
CHECKREG r4, 0xFFFF0000;
CHECKREG r5, 0xFFFFFFFF;
CHECKREG r6, 0xFFFF0000;
CHECKREG r7, 0xFFFF0000;


imm32 r0, 0xde010000;
imm32 r1, 0xde010000;
imm32 r2, 0xde020000;
imm32 r3, 0xde030000;
imm32 r4, 0xde040000;
imm32 r5, 0xde050000;
R6.L = -15;
imm32 r7, 0xd0070000;
R0.L = R0.H >>> 10;
R1.L = R1.H >>> 10;
R2.L = R2.H >>> 10;
R3.L = R3.H >>> 10;
R4.L = R4.H >>> 10;
R5.L = R5.H >>> 10;
R6.L = R6.H >>> 10;
R7.L = R7.H >>> 10;
CHECKREG r0, 0xDE01FFF7;
CHECKREG r1, 0xDE01FFF7;
CHECKREG r2, 0xDE02FFF7;
CHECKREG r3, 0xDE03FFF7;
CHECKREG r4, 0xDE04FFF7;
CHECKREG r5, 0xDE05FFF7;
CHECKREG r6, 0xFFFFFFFF;
CHECKREG r7, 0xD007FFF4;

imm32 r0, 0x9f010c00;
imm32 r1, 0xaf010c00;
imm32 r2, 0xbf020c00;
imm32 r3, 0xcf030c00;
imm32 r4, 0xdf040c00;
imm32 r5, 0xef050c00;
imm32 r6, 0xff060c00;
R7.L = -16;
R0.H = R0.H >>> 5;
R1.H = R1.H >>> 5;
R2.H = R2.H >>> 5;
R3.H = R3.H >>> 5;
R4.H = R4.H >>> 5;
R5.H = R5.H >>> 5;
R6.H = R6.H >>> 5;
R7.H = R7.H >>> 5;
CHECKREG r0, 0xFCF80C00;
CHECKREG r1, 0xFD780C00;
CHECKREG r2, 0xFDF80C00;
CHECKREG r3, 0xFE780C00;
CHECKREG r4, 0xFEF80C00;
CHECKREG r5, 0xFF780C00;
CHECKREG r6, 0xFFF80C00;
CHECKREG r7, 0xFE80FFF0;
pass
