#objdump: -dr
#as: -mfix-24k -32
#name: 24K: Triple Store (Opcode Check)
#source: 24k-triple-stores-1.s

.*: +file format .*mips.*

Disassembly of section \.text:

[0-9a-f]+ <.*>:
 *[0-9a-f]+:	185d 0000 	sb	v0,0\(sp\)
 *[0-9a-f]+:	187d 0008 	sb	v1,8\(sp\)
 *[0-9a-f]+:	189d 0010 	sb	a0,16\(sp\)
 *[0-9a-f]+:	18bd 0018 	sb	a1,24\(sp\)
 *[0-9a-f]+:	18dd 0020 	sb	a2,32\(sp\)
 *[0-9a-f]+:	385d 0000 	sh	v0,0\(sp\)
 *[0-9a-f]+:	387d 0008 	sh	v1,8\(sp\)
 *[0-9a-f]+:	389d 0010 	sh	a0,16\(sp\)
 *[0-9a-f]+:	38bd 0018 	sh	a1,24\(sp\)
 *[0-9a-f]+:	38dd 0020 	sh	a2,32\(sp\)
 *[0-9a-f]+:	c840      	sw	v0,0\(sp\)
 *[0-9a-f]+:	c862      	sw	v1,8\(sp\)
 *[0-9a-f]+:	c884      	sw	a0,16\(sp\)
 *[0-9a-f]+:	c8a6      	sw	a1,24\(sp\)
 *[0-9a-f]+:	c8c8      	sw	a2,32\(sp\)
 *[0-9a-f]+:	605d 9000 	swr	v0,0\(sp\)
 *[0-9a-f]+:	607d 9008 	swr	v1,8\(sp\)
 *[0-9a-f]+:	609d 9010 	swr	a0,16\(sp\)
 *[0-9a-f]+:	60bd 9018 	swr	a1,24\(sp\)
 *[0-9a-f]+:	60dd 9020 	swr	a2,32\(sp\)
 *[0-9a-f]+:	605d 8000 	swl	v0,0\(sp\)
 *[0-9a-f]+:	607d 8008 	swl	v1,8\(sp\)
 *[0-9a-f]+:	609d 8010 	swl	a0,16\(sp\)
 *[0-9a-f]+:	60bd 8018 	swl	a1,24\(sp\)
 *[0-9a-f]+:	60dd 8020 	swl	a2,32\(sp\)
 *[0-9a-f]+:	605d b000 	sc	v0,0\(sp\)
 *[0-9a-f]+:	607d b008 	sc	v1,8\(sp\)
 *[0-9a-f]+:	609d b010 	sc	a0,16\(sp\)
 *[0-9a-f]+:	60bd b018 	sc	a1,24\(sp\)
 *[0-9a-f]+:	60dd b020 	sc	a2,32\(sp\)
 *[0-9a-f]+:	985d 0000 	swc1	\$f2,0\(sp\)
 *[0-9a-f]+:	987d 0008 	swc1	\$f3,8\(sp\)
 *[0-9a-f]+:	989d 0010 	swc1	\$f4,16\(sp\)
 *[0-9a-f]+:	98bd 0018 	swc1	\$f5,24\(sp\)
 *[0-9a-f]+:	98dd 0020 	swc1	\$f6,32\(sp\)
 *[0-9a-f]+:	205d 8000 	swc2	\$2,0\(sp\)
 *[0-9a-f]+:	207d 8008 	swc2	\$3,8\(sp\)
 *[0-9a-f]+:	209d 8010 	swc2	\$4,16\(sp\)
 *[0-9a-f]+:	20bd 8018 	swc2	\$5,24\(sp\)
 *[0-9a-f]+:	20dd 8020 	swc2	\$6,32\(sp\)
 *[0-9a-f]+:	b85d 0000 	sdc1	\$f2,0\(sp\)
 *[0-9a-f]+:	b87d 0008 	sdc1	\$f3,8\(sp\)
 *[0-9a-f]+:	b89d 0010 	sdc1	\$f4,16\(sp\)
 *[0-9a-f]+:	b8bd 0018 	sdc1	\$f5,24\(sp\)
 *[0-9a-f]+:	b8dd 0020 	sdc1	\$f6,32\(sp\)
 *[0-9a-f]+:	205d a000 	sdc2	\$2,0\(sp\)
 *[0-9a-f]+:	207d a008 	sdc2	\$3,8\(sp\)
 *[0-9a-f]+:	209d a010 	sdc2	\$4,16\(sp\)
 *[0-9a-f]+:	20bd a018 	sdc2	\$5,24\(sp\)
 *[0-9a-f]+:	20dd a020 	sdc2	\$6,32\(sp\)
 *[0-9a-f]+:	5528 0048 	lwxc1	\$f0,t1\(t0\)
 *[0-9a-f]+:	5548 0848 	lwxc1	\$f1,t2\(t0\)
 *[0-9a-f]+:	5568 1048 	lwxc1	\$f2,t3\(t0\)
 *[0-9a-f]+:	5588 1848 	lwxc1	\$f3,t4\(t0\)
 *[0-9a-f]+:	55a8 2048 	lwxc1	\$f4,t5\(t0\)
 *[0-9a-f]+:	5528 0108 	sdxc1	\$f0,t1\(t0\)
 *[0-9a-f]+:	5548 1108 	sdxc1	\$f2,t2\(t0\)
 *[0-9a-f]+:	5568 2108 	sdxc1	\$f4,t3\(t0\)
 *[0-9a-f]+:	5588 3108 	sdxc1	\$f6,t4\(t0\)
 *[0-9a-f]+:	55a8 4108 	sdxc1	\$f8,t5\(t0\)
 *[0-9a-f]+:	5528 0188 	suxc1	\$f0,t1\(t0\)
 *[0-9a-f]+:	5548 1188 	suxc1	\$f2,t2\(t0\)
 *[0-9a-f]+:	5568 2188 	suxc1	\$f4,t3\(t0\)
 *[0-9a-f]+:	5588 3188 	suxc1	\$f6,t4\(t0\)
 *[0-9a-f]+:	55a8 4188 	suxc1	\$f8,t5\(t0\)
 *[0-9a-f]+:	0c00      	nop
	\.\.\.
