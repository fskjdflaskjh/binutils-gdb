#objdump: -dr -mmips:4000 -mmips:16
#as: -mips3 -mtune=r4000 -mips16
#name: mips16 jalx
.*:     file format .*
Disassembly of section .text:
00000000 <.text>:
   0:	1c00 0000 	jalx	0x0
			0: R_MIPS16_26	external_label
   4:	6500      	nop
   6:	6500      	nop
