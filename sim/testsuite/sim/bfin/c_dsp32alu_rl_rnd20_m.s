//Original:/testcases/core/c_dsp32alu_rl_rnd20_m/c_dsp32alu_rl_rnd20_m.dsp
// Spec Reference: dsp32alu dreg (half)
# mach: bfin

.include "testutils.inc"
	start

imm32 r0, 0x75678911;
imm32 r1, 0xa789ab1d;
imm32 r2, 0x34745515;
imm32 r3, 0x4b677717;
imm32 r4, 0x5678791b;
imm32 r5, 0xc789a71d;
imm32 r6, 0x74445515;
imm32 r7, 0x86667777;
R0.L = R0 - R0 (RND20);
R1.L = R0 - R1 (RND20);
R2.L = R0 - R2 (RND20);
R3.L = R0 - R3 (RND20);
R4.L = R0 - R4 (RND20);
R5.L = R0 - R5 (RND20);
R6.L = R0 - R6 (RND20);
R7.L = R0 - R7 (RND20);
CHECKREG r0, 0x75670000;
CHECKREG r1, 0xA7890CDE;
CHECKREG r2, 0x3474040F;
CHECKREG r3, 0x4B6702A0;
CHECKREG r4, 0x567801EF;
CHECKREG r5, 0xC7890ADE;
CHECKREG r6, 0x74440012;
CHECKREG r7, 0x86660EF0;

imm32 r0, 0xe5678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0x3e445515;
imm32 r3, 0x46667717;
imm32 r4, 0x56e8891b;
imm32 r5, 0x678eab1d;
imm32 r6, 0x74445515;
imm32 r7, 0x86e67e77;
R0.L = R1 - R0 (RND20);
CHECKREG r0, 0xE5670422;
R1.L = R1 - R1 (RND20);
CHECKREG r1, 0x27890000;
R2.L = R1 - R2 (RND20);
CHECKREG r2, 0x3E44FE94;
R3.L = R1 - R3 (RND20);
CHECKREG r3, 0x4666FE12;
R4.L = R1 - R4 (RND20);
R5.L = R1 - R5 (RND20);
R6.L = R1 - R6 (RND20);
R7.L = R1 - R7 (RND20);
CHECKREG r0, 0xE5670422;
CHECKREG r1, 0x27890000;
CHECKREG r2, 0x3E44FE94;
CHECKREG r3, 0x4666FE12;
CHECKREG r4, 0x56E8FD0A;
CHECKREG r5, 0x678EFC00;
CHECKREG r6, 0x7444FB34;
CHECKREG r7, 0x86E60A0A;

imm32 r0, 0xdd678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0x3d445515;
imm32 r3, 0x46667717;
imm32 r4, 0x56d8891b;
imm32 r5, 0x678dab1d;
imm32 r6, 0x7444d515;
imm32 r7, 0x86667d77;
R0.L = R2 - R0 (RND20);
R1.L = R2 - R1 (RND20);
R2.L = R2 - R2 (RND20);
R3.L = R2 - R3 (RND20);
R4.L = R2 - R4 (RND20);
R5.L = R2 - R5 (RND20);
R6.L = R2 - R6 (RND20);
R7.L = R2 - R7 (RND20);
CHECKREG r0, 0xDD6705FE;
CHECKREG r1, 0x2789015C;
CHECKREG r2, 0x3D440000;
CHECKREG r3, 0x4666FF6E;
CHECKREG r4, 0x56D8FE67;
CHECKREG r5, 0x678DFD5B;
CHECKREG r6, 0x7444FC90;
CHECKREG r7, 0x86660B6E;

imm32 r0, 0xa5678911;
imm32 r1, 0x2a89ab1d;
imm32 r2, 0x34445515;
imm32 r3, 0x46a67717;
imm32 r4, 0x567a891b;
imm32 r5, 0x6789ab1d;
imm32 r6, 0x7444c515;
imm32 r7, 0x86667c77;
R0.L = R3 - R0 (RND20);
R1.L = R3 - R1 (RND20);
R2.L = R3 - R2 (RND20);
R3.L = R3 - R3 (RND20);
R4.L = R3 - R4 (RND20);
R5.L = R3 - R5 (RND20);
R6.L = R3 - R6 (RND20);
R7.L = R3 - R7 (RND20);
CHECKREG r0, 0xA5670A14;
CHECKREG r1, 0x2A8901C2;
CHECKREG r2, 0x34440126;
CHECKREG r3, 0x46A60000;
CHECKREG r4, 0x567AFF03;
CHECKREG r5, 0x6789FDF2;
CHECKREG r6, 0x7444FD26;
CHECKREG r7, 0x86660C04;

imm32 r0, 0x15678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0x34445515;
imm32 r3, 0x46667717;
imm32 r4, 0x5678891b;
imm32 r5, 0x6789ab1d;
imm32 r6, 0x74445515;
imm32 r7, 0x86667777;
R0.L = R4 - R0 (RND20);
R1.L = R4 - R1 (RND20);
R2.L = R4 - R2 (RND20);
R3.L = R4 - R3 (RND20);
R4.L = R4 - R4 (RND20);
R5.L = R4 - R5 (RND20);
R6.L = R4 - R6 (RND20);
R7.L = R4 - R7 (RND20);
CHECKREG r0, 0x15670411;
CHECKREG r1, 0x278902EF;
CHECKREG r2, 0x34440223;
CHECKREG r3, 0x46660101;
CHECKREG r4, 0x56780000;
CHECKREG r5, 0x6789FEEF;
CHECKREG r6, 0x7444FE23;
CHECKREG r7, 0x86660D01;

