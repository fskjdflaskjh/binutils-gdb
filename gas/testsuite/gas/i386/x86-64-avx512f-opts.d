#as:
#objdump: -dw -Msuffix
#name: x86_64 AVX512F opts insns

.*: +file format .*


Disassembly of section .text:

0+ <_start>:
[ 	]*[a-f0-9]+:	62 01 fd 48 29 ee    	vmovapd.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fd 48 28 f5    	vmovapd %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fd 4f 29 ee    	vmovapd.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fd 4f 28 f5    	vmovapd %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fd cf 29 ee    	vmovapd.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fd cf 28 f5    	vmovapd %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7c 48 29 ee    	vmovaps.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7c 48 28 f5    	vmovaps %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7c 4f 29 ee    	vmovaps.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7c 4f 28 f5    	vmovaps %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7c cf 29 ee    	vmovaps.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7c cf 28 f5    	vmovaps %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 61 7d 08 7e f0    	vmovd  %xmm30,%eax
[ 	]*[a-f0-9]+:	62 61 7d 08 7e f0    	vmovd  %xmm30,%eax
[ 	]*[a-f0-9]+:	62 61 7d 08 7e f5    	vmovd  %xmm30,%ebp
[ 	]*[a-f0-9]+:	62 61 7d 08 7e f5    	vmovd  %xmm30,%ebp
[ 	]*[a-f0-9]+:	62 41 7d 08 7e f5    	vmovd  %xmm30,%r13d
[ 	]*[a-f0-9]+:	62 41 7d 08 7e f5    	vmovd  %xmm30,%r13d
[ 	]*[a-f0-9]+:	62 01 7d 48 7f ee    	vmovdqa32.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7d 48 6f f5    	vmovdqa32 %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7d 4f 7f ee    	vmovdqa32.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7d 4f 6f f5    	vmovdqa32 %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7d cf 7f ee    	vmovdqa32.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7d cf 6f f5    	vmovdqa32 %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fd 48 7f ee    	vmovdqa64.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fd 48 6f f5    	vmovdqa64 %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fd 4f 7f ee    	vmovdqa64.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fd 4f 6f f5    	vmovdqa64 %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fd cf 7f ee    	vmovdqa64.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fd cf 6f f5    	vmovdqa64 %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7e 48 7f ee    	vmovdqu32.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7e 48 6f f5    	vmovdqu32 %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7e 4f 7f ee    	vmovdqu32.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7e 4f 6f f5    	vmovdqu32 %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7e cf 7f ee    	vmovdqu32.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7e cf 6f f5    	vmovdqu32 %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fe 48 7f ee    	vmovdqu64.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fe 48 6f f5    	vmovdqu64 %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fe 4f 7f ee    	vmovdqu64.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fe 4f 6f f5    	vmovdqu64 %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fe cf 7f ee    	vmovdqu64.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fe cf 6f f5    	vmovdqu64 %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 61 fd 08 7e f0    	vmovq  %xmm30,%rax
[ 	]*[a-f0-9]+:	62 61 fd 08 7e f0    	vmovq  %xmm30,%rax
[ 	]*[a-f0-9]+:	62 41 fd 08 7e f0    	vmovq  %xmm30,%r8
[ 	]*[a-f0-9]+:	62 41 fd 08 7e f0    	vmovq  %xmm30,%r8
[ 	]*[a-f0-9]+:	62 01 fd 08 d6 ee    	vmovq  %xmm29,%xmm30
[ 	]*[a-f0-9]+:	62 01 fe 08 7e f5    	vmovq  %xmm29,%xmm30
[ 	]*[a-f0-9]+:	62 01 97 07 11 e6    	vmovsd.s %xmm28,%xmm29,%xmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 97 07 10 f4    	vmovsd %xmm28,%xmm29,%xmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 97 87 11 e6    	vmovsd.s %xmm28,%xmm29,%xmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 97 87 10 f4    	vmovsd %xmm28,%xmm29,%xmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 16 07 11 e6    	vmovss.s %xmm28,%xmm29,%xmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 16 07 10 f4    	vmovss %xmm28,%xmm29,%xmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 16 87 11 e6    	vmovss.s %xmm28,%xmm29,%xmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 16 87 10 f4    	vmovss %xmm28,%xmm29,%xmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fd 48 11 ee    	vmovupd.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fd 48 10 f5    	vmovupd %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fd 4f 11 ee    	vmovupd.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fd 4f 10 f5    	vmovupd %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fd cf 11 ee    	vmovupd.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fd cf 10 f5    	vmovupd %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7c 48 11 ee    	vmovups.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7c 48 10 f5    	vmovups %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7c 4f 11 ee    	vmovups.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7c 4f 10 f5    	vmovups %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7c cf 11 ee    	vmovups.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7c cf 10 f5    	vmovups %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fd 48 29 ee    	vmovapd.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fd 48 28 f5    	vmovapd %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fd 4f 29 ee    	vmovapd.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fd 4f 28 f5    	vmovapd %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fd cf 29 ee    	vmovapd.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fd cf 28 f5    	vmovapd %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7c 48 29 ee    	vmovaps.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7c 48 28 f5    	vmovaps %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7c 4f 29 ee    	vmovaps.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7c 4f 28 f5    	vmovaps %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7c cf 29 ee    	vmovaps.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7c cf 28 f5    	vmovaps %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 61 7d 08 7e f0    	vmovd  %xmm30,%eax
[ 	]*[a-f0-9]+:	62 61 7d 08 7e f0    	vmovd  %xmm30,%eax
[ 	]*[a-f0-9]+:	62 61 7d 08 7e f5    	vmovd  %xmm30,%ebp
[ 	]*[a-f0-9]+:	62 61 7d 08 7e f5    	vmovd  %xmm30,%ebp
[ 	]*[a-f0-9]+:	62 41 7d 08 7e f5    	vmovd  %xmm30,%r13d
[ 	]*[a-f0-9]+:	62 41 7d 08 7e f5    	vmovd  %xmm30,%r13d
[ 	]*[a-f0-9]+:	62 01 7d 48 7f ee    	vmovdqa32.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7d 48 6f f5    	vmovdqa32 %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7d 4f 7f ee    	vmovdqa32.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7d 4f 6f f5    	vmovdqa32 %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7d cf 7f ee    	vmovdqa32.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7d cf 6f f5    	vmovdqa32 %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fd 48 7f ee    	vmovdqa64.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fd 48 6f f5    	vmovdqa64 %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fd 4f 7f ee    	vmovdqa64.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fd 4f 6f f5    	vmovdqa64 %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fd cf 7f ee    	vmovdqa64.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fd cf 6f f5    	vmovdqa64 %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7e 48 7f ee    	vmovdqu32.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7e 48 6f f5    	vmovdqu32 %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7e 4f 7f ee    	vmovdqu32.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7e 4f 6f f5    	vmovdqu32 %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7e cf 7f ee    	vmovdqu32.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7e cf 6f f5    	vmovdqu32 %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fe 48 7f ee    	vmovdqu64.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fe 48 6f f5    	vmovdqu64 %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fe 4f 7f ee    	vmovdqu64.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fe 4f 6f f5    	vmovdqu64 %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fe cf 7f ee    	vmovdqu64.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fe cf 6f f5    	vmovdqu64 %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 61 fd 08 7e f0    	vmovq  %xmm30,%rax
[ 	]*[a-f0-9]+:	62 61 fd 08 7e f0    	vmovq  %xmm30,%rax
[ 	]*[a-f0-9]+:	62 41 fd 08 7e f0    	vmovq  %xmm30,%r8
[ 	]*[a-f0-9]+:	62 41 fd 08 7e f0    	vmovq  %xmm30,%r8
[ 	]*[a-f0-9]+:	62 01 fd 08 d6 ee    	vmovq  %xmm29,%xmm30
[ 	]*[a-f0-9]+:	62 01 fe 08 7e f5    	vmovq  %xmm29,%xmm30
[ 	]*[a-f0-9]+:	62 01 97 07 11 e6    	vmovsd.s %xmm28,%xmm29,%xmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 97 07 10 f4    	vmovsd %xmm28,%xmm29,%xmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 97 87 11 e6    	vmovsd.s %xmm28,%xmm29,%xmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 97 87 10 f4    	vmovsd %xmm28,%xmm29,%xmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 16 07 11 e6    	vmovss.s %xmm28,%xmm29,%xmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 16 07 10 f4    	vmovss %xmm28,%xmm29,%xmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 16 87 11 e6    	vmovss.s %xmm28,%xmm29,%xmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 16 87 10 f4    	vmovss %xmm28,%xmm29,%xmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fd 48 11 ee    	vmovupd.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fd 48 10 f5    	vmovupd %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 fd 4f 11 ee    	vmovupd.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fd 4f 10 f5    	vmovupd %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 fd cf 11 ee    	vmovupd.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 fd cf 10 f5    	vmovupd %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7c 48 11 ee    	vmovups.s %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7c 48 10 f5    	vmovups %zmm29,%zmm30
[ 	]*[a-f0-9]+:	62 01 7c 4f 11 ee    	vmovups.s %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7c 4f 10 f5    	vmovups %zmm29,%zmm30\{%k7\}
[ 	]*[a-f0-9]+:	62 01 7c cf 11 ee    	vmovups.s %zmm29,%zmm30\{%k7\}\{z\}
[ 	]*[a-f0-9]+:	62 01 7c cf 10 f5    	vmovups %zmm29,%zmm30\{%k7\}\{z\}
#pass
