//Original:/testcases/core/c_dsp32alu_rl_m/c_dsp32alu_rl_m.dsp
// Spec Reference: dsp32alu dreg (half)
# mach: bfin

.include "testutils.inc"
	start




imm32 r0, 0x55678911;
imm32 r1, 0x2759ab1d;
imm32 r2, 0x34455515;
imm32 r3, 0x46665717;
imm32 r4, 0x5678891b;
imm32 r5, 0x6789a51d;
imm32 r6, 0x74445515;
imm32 r7, 0x86667777;
R0.L = R0.L - R0.L (NS);
R1.L = R0.L - R1.H (NS);
R2.L = R0.H - R2.L (NS);
R3.L = R0.H - R3.H (NS);
R4.L = R0.L - R4.L (NS);
R5.L = R0.L - R5.H (NS);
R6.L = R0.H - R6.L (NS);
R7.L = R0.H - R7.H (NS);
CHECKREG r4, 0x567876E5;
CHECKREG r5, 0x67899877;
CHECKREG r6, 0x74440052;
CHECKREG r7, 0x8666CF01;
CHECKREG r4, 0x567876E5;
CHECKREG r5, 0x67899877;
CHECKREG r6, 0x74440052;
CHECKREG r7, 0x8666CF01;

imm32 r0, 0x44678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0x344d5515;
imm32 r3, 0x4666d717;
imm32 r4, 0x5678891b;
imm32 r5, 0x6789cc1d;
imm32 r6, 0x74445c15;
imm32 r7, 0x86667c77;
R0.L = R1.L - R0.L (NS);
R1.L = R1.L - R1.H (NS);
R2.L = R1.H - R2.L (NS);
R3.L = R1.H - R3.H (NS);
R4.L = R1.L - R4.L (NS);
R5.L = R1.L - R5.H (NS);
R6.L = R1.H - R6.L (NS);
R7.L = R1.H - R7.H (NS);
CHECKREG r4, 0x5678FA79;
CHECKREG r5, 0x67891C0B;
CHECKREG r6, 0x7444CB74;
CHECKREG r7, 0x8666A123;
CHECKREG r4, 0x5678FA79;
CHECKREG r5, 0x67891C0B;
CHECKREG r6, 0x7444CB74;
CHECKREG r7, 0x8666A123;

imm32 r0, 0xcc678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0x34c45515;
imm32 r3, 0x466c7717;
imm32 r4, 0x5678c91b;
imm32 r5, 0x6789ac1d;
imm32 r6, 0x74445515;
imm32 r7, 0x866677c7;
R0.L = R2.L - R0.L (NS);
R1.L = R2.L - R1.H (NS);
R2.L = R2.H - R2.L (NS);
R3.L = R2.H - R3.H (NS);
R4.L = R2.L - R4.L (NS);
R5.L = R2.L - R5.H (NS);
R6.L = R2.H - R6.L (NS);
R7.L = R2.H - R7.H (NS);
CHECKREG r4, 0x56781694;
CHECKREG r5, 0x67897826;
CHECKREG r6, 0x7444DFAF;
CHECKREG r7, 0x8666AE5E;
CHECKREG r4, 0x56781694;
CHECKREG r5, 0x67897826;
CHECKREG r6, 0x7444DFAF;
CHECKREG r7, 0x8666AE5E;

imm32 r0, 0x15678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0x34445515;
imm32 r3, 0x46667717;
imm32 r4, 0x5678891b;
imm32 r5, 0x6789ab1d;
imm32 r6, 0x74445515;
imm32 r7, 0x86667777;
R0.L = R3.L - R0.L (NS);
R1.L = R3.L - R1.H (NS);
R2.L = R3.H - R2.L (NS);
R3.L = R3.H - R3.H (NS);
R4.L = R3.L - R4.L (NS);
R5.L = R3.L - R5.H (NS);
R6.L = R3.H - R6.L (NS);
R7.L = R3.H - R7.H (NS);
CHECKREG r4, 0x567876E5;
CHECKREG r5, 0x67899877;
CHECKREG r6, 0x7444F151;
CHECKREG r7, 0x8666C000;
CHECKREG r4, 0x567876E5;
CHECKREG r5, 0x67899877;
CHECKREG r6, 0x7444F151;
CHECKREG r7, 0x8666C000;

imm32 r0, 0xe5678911;
imm32 r1, 0x2e89ab1d;
imm32 r2, 0x34e45515;
imm32 r3, 0x466e7717;
imm32 r4, 0x5678e91b;
imm32 r5, 0x6789ae1d;
imm32 r6, 0x744455e5;
imm32 r7, 0x8666777e;
R0.L = R4.L - R0.L (NS);
R1.L = R4.L - R1.H (NS);
R2.L = R4.H - R2.L (NS);
R3.L = R4.H - R3.H (NS);
R4.L = R4.L - R4.L (NS);
R5.L = R4.L - R5.H (NS);
R6.L = R4.H - R6.L (NS);
R7.L = R4.H - R7.H (NS);
CHECKREG r4, 0x56780000;
CHECKREG r5, 0x67899877;
CHECKREG r6, 0x74440093;
CHECKREG r7, 0x8666D012;
CHECKREG r4, 0x56780000;
CHECKREG r5, 0x67899877;
CHECKREG r6, 0x74440093;
CHECKREG r7, 0x8666D012;

