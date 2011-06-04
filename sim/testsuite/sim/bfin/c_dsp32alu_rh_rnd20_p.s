//Original:/testcases/core/c_dsp32alu_rh_rnd20_p/c_dsp32alu_rh_rnd20_p.dsp
// Spec Reference: dsp32alu dreg (half)
# mach: bfin

.include "testutils.inc"
	start

imm32 r0, 0xa5678911;
imm32 r1, 0x2a89ab1d;
imm32 r2, 0x34a45515;
imm32 r3, 0x46a67717;
imm32 r4, 0x5678891b;
imm32 r5, 0x678aab1d;
imm32 r6, 0x7444a515;
imm32 r7, 0x86667a77;
R0.H = R0 + R0 (RND20);
R1.H = R0 + R1 (RND20);
R2.H = R0 + R2 (RND20);
R3.H = R0 + R3 (RND20);
R4.H = R0 + R4 (RND20);
R5.H = R0 + R5 (RND20);
R6.H = R0 + R6 (RND20);
R7.H = R0 + R7 (RND20);
CHECKREG r0, 0xF4AD8911;
CHECKREG r1, 0x01F3AB1D;
CHECKREG r2, 0x02955515;
CHECKREG r3, 0x03B57717;
CHECKREG r4, 0x04B2891B;
CHECKREG r5, 0x05C4AB1D;
CHECKREG r6, 0x068FA515;
CHECKREG r7, 0xF7B17A77;

imm32 r0, 0xa5678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0xb4445515;
imm32 r3, 0x46667717;
imm32 r4, 0x5b78891b;
imm32 r5, 0x67bbab1d;
imm32 r6, 0x7444b515;
imm32 r7, 0x86667b77;
R0.H = R1 + R0 (RND20);
R1.H = R1 + R1 (RND20);
R2.H = R1 + R2 (RND20);
R3.H = R1 + R3 (RND20);
R4.H = R1 + R4 (RND20);
R5.H = R1 + R5 (RND20);
R6.H = R1 + R6 (RND20);
R7.H = R1 + R7 (RND20);
CHECKREG r0, 0xFCCF8911;
CHECKREG r1, 0x04F1AB1D;
CHECKREG r2, 0xFB935515;
CHECKREG r3, 0x04B67717;
CHECKREG r4, 0x0607891B;
CHECKREG r5, 0x06CBAB1D;
CHECKREG r6, 0x0793B515;
CHECKREG r7, 0xF8B67B77;

imm32 r0, 0xa5678911;
imm32 r1, 0x2a89ab1d;
imm32 r2, 0x3a445515;
imm32 r3, 0x46a67717;
imm32 r4, 0x567a891b;
imm32 r5, 0x6789ab1d;
imm32 r6, 0x74445a15;
imm32 r7, 0x866677a7;
R0.H = R2 + R0 (RND20);
R1.H = R2 + R1 (RND20);
R2.H = R2 + R2 (RND20);
R3.H = R2 + R3 (RND20);
R4.H = R2 + R4 (RND20);
R5.H = R2 + R5 (RND20);
R6.H = R2 + R6 (RND20);
R7.H = R2 + R7 (RND20);
CHECKREG r0, 0xFDFB8911;
CHECKREG r1, 0x064DAB1D;
CHECKREG r2, 0x07495515;
CHECKREG r3, 0x04DF7717;
CHECKREG r4, 0x05DC891B;
CHECKREG r5, 0x06EDAB1D;
CHECKREG r6, 0x07B95A15;
CHECKREG r7, 0xF8DB77A7;

imm32 r0, 0xb5678911;
imm32 r1, 0xb789ab1d;
imm32 r2, 0x3d445515;
imm32 r3, 0x46d67717;
imm32 r4, 0x5678891b;
imm32 r5, 0x678ddb1d;
imm32 r6, 0x74445d15;
imm32 r7, 0x866677d7;
R0.H = R3 + R0 (RND20);
R1.H = R3 + R1 (RND20);
R2.H = R3 + R2 (RND20);
R3.H = R3 + R3 (RND20);
R4.H = R3 + R4 (RND20);
R5.H = R3 + R5 (RND20);
R6.H = R3 + R6 (RND20);
R7.H = R3 + R7 (RND20);
CHECKREG r0, 0xFFC48911;
CHECKREG r1, 0xFFE6AB1D;
CHECKREG r2, 0x08425515;
CHECKREG r3, 0x08DB7717;
CHECKREG r4, 0x05F5891B;
CHECKREG r5, 0x0707DB1D;
CHECKREG r6, 0x07D25D15;
CHECKREG r7, 0xF8F477D7;

imm32 r0, 0xd5678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0xd4445515;
imm32 r3, 0xd6667717;
imm32 r4, 0x5d78891b;
imm32 r5, 0x67d9ab1d;
imm32 r6, 0x744d5515;
imm32 r7, 0x8666dd77;
R0.H = R4 + R0 (RND20);
R1.H = R4 + R1 (RND20);
R2.H = R4 + R2 (RND20);
R3.H = R4 + R3 (RND20);
R4.H = R4 + R4 (RND20);
R5.H = R4 + R5 (RND20);
R6.H = R4 + R6 (RND20);
R7.H = R4 + R7 (RND20);
CHECKREG r0, 0x032E8911;
CHECKREG r1, 0x0850AB1D;
CHECKREG r2, 0x031C5515;
CHECKREG r3, 0x033E7717;
CHECKREG r4, 0x0BAF891B;
CHECKREG r5, 0x0739AB1D;
CHECKREG r6, 0x08005515;
CHECKREG r7, 0xF921DD77;

