//Original:/testcases/core/c_dsp32alu_rmp/c_dsp32alu_rmp.dsp
// Spec Reference: dsp32alu dreg = -/+ ( dreg, dreg)
# mach: bfin

.include "testutils.inc"
	start




// ALU operations include parallel addition, subtraction
// and 32-bit data. If an operation use a single ALU only, it uses ALU0.

imm32 r0, 0x15678911;
imm32 r1, 0x2789ab1d;
imm32 r2, 0x34445515;
imm32 r3, 0x46667717;
imm32 r4, 0x5567891b;
imm32 r5, 0x6789ab1d;
imm32 r6, 0x74445515;
imm32 r7, 0x86667777;
R0 = R0 -|+ R0;
R1 = R0 -|+ R1;
R2 = R0 -|+ R2;
R3 = R0 -|+ R3;
R4 = R0 -|+ R4;
R5 = R0 -|+ R5;
R6 = R0 -|+ R6;
R7 = R0 -|+ R7;
CHECKREG r0, 0x00001222;
CHECKREG r1, 0xD877BD3F;
CHECKREG r2, 0xCBBC6737;
CHECKREG r3, 0xB99A8939;
CHECKREG r4, 0xAA999B3D;
CHECKREG r5, 0x9877BD3F;
CHECKREG r6, 0x8BBC6737;
CHECKREG r7, 0x799A8999;

imm32 r0, 0x9567892b;
imm32 r1, 0xa789ab2d;
imm32 r2, 0xb4445525;
imm32 r3, 0xc6667727;
imm32 r4, 0xd8889929;
imm32 r5, 0xeaaabb2b;
imm32 r6, 0xfcccdd2d;
imm32 r7, 0x0eeeffff;
R0 = R1 -|+ R0;
R1 = R1 -|+ R1;
R2 = R1 -|+ R2;
R3 = R1 -|+ R3;
R4 = R1 -|+ R4;
R5 = R1 -|+ R5;
R6 = R1 -|+ R6;
R7 = R1 -|+ R7;
CHECKREG r0, 0x12223458;
CHECKREG r1, 0x0000565A;
CHECKREG r2, 0x4BBCAB7F;
CHECKREG r3, 0x399ACD81;
CHECKREG r4, 0x2778EF83;
CHECKREG r5, 0x15561185;
CHECKREG r6, 0x03343387;
CHECKREG r7, 0xF1125659;

imm32 r0, 0x416789ab;
imm32 r1, 0x6289abcd;
imm32 r2, 0x43445555;
imm32 r3, 0x64667777;
imm32 r4, 0x456789ab;
imm32 r5, 0x6689abcd;
imm32 r6, 0x47445555;
imm32 r7, 0x68667777;
R0 = R2 -|+ R0;
R1 = R2 -|+ R1;
R2 = R2 -|+ R2;
R3 = R2 -|+ R3;
R4 = R2 -|+ R4;
R5 = R2 -|+ R5;
R6 = R2 -|+ R6;
R7 = R2 -|+ R7;
CHECKREG r0, 0x01DDDF00;
CHECKREG r1, 0xE0BB0122;
CHECKREG r2, 0x0000AAAA;
CHECKREG r3, 0x9B9A2221;
CHECKREG r4, 0xBA993455;
CHECKREG r5, 0x99775677;
CHECKREG r6, 0xB8BCFFFF;
CHECKREG r7, 0x979A2221;

imm32 r0, 0x9567892b;
imm32 r1, 0xa789ab2d;
imm32 r2, 0xb4445525;
imm32 r3, 0xc6667727;
imm32 r0, 0x9567892b;
imm32 r1, 0xa789ab2d;
imm32 r2, 0xb4445525;
imm32 r3, 0xc6667727;
R0 = R3 -|+ R0;
R1 = R3 -|+ R1;
R2 = R3 -|+ R2;
R3 = R3 -|+ R3;
R4 = R3 -|+ R4;
R5 = R3 -|+ R5;
R6 = R3 -|+ R6;
R7 = R3 -|+ R7;
CHECKREG r4, 0x456722A3;
CHECKREG r5, 0x668944C5;
CHECKREG r6, 0x4744EE4D;
CHECKREG r7, 0x6866106F;
CHECKREG r4, 0x456722A3;
CHECKREG r5, 0x668944C5;
CHECKREG r6, 0x4744EE4D;
CHECKREG r7, 0x6866106F;

imm32 r0, 0x4537891b;
imm32 r1, 0x6759ab2d;
imm32 r2, 0x44555535;
imm32 r3, 0x66665747;
imm32 r4, 0x88789565;
imm32 r5, 0xaa8abb5b;
imm32 r6, 0xcc9cdd85;
imm32 r7, 0xeeaeff9f;
R0 = R4 -|+ R0;
R1 = R4 -|+ R1;
R2 = R4 -|+ R2;
R3 = R4 -|+ R3;
R4 = R4 -|+ R4;
R5 = R4 -|+ R5;
R6 = R4 -|+ R6;
R7 = R4 -|+ R7;
CHECKREG r0, 0x43411E80;
CHECKREG r1, 0x211F4092;
CHECKREG r2, 0x4423EA9A;
CHECKREG r3, 0x2212ECAC;
CHECKREG r4, 0x00002ACA;
CHECKREG r5, 0x5576E625;
CHECKREG r6, 0x3364084F;
CHECKREG r7, 0x11522A69;