imm32 r0, 0xdd678911;
imm32 r1, 0xd789ab1d;
imm32 r2, 0x3d445515;
imm32 r3, 0x46d67717;
imm32 r4, 0x567d891b;
imm32 r5, 0x6789db1d;
imm32 r6, 0x74445d15;
imm32 r7, 0x866677d7;
R0.L = R5.L - R0.L (NS);
R1.L = R5.L - R1.H (NS);
R2.L = R5.H - R2.L (NS);
R3.L = R5.H - R3.H (NS);
R4.L = R5.L - R4.L (NS);
R5.L = R5.L - R5.H (NS);
R6.L = R5.H - R6.L (NS);
R7.L = R5.H - R7.H (NS);
CHECKREG r4, 0x567D5202;
CHECKREG r5, 0x67897394;
CHECKREG r6, 0x74440A74;
CHECKREG r7, 0x8666E123;
CHECKREG r4, 0x567D5202;
CHECKREG r5, 0x67897394;
CHECKREG r6, 0x74440A74;
CHECKREG r7, 0x8666E123;

imm32 r0, 0x85678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0x38445515;
imm32 r3, 0x46667717;
imm32 r4, 0x568a891b;
imm32 r5, 0x67a9ab1d;
imm32 r6, 0x744a5515;
imm32 r7, 0x8666aa77;
R0.L = R6.L - R0.L (NS);
R1.L = R6.L - R1.H (NS);
R2.L = R6.H - R2.L (NS);
R3.L = R6.H - R3.H (NS);
R4.L = R6.L - R4.L (NS);
R5.L = R6.L - R5.H (NS);
R6.L = R6.H - R6.L (NS);
R7.L = R6.H - R7.H (NS);
CHECKREG r4, 0x568ACBFA;
CHECKREG r5, 0x67A9ED6C;
CHECKREG r6, 0x744A1F35;
CHECKREG r7, 0x8666EDE4;
CHECKREG r4, 0x568ACBFA;
CHECKREG r5, 0x67A9ED6C;
CHECKREG r6, 0x744A1F35;
CHECKREG r7, 0x8666EDE4;

imm32 r0, 0x35678911;
imm32 r1, 0x2389ab1d;
imm32 r2, 0x34845515;
imm32 r3, 0x466a7717;
imm32 r4, 0x5678a91b;
imm32 r5, 0x6789ab1d;
imm32 r6, 0x74445b15;
imm32 r7, 0x866677b7;
R0.L = R7.L - R0.L (NS);
R1.L = R7.L - R1.H (NS);
R2.L = R7.H - R2.L (NS);
R3.L = R7.H - R3.H (NS);
R4.L = R7.L - R4.L (NS);
R5.L = R7.L - R5.H (NS);
R6.L = R7.H - R6.L (NS);
R7.L = R7.H - R7.H (NS);
CHECKREG r4, 0x5678CE9C;
CHECKREG r5, 0x6789102E;
CHECKREG r6, 0x74442B51;
CHECKREG r7, 0x86660000;
CHECKREG r4, 0x5678CE9C;
CHECKREG r5, 0x6789102E;
CHECKREG r6, 0x74442B51;
CHECKREG r7, 0x86660000;

imm32 r0, 0x15678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0x34445515;
imm32 r3, 0x46667717;
imm32 r4, 0x5678891b;
imm32 r5, 0x6789ab1d;
imm32 r6, 0x74445515;
imm32 r7, 0x86667777;
R6.L = R2.L - R3.L (S);
R1.L = R4.L - R5.H (S);
R5.L = R7.H - R2.L (S);
R3.L = R0.H - R0.H (S);
R0.L = R3.L - R4.L (S);
R2.L = R5.L - R7.H (S);
R7.L = R6.H - R7.L (S);
R4.L = R1.H - R6.H (S);
CHECKREG r4, 0x5678B345;
CHECKREG r5, 0x67898000;
CHECKREG r6, 0x7444DDFE;
CHECKREG r7, 0x8666FCCD;
CHECKREG r4, 0x5678B345;
CHECKREG r5, 0x67898000;
CHECKREG r6, 0x7444DDFE;
CHECKREG r7, 0x8666FCCD;

imm32 r0, 0x1d678911;
imm32 r1, 0x27d9ab1d;
imm32 r2, 0x34445515;
imm32 r3, 0x466d7717;
imm32 r4, 0x5678891b;
imm32 r5, 0x6789dd1d;
imm32 r6, 0x74445515;
imm32 r7, 0x866677d7;
R3.L = R4.L - R0.L (S);
R1.L = R6.L - R3.H (S);
R4.L = R3.H - R2.L (S);
R6.L = R7.H - R1.H (S);
R2.L = R5.L - R4.L (S);
R7.L = R2.L - R7.H (S);
R0.L = R1.H - R6.L (S);
R5.L = R0.H - R5.H (S);
CHECKREG r4, 0x5678F158;
CHECKREG r5, 0x6789B5DE;
CHECKREG r6, 0x74448000;
CHECKREG r7, 0x8666655F;
CHECKREG r4, 0x5678F158;
CHECKREG r5, 0x6789B5DE;
CHECKREG r6, 0x74448000;
CHECKREG r7, 0x8666655F;



pass
