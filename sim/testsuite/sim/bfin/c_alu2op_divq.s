//Original:/testcases/core/c_alu2op_divq/c_alu2op_divq.dsp
// Spec Reference: alu2op divide q
# mach: bfin

.include "testutils.inc"
	start



imm32 r0, 0x00000000;
imm32 r1, 0x12345678;
imm32 r2, 0x23456789;
imm32 r3, 0x3456789a;
imm32 r4, 0x856789ab;
imm32 r5, 0x96789abc;
imm32 r6, 0xa789abcd;
imm32 r7, 0xb89abcde;
R0.L = 1;
DIVQ ( R1 , R0 );
DIVQ ( R2 , R0 );
DIVQ ( R3 , R0 );
DIVQ ( R4 , R0 );
DIVQ ( R5 , R0 );
DIVQ ( R6 , R0 );
DIVQ ( R7 , R0 );
DIVQ ( R4 , R0 );
DIVQ ( R0 , R0 );
CHECKREG r1, 0x2466ACF1;
CHECKREG r2, 0x4688CF13;
CHECKREG r3, 0x68AAF135;
CHECKREG r4, 0x159C26AD;
CHECKREG r5, 0x2CF33578;
CHECKREG r6, 0x4F15579A;
CHECKREG r7, 0x713779BC;
CHECKREG r0, 0xFFFE0002;

imm32 r0, 0x01230002;
imm32 r1, 0x00000000;
imm32 r2, 0x93456789;
imm32 r3, 0xa456789a;
imm32 r4, 0xb56789ab;
imm32 r5, 0xc6789abc;
imm32 r6, 0xd789abcd;
imm32 r7, 0xe89abcde;
R1.L = -1;
DIVQ ( R0 , R1 );
DIVQ ( R2 , R1 );
DIVQ ( R3 , R1 );
DIVQ ( R4 , R1 );
DIVQ ( R5 , R1 );
DIVQ ( R6 , R1 );
DIVQ ( R7 , R1 );
DIVQ ( R1 , R1 );
CHECKREG r0, 0x02440004;
CHECKREG r1, 0x0003FFFE;
CHECKREG r2, 0x2688CF13;
CHECKREG r3, 0x48AEF135;
CHECKREG r4, 0x6AD11357;
CHECKREG r5, 0x8CF33579;
CHECKREG r6, 0xAF15579B;
CHECKREG r7, 0xD13779BD;

imm32 r0, 0x51230002;
imm32 r1, 0x12345678;
imm32 r2, 0x00000000;
imm32 r3, 0x3456789a;
imm32 r4, 0x956789ab;
imm32 r5, 0x86789abc;
imm32 r6, 0x6789abcd;
imm32 r7, 0x789abcde;
R2.L = 31;
DIVQ ( R0 , R2 );
DIVQ ( R1 , R2 );
DIVQ ( R3 , R2 );
DIVQ ( R4 , R2 );
DIVQ ( R5 , R2 );
DIVQ ( R6 , R2 );
DIVQ ( R7 , R2 );
DIVQ ( R2 , R2 );
CHECKREG r0, 0xA2840005;
CHECKREG r1, 0x242AACF1;
CHECKREG r2, 0xFFC2003E;
CHECKREG r3, 0x686EF135;
CHECKREG r4, 0x2A911356;
CHECKREG r5, 0x0D2F3578;
CHECKREG r6, 0xCF51579B;
CHECKREG r7, 0xF0F779BD;

imm32 r0, 0x01230002;
imm32 r1, 0x82345678;
imm32 r2, 0x93456789;
imm32 r3, 0x00000000;
imm32 r4, 0xb56789ab;
imm32 r5, 0xc6789abc;
imm32 r6, 0xd789abcd;
imm32 r7, 0xe89abcde;
R3.L = -31;
DIVQ ( R0 , R3 );
DIVQ ( R1 , R3 );
DIVQ ( R2 , R3 );
DIVQ ( R4 , R3 );
DIVQ ( R5 , R3 );
DIVQ ( R6 , R3 );
DIVQ ( R7 , R3 );
DIVQ ( R3 , R3 );
CHECKREG r0, 0x02080004;
CHECKREG r1, 0x042AACF1;
CHECKREG r2, 0x26C8CF13;
CHECKREG r3, 0x003FFFC2;
CHECKREG r4, 0x6B0D1357;
CHECKREG r5, 0x8D2F3579;
CHECKREG r6, 0xAF51579B;
CHECKREG r7, 0xD17379BD;