imm32 r0, 0xe5678911;
imm32 r1, 0x2e89ab1d;
imm32 r2, 0x34d45515;
imm32 r3, 0x46667717;
imm32 r4, 0x567d891b;
imm32 r5, 0x6789db1d;
imm32 r6, 0x74445d15;
imm32 r7, 0x866677d7;
R0.H = R5 + R0 (RND20);
R1.H = R5 + R1 (RND20);
R2.H = R5 + R2 (RND20);
R3.H = R5 + R3 (RND20);
R4.H = R5 + R4 (RND20);
R5.H = R5 + R5 (RND20);
R6.H = R5 + R6 (RND20);
R7.H = R5 + R7 (RND20);
CHECKREG r0, 0x04CF8911;
CHECKREG r1, 0x0961AB1D;
CHECKREG r2, 0x09C65515;
CHECKREG r3, 0x0ADF7717;
CHECKREG r4, 0x0BE0891B;
CHECKREG r5, 0x0CF1DB1D;
CHECKREG r6, 0x08135D15;
CHECKREG r7, 0xF93677D7;

imm32 r0, 0xa5678911;
imm32 r1, 0x2a89ab1d;
imm32 r2, 0x34a45515;
imm32 r3, 0x46a67717;
imm32 r4, 0x56a8891b;
imm32 r5, 0x678aab1d;
imm32 r6, 0x7444a515;
imm32 r7, 0x86667a77;
R0.H = R6 + R0 (RND20);
R1.H = R6 + R1 (RND20);
R2.H = R6 + R2 (RND20);
R3.H = R6 + R3 (RND20);
R4.H = R6 + R4 (RND20);
R5.H = R6 + R5 (RND20);
R6.H = R6 + R6 (RND20);
R7.H = R6 + R7 (RND20);
CHECKREG r0, 0x019B8911;
CHECKREG r1, 0x09EDAB1D;
CHECKREG r2, 0x0A8F5515;
CHECKREG r3, 0x0BAF7717;
CHECKREG r4, 0x0CAF891B;
CHECKREG r5, 0x0DBDAB1D;
CHECKREG r6, 0x0E89A515;
CHECKREG r7, 0xF94F7A77;

imm32 r0, 0x15678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0x34445515;
imm32 r3, 0x46667717;
imm32 r4, 0x5678891b;
imm32 r5, 0x6789ab1d;
imm32 r6, 0x74445515;
imm32 r7, 0x86667777;
R0.H = R7 + R0 (RND20);
R1.H = R7 + R1 (RND20);
R2.H = R7 + R2 (RND20);
R3.H = R7 + R3 (RND20);
R4.H = R7 + R4 (RND20);
R5.H = R7 + R5 (RND20);
R6.H = R7 + R6 (RND20);
R7.H = R7 + R7 (RND20);
CHECKREG r0, 0xF9BD8911;
CHECKREG r1, 0xFADFAB1D;
CHECKREG r2, 0xFBAB5515;
CHECKREG r3, 0xFCCD7717;
CHECKREG r4, 0xFDCE891B;
CHECKREG r5, 0xFEDFAB1D;
CHECKREG r6, 0xFFAB5515;
CHECKREG r7, 0xF0CD7777;

imm32 r0, 0xe5678911;
imm32 r1, 0xe789ab1d;
imm32 r2, 0xe4445515;
imm32 r3, 0x4ee67717;
imm32 r4, 0x567e891b;
imm32 r5, 0x6789ab1d;
imm32 r6, 0x7444e515;
imm32 r7, 0x86667e77;
R6.H = R2 + R3 (RND20);
R1.H = R4 + R5 (RND20);
R5.H = R7 + R2 (RND20);
R3.H = R0 + R0 (RND20);
R0.H = R3 + R4 (RND20);
R2.H = R5 + R7 (RND20);
R7.H = R6 + R7 (RND20);
R4.H = R1 + R6 (RND20);
CHECKREG r0, 0x05338911;
CHECKREG r1, 0x0BE1AB1D;
CHECKREG r2, 0xF7D15515;
CHECKREG r3, 0xFCAD7717;
CHECKREG r4, 0x00F1891B;
CHECKREG r5, 0xF6ABAB1D;
CHECKREG r6, 0x0333E515;
CHECKREG r7, 0xF89A7E77;

imm32 r0, 0xe5678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0x3d445515;
imm32 r3, 0x46d67717;
imm32 r4, 0x567d891b;
imm32 r5, 0x6789db1d;
imm32 r6, 0x7444d515;
imm32 r7, 0x86667d77;
R3.H = R4 + R0 (RND20);
R1.H = R6 + R3 (RND20);
R4.H = R3 + R2 (RND20);
R6.H = R7 + R1 (RND20);
R2.H = R5 + R4 (RND20);
R7.H = R2 + R7 (RND20);
R0.H = R1 + R6 (RND20);
R5.H = R0 + R5 (RND20);
CHECKREG r0, 0x00068911;
CHECKREG r1, 0x0780AB1D;
CHECKREG r2, 0x06BA5515;
CHECKREG r3, 0x03BE7717;
CHECKREG r4, 0x0410891B;
CHECKREG r5, 0x0679DB1D;
CHECKREG r6, 0xF8DED515;
CHECKREG r7, 0xF8D27D77;

pass
