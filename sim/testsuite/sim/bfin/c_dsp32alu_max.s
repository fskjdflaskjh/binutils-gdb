//Original:/testcases/core/c_dsp32alu_max/c_dsp32alu_max.dsp
// Spec Reference: dsp32alu dregs = max ( dregs, dregs)
# mach: bfin

.include "testutils.inc"
	start




imm32 r0, 0x85678911;
imm32 r1, 0x9789ab1d;
imm32 r2, 0xa4445b15;
imm32 r3, 0x46667717;
imm32 r4, 0xd567f91b;
imm32 r5, 0x6789ab1d;
imm32 r6, 0x74445515;
imm32 r7, 0x86667777;
R0 = MAX ( R0 , R0 );
R1 = MAX ( R0 , R1 );
R2 = MAX ( R0 , R2 );
R3 = MAX ( R0 , R3 );
R4 = MAX ( R0 , R4 );
R5 = MAX ( R0 , R5 );
R6 = MAX ( R0 , R6 );
R7 = MAX ( R0 , R7 );
CHECKREG r0, 0x85678911;
CHECKREG r1, 0x9789AB1D;
CHECKREG r2, 0xA4445B15;
CHECKREG r3, 0x46667717;
CHECKREG r4, 0xD567F91B;
CHECKREG r5, 0x6789AB1D;
CHECKREG r6, 0x74445515;
CHECKREG r7, 0x86667777;

imm32 r0, 0x9567892b;
imm32 r1, 0xa789ab2d;
imm32 r2, 0xb4445525;
imm32 r3, 0xc6667727;
imm32 r4, 0xd8889929;
imm32 r5, 0xeaaabb2b;
imm32 r6, 0xfcccdd2d;
imm32 r7, 0x0eeeffff;
R0 = MAX ( R1 , R0 );
R1 = MAX ( R1 , R1 );
R2 = MAX ( R1 , R2 );
R3 = MAX ( R1 , R3 );
R4 = MAX ( R1 , R4 );
R5 = MAX ( R1 , R5 );
R6 = MAX ( R1 , R6 );
R7 = MAX ( R1 , R7 );
CHECKREG r0, 0xA789AB2D;
CHECKREG r1, 0xA789AB2D;
CHECKREG r2, 0xB4445525;
CHECKREG r3, 0xC6667727;
CHECKREG r4, 0xD8889929;
CHECKREG r5, 0xEAAABB2B;
CHECKREG r6, 0xFCCCDD2D;
CHECKREG r7, 0x0EEEFFFF;

imm32 r0, 0x416789ab;
imm32 r1, 0x6289abcd;
imm32 r2, 0x43445555;
imm32 r3, 0x64667777;
imm32 r4, 0x456789ab;
imm32 r5, 0x6689abcd;
imm32 r6, 0x47445555;
imm32 r7, 0x68667777;
R0 = MAX ( R2 , R0 );
R1 = MAX ( R2 , R1 );
R2 = MAX ( R2 , R2 );
R3 = MAX ( R2 , R3 );
R4 = MAX ( R2 , R4 );
R5 = MAX ( R2 , R5 );
R6 = MAX ( R2 , R6 );
R7 = MAX ( R2 , R7 );
CHECKREG r0, 0x43445555;
CHECKREG r1, 0x6289ABCD;
CHECKREG r2, 0x43445555;
CHECKREG r3, 0x64667777;
CHECKREG r4, 0x456789AB;
CHECKREG r5, 0x6689ABCD;
CHECKREG r6, 0x47445555;
CHECKREG r7, 0x68667777;

imm32 r0, 0x9567892b;
imm32 r1, 0xa789ab2d;
imm32 r2, 0xb4445525;
imm32 r3, 0xc6667727;
imm32 r0, 0x9567892b;
imm32 r1, 0xa789ab2d;
imm32 r2, 0xb4445525;
imm32 r3, 0xc6667727;
R0 = MAX ( R3 , R0 );
R1 = MAX ( R3 , R1 );
R2 = MAX ( R3 , R2 );
R3 = MAX ( R3 , R3 );
R4 = MAX ( R3 , R4 );
R5 = MAX ( R3 , R5 );
R6 = MAX ( R3 , R6 );
R7 = MAX ( R3 , R7 );
CHECKREG r0, 0xC6667727;
CHECKREG r1, 0xC6667727;
CHECKREG r2, 0xC6667727;
CHECKREG r3, 0xC6667727;
CHECKREG r4, 0x456789AB;
CHECKREG r5, 0x6689ABCD;
CHECKREG r6, 0x47445555;
CHECKREG r7, 0x68667777;

imm32 r0, 0x5537891b;
imm32 r1, 0x6759ab2d;
imm32 r2, 0x74555535;
imm32 r3, 0x86665747;
imm32 r4, 0x88789565;
imm32 r5, 0xaa8abb5b;
imm32 r6, 0xcc9cdd85;
imm32 r7, 0xeeaeff9f;
R0 = MAX ( R4 , R0 );
R1 = MAX ( R4 , R1 );
R2 = MAX ( R4 , R2 );
R3 = MAX ( R4 , R3 );
R4 = MAX ( R4 , R4 );
R5 = MAX ( R4 , R5 );
R6 = MAX ( R4 , R6 );
R7 = MAX ( R4 , R7 );
CHECKREG r0, 0x5537891B;
CHECKREG r1, 0x6759AB2D;
CHECKREG r2, 0x74555535;
CHECKREG r3, 0x88789565;
CHECKREG r4, 0x88789565;
CHECKREG r5, 0xAA8ABB5B;
CHECKREG r6, 0xCC9CDD85;
CHECKREG r7, 0xEEAEFF9F;

