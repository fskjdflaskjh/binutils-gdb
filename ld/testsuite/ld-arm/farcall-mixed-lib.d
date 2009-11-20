tmpdir/farcall-mixed-lib.so:     file format elf32-(little|big)arm
architecture: arm, flags 0x00000150:
HAS_SYMS, DYNAMIC, D_PAGED
start address 0x.*

Disassembly of section .plt:

.* <.plt>:
 .*:	e52de004 	push	{lr}		; \(str lr, \[sp, #-4\]!\)
 .*:	e59fe004 	ldr	lr, \[pc, #4\]	; .* <lib_func1-0x.*>
 .*:	e08fe00e 	add	lr, pc, lr
 .*:	e5bef008 	ldr	pc, \[lr, #8\]!
 .*:	.*
 .*:	e28fc6.* 	add	ip, pc, #.*
 .*:	e28cca.* 	add	ip, ip, #.*	; 0x.*
 .*:	e5bcf.* 	ldr	pc, \[ip, #.*\]!.*
 .*:	e28fc6.* 	add	ip, pc, #.*
 .*:	e28cca.* 	add	ip, ip, #.*	; 0x.*
 .*:	e5bcf.* 	ldr	pc, \[ip, #.*\]!.*
 .*:	e28fc6.* 	add	ip, pc, #.*
 .*:	e28cca.* 	add	ip, ip, #.*	; 0x.*
 .*:	e5bcf.* 	ldr	pc, \[ip, #.*\]!.*
 .*:	e28fc6.* 	add	ip, pc, #.*
 .*:	e28cca.* 	add	ip, ip, #.*	; 0x.*
 .*:	e5bcf.* 	ldr	pc, \[ip, #.*\]!.*

Disassembly of section .text:

.* <lib_func1>:
 .*:	e1a0c00d 	mov	ip, sp
 .*:	e92dd800 	push	{fp, ip, lr, pc}
 .*:	ebffff.. 	bl	.* <lib_func1-0x..?>
 .*:	ebffff.. 	bl	.* <lib_func1-0x..?>
 .*:	ebfffff. 	bl	.* <lib_func1-0x..?>
 .*:	ebfffff. 	bl	.* <lib_func1-0x..?>
 .*:	e89d6800 	ldm	sp, {fp, sp, lr}
 .*:	e12fff1e 	bx	lr
	...

.* <lib_func2>:
 .*:	f000 e80e 	blx	1000320 <__app_func_from_thumb>
 .*:	f000 e81a 	blx	100033c <__app_func_weak_from_thumb>
 .*:	f000 e810 	blx	100032c <__lib_func3_veneer>
 .*:	f000 e81c 	blx	1000348 <__lib_func4_from_thumb>
 .*:	4770      	bx	lr
 .*:	46c0      	nop			; \(mov r8, r8\)
 .*:	46c0      	nop			; \(mov r8, r8\)
 .*:	46c0      	nop			; \(mov r8, r8\)
 .*:	46c0      	nop			; \(mov r8, r8\)
 .*:	46c0      	nop			; \(mov r8, r8\)
 .*:	46c0      	nop			; \(mov r8, r8\)
 .*:	46c0      	nop			; \(mov r8, r8\)

.* <__app_func_from_thumb>:
 .*:	e59fc000 	ldr	ip, \[pc, #0\]	; 1000328 <__app_func_from_thumb\+0x8>
 .*:	e08ff00c 	add	pc, pc, ip
 .*:	feffff78 	.word	0xfeffff78

.* <__lib_func3_veneer>:
 .*:	e59fc004 	ldr	ip, \[pc, #4\]	; 1000338 <__lib_func3_veneer\+0xc>
 .*:	e08fc00c 	add	ip, pc, ip
 .*:	e12fff1c 	bx	ip
 .*:	feffff85 	.word	0xfeffff85

.* <__app_func_weak_from_thumb>:
 .*:	e59fc000 	ldr	ip, \[pc, #0\]	; 1000344 <__app_func_weak_from_thumb\+0x8>
 .*:	e08ff00c 	add	pc, pc, ip
 .*:	feffff68 	.word	0xfeffff68

.* <__lib_func4_from_thumb>:
 .*:	e59fc000 	ldr	ip, \[pc, #0\]	; 1000350 <__lib_func4_from_thumb\+0x8>
 .*:	e08ff00c 	add	pc, pc, ip
 .*:	feffff74 	.word	0xfeffff74
	...

.* <lib_func3>:
 .*:	f000 e80c 	blx	200037c <__app_func_from_thumb>
 .*:	f000 e804 	blx	2000370 <__app_func_weak_from_thumb>
 .*:	4770      	bx	lr
 .*:	46c0      	nop			; \(mov r8, r8\)
 .*:	46c0      	nop			; \(mov r8, r8\)
 .*:	46c0      	nop			; \(mov r8, r8\)

.* <__app_func_weak_from_thumb>:
 .*:	e59fc000 	ldr	ip, \[pc, #0\]	; 2000378 <__app_func_weak_from_thumb\+0x8>
 .*:	e08ff00c 	add	pc, pc, ip
 .*:	fdffff34 	.word	0xfdffff34

.* <__app_func_from_thumb>:
 .*:	e59fc000 	ldr	ip, \[pc, #0\]	; 2000384 <__app_func_from_thumb\+0x8>
 .*:	e08ff00c 	add	pc, pc, ip
 .*:	fdffff1c 	.word	0xfdffff1c
	...
