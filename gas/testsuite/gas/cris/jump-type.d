#objdump: -dr
#name: @OC@

# Test the @OC@ insn.

.*:[ 	]+file format .*-cris

Disassembly of section \.text:
00000000 <notstart>:
   0:	0000[ ]+	bcc ( 0x2|\.\+2)
	\.\.\.

00000004 <start>:
[	 ]+4:[	 ]+@IM+b7b9@[ 	]+@OC@[ ]+r7
[	 ]+6:[	 ]+@IM+b6b9@[ 	]+@OC@[ ]+r6
[	 ]+8:[	 ]+@IM+30b9@[ 	]+@OC@[ ]+\[r0\]
[	 ]+a:[	 ]+@IM+33b9@[ 	]+@OC@[ ]+\[r3\]
[	 ]+c:[	 ]+@IM+34bd@[ 	]+@OC@[ ]+\[r4\+\]
[	 ]+e:[	 ]+@IM+31bd@[ 	]+@OC@[ ]+\[r1\+\]
[	 ]+10:[	 ]+4bd5 @IM+30b9@[ 	]+@OC@[ ]+\[r11\+r13\.b\]
[	 ]+14:[	 ]+42a5 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+r10\.b\]
[	 ]+18:[	 ]+45c9 @IM+30b9@[ 	]+@OC@[ ]+\[r12\+\[r5\]\.b\]
[	 ]+1c:[	 ]+4ad9 @IM+30b9@[ 	]+@OC@[ ]+\[r13\+\[r10\]\.b\]
[	 ]+20:[	 ]+4d2d @IM+30b9@[ 	]+@OC@[ ]+\[r2\+\[r13\+\]\.b\]
[	 ]+24:[	 ]+40cd @IM+30b9@[ 	]+@OC@[ ]+\[r12\+\[r0\+\]\.b\]
[	 ]+28:[	 ]+55b5 @IM+30b9@[ 	]+@OC@[ ]+\[r5\+r11\.w\]
[	 ]+2c:[	 ]+5115 @IM+30b9@[ 	]+@OC@[ ]+\[r1\+r1\.w\]
[	 ]+30:[	 ]+5009 @IM+30b9@[ 	]+@OC@[ ]+\[r0\+\[r0\]\.w\]
[	 ]+34:[	 ]+5729 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+\[r7\]\.w\]
[	 ]+38:[	 ]+532d @IM+30b9@[ 	]+@OC@[ ]+\[r2\+\[r3\+\]\.w\]
[	 ]+3c:[	 ]+587d @IM+30b9@[ 	]+@OC@[ ]+\[r7\+\[r8\+\]\.w\]
[	 ]+40:[	 ]+6255 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+r5\.d\]
[	 ]+44:[	 ]+63a5 @IM+30b9@[ 	]+@OC@[ ]+\[r3\+r10\.d\]
[	 ]+48:[	 ]+6259 @IM+30b9@[ 	]+@OC@[ ]+\[r5\+\[r2\]\.d\]
[	 ]+4c:[	 ]+6ac9 @IM+30b9@[ 	]+@OC@[ ]+\[r12\+\[r10\]\.d\]
[	 ]+50:[	 ]+651d @IM+30b9@[ 	]+@OC@[ ]+\[r1\+\[r5\+\]\.d\]
[	 ]+54:[	 ]+6a2d @IM+30b9@[ 	]+@OC@[ ]+\[r2\+\[r10\+\]\.d\]
[	 ]+58:[	 ]+0021 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+0\]
[	 ]+5c:[	 ]+0121 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+1\]
[	 ]+60:[	 ]+7f21 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+127\]
[	 ]+64:[	 ]+5f2d 8000 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+128\]
[	 ]+6a:[	 ]+ff21 @IM+30b9@[ 	]+@OC@[ ]+\[r2-1\]
[	 ]+6e:[	 ]+ff21 @IM+30b9@[ 	]+@OC@[ ]+\[r2-1\]
[	 ]+72:[	 ]+8121 @IM+30b9@[ 	]+@OC@[ ]+\[r2-127\]
[	 ]+76:[	 ]+8021 @IM+30b9@[ 	]+@OC@[ ]+\[r2-128\]
[	 ]+7a:[	 ]+8121 @IM+30b9@[ 	]+@OC@[ ]+\[r2-127\]
[	 ]+7e:[	 ]+8021 @IM+30b9@[ 	]+@OC@[ ]+\[r2-128\]
[	 ]+82:[	 ]+5f2d ff00 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+255\]
[	 ]+88:[	 ]+5f2d 01ff @IM+30b9@[ 	]+@OC@[ ]+\[r2-255\]
[	 ]+8e:[	 ]+5f2d 01ff @IM+30b9@[ 	]+@OC@[ ]+\[r2-255\]
[	 ]+94:[	 ]+5f2d 0001 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+256\]
[	 ]+9a:[	 ]+5f2d 00ff @IM+30b9@[ 	]+@OC@[ ]+\[r2-256\]
[	 ]+a0:[	 ]+5f2d 68dd @IM+30b9@[ 	]+@OC@[ ]+\[r2-8856\]
[	 ]+a6:[	 ]+5f2d 00ff @IM+30b9@[ 	]+@OC@[ ]+\[r2-256\]
[	 ]+ac:[	 ]+5f2d 68dd @IM+30b9@[ 	]+@OC@[ ]+\[r2-8856\]
[	 ]+b2:[	 ]+5f2d 9822 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+8856\]
[	 ]+b8:[	 ]+6f2d ac72 2a00 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(2781868|2a72ac <two701867\+0x13881>)\]
[	 ]+c0:[	 ]+6f2d d5c5 d6ff @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0xffd6c5d5|ffd6c5d5 <const_int_m32\+0xd13e1620>)\]
[	 ]+c8:[	 ]+6f2d acce c09e @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0x9ec0ceac|9ec0ceac <const_int_m32\+0x70281ef7>)\]
[	 ]+d0:[	 ]+6f2d 5331 3f81 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0x813f3153|813f3153 <const_int_m32\+0x52a6819e>)\]
[	 ]+d8:[	 ]+6f2d 5331 3f81 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0x813f3153|813f3153 <const_int_m32\+0x52a6819e>)\]
[	 ]+e0:[	 ]+6f2d b5af 982e @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0x2e98afb5|2e98afb5 <const_int_m32>)\]
[	 ]+e8:[	 ]+6f2d 2b45 941b @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0x1b94452b|1b94452b <const_int_32>)\]
[	 ]+f0:[	 ]+2a21 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+42\]
[	 ]+f4:[	 ]+d621 @IM+30b9@[ 	]+@OC@[ ]+\[r2-42\]
[	 ]+f8:[	 ]+d621 @IM+30b9@[ 	]+@OC@[ ]+\[r2-42\]
[	 ]+fc:[	 ]+2a21 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+42\]
[	 ]+100:[	 ]+d621 @IM+30b9@[ 	]+@OC@[ ]+\[r2-42\]
[	 ]+104:[	 ]+d621 @IM+30b9@[ 	]+@OC@[ ]+\[r2-42\]
[	 ]+108:[	 ]+2a21 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+42\]
[	 ]+10c:[	 ]+d621 @IM+30b9@[ 	]+@OC@[ ]+\[r2-42\]
[	 ]+110:[	 ]+2a21 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+42\]
[	 ]+114:[	 ]+5f2d ff7f @IM+30b9@[ 	]+@OC@[ ]+\[r2\+32767\]
[	 ]+11a:[	 ]+6f2d 0080 0000 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(32768|8000 <three2767\+0x1>)\]
[	 ]+122:[	 ]+6f2d 0180 0000 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(32769|8001 <three2767\+0x2>)\]
[	 ]+12a:[	 ]+5f2d 0180 @IM+30b9@[ 	]+@OC@[ ]+\[r2-32767\]
[	 ]+130:[	 ]+5f2d 0080 @IM+30b9@[ 	]+@OC@[ ]+\[r2-32768\]
[	 ]+136:[	 ]+6f2d ff7f ffff @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0xffff7fff|ffff7fff <const_int_m32\+0xd166d04a>)\]
[	 ]+13e:[	 ]+5f2d 0180 @IM+30b9@[ 	]+@OC@[ ]+\[r2-32767\]
[	 ]+144:[	 ]+5f2d 0080 @IM+30b9@[ 	]+@OC@[ ]+\[r2-32768\]
[	 ]+14a:[	 ]+6f2d ff7f ffff @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0xffff7fff|ffff7fff <const_int_m32\+0xd166d04a>)\]
[	 ]+152:[	 ]+6f2d ffff 0000 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(65535|ffff <six5535>)\]
[	 ]+15a:[	 ]+6f2d 0000 0100 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(65536|10000 <six5535\+0x1>)\]
[	 ]+162:[	 ]+6f2d 2b3a 2900 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(2701867|293a2b <two701867>)\]
[	 ]+16a:[	 ]+6f2d d5c5 d6ff @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0xffd6c5d5|ffd6c5d5 <const_int_m32\+0xd13e1620>)\]
[	 ]+172:[	 ]+6f2d d5c5 d6ff @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0xffd6c5d5|ffd6c5d5 <const_int_m32\+0xd13e1620>)\]
[	 ]+17a:[	 ]+6f2d 0000 0000 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+0( <notstart>)?\]
[ 	]+17c:[ 	]+(R_CRIS_)?32[ 	]+externalsym
[	 ]+182:[	 ]+0021 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+0\]
[	 ]+186:[	 ]+0121 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+1\]
[	 ]+18a:[	 ]+7f21 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+127\]
[	 ]+18e:[	 ]+5f2d 8000 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+128\]
[	 ]+194:[	 ]+ff21 @IM+30b9@[ 	]+@OC@[ ]+\[r2-1\]
[	 ]+198:[	 ]+ff21 @IM+30b9@[ 	]+@OC@[ ]+\[r2-1\]
[	 ]+19c:[	 ]+8121 @IM+30b9@[ 	]+@OC@[ ]+\[r2-127\]
[	 ]+1a0:[	 ]+8021 @IM+30b9@[ 	]+@OC@[ ]+\[r2-128\]
[	 ]+1a4:[	 ]+8121 @IM+30b9@[ 	]+@OC@[ ]+\[r2-127\]
[	 ]+1a8:[	 ]+8021 @IM+30b9@[ 	]+@OC@[ ]+\[r2-128\]
[	 ]+1ac:[	 ]+5f2d ff00 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+255\]
[	 ]+1b2:[	 ]+5f2d 01ff @IM+30b9@[ 	]+@OC@[ ]+\[r2-255\]
[	 ]+1b8:[	 ]+5f2d 01ff @IM+30b9@[ 	]+@OC@[ ]+\[r2-255\]
[	 ]+1be:[	 ]+5f2d 0001 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+256\]
[	 ]+1c4:[	 ]+5f2d 00ff @IM+30b9@[ 	]+@OC@[ ]+\[r2-256\]
[	 ]+1ca:[	 ]+5f2d 68dd @IM+30b9@[ 	]+@OC@[ ]+\[r2-8856\]
[	 ]+1d0:[	 ]+5f2d 00ff @IM+30b9@[ 	]+@OC@[ ]+\[r2-256\]
[	 ]+1d6:[	 ]+5f2d 68dd @IM+30b9@[ 	]+@OC@[ ]+\[r2-8856\]
[	 ]+1dc:[	 ]+5f2d 9822 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+8856\]
[	 ]+1e2:[	 ]+6f2d ac72 2a00 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(2781868|2a72ac <two701867\+0x13881>)\]
[	 ]+1ea:[	 ]+6f2d d5c5 d6ff @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0xffd6c5d5|ffd6c5d5 <const_int_m32\+0xd13e1620>)\]
[	 ]+1f2:[	 ]+6f2d acce c09e @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0x9ec0ceac|9ec0ceac <const_int_m32\+0x70281ef7>)\]
[	 ]+1fa:[	 ]+6f2d 5331 3f81 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0x813f3153|813f3153 <const_int_m32\+0x52a6819e>)\]
[	 ]+202:[	 ]+6f2d 5331 3f81 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0x813f3153|813f3153 <const_int_m32\+0x52a6819e>)\]
[	 ]+20a:[	 ]+6f2d b5af 982e @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0x2e98afb5|2e98afb5 <const_int_m32>)\]
[	 ]+212:[	 ]+6f2d 2b45 941b @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0x1b94452b|1b94452b <const_int_32>)\]
[	 ]+21a:[	 ]+2a21 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+42\]
[	 ]+21e:[	 ]+d621 @IM+30b9@[ 	]+@OC@[ ]+\[r2-42\]
[	 ]+222:[	 ]+d621 @IM+30b9@[ 	]+@OC@[ ]+\[r2-42\]
[	 ]+226:[	 ]+2a21 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+42\]
[	 ]+22a:[	 ]+d621 @IM+30b9@[ 	]+@OC@[ ]+\[r2-42\]
[	 ]+22e:[	 ]+d621 @IM+30b9@[ 	]+@OC@[ ]+\[r2-42\]
[	 ]+232:[	 ]+2a21 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+42\]
[	 ]+236:[	 ]+d621 @IM+30b9@[ 	]+@OC@[ ]+\[r2-42\]
[	 ]+23a:[	 ]+2a21 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+42\]
[	 ]+23e:[	 ]+5f2d ff7f @IM+30b9@[ 	]+@OC@[ ]+\[r2\+32767\]
[	 ]+244:[	 ]+6f2d 0080 0000 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(32768|8000 <three2767\+0x1>)\]
[	 ]+24c:[	 ]+6f2d 0180 0000 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(32769|8001 <three2767\+0x2>)\]
[	 ]+254:[	 ]+5f2d 0180 @IM+30b9@[ 	]+@OC@[ ]+\[r2-32767\]
[	 ]+25a:[	 ]+5f2d 0080 @IM+30b9@[ 	]+@OC@[ ]+\[r2-32768\]
[	 ]+260:[	 ]+6f2d ff7f ffff @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0xffff7fff|ffff7fff <const_int_m32\+0xd166d04a>)\]
[	 ]+268:[	 ]+5f2d 0180 @IM+30b9@[ 	]+@OC@[ ]+\[r2-32767\]
[	 ]+26e:[	 ]+5f2d 0080 @IM+30b9@[ 	]+@OC@[ ]+\[r2-32768\]
[	 ]+274:[	 ]+6f2d ff7f ffff @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0xffff7fff|ffff7fff <const_int_m32\+0xd166d04a>)\]
[	 ]+27c:[	 ]+6f2d ffff 0000 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(65535|ffff <six5535>)\]
[	 ]+284:[	 ]+6f2d 0000 0100 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(65536|10000 <six5535\+0x1>)\]
[	 ]+28c:[	 ]+6f2d 2b3a 2900 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(2701867|293a2b <two701867>)\]
[	 ]+294:[	 ]+6f2d d5c5 d6ff @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0xffd6c5d5|ffd6c5d5 <const_int_m32\+0xd13e1620>)\]
[	 ]+29c:[	 ]+6f2d d5c5 d6ff @IM+30b9@[ 	]+@OC@[ ]+\[r2\+(0xffd6c5d5|ffd6c5d5 <const_int_m32\+0xd13e1620>)\]
[	 ]+2a4:[	 ]+6f2d 0000 0000 @IM+30b9@[ 	]+@OC@[ ]+\[r2\+0( <notstart>)?\]
[ 	]+2a6:[ 	]+(R_CRIS_)?32[ 	]+externalsym
[	 ]+2ac:[	 ]+4235 @IM+31bd@[ 	]+@OC@[ ]+\[r1=r2\+r3\.b\]
[	 ]+2b0:[	 ]+42a5 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+r10\.b\]
[	 ]+2b4:[	 ]+4529 @IM+30bd@[ 	]+@OC@[ ]+\[r0=r2\+\[r5\]\.b\]
[	 ]+2b8:[	 ]+4a29 @IM+33bd@[ 	]+@OC@[ ]+\[r3=r2\+\[r10\]\.b\]
[	 ]+2bc:[	 ]+442d @IM+35bd@[ 	]+@OC@[ ]+\[r5=r2\+\[r4\+\]\.b\]
[	 ]+2c0:[	 ]+474d @IM+32bd@[ 	]+@OC@[ ]+\[r2=r4\+\[r7\+\]\.b\]
[	 ]+2c4:[	 ]+5c55 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r12\+r5\.w\]
[	 ]+2c8:[	 ]+53a5 @IM+31bd@[ 	]+@OC@[ ]+\[r1=r3\+r10\.w\]
[	 ]+2cc:[	 ]+5529 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+\[r5\]\.w\]
[	 ]+2d0:[	 ]+5a79 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r7\+\[r10\]\.w\]
[	 ]+2d4:[	 ]+576d @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r6\+\[r7\+\]\.w\]
[	 ]+2d8:[	 ]+513d @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r3\+\[r1\+\]\.w\]
[	 ]+2dc:[	 ]+6255 @IM+34bd@[ 	]+@OC@[ ]+\[r4=r2\+r5\.d\]
[	 ]+2e0:[	 ]+62a5 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+r10\.d\]
[	 ]+2e4:[	 ]+6539 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r3\+\[r5\]\.d\]
[	 ]+2e8:[	 ]+6a49 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r4\+\[r10\]\.d\]
[	 ]+2ec:[	 ]+658d @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r8\+\[r5\+\]\.d\]
[	 ]+2f0:[	 ]+6a9d @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r9\+\[r10\+\]\.d\]
[	 ]+2f4:[	 ]+0021 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+0\]
[	 ]+2f8:[	 ]+0121 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+1\]
[	 ]+2fc:[	 ]+7f21 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+127\]
[	 ]+300:[	 ]+5f2d 8000 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+128\]
[	 ]+306:[	 ]+ff21 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-1\]
[	 ]+30a:[	 ]+ff21 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-1\]
[	 ]+30e:[	 ]+8121 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-127\]
[	 ]+312:[	 ]+8021 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-128\]
[	 ]+316:[	 ]+8121 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-127\]
[	 ]+31a:[	 ]+8021 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-128\]
[	 ]+31e:[	 ]+5f2d ff00 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+255\]
[	 ]+324:[	 ]+5f2d 01ff @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-255\]
[	 ]+32a:[	 ]+5f2d 01ff @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-255\]
[	 ]+330:[	 ]+5f2d 0001 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+256\]
[	 ]+336:[	 ]+5f2d 00ff @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-256\]
[	 ]+33c:[	 ]+5f2d 68dd @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-8856\]
[	 ]+342:[	 ]+5f2d 00ff @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-256\]
[	 ]+348:[	 ]+5f2d 68dd @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-8856\]
[	 ]+34e:[	 ]+5f2d 9822 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+8856\]
[	 ]+354:[	 ]+6f2d ac72 2a00 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(2781868|2a72ac <two701867\+0x13881>)\]
[	 ]+35c:[	 ]+6f2d d5c5 d6ff @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(0xffd6c5d5|ffd6c5d5 <const_int_m32\+0xd13e1620>)\]
[	 ]+364:[	 ]+6f2d acce c09e @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(0x9ec0ceac|9ec0ceac <const_int_m32\+0x70281ef7>)\]
[	 ]+36c:[	 ]+6f2d 5331 3f81 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(0x813f3153|813f3153 <const_int_m32\+0x52a6819e>)\]
[	 ]+374:[	 ]+6f2d 5331 3f81 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(0x813f3153|813f3153 <const_int_m32\+0x52a6819e>)\]
[	 ]+37c:[	 ]+6f2d b5af 982e @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(0x2e98afb5|2e98afb5 <const_int_m32>)\]
[	 ]+384:[	 ]+6f2d 2b45 941b @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(0x1b94452b|1b94452b <const_int_32>)\]
[	 ]+38c:[	 ]+2a21 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+42\]
[	 ]+390:[	 ]+d621 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-42\]
[	 ]+394:[	 ]+d621 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-42\]
[	 ]+398:[	 ]+2a21 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+42\]
[	 ]+39c:[	 ]+d621 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-42\]
[	 ]+3a0:[	 ]+d621 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-42\]
[	 ]+3a4:[	 ]+2a21 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+42\]
[	 ]+3a8:[	 ]+d621 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-42\]
[	 ]+3ac:[	 ]+2a21 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+42\]
[	 ]+3b0:[	 ]+5f2d ff7f @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+32767\]
[	 ]+3b6:[	 ]+6f2d 0080 0000 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(32768|8000 <three2767\+0x1>)\]
[	 ]+3be:[	 ]+6f2d 0180 0000 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(32769|8001 <three2767\+0x2>)\]
[	 ]+3c6:[	 ]+5f2d 0180 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-32767\]
[	 ]+3cc:[	 ]+5f2d 0080 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-32768\]
[	 ]+3d2:[	 ]+6f2d ff7f ffff @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(0xffff7fff|ffff7fff <const_int_m32\+0xd166d04a>)\]
[	 ]+3da:[	 ]+5f2d 0180 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-32767\]
[	 ]+3e0:[	 ]+5f2d 0080 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2-32768\]
[	 ]+3e6:[	 ]+6f2d ff7f ffff @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(0xffff7fff|ffff7fff <const_int_m32\+0xd166d04a>)\]
[	 ]+3ee:[	 ]+6f2d ffff 0000 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(65535|ffff <six5535>)\]
[	 ]+3f6:[	 ]+6f2d 0000 0100 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(65536|10000 <six5535\+0x1>)\]
[	 ]+3fe:[	 ]+6f2d 2b3a 2900 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(2701867|293a2b <two701867>)\]
[	 ]+406:[	 ]+6f2d d5c5 d6ff @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(0xffd6c5d5|ffd6c5d5 <const_int_m32\+0xd13e1620>)\]
[	 ]+40e:[	 ]+6f2d d5c5 d6ff @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+(0xffd6c5d5|ffd6c5d5 <const_int_m32\+0xd13e1620>)\]
[	 ]+416:[	 ]+6f2d 0000 0000 @IM+3cbd@[ 	]+@OC@[ ]+\[r12=r2\+0( <notstart>)?\]
[ 	]+418:[ 	]+(R_CRIS_)?32[ 	]+externalsym
[	 ]+41e:[	 ]+7209 @IM+30b9@[ 	]+@OC@[ ]+\[\[r2\]\]
[	 ]+422:[	 ]+7309 @IM+30b9@[ 	]+@OC@[ ]+\[\[r3\]\]
[	 ]+426:[	 ]+730d @IM+30b9@[ 	]+@OC@[ ]+\[\[r3\+\]\]
[	 ]+42a:[	 ]+710d @IM+30b9@[ 	]+@OC@[ ]+\[\[r1\+\]\]
[	 ]+42e:[	 ]+7f0d 0000 0000 @IM+30b9@[ 	]+@OC@[ ]+\[(0x0|0 <notstart>)\]
[ 	]+430:[ 	]+(R_CRIS_)?32[ 	]+externalsym
[	 ]+436:[	 ]+7f0d 0000 0000 @IM+30b9@[ 	]+@OC@[ ]+\[(0x0|0 <notstart>)\]
[ 	]+438:[ 	]+(R_CRIS_)?32[ 	]+\.text

0000043e <end>:
	\.\.\.
