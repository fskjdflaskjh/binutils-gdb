//Original:/testcases/core/c_alu2op_shadd_1/c_alu2op_shadd_1.dsp
// Spec Reference: alu2op shadd 1
# mach: bfin

.include "testutils.inc"
	start



imm32 r0, 0x03417990;
imm32 r1, 0x12315678;
imm32 r2, 0x23416789;
imm32 r3, 0x3451789a;
imm32 r4, 0x856189ab;
imm32 r5, 0x96719abc;
imm32 r6, 0xa781abcd;
imm32 r7, 0xb891bcde;
R1 = ( R1 + R0 ) << 1;
R2 = ( R2 + R0 ) << 1;
R3 = ( R3 + R0 ) << 1;
R4 = ( R4 + R0 ) << 1;
R5 = ( R5 + R0 ) << 1;
R6 = ( R6 + R0 ) << 1;
R7 = ( R7 + R0 ) << 1;
R0 = ( R0 + R0 ) << 1;
CHECKREG r0, 0x0D05E640;
CHECKREG r1, 0x2AE5A010;
CHECKREG r2, 0x4D05C232;
CHECKREG r3, 0x6F25E454;
CHECKREG r4, 0x11460676;
CHECKREG r5, 0x33662898;
CHECKREG r6, 0x55864ABA;
CHECKREG r7, 0x77A66CDC;

imm32 r0, 0x03457290;
imm32 r1, 0x12345278;
imm32 r2, 0x23456289;
imm32 r3, 0x3456729a;
imm32 r4, 0x856782ab;
imm32 r5, 0x967892bc;
imm32 r6, 0xa789a2cd;
imm32 r7, 0xb89ab2de;
R0 = ( R0 + R1 ) << 1;
R2 = ( R2 + R1 ) << 1;
R3 = ( R3 + R1 ) << 1;
R4 = ( R4 + R1 ) << 1;
R5 = ( R5 + R1 ) << 1;
R6 = ( R6 + R1 ) << 1;
R7 = ( R7 + R1 ) << 1;
R1 = ( R1 + R1 ) << 1;
CHECKREG r0, 0x2AF38A10;
CHECKREG r1, 0x48D149E0;
CHECKREG r2, 0x6AF36A02;
CHECKREG r3, 0x8D158A24;
CHECKREG r4, 0x2F37AA46;
CHECKREG r5, 0x5159CA68;
CHECKREG r6, 0x737BEA8A;
CHECKREG r7, 0x959E0AAC;

imm32 r0, 0x03457930;
imm32 r1, 0x12345638;
imm32 r2, 0x23456739;
imm32 r3, 0x3456783a;
imm32 r4, 0x8567893b;
imm32 r5, 0x96789a3c;
imm32 r6, 0xa789ab3d;
imm32 r7, 0xb89abc3e;
R0 = ( R0 + R2 ) << 1;
R1 = ( R1 + R2 ) << 1;
R3 = ( R3 + R2 ) << 1;
R4 = ( R4 + R2 ) << 1;
R5 = ( R5 + R2 ) << 1;
R6 = ( R6 + R2 ) << 1;
R7 = ( R7 + R2 ) << 1;
R2 = ( R2 + R2 ) << 1;
CHECKREG r0, 0x4D15C0D2;
CHECKREG r1, 0x6AF37AE2;
CHECKREG r2, 0x8D159CE4;
CHECKREG r3, 0xAF37BEE6;
CHECKREG r4, 0x5159E0E8;
CHECKREG r5, 0x737C02EA;
CHECKREG r6, 0x959E24EC;
CHECKREG r7, 0xB7C046EE;

imm32 r0, 0x04457990;
imm32 r1, 0x14345678;
imm32 r2, 0x24456789;
imm32 r3, 0x3456789a;
imm32 r4, 0x846789ab;
imm32 r5, 0x94789abc;
imm32 r6, 0xa489abcd;
imm32 r7, 0xb49abcde;
R0 = ( R0 + R3 ) << 1;
R1 = ( R1 + R3 ) << 1;
R2 = ( R2 + R3 ) << 1;
R4 = ( R4 + R3 ) << 1;
R5 = ( R5 + R3 ) << 1;
R6 = ( R6 + R3 ) << 1;
R7 = ( R7 + R3 ) << 1;
R3 = ( R3 + R3 ) << 1;
CHECKREG r0, 0x7137E454;
CHECKREG r1, 0x91159E24;
CHECKREG r2, 0xB137C046;
CHECKREG r3, 0xD159E268;
CHECKREG r4, 0x717C048A;
CHECKREG r5, 0x919E26AC;
CHECKREG r6, 0xB1C048CE;
CHECKREG r7, 0xD1E26AF0;