imm32 r0, 0x00000001;
imm32 r1, 0x12345678;
imm32 r2, 0x23456789;
imm32 r3, 0x3456789a;
imm32 r4, 0x00000000;
imm32 r5, 0x96789abc;
imm32 r6, 0xa789abcd;
imm32 r7, 0xb89abcde;
R4.L = 15;
DIVQ ( R1 , R4 );
DIVQ ( R2 , R4 );
DIVQ ( R3 , R4 );
DIVQ ( R0 , R4 );
DIVQ ( R5 , R4 );
DIVQ ( R6 , R4 );
DIVQ ( R7 , R4 );
DIVQ ( R4 , R4 );
CHECKREG r0, 0xFFE20002;
CHECKREG r1, 0x2486ACF1;
CHECKREG r2, 0x466CCF13;
CHECKREG r3, 0x688EF135;
CHECKREG r4, 0x001E001F;
CHECKREG r5, 0x2D0F3578;
CHECKREG r6, 0x4F31579A;
CHECKREG r7, 0x715379BC;

imm32 r0, 0x01230002;
imm32 r1, 0x00000000;
imm32 r2, 0x93456789;
imm32 r3, 0xa456789a;
imm32 r4, 0xb56789ab;
imm32 r5, 0x00000000;
imm32 r6, 0xd789abcd;
imm32 r7, 0xe89abcde;
R5.L = -15;
DIVQ ( R0 , R5 );
DIVQ ( R1 , R5 );
DIVQ ( R2 , R5 );
DIVQ ( R3 , R5 );
DIVQ ( R4 , R5 );
DIVQ ( R6 , R5 );
DIVQ ( R7 , R5 );
DIVQ ( R5 , R5 );
CHECKREG r0, 0x02640004;
CHECKREG r1, 0xFFE20001;
CHECKREG r2, 0x26A8CF13;
CHECKREG r3, 0x48CAF135;
CHECKREG r4, 0x6AED1357;
CHECKREG r5, 0x001FFFE2;
CHECKREG r6, 0xAF31579B;
CHECKREG r7, 0xD15379BD;

imm32 r0, 0x51230002;
imm32 r1, 0x12345678;
imm32 r2, 0xb1256790;
imm32 r3, 0x3456789a;
imm32 r4, 0x956789ab;
imm32 r5, 0x86789abc;
imm32 r6, 0x00000000;
imm32 r7, 0x789abcde;
R6.L = 24;
DIVQ ( R0 , R6 );
DIVQ ( R1 , R6 );
DIVQ ( R2 , R6 );
DIVQ ( R3 , R6 );
DIVQ ( R4 , R6 );
DIVQ ( R5 , R6 );
DIVQ ( R7 , R6 );
DIVQ ( R6 , R6 );
CHECKREG r0, 0xA2760005;
CHECKREG r1, 0x2438ACF1;
CHECKREG r2, 0x621ACF20;
CHECKREG r3, 0x68DCF135;
CHECKREG r4, 0x2A9F1356;
CHECKREG r5, 0x0D213578;
CHECKREG r6, 0xFFD00030;
CHECKREG r7, 0xF16579BD;

imm32 r0, 0x01230002;
imm32 r1, 0x82345678;
imm32 r2, 0x93456789;
imm32 r3, 0xa456789a;
imm32 r4, 0xb56789ab;
imm32 r5, 0xc6789abc;
imm32 r6, 0xd789abcd;
imm32 r7, 0x00000000;
R7.L = -24;
DIVQ ( R0 , R7 );
DIVQ ( R1 , R7 );
DIVQ ( R2 , R7 );
DIVQ ( R3 , R7 );
DIVQ ( R4 , R7 );
DIVQ ( R5 , R7 );
DIVQ ( R6 , R7 );
DIVQ ( R7 , R7 );
CHECKREG r0, 0x02160004;
CHECKREG r1, 0x0438ACF1;
CHECKREG r2, 0x26BACF13;
CHECKREG r3, 0x48DCF135;
CHECKREG r4, 0x6AFF1357;
CHECKREG r5, 0x8D213579;
CHECKREG r6, 0xAF43579B;
CHECKREG r7, 0x0031FFD0;


pass
