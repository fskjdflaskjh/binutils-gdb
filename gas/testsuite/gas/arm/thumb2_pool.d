# as: -march=armv6t2
# objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format .*arm.*

Disassembly of section .text:
0+000 <[^>]+> 4e04      	ldr	r6, \[pc, #16\]	\(00+14 <[^>]+>\)
0+002 <[^>]+> 4904      	ldr	r1, \[pc, #16\]	\(00+14 <[^>]+>\)
0+004 <[^>]+> f8df 600c 	ldr\.w	r6, \[pc, #12\]	; 00+14 <[^>]+>
0+008 <[^>]+> f8df 9008 	ldr\.w	r9, \[pc, #8\]	; 00+14 <[^>]+>
0+00c <[^>]+> bf00      	nop
0+00e <[^>]+> f8df 5004 	ldr\.w	r5, \[pc, #4\]	; 00+14 <[^>]+>
0+012 <[^>]+> 4900      	ldr	r1, \[pc, #0\]	\(00+14 <[^>]+>\)
0+014 <[^>]+> (5678|1234) .*
0+016 <[^>]+> (1234|5678) .*