imm32 r0, 0x03417990;
imm32 r1, 0x12315678;
imm32 r2, 0x23416789;
imm32 r3, 0x3451789a;
imm32 r4, 0x856189ab;
imm32 r5, 0x96719abc;
imm32 r6, 0xa781abcd;
imm32 r7, 0xb891bcde;
R0 = ( R0 + R4 ) << 1;
R1 = ( R1 + R4 ) << 1;
R2 = ( R2 + R4 ) << 1;
R3 = ( R3 + R4 ) << 1;
R5 = ( R5 + R4 ) << 1;
R6 = ( R6 + R4 ) << 1;
R7 = ( R7 + R4 ) << 1;
R4 = ( R4 + R4 ) << 1;
CHECKREG r0, 0x11460676;
CHECKREG r1, 0x2F25C046;
CHECKREG r2, 0x5145E268;
CHECKREG r3, 0x7366048A;
CHECKREG r4, 0x158626AC;
CHECKREG r5, 0x37A648CE;
CHECKREG r6, 0x59C66AF0;
CHECKREG r7, 0x7BE68D12;

imm32 r0, 0x03457290;
imm32 r1, 0x12345278;
imm32 r2, 0x23456289;
imm32 r3, 0x3456729a;
imm32 r4, 0x856782ab;
imm32 r5, 0x967892bc;
imm32 r6, 0xa789a2cd;
imm32 r7, 0xb89ab2de;
R0 = ( R0 + R5 ) << 1;
R1 = ( R1 + R5 ) << 1;
R2 = ( R2 + R5 ) << 1;
R3 = ( R3 + R5 ) << 1;
R4 = ( R4 + R5 ) << 1;
R6 = ( R6 + R5 ) << 1;
R7 = ( R7 + R5 ) << 1;
R5 = ( R5 + R5 ) << 1;
CHECKREG r0, 0x337C0A98;
CHECKREG r1, 0x5159CA68;
CHECKREG r2, 0x737BEA8A;
CHECKREG r3, 0x959E0AAC;
CHECKREG r4, 0x37C02ACE;
CHECKREG r5, 0x59E24AF0;
CHECKREG r6, 0x7C046B12;
CHECKREG r7, 0x9E268B34;

imm32 r0, 0x03457930;
imm32 r1, 0x12345638;
imm32 r2, 0x23456739;
imm32 r3, 0x3456783a;
imm32 r4, 0x8567893b;
imm32 r5, 0x96789a3c;
imm32 r6, 0xa789ab3d;
imm32 r7, 0xb89abc3e;
R0 = ( R0 + R6 ) << 1;
R1 = ( R1 + R6 ) << 1;
R2 = ( R2 + R6 ) << 1;
R3 = ( R3 + R6 ) << 1;
R4 = ( R4 + R6 ) << 1;
R5 = ( R5 + R6 ) << 1;
R7 = ( R7 + R6 ) << 1;
R6 = ( R6 + R6 ) << 1;
CHECKREG r0, 0x559E48DA;
CHECKREG r1, 0x737C02EA;
CHECKREG r2, 0x959E24EC;
CHECKREG r3, 0xB7C046EE;
CHECKREG r4, 0x59E268F0;
CHECKREG r5, 0x7C048AF2;
CHECKREG r6, 0x9E26ACF4;
CHECKREG r7, 0xC048CEF6;

imm32 r0, 0x04457990;
imm32 r1, 0x14345678;
imm32 r2, 0x24456789;
imm32 r3, 0x3456789a;
imm32 r4, 0x846789ab;
imm32 r5, 0x94789abc;
imm32 r6, 0xa489abcd;
imm32 r7, 0xb49abcde;
R0 = ( R0 + R7 ) << 1;
R1 = ( R1 + R7 ) << 1;
R2 = ( R2 + R7 ) << 1;
R3 = ( R3 + R7 ) << 1;
R4 = ( R4 + R7 ) << 1;
R5 = ( R5 + R7 ) << 1;
R6 = ( R6 + R7 ) << 1;
R7 = ( R7 + R7 ) << 1;
CHECKREG r0, 0x71C06CDC;
CHECKREG r1, 0x919E26AC;
CHECKREG r2, 0xB1C048CE;
CHECKREG r3, 0xD1E26AF0;
CHECKREG r4, 0x72048D12;
CHECKREG r5, 0x9226AF34;
CHECKREG r6, 0xB248D156;
CHECKREG r7, 0xD26AF378;
pass