imm32 r0, 0x556b89ab;
imm32 r1, 0x69764bcd;
imm32 r2, 0x79736564;
imm32 r3, 0x81278394;
imm32 r4, 0x98876439;
imm32 r5, 0xaaaa0bbb;
imm32 r6, 0xcccc1ddd;
imm32 r7, 0x12346fff;
R0 = MAX ( R5 , R0 );
R1 = MAX ( R5 , R1 );
R2 = MAX ( R5 , R2 );
R3 = MAX ( R5 , R3 );
R4 = MAX ( R5 , R4 );
R5 = MAX ( R5 , R5 );
R6 = MAX ( R5 , R6 );
R7 = MAX ( R5 , R7 );
CHECKREG r0, 0x556B89AB;
CHECKREG r1, 0x69764BCD;
CHECKREG r2, 0x79736564;
CHECKREG r3, 0xAAAA0BBB;
CHECKREG r4, 0xAAAA0BBB;
CHECKREG r5, 0xAAAA0BBB;
CHECKREG r6, 0xCCCC1DDD;
CHECKREG r7, 0x12346FFF;

imm32 r0, 0xe56739ab;
imm32 r1, 0xf7694bcd;
imm32 r2, 0xa3456755;
imm32 r3, 0x66666777;
imm32 r4, 0x42345699;
imm32 r5, 0x45678b6b;
imm32 r6, 0x043290d6;
imm32 r7, 0x1234567f;
R0 = MAX ( R6 , R0 );
R1 = MAX ( R6 , R1 );
R2 = MAX ( R6 , R2 );
R3 = MAX ( R6 , R3 );
R4 = MAX ( R6 , R4 );
R5 = MAX ( R6 , R5 );
R6 = MAX ( R6 , R6 );
R7 = MAX ( R6 , R7 );
CHECKREG r0, 0x043290D6;
CHECKREG r1, 0x043290D6;
CHECKREG r2, 0x043290D6;
CHECKREG r3, 0x66666777;
CHECKREG r4, 0x42345699;
CHECKREG r5, 0x45678B6B;
CHECKREG r6, 0x043290D6;
CHECKREG r7, 0x1234567F;

imm32 r0, 0x576789ab;
imm32 r1, 0xd779abcd;
imm32 r2, 0x23456755;
imm32 r3, 0x56789007;
imm32 r4, 0x789ab799;
imm32 r5, 0xaaaa0bbb;
imm32 r6, 0xf9ab1d7d;
imm32 r7, 0xabcd2ff7;
R0 = MAX ( R7 , R0 );
R1 = MAX ( R7 , R1 );
R2 = MAX ( R7 , R2 );
R3 = MAX ( R7 , R3 );
R4 = MAX ( R7 , R4 );
R5 = MAX ( R7 , R5 );
R6 = MAX ( R7 , R6 );
R7 = MAX ( R7 , R7 );
CHECKREG r0, 0x576789AB;
CHECKREG r1, 0xD779ABCD;
CHECKREG r2, 0x23456755;
CHECKREG r3, 0x56789007;
CHECKREG r4, 0x789AB799;
CHECKREG r5, 0xABCD2FF7;
CHECKREG r6, 0xF9AB1D7D;
CHECKREG r7, 0xABCD2FF7;
imm32 r0, 0xe56739ab;
imm32 r1, 0x67694bcd;
imm32 r2, 0xd3456755;
imm32 r3, 0x66666777;
imm32 r4, 0x12345699;
imm32 r5, 0x45678b6b;
imm32 r6, 0x043290d6;
imm32 r7, 0x1234567f;
R4 = MAX ( R4 , R7 );
R5 = MAX ( R5 , R5 );
R2 = MAX ( R6 , R3 );
R6 = MAX ( R0 , R4 );
R0 = MAX ( R1 , R6 );
R2 = MAX ( R2 , R1 );
R1 = MAX ( R3 , R0 );
R7 = MAX ( R7 , R4 );
CHECKREG r0, 0x67694BCD;
CHECKREG r1, 0x67694BCD;
CHECKREG r2, 0x67694BCD;
CHECKREG r3, 0x66666777;
CHECKREG r4, 0x12345699;
CHECKREG r5, 0x45678B6B;
CHECKREG r6, 0x12345699;
CHECKREG r7, 0x12345699;

imm32 r0, 0xd76789ab;
imm32 r1, 0x6779abcd;
imm32 r2, 0xe3456755;
imm32 r3, 0x56789007;
imm32 r4, 0x789ab799;
imm32 r5, 0xaaaa0bbb;
imm32 r6, 0x89ab1d7d;
imm32 r7, 0xabcd2ff7;
R3 = MAX ( R4 , R0 );
R5 = MAX ( R5 , R1 );
R2 = MAX ( R2 , R2 );
R7 = MAX ( R7 , R3 );
R4 = MAX ( R3 , R4 );
R0 = MAX ( R1 , R5 );
R1 = MAX ( R0 , R6 );
R6 = MAX ( R6 , R7 );
CHECKREG r0, 0x6779ABCD;
CHECKREG r1, 0x6779ABCD;
CHECKREG r2, 0xE3456755;
CHECKREG r3, 0x789AB799;
CHECKREG r4, 0x789AB799;
CHECKREG r5, 0x6779ABCD;
CHECKREG r6, 0x789AB799;
CHECKREG r7, 0x789AB799;


pass
