#objdump: -dr --prefix-addresses --show-raw-insn -Mmsa
#name: MSA relax
#as: -32 -mmsa -relax-branch
#stderr: msa-relax.l

.*: +file format .*mips.*

Disassembly of section \.text:
[0-9a-f]+ <[^>]*> 47800002 	bnz\.b	\$w0,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08008028 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 47a10002 	bnz\.h	\$w1,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08008028 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 47c20002 	bnz\.w	\$w2,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08008028 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 47e30002 	bnz\.d	\$w3,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08008028 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 47040002 	bz\.b	\$w4,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08008028 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 47250002 	bz\.h	\$w5,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08008028 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 47460002 	bz\.w	\$w6,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08008028 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 47670002 	bz\.d	\$w7,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08008028 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 45e80002 	bnz\.v	\$w8,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08008028 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 45690002 	bz\.v	\$w9,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08008028 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
	\.\.\.
[0-9a-f]+ <[^>]*> 478a0002 	bnz\.b	\$w10,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08000000 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 47ab0002 	bnz\.h	\$w11,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08000000 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 47cc0002 	bnz\.w	\$w12,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08000000 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 47ed0002 	bnz\.d	\$w13,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08000000 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 470e0002 	bz\.b	\$w14,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08000000 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 472f0002 	bz\.h	\$w15,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08000000 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 47500002 	bz\.w	\$w16,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08000000 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 47710002 	bz\.d	\$w17,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08000000 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 45f20002 	bnz\.v	\$w18,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08000000 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 45730002 	bz\.v	\$w19,[0-9a-f]+ <[^>]*>
[0-9a-f]+ <[^>]*> 00000000 	nop
[0-9a-f]+ <[^>]*> 08000000 	j	[0-9a-f]+ <[^>]*>
[	]*[0-9a-f]+: R_MIPS_26	\.text
[0-9a-f]+ <[^>]*> 00000000 	nop
	\.\.\.