imm32 r0, 0x95678911;
imm32 r1, 0x8789ab1d;
imm32 r2, 0x74445515;
imm32 r3, 0x4a667717;
imm32 r4, 0x56b8891b;
imm32 r5, 0x678dab1d;
imm32 r6, 0x7444e515;
imm32 r7, 0x86667d77;
R0.L = R5 - R0 (RND20);
R1.L = R5 - R1 (RND20);
R2.L = R5 - R2 (RND20);
R3.L = R5 - R3 (RND20);
R4.L = R5 - R4 (RND20);
R5.L = R5 - R5 (RND20);
R6.L = R5 - R6 (RND20);
R7.L = R5 - R7 (RND20);
CHECKREG r0, 0x95670D22;
CHECKREG r1, 0x87890E00;
CHECKREG r2, 0x7444FF35;
CHECKREG r3, 0x4A6601D2;
CHECKREG r4, 0x56B8010D;
CHECKREG r5, 0x678D0000;
CHECKREG r6, 0x7444FF35;
CHECKREG r7, 0x86660E12;

imm32 r0, 0x35678911;
imm32 r1, 0x2459ab1d;
imm32 r2, 0x34465515;
imm32 r3, 0xe6667717;
imm32 r4, 0x5d78891b;
imm32 r5, 0x67b9ab1d;
imm32 r6, 0x744a5515;
imm32 r7, 0x8666c777;
R0.L = R6 - R0 (RND20);
R1.L = R6 - R1 (RND20);
R2.L = R6 - R2 (RND20);
R3.L = R6 - R3 (RND20);
R4.L = R6 - R4 (RND20);
R5.L = R6 - R5 (RND20);
R6.L = R6 - R6 (RND20);
R7.L = R6 - R7 (RND20);
CHECKREG r0, 0x356703EE;
CHECKREG r1, 0x245904FF;
CHECKREG r2, 0x34460400;
CHECKREG r3, 0xE66608DE;
CHECKREG r4, 0x5D78016D;
CHECKREG r5, 0x67B900C9;
CHECKREG r6, 0x744A0000;
CHECKREG r7, 0x86660EDE;

imm32 r0, 0xa5678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0x3a445515;
imm32 r3, 0x4c667717;
imm32 r4, 0x56b8891b;
imm32 r5, 0x678dab1d;
imm32 r6, 0x74445515;
imm32 r7, 0x8666d777;
R0.L = R7 - R0 (RND20);
R1.L = R7 - R1 (RND20);
R2.L = R7 - R2 (RND20);
R3.L = R7 - R3 (RND20);
R4.L = R7 - R4 (RND20);
R5.L = R7 - R5 (RND20);
R6.L = R7 - R6 (RND20);
R7.L = R7 - R7 (RND20);
CHECKREG r0, 0xA567FE10;
CHECKREG r1, 0x2789F5EE;
CHECKREG r2, 0x3A44F4C2;
CHECKREG r3, 0x4C66F3A0;
CHECKREG r4, 0x56B8F2FB;
CHECKREG r5, 0x678DF1EE;
CHECKREG r6, 0x7444F122;
CHECKREG r7, 0x86660000;

imm32 r0, 0xabd78911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0xd4445515;
imm32 r3, 0x4e667717;
imm32 r4, 0x56f8891b;
imm32 r5, 0x678aab1d;
imm32 r6, 0x7444b515;
imm32 r7, 0x86667d77;
R6.L = R2 - R3 (RND20);
R1.L = R4 - R5 (RND20);
R5.L = R7 - R2 (RND20);
R3.L = R0 - R0 (RND20);
R0.L = R3 - R4 (RND20);
R2.L = R5 - R7 (RND20);
R7.L = R6 - R7 (RND20);
R4.L = R1 - R6 (RND20);
CHECKREG r0, 0xABD7FF77;
CHECKREG r1, 0x2789FEF7;
CHECKREG r2, 0xD4440E12;
CHECKREG r3, 0x4E660000;
CHECKREG r4, 0x56F8FB34;
CHECKREG r5, 0x678AFB22;
CHECKREG r6, 0x7444F85E;
CHECKREG r7, 0x86660EDE;

imm32 r0, 0x15678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0x34445515;
imm32 r3, 0x46667717;
imm32 r4, 0x5678891b;
imm32 r5, 0x6789ab1d;
imm32 r6, 0x74445515;
imm32 r7, 0x86667777;
R3.L = R4 - R0 (RND20);
R1.L = R6 - R3 (RND20);
R4.L = R3 - R2 (RND20);
R6.L = R7 - R1 (RND20);
R2.L = R5 - R4 (RND20);
R7.L = R2 - R7 (RND20);
R0.L = R1 - R6 (RND20);
R5.L = R0 - R5 (RND20);
CHECKREG r0, 0x1567FB34;
CHECKREG r1, 0x278902DE;
CHECKREG r2, 0x34440111;
CHECKREG r3, 0x46660411;
CHECKREG r4, 0x56780122;
CHECKREG r5, 0x6789FADE;
CHECKREG r6, 0x7444F5EE;
CHECKREG r7, 0x86660ADE;

pass
