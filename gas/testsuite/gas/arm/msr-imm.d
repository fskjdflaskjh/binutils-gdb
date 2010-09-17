# name: MSR immediate operands
# as: -march=armv7-a
# objdump: -dr --prefix-addresses --show-raw-insn

.*: +file format .*arm.*

Disassembly of section .text:
00000000 <[^>]*> e329f113 	msr	CPSR_fc, #-1073741820	; 0xc0000004
00000004 <[^>]*> e324f113 	msr	CPSR_s, #-1073741820	; 0xc0000004
00000008 <[^>]*> e328f113 	msr	CPSR_f, #-1073741820	; 0xc0000004
0000000c <[^>]*> e32cf113 	msr	CPSR_fs, #-1073741820	; 0xc0000004
00000010 <[^>]*> e329f113 	msr	CPSR_fc, #-1073741820	; 0xc0000004
00000014 <[^>]*> e324f113 	msr	CPSR_s, #-1073741820	; 0xc0000004
00000018 <[^>]*> e328f113 	msr	CPSR_f, #-1073741820	; 0xc0000004
0000001c <[^>]*> e321f113 	msr	CPSR_c, #-1073741820	; 0xc0000004
00000020 <[^>]*> e322f113 	msr	CPSR_x, #-1073741820	; 0xc0000004
00000024 <[^>]*> e32cf113 	msr	CPSR_fs, #-1073741820	; 0xc0000004
00000028 <[^>]*> e32af113 	msr	CPSR_fx, #-1073741820	; 0xc0000004
0000002c <[^>]*> e329f113 	msr	CPSR_fc, #-1073741820	; 0xc0000004
00000030 <[^>]*> e32cf113 	msr	CPSR_fs, #-1073741820	; 0xc0000004
00000034 <[^>]*> e326f113 	msr	CPSR_sx, #-1073741820	; 0xc0000004
00000038 <[^>]*> e325f113 	msr	CPSR_sc, #-1073741820	; 0xc0000004
0000003c <[^>]*> e32af113 	msr	CPSR_fx, #-1073741820	; 0xc0000004
00000040 <[^>]*> e326f113 	msr	CPSR_sx, #-1073741820	; 0xc0000004
00000044 <[^>]*> e323f113 	msr	CPSR_xc, #-1073741820	; 0xc0000004
00000048 <[^>]*> e329f113 	msr	CPSR_fc, #-1073741820	; 0xc0000004
0000004c <[^>]*> e325f113 	msr	CPSR_sc, #-1073741820	; 0xc0000004
00000050 <[^>]*> e323f113 	msr	CPSR_xc, #-1073741820	; 0xc0000004
00000054 <[^>]*> e32ef113 	msr	CPSR_fsx, #-1073741820	; 0xc0000004
00000058 <[^>]*> e32df113 	msr	CPSR_fsc, #-1073741820	; 0xc0000004
0000005c <[^>]*> e32ef113 	msr	CPSR_fsx, #-1073741820	; 0xc0000004
00000060 <[^>]*> e32bf113 	msr	CPSR_fxc, #-1073741820	; 0xc0000004
00000064 <[^>]*> e32df113 	msr	CPSR_fsc, #-1073741820	; 0xc0000004
00000068 <[^>]*> e32bf113 	msr	CPSR_fxc, #-1073741820	; 0xc0000004
0000006c <[^>]*> e32ef113 	msr	CPSR_fsx, #-1073741820	; 0xc0000004
00000070 <[^>]*> e32df113 	msr	CPSR_fsc, #-1073741820	; 0xc0000004
00000074 <[^>]*> e32ef113 	msr	CPSR_fsx, #-1073741820	; 0xc0000004
00000078 <[^>]*> e327f113 	msr	CPSR_sxc, #-1073741820	; 0xc0000004
0000007c <[^>]*> e32df113 	msr	CPSR_fsc, #-1073741820	; 0xc0000004
00000080 <[^>]*> e327f113 	msr	CPSR_sxc, #-1073741820	; 0xc0000004
00000084 <[^>]*> e32ef113 	msr	CPSR_fsx, #-1073741820	; 0xc0000004
00000088 <[^>]*> e32bf113 	msr	CPSR_fxc, #-1073741820	; 0xc0000004
0000008c <[^>]*> e32ef113 	msr	CPSR_fsx, #-1073741820	; 0xc0000004
00000090 <[^>]*> e327f113 	msr	CPSR_sxc, #-1073741820	; 0xc0000004
00000094 <[^>]*> e32bf113 	msr	CPSR_fxc, #-1073741820	; 0xc0000004
00000098 <[^>]*> e327f113 	msr	CPSR_sxc, #-1073741820	; 0xc0000004
0000009c <[^>]*> e32df113 	msr	CPSR_fsc, #-1073741820	; 0xc0000004
000000a0 <[^>]*> e32bf113 	msr	CPSR_fxc, #-1073741820	; 0xc0000004
000000a4 <[^>]*> e32df113 	msr	CPSR_fsc, #-1073741820	; 0xc0000004
000000a8 <[^>]*> e327f113 	msr	CPSR_sxc, #-1073741820	; 0xc0000004
000000ac <[^>]*> e32bf113 	msr	CPSR_fxc, #-1073741820	; 0xc0000004
000000b0 <[^>]*> e327f113 	msr	CPSR_sxc, #-1073741820	; 0xc0000004
000000b4 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000b8 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000bc <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000c0 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000c4 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000c8 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000cc <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000d0 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000d4 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000d8 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000dc <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000e0 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000e4 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000e8 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000ec <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000f0 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000f4 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000f8 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
000000fc <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
00000100 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
00000104 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
00000108 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
0000010c <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
00000110 <[^>]*> e32ff113 	msr	CPSR_fsxc, #-1073741820	; 0xc0000004
00000114 <[^>]*> e369f113 	msr	SPSR_fc, #-1073741820	; 0xc0000004
00000118 <[^>]*> e364f113 	msr	SPSR_s, #-1073741820	; 0xc0000004
0000011c <[^>]*> e368f113 	msr	SPSR_f, #-1073741820	; 0xc0000004
00000120 <[^>]*> e361f113 	msr	SPSR_c, #-1073741820	; 0xc0000004
00000124 <[^>]*> e362f113 	msr	SPSR_x, #-1073741820	; 0xc0000004
00000128 <[^>]*> e36cf113 	msr	SPSR_fs, #-1073741820	; 0xc0000004
0000012c <[^>]*> e36af113 	msr	SPSR_fx, #-1073741820	; 0xc0000004
00000130 <[^>]*> e369f113 	msr	SPSR_fc, #-1073741820	; 0xc0000004
00000134 <[^>]*> e36cf113 	msr	SPSR_fs, #-1073741820	; 0xc0000004
00000138 <[^>]*> e366f113 	msr	SPSR_sx, #-1073741820	; 0xc0000004
0000013c <[^>]*> e365f113 	msr	SPSR_sc, #-1073741820	; 0xc0000004
00000140 <[^>]*> e36af113 	msr	SPSR_fx, #-1073741820	; 0xc0000004
00000144 <[^>]*> e366f113 	msr	SPSR_sx, #-1073741820	; 0xc0000004
00000148 <[^>]*> e363f113 	msr	SPSR_xc, #-1073741820	; 0xc0000004
0000014c <[^>]*> e369f113 	msr	SPSR_fc, #-1073741820	; 0xc0000004
00000150 <[^>]*> e365f113 	msr	SPSR_sc, #-1073741820	; 0xc0000004
00000154 <[^>]*> e363f113 	msr	SPSR_xc, #-1073741820	; 0xc0000004
00000158 <[^>]*> e36ef113 	msr	SPSR_fsx, #-1073741820	; 0xc0000004
0000015c <[^>]*> e36df113 	msr	SPSR_fsc, #-1073741820	; 0xc0000004
00000160 <[^>]*> e36ef113 	msr	SPSR_fsx, #-1073741820	; 0xc0000004
00000164 <[^>]*> e36bf113 	msr	SPSR_fxc, #-1073741820	; 0xc0000004
00000168 <[^>]*> e36df113 	msr	SPSR_fsc, #-1073741820	; 0xc0000004
0000016c <[^>]*> e36bf113 	msr	SPSR_fxc, #-1073741820	; 0xc0000004
00000170 <[^>]*> e36ef113 	msr	SPSR_fsx, #-1073741820	; 0xc0000004
00000174 <[^>]*> e36df113 	msr	SPSR_fsc, #-1073741820	; 0xc0000004
00000178 <[^>]*> e36ef113 	msr	SPSR_fsx, #-1073741820	; 0xc0000004
0000017c <[^>]*> e367f113 	msr	SPSR_sxc, #-1073741820	; 0xc0000004
00000180 <[^>]*> e36df113 	msr	SPSR_fsc, #-1073741820	; 0xc0000004
00000184 <[^>]*> e367f113 	msr	SPSR_sxc, #-1073741820	; 0xc0000004
00000188 <[^>]*> e36ef113 	msr	SPSR_fsx, #-1073741820	; 0xc0000004
0000018c <[^>]*> e36bf113 	msr	SPSR_fxc, #-1073741820	; 0xc0000004
00000190 <[^>]*> e36ef113 	msr	SPSR_fsx, #-1073741820	; 0xc0000004
00000194 <[^>]*> e367f113 	msr	SPSR_sxc, #-1073741820	; 0xc0000004
00000198 <[^>]*> e36bf113 	msr	SPSR_fxc, #-1073741820	; 0xc0000004
0000019c <[^>]*> e367f113 	msr	SPSR_sxc, #-1073741820	; 0xc0000004
000001a0 <[^>]*> e36df113 	msr	SPSR_fsc, #-1073741820	; 0xc0000004
000001a4 <[^>]*> e36bf113 	msr	SPSR_fxc, #-1073741820	; 0xc0000004
000001a8 <[^>]*> e36df113 	msr	SPSR_fsc, #-1073741820	; 0xc0000004
000001ac <[^>]*> e367f113 	msr	SPSR_sxc, #-1073741820	; 0xc0000004
000001b0 <[^>]*> e36bf113 	msr	SPSR_fxc, #-1073741820	; 0xc0000004
000001b4 <[^>]*> e367f113 	msr	SPSR_sxc, #-1073741820	; 0xc0000004
000001b8 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001bc <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001c0 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001c4 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001c8 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001cc <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001d0 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001d4 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001d8 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001dc <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001e0 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001e4 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001e8 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001ec <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001f0 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001f4 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001f8 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
000001fc <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
00000200 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
00000204 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
00000208 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
0000020c <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
00000210 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
00000214 <[^>]*> e36ff113 	msr	SPSR_fsxc, #-1073741820	; 0xc0000004
