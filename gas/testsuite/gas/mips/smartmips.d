#objdump: -dr --prefix-addresses --show-raw-insn -M reg-names=numeric
#name: SmartMIPS
#as: -msmartmips -32


.*: +file format .*mips.*

Disassembly of section \.text:

0+0000 <[^>]*> 00c52046 	rorv	\$4,\$5,\$6
0+0004 <[^>]*> 00c52046 	rorv	\$4,\$5,\$6
0+0008 <[^>]*> 00c52046 	rorv	\$4,\$5,\$6
0+000c <[^>]*> 00c52046 	rorv	\$4,\$5,\$6
0+0010 <[^>]*> 002527c2 	ror	\$4,\$5,0x1f
0+0014 <[^>]*> 00252202 	ror	\$4,\$5,0x8
0+0018 <[^>]*> 00252042 	ror	\$4,\$5,0x1
0+001c <[^>]*> 00252002 	ror	\$4,\$5,0x0
0+0020 <[^>]*> 002527c2 	ror	\$4,\$5,0x1f
0+0024 <[^>]*> 00252042 	ror	\$4,\$5,0x1
0+0028 <[^>]*> 00252602 	ror	\$4,\$5,0x18
0+002c <[^>]*> 002527c2 	ror	\$4,\$5,0x1f
0+0030 <[^>]*> 00252002 	ror	\$4,\$5,0x0
0+0034 <[^>]*> 70a41088 	lwxs	\$2,\$4\(\$5\)
0+0038 <[^>]*> 72110441 	maddp	\$16,\$17
0+003c <[^>]*> 016c0459 	multp	\$11,\$12
0+0040 <[^>]*> 00004052 	mflhxu	\$8
0+0044 <[^>]*> 00800053 	mtlhx	\$4
0+0048 <[^>]*> 70d80481 	pperm	\$6,\$24
0+004c <[^>]*> 00000000 	nop