imm32 r0, 0x456b89ab;
imm32 r1, 0x69764bcd;
imm32 r2, 0x49736564;
imm32 r3, 0x61278394;
imm32 r4, 0x98876439;
imm32 r5, 0xaaaa0bbb;
imm32 r6, 0xcccc1ddd;
imm32 r7, 0x12346fff;
R0 = R5 -|+ R0;
R1 = R5 -|+ R1;
R2 = R5 -|+ R2;
R3 = R5 -|+ R3;
R4 = R5 -|+ R4;
R5 = R5 -|+ R5;
R6 = R5 -|+ R6;
R7 = R5 -|+ R7;
CHECKREG r0, 0x653F9566;
CHECKREG r1, 0x41345788;
CHECKREG r2, 0x6137711F;
CHECKREG r3, 0x49838F4F;
CHECKREG r4, 0x12236FF4;
CHECKREG r5, 0x00001776;
CHECKREG r6, 0x33343553;
CHECKREG r7, 0xEDCC8775;

imm32 r0, 0x456739ab;
imm32 r1, 0x67694bcd;
imm32 r2, 0x03456755;
imm32 r3, 0x66666777;
imm32 r4, 0x12345699;
imm32 r5, 0x45678b6b;
imm32 r6, 0x043290d6;
imm32 r7, 0x1234567f;
R0 = R6 -|+ R0;
R1 = R6 -|+ R1;
R2 = R6 -|+ R2;
R3 = R6 -|+ R3;
R4 = R6 -|+ R4;
R5 = R6 -|+ R5;
R6 = R6 -|+ R6;
R7 = R6 -|+ R7;
CHECKREG r0, 0xBECBCA81;
CHECKREG r1, 0x9CC9DCA3;
CHECKREG r2, 0x00EDF82B;
CHECKREG r3, 0x9DCCF84D;
CHECKREG r4, 0xF1FEE76F;
CHECKREG r5, 0xBECB1C41;
CHECKREG r6, 0x000021AC;
CHECKREG r7, 0xEDCC782B;

imm32 r0, 0x476789ab;
imm32 r1, 0x6779abcd;
imm32 r2, 0x23456755;
imm32 r3, 0x56789007;
imm32 r4, 0x789ab799;
imm32 r5, 0xaaaa0bbb;
imm32 r6, 0x89ab1d7d;
imm32 r7, 0xabcd2ff7;
R0 = R7 -|+ R0;
R1 = R7 -|+ R1;
R2 = R7 -|+ R2;
R3 = R7 -|+ R3;
R4 = R7 -|+ R4;
R5 = R7 -|+ R5;
R6 = R7 -|+ R6;
R7 = R7 -|+ R7;
CHECKREG r0, 0x6466B9A2;
CHECKREG r1, 0x4454DBC4;
CHECKREG r2, 0x8888974C;
CHECKREG r3, 0x5555BFFE;
CHECKREG r4, 0x3333E790;
CHECKREG r5, 0x01233BB2;
CHECKREG r6, 0x22224D74;
CHECKREG r7, 0x00005FEE;

imm32 r0, 0x456739ab;
imm32 r1, 0x67694bcd;
imm32 r2, 0x03456755;
imm32 r3, 0x66666777;
imm32 r4, 0x12345699;
imm32 r5, 0x45678b6b;
imm32 r6, 0x043290d6;
imm32 r7, 0x1234567f;
R4 = R4 -|+ R7 (S);
R5 = R5 -|+ R5 (CO);
R2 = R6 -|+ R3 (SCO);
R6 = R0 -|+ R4 (S);
R0 = R1 -|+ R6 (S);
R2 = R2 -|+ R1 (CO);
R1 = R3 -|+ R0 (CO);
R7 = R7 -|+ R4 (SCO);
CHECKREG r0, 0x22027FFF;
CHECKREG r1, 0xE7764464;
CHECKREG r2, 0xE99990E4;
CHECKREG r3, 0x66666777;
CHECKREG r4, 0x00007FFF;
CHECKREG r5, 0x16D60000;
CHECKREG r6, 0x45677FFF;
CHECKREG r7, 0x7FFF1234;

imm32 r0, 0x476789ab;
imm32 r1, 0x6779abcd;
imm32 r2, 0x23456755;
imm32 r3, 0x56789007;
imm32 r4, 0x789ab799;
imm32 r5, 0xaaaa0bbb;
imm32 r6, 0x89ab1d7d;
imm32 r7, 0xabcd2ff7;
R3 = R4 -|+ R0 (S);
R5 = R5 -|+ R1 (SCO);
R2 = R2 -|+ R2 (S);
R7 = R7 -|+ R3 (CO);
R4 = R3 -|+ R4 (CO);
R0 = R1 -|+ R5 (S);
R1 = R0 -|+ R6 (SCO);
R6 = R6 -|+ R7 (SCO);
CHECKREG r0, 0x7FFF8000;
CHECKREG r1, 0x9D7D7FFF;
CHECKREG r2, 0x00007FFF;
CHECKREG r3, 0x31338000;
CHECKREG r4, 0x3799B899;
CHECKREG r5, 0xB7888000;
CHECKREG r6, 0x7FFFD9B4;
CHECKREG r7, 0xAFF77A9A;

pass
