! Generated file. DO NOT EDIT.
!
! This file was generated by gas/testsuite/gas/sh/arch/arch.exp .
! This file should contain every instruction valid on
! architecture sh4a-nofpu but no more.
! If the tests are failing because the expected results
! have changed then run 'make check' and copy the new file
! from <objdir>/gas/testsuite/sh4a-nofpu.s
! to   <srcdir>/gas/testsuite/gas/sh/arch/sh4a-nofpu.s .
! Make sure there are no unexpected or missing instructions.

	.section .text
sh4a_nofpu:
! Instructions introduced into sh4a-nofpu
	icbi @r4                  ;!/* 0000nnnn11100011 icbi @<REG_N>       */{"icbi",{A_IND_N},{HEX_0,REG_N,HEX_E,HEX_3}, arch_sh4a_nofpu_up}
	movco.l r0,@r4            ;!/* 0000nnnn01110011 movco.l r0,@<REG_N> */{"movco.l",{A_R0,A_IND_N},{HEX_0,REG_N,HEX_7,HEX_3}, arch_sh4a_nofpu_up}
	movli.l @r5,r0            ;!/* 0000mmmm01100011 movli.l @<REG_M>,r0 */{"movli.l",{A_IND_M,A_R0},{HEX_0,REG_M,HEX_6,HEX_3}, arch_sh4a_nofpu_up}
	movua.l @r5,r0            ;!/* 0100mmmm10101001 movua.l @<REG_M>,r0 */{"movua.l",{A_IND_M,A_R0},{HEX_4,REG_M,HEX_A,HEX_9}, arch_sh4a_nofpu_up}
	movua.l @r5+,r0           ;!/* 0100mmmm11101001 movua.l @<REG_M>+,r0 */{"movua.l",{A_INC_M,A_R0},{HEX_4,REG_M,HEX_E,HEX_9}, arch_sh4a_nofpu_up}
	prefi @r4                 ;!/* 0000nnnn11010011 prefi @<REG_N>      */{"prefi",{A_IND_N},{HEX_0,REG_N,HEX_D,HEX_3}, arch_sh4a_nofpu_up}
	synco                     ;!/* 0000000010101011 synco               */{"synco",{0},{HEX_0,HEX_0,HEX_A,HEX_B}, arch_sh4a_nofpu_up}

! Instructions inherited from ancestors: sh sh2 sh2a-nofpu-or-sh3-nommu sh2a-nofpu-or-sh4-nommu-nofpu sh3 sh3-nommu sh4-nofpu sh4-nommu-nofpu
	add #4,r4                 ;!/* 0111nnnni8*1.... add #<imm>,<REG_N>  */{"add",{A_IMM,A_REG_N},{HEX_7,REG_N,IMM0_8}, arch_sh_up}
	add r5,r4                 ;!/* 0011nnnnmmmm1100 add <REG_M>,<REG_N> */{"add",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_C}, arch_sh_up}
	addc r5,r4                ;!/* 0011nnnnmmmm1110 addc <REG_M>,<REG_N>*/{"addc",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_E}, arch_sh_up}
	addv r5,r4                ;!/* 0011nnnnmmmm1111 addv <REG_M>,<REG_N>*/{"addv",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_F}, arch_sh_up}
	and #4,R0                 ;!/* 11001001i8*1.... and #<imm>,R0       */{"and",{A_IMM,A_R0},{HEX_C,HEX_9,IMM0_8}, arch_sh_up}
	and r5,r4                 ;!/* 0010nnnnmmmm1001 and <REG_M>,<REG_N> */{"and",{ A_REG_M,A_REG_N},{HEX_2,REG_N,REG_M,HEX_9}, arch_sh_up}
	and.b #4,@(R0,GBR)        ;!/* 11001101i8*1.... and.b #<imm>,@(R0,GBR)*/{"and.b",{A_IMM,A_R0_GBR},{HEX_C,HEX_D,IMM0_8}, arch_sh_up}
	bra .+8                   ;!/* 1010i12......... bra <bdisp12>       */{"bra",{A_BDISP12},{HEX_A,BRANCH_12}, arch_sh_up}
	bsr .+8                   ;!/* 1011i12......... bsr <bdisp12>       */{"bsr",{A_BDISP12},{HEX_B,BRANCH_12}, arch_sh_up}
	bt .+8                    ;!/* 10001001i8p1.... bt <bdisp8>         */{"bt",{A_BDISP8},{HEX_8,HEX_9,BRANCH_8}, arch_sh_up}
	bf .+8                    ;!/* 10001011i8p1.... bf <bdisp8>         */{"bf",{A_BDISP8},{HEX_8,HEX_B,BRANCH_8}, arch_sh_up}
	bt.s .+8                  ;!/* 10001101i8p1.... bt.s <bdisp8>       */{"bt.s",{A_BDISP8},{HEX_8,HEX_D,BRANCH_8}, arch_sh2_up}
	bt/s .+8                  ;!/* 10001101i8p1.... bt/s <bdisp8>       */{"bt/s",{A_BDISP8},{HEX_8,HEX_D,BRANCH_8}, arch_sh2_up}
	bf.s .+8                  ;!/* 10001111i8p1.... bf.s <bdisp8>       */{"bf.s",{A_BDISP8},{HEX_8,HEX_F,BRANCH_8}, arch_sh2_up}
	bf/s .+8                  ;!/* 10001111i8p1.... bf/s <bdisp8>       */{"bf/s",{A_BDISP8},{HEX_8,HEX_F,BRANCH_8}, arch_sh2_up}
	clrmac                    ;!/* 0000000000101000 clrmac              */{"clrmac",{0},{HEX_0,HEX_0,HEX_2,HEX_8}, arch_sh_up}
	clrs                      ;!/* 0000000001001000 clrs                */{"clrs",{0},{HEX_0,HEX_0,HEX_4,HEX_8}, arch_sh_up}
	clrt                      ;!/* 0000000000001000 clrt                */{"clrt",{0},{HEX_0,HEX_0,HEX_0,HEX_8}, arch_sh_up}
	cmp/eq #4,R0              ;!/* 10001000i8*1.... cmp/eq #<imm>,R0    */{"cmp/eq",{A_IMM,A_R0},{HEX_8,HEX_8,IMM0_8}, arch_sh_up}
	cmp/eq r5,r4              ;!/* 0011nnnnmmmm0000 cmp/eq <REG_M>,<REG_N>*/{"cmp/eq",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_0}, arch_sh_up}
	cmp/ge r5,r4              ;!/* 0011nnnnmmmm0011 cmp/ge <REG_M>,<REG_N>*/{"cmp/ge",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_3}, arch_sh_up}
	cmp/gt r5,r4              ;!/* 0011nnnnmmmm0111 cmp/gt <REG_M>,<REG_N>*/{"cmp/gt",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_7}, arch_sh_up}
	cmp/hi r5,r4              ;!/* 0011nnnnmmmm0110 cmp/hi <REG_M>,<REG_N>*/{"cmp/hi",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_6}, arch_sh_up}
	cmp/hs r5,r4              ;!/* 0011nnnnmmmm0010 cmp/hs <REG_M>,<REG_N>*/{"cmp/hs",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_2}, arch_sh_up}
	cmp/pl r4                 ;!/* 0100nnnn00010101 cmp/pl <REG_N>      */{"cmp/pl",{A_REG_N},{HEX_4,REG_N,HEX_1,HEX_5}, arch_sh_up}
	cmp/pz r4                 ;!/* 0100nnnn00010001 cmp/pz <REG_N>      */{"cmp/pz",{A_REG_N},{HEX_4,REG_N,HEX_1,HEX_1}, arch_sh_up}
	cmp/str r5,r4             ;!/* 0010nnnnmmmm1100 cmp/str <REG_M>,<REG_N>*/{"cmp/str",{ A_REG_M,A_REG_N},{HEX_2,REG_N,REG_M,HEX_C}, arch_sh_up}
	div0s r5,r4               ;!/* 0010nnnnmmmm0111 div0s <REG_M>,<REG_N>*/{"div0s",{ A_REG_M,A_REG_N},{HEX_2,REG_N,REG_M,HEX_7}, arch_sh_up}
	div0u                     ;!/* 0000000000011001 div0u               */{"div0u",{0},{HEX_0,HEX_0,HEX_1,HEX_9}, arch_sh_up}
	div1 r5,r4                ;!/* 0011nnnnmmmm0100 div1 <REG_M>,<REG_N>*/{"div1",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_4}, arch_sh_up}
	exts.b r5,r4              ;!/* 0110nnnnmmmm1110 exts.b <REG_M>,<REG_N>*/{"exts.b",{ A_REG_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_E}, arch_sh_up}
	exts.w r5,r4              ;!/* 0110nnnnmmmm1111 exts.w <REG_M>,<REG_N>*/{"exts.w",{ A_REG_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_F}, arch_sh_up}
	extu.b r5,r4              ;!/* 0110nnnnmmmm1100 extu.b <REG_M>,<REG_N>*/{"extu.b",{ A_REG_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_C}, arch_sh_up}
	extu.w r5,r4              ;!/* 0110nnnnmmmm1101 extu.w <REG_M>,<REG_N>*/{"extu.w",{ A_REG_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_D}, arch_sh_up}
	jmp @r4                   ;!/* 0100nnnn00101011 jmp @<REG_N>        */{"jmp",{A_IND_N},{HEX_4,REG_N,HEX_2,HEX_B}, arch_sh_up}
	jsr @r4                   ;!/* 0100nnnn00001011 jsr @<REG_N>        */{"jsr",{A_IND_N},{HEX_4,REG_N,HEX_0,HEX_B}, arch_sh_up}
	ldc r4,SR                 ;!/* 0100nnnn00001110 ldc <REG_N>,SR      */{"ldc",{A_REG_N,A_SR},{HEX_4,REG_N,HEX_0,HEX_E}, arch_sh_up}
	ldc r4,GBR                ;!/* 0100nnnn00011110 ldc <REG_N>,GBR     */{"ldc",{A_REG_N,A_GBR},{HEX_4,REG_N,HEX_1,HEX_E}, arch_sh_up}
	ldc r4,SGR                ;!/* 0100nnnn00111010 ldc <REG_N>,SGR     */{"ldc",{A_REG_N,A_SGR},{HEX_4,REG_N,HEX_3,HEX_A}, arch_sh4_nommu_nofpu_up}
	ldc r4,VBR                ;!/* 0100nnnn00101110 ldc <REG_N>,VBR     */{"ldc",{A_REG_N,A_VBR},{HEX_4,REG_N,HEX_2,HEX_E}, arch_sh_up}
	ldc r4,SSR                ;!/* 0100nnnn00111110 ldc <REG_N>,SSR     */{"ldc",{A_REG_N,A_SSR},{HEX_4,REG_N,HEX_3,HEX_E}, arch_sh3_nommu_up}
	ldc r4,SPC                ;!/* 0100nnnn01001110 ldc <REG_N>,SPC     */{"ldc",{A_REG_N,A_SPC},{HEX_4,REG_N,HEX_4,HEX_E}, arch_sh3_nommu_up}
	ldc r4,DBR                ;!/* 0100nnnn11111010 ldc <REG_N>,DBR     */{"ldc",{A_REG_N,A_DBR},{HEX_4,REG_N,HEX_F,HEX_A}, arch_sh4_nommu_nofpu_up}
	ldc r4,r1_bank            ;!/* 0100nnnn1xxx1110 ldc <REG_N>,Rn_BANK */{"ldc",{A_REG_N,A_REG_B},{HEX_4,REG_N,REG_B,HEX_E}, arch_sh3_nommu_up}
	ldc.l @r4+,SR             ;!/* 0100nnnn00000111 ldc.l @<REG_N>+,SR  */{"ldc.l",{A_INC_N,A_SR},{HEX_4,REG_N,HEX_0,HEX_7}, arch_sh_up}
	ldc.l @r4+,GBR            ;!/* 0100nnnn00010111 ldc.l @<REG_N>+,GBR */{"ldc.l",{A_INC_N,A_GBR},{HEX_4,REG_N,HEX_1,HEX_7}, arch_sh_up}
	ldc.l @r4+,VBR            ;!/* 0100nnnn00100111 ldc.l @<REG_N>+,VBR */{"ldc.l",{A_INC_N,A_VBR},{HEX_4,REG_N,HEX_2,HEX_7}, arch_sh_up}
	ldc.l @r4+,SGR            ;!/* 0100nnnn00110110 ldc.l @<REG_N>+,SGR */{"ldc.l",{A_INC_N,A_SGR},{HEX_4,REG_N,HEX_3,HEX_6}, arch_sh4_nommu_nofpu_up}
	ldc.l @r4+,SSR            ;!/* 0100nnnn00110111 ldc.l @<REG_N>+,SSR */{"ldc.l",{A_INC_N,A_SSR},{HEX_4,REG_N,HEX_3,HEX_7}, arch_sh3_nommu_up}
	ldc.l @r4+,SPC            ;!/* 0100nnnn01000111 ldc.l @<REG_N>+,SPC */{"ldc.l",{A_INC_N,A_SPC},{HEX_4,REG_N,HEX_4,HEX_7}, arch_sh3_nommu_up}
	ldc.l @r4+,DBR            ;!/* 0100nnnn11110110 ldc.l @<REG_N>+,DBR */{"ldc.l",{A_INC_N,A_DBR},{HEX_4,REG_N,HEX_F,HEX_6}, arch_sh4_nommu_nofpu_up}
	ldc.l @r4+,r1_bank        ;!/* 0100nnnn1xxx0111 ldc.l @<REG_N>+,Rn_BANK */{"ldc.l",{A_INC_N,A_REG_B},{HEX_4,REG_N,REG_B,HEX_7}, arch_sh3_nommu_up}
	lds r4,MACH               ;!/* 0100nnnn00001010 lds <REG_N>,MACH    */{"lds",{A_REG_N,A_MACH},{HEX_4,REG_N,HEX_0,HEX_A}, arch_sh_up}
	lds r4,MACL               ;!/* 0100nnnn00011010 lds <REG_N>,MACL    */{"lds",{A_REG_N,A_MACL},{HEX_4,REG_N,HEX_1,HEX_A}, arch_sh_up}
	lds r4,PR                 ;!/* 0100nnnn00101010 lds <REG_N>,PR      */{"lds",{A_REG_N,A_PR},{HEX_4,REG_N,HEX_2,HEX_A}, arch_sh_up}
	lds.l @r4+,MACH           ;!/* 0100nnnn00000110 lds.l @<REG_N>+,MACH*/{"lds.l",{A_INC_N,A_MACH},{HEX_4,REG_N,HEX_0,HEX_6}, arch_sh_up}
	lds.l @r4+,MACL           ;!/* 0100nnnn00010110 lds.l @<REG_N>+,MACL*/{"lds.l",{A_INC_N,A_MACL},{HEX_4,REG_N,HEX_1,HEX_6}, arch_sh_up}
	lds.l @r4+,PR             ;!/* 0100nnnn00100110 lds.l @<REG_N>+,PR  */{"lds.l",{A_INC_N,A_PR},{HEX_4,REG_N,HEX_2,HEX_6}, arch_sh_up}
	ldtlb                     ;!/* 0000000000111000 ldtlb               */{"ldtlb",{0},{HEX_0,HEX_0,HEX_3,HEX_8}, arch_sh3_up}
	mac.w @r5+,@r4+           ;!/* 0100nnnnmmmm1111 mac.w @<REG_M>+,@<REG_N>+*/{"mac.w",{A_INC_M,A_INC_N},{HEX_4,REG_N,REG_M,HEX_F}, arch_sh_up}
	mov #4,r4                 ;!/* 1110nnnni8*1.... mov #<imm>,<REG_N>  */{"mov",{A_IMM,A_REG_N},{HEX_E,REG_N,IMM0_8}, arch_sh_up}
	mov r5,r4                 ;!/* 0110nnnnmmmm0011 mov <REG_M>,<REG_N> */{"mov",{ A_REG_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_3}, arch_sh_up}
	mov.b r5,@(R0,r4)         ;!/* 0000nnnnmmmm0100 mov.b <REG_M>,@(R0,<REG_N>)*/{"mov.b",{ A_REG_M,A_IND_R0_REG_N},{HEX_0,REG_N,REG_M,HEX_4}, arch_sh_up}
	mov.b r5,@-r4             ;!/* 0010nnnnmmmm0100 mov.b <REG_M>,@-<REG_N>*/{"mov.b",{ A_REG_M,A_DEC_N},{HEX_2,REG_N,REG_M,HEX_4}, arch_sh_up}
	mov.b r5,@r4              ;!/* 0010nnnnmmmm0000 mov.b <REG_M>,@<REG_N>*/{"mov.b",{ A_REG_M,A_IND_N},{HEX_2,REG_N,REG_M,HEX_0}, arch_sh_up}
	mov.b @(8,r5),R0          ;!/* 10000100mmmmi4*1 mov.b @(<disp>,<REG_M>),R0*/{"mov.b",{A_DISP_REG_M,A_R0},{HEX_8,HEX_4,REG_M,IMM0_4}, arch_sh_up}
	mov.b @(8,GBR),R0         ;!/* 11000100i8*1.... mov.b @(<disp>,GBR),R0*/{"mov.b",{A_DISP_GBR,A_R0},{HEX_C,HEX_4,IMM0_8}, arch_sh_up}
	mov.b @(R0,r5),r4         ;!/* 0000nnnnmmmm1100 mov.b @(R0,<REG_M>),<REG_N>*/{"mov.b",{A_IND_R0_REG_M,A_REG_N},{HEX_0,REG_N,REG_M,HEX_C}, arch_sh_up}
	mov.b @r5+,r4             ;!/* 0110nnnnmmmm0100 mov.b @<REG_M>+,<REG_N>*/{"mov.b",{A_INC_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_4}, arch_sh_up}
	mov.b @r5,r4              ;!/* 0110nnnnmmmm0000 mov.b @<REG_M>,<REG_N>*/{"mov.b",{A_IND_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_0}, arch_sh_up}
	mov.b R0,@(8,r5)          ;!/* 10000000mmmmi4*1 mov.b R0,@(<disp>,<REG_M>)*/{"mov.b",{A_R0,A_DISP_REG_M},{HEX_8,HEX_0,REG_M,IMM1_4}, arch_sh_up}
	mov.b R0,@(8,GBR)         ;!/* 11000000i8*1.... mov.b R0,@(<disp>,GBR)*/{"mov.b",{A_R0,A_DISP_GBR},{HEX_C,HEX_0,IMM1_8}, arch_sh_up}
	mov.l r5,@(8,r4)          ;!/* 0001nnnnmmmmi4*4 mov.l <REG_M>,@(<disp>,<REG_N>)*/{"mov.l",{ A_REG_M,A_DISP_REG_N},{HEX_1,REG_N,REG_M,IMM1_4BY4}, arch_sh_up}
	mov.l r5,@(R0,r4)         ;!/* 0000nnnnmmmm0110 mov.l <REG_M>,@(R0,<REG_N>)*/{"mov.l",{ A_REG_M,A_IND_R0_REG_N},{HEX_0,REG_N,REG_M,HEX_6}, arch_sh_up}
	mov.l r5,@-r4             ;!/* 0010nnnnmmmm0110 mov.l <REG_M>,@-<REG_N>*/{"mov.l",{ A_REG_M,A_DEC_N},{HEX_2,REG_N,REG_M,HEX_6}, arch_sh_up}
	mov.l r5,@r4              ;!/* 0010nnnnmmmm0010 mov.l <REG_M>,@<REG_N>*/{"mov.l",{ A_REG_M,A_IND_N},{HEX_2,REG_N,REG_M,HEX_2}, arch_sh_up}
	mov.l @(8,r5),r4          ;!/* 0101nnnnmmmmi4*4 mov.l @(<disp>,<REG_M>),<REG_N>*/{"mov.l",{A_DISP_REG_M,A_REG_N},{HEX_5,REG_N,REG_M,IMM0_4BY4}, arch_sh_up}
	mov.l @(8,GBR),R0         ;!/* 11000110i8*4.... mov.l @(<disp>,GBR),R0*/{"mov.l",{A_DISP_GBR,A_R0},{HEX_C,HEX_6,IMM0_8BY4}, arch_sh_up}
	.align 2
	mov.l @(8,PC),r4 ;!/* 1101nnnni8p4.... mov.l @(<disp>,PC),<REG_N>*/{"mov.l",{A_DISP_PC,A_REG_N},{HEX_D,REG_N,PCRELIMM_8BY4}, arch_sh_up}
	mov.l @(R0,r5),r4         ;!/* 0000nnnnmmmm1110 mov.l @(R0,<REG_M>),<REG_N>*/{"mov.l",{A_IND_R0_REG_M,A_REG_N},{HEX_0,REG_N,REG_M,HEX_E}, arch_sh_up}
	mov.l @r5+,r4             ;!/* 0110nnnnmmmm0110 mov.l @<REG_M>+,<REG_N>*/{"mov.l",{A_INC_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_6}, arch_sh_up}
	mov.l @r5,r4              ;!/* 0110nnnnmmmm0010 mov.l @<REG_M>,<REG_N>*/{"mov.l",{A_IND_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_2}, arch_sh_up}
	mov.l R0,@(8,GBR)         ;!/* 11000010i8*4.... mov.l R0,@(<disp>,GBR)*/{"mov.l",{A_R0,A_DISP_GBR},{HEX_C,HEX_2,IMM1_8BY4}, arch_sh_up}
	mov.w r5,@(R0,r4)         ;!/* 0000nnnnmmmm0101 mov.w <REG_M>,@(R0,<REG_N>)*/{"mov.w",{ A_REG_M,A_IND_R0_REG_N},{HEX_0,REG_N,REG_M,HEX_5}, arch_sh_up}
	mov.w r5,@-r4             ;!/* 0010nnnnmmmm0101 mov.w <REG_M>,@-<REG_N>*/{"mov.w",{ A_REG_M,A_DEC_N},{HEX_2,REG_N,REG_M,HEX_5}, arch_sh_up}
	mov.w r5,@r4              ;!/* 0010nnnnmmmm0001 mov.w <REG_M>,@<REG_N>*/{"mov.w",{ A_REG_M,A_IND_N},{HEX_2,REG_N,REG_M,HEX_1}, arch_sh_up}
	mov.w @(8,r5),R0          ;!/* 10000101mmmmi4*2 mov.w @(<disp>,<REG_M>),R0*/{"mov.w",{A_DISP_REG_M,A_R0},{HEX_8,HEX_5,REG_M,IMM0_4BY2}, arch_sh_up}
	mov.w @(8,GBR),R0         ;!/* 11000101i8*2.... mov.w @(<disp>,GBR),R0*/{"mov.w",{A_DISP_GBR,A_R0},{HEX_C,HEX_5,IMM0_8BY2}, arch_sh_up}
	mov.w @(8,PC),r4          ;!/* 1001nnnni8p2.... mov.w @(<disp>,PC),<REG_N>*/{"mov.w",{A_DISP_PC,A_REG_N},{HEX_9,REG_N,PCRELIMM_8BY2}, arch_sh_up}
	mov.w @(R0,r5),r4         ;!/* 0000nnnnmmmm1101 mov.w @(R0,<REG_M>),<REG_N>*/{"mov.w",{A_IND_R0_REG_M,A_REG_N},{HEX_0,REG_N,REG_M,HEX_D}, arch_sh_up}
	mov.w @r5+,r4             ;!/* 0110nnnnmmmm0101 mov.w @<REG_M>+,<REG_N>*/{"mov.w",{A_INC_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_5}, arch_sh_up}
	mov.w @r5,r4              ;!/* 0110nnnnmmmm0001 mov.w @<REG_M>,<REG_N>*/{"mov.w",{A_IND_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_1}, arch_sh_up}
	mov.w R0,@(8,r5)          ;!/* 10000001mmmmi4*2 mov.w R0,@(<disp>,<REG_M>)*/{"mov.w",{A_R0,A_DISP_REG_M},{HEX_8,HEX_1,REG_M,IMM1_4BY2}, arch_sh_up}
	mov.w R0,@(8,GBR)         ;!/* 11000001i8*2.... mov.w R0,@(<disp>,GBR)*/{"mov.w",{A_R0,A_DISP_GBR},{HEX_C,HEX_1,IMM1_8BY2}, arch_sh_up}
	.align 2
	mova @(8,PC),R0 ;!/* 11000111i8p4.... mova @(<disp>,PC),R0*/{"mova",{A_DISP_PC,A_R0},{HEX_C,HEX_7,PCRELIMM_8BY4}, arch_sh_up}
	movca.l R0,@r4            ;!/* 0000nnnn11000011 movca.l R0,@<REG_N> */{"movca.l",{A_R0,A_IND_N},{HEX_0,REG_N,HEX_C,HEX_3}, arch_sh4_nommu_nofpu_up}
	movt r4                   ;!/* 0000nnnn00101001 movt <REG_N>        */{"movt",{A_REG_N},{HEX_0,REG_N,HEX_2,HEX_9}, arch_sh_up}
	muls.w r5,r4              ;!/* 0010nnnnmmmm1111 muls.w <REG_M>,<REG_N>*/{"muls.w",{ A_REG_M,A_REG_N},{HEX_2,REG_N,REG_M,HEX_F}, arch_sh_up}
	muls r5,r4                ;!/* 0010nnnnmmmm1111 muls <REG_M>,<REG_N>*/{"muls",{ A_REG_M,A_REG_N},{HEX_2,REG_N,REG_M,HEX_F}, arch_sh_up}
	mul.l r5,r4               ;!/* 0000nnnnmmmm0111 mul.l <REG_M>,<REG_N>*/{"mul.l",{ A_REG_M,A_REG_N},{HEX_0,REG_N,REG_M,HEX_7}, arch_sh2_up}
	mulu.w r5,r4              ;!/* 0010nnnnmmmm1110 mulu.w <REG_M>,<REG_N>*/{"mulu.w",{ A_REG_M,A_REG_N},{HEX_2,REG_N,REG_M,HEX_E}, arch_sh_up}
	mulu r5,r4                ;!/* 0010nnnnmmmm1110 mulu <REG_M>,<REG_N>*/{"mulu",{ A_REG_M,A_REG_N},{HEX_2,REG_N,REG_M,HEX_E}, arch_sh_up}
	neg r5,r4                 ;!/* 0110nnnnmmmm1011 neg <REG_M>,<REG_N> */{"neg",{ A_REG_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_B}, arch_sh_up}
	negc r5,r4                ;!/* 0110nnnnmmmm1010 negc <REG_M>,<REG_N>*/{"negc",{ A_REG_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_A}, arch_sh_up}
	nop                       ;!/* 0000000000001001 nop                 */{"nop",{0},{HEX_0,HEX_0,HEX_0,HEX_9}, arch_sh_up}
	not r5,r4                 ;!/* 0110nnnnmmmm0111 not <REG_M>,<REG_N> */{"not",{ A_REG_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_7}, arch_sh_up}
	ocbi @r4                  ;!/* 0000nnnn10010011 ocbi @<REG_N>       */{"ocbi",{A_IND_N},{HEX_0,REG_N,HEX_9,HEX_3}, arch_sh4_nommu_nofpu_up}
	ocbp @r4                  ;!/* 0000nnnn10100011 ocbp @<REG_N>       */{"ocbp",{A_IND_N},{HEX_0,REG_N,HEX_A,HEX_3}, arch_sh4_nommu_nofpu_up}
	ocbwb @r4                 ;!/* 0000nnnn10110011 ocbwb @<REG_N>      */{"ocbwb",{A_IND_N},{HEX_0,REG_N,HEX_B,HEX_3}, arch_sh4_nommu_nofpu_up}
	or #4,R0                  ;!/* 11001011i8*1.... or #<imm>,R0        */{"or",{A_IMM,A_R0},{HEX_C,HEX_B,IMM0_8}, arch_sh_up}
	or r5,r4                  ;!/* 0010nnnnmmmm1011 or <REG_M>,<REG_N>  */{"or",{ A_REG_M,A_REG_N},{HEX_2,REG_N,REG_M,HEX_B}, arch_sh_up}
	or.b #4,@(R0,GBR)         ;!/* 11001111i8*1.... or.b #<imm>,@(R0,GBR)*/{"or.b",{A_IMM,A_R0_GBR},{HEX_C,HEX_F,IMM0_8}, arch_sh_up}
	pref @r4                  ;!/* 0000nnnn10000011 pref @<REG_N>       */{"pref",{A_IND_N},{HEX_0,REG_N,HEX_8,HEX_3}, arch_sh2a_nofpu_or_sh4_nommu_nofpu_up}
	rotcl r4                  ;!/* 0100nnnn00100100 rotcl <REG_N>       */{"rotcl",{A_REG_N},{HEX_4,REG_N,HEX_2,HEX_4}, arch_sh_up}
	rotcr r4                  ;!/* 0100nnnn00100101 rotcr <REG_N>       */{"rotcr",{A_REG_N},{HEX_4,REG_N,HEX_2,HEX_5}, arch_sh_up}
	rotl r4                   ;!/* 0100nnnn00000100 rotl <REG_N>        */{"rotl",{A_REG_N},{HEX_4,REG_N,HEX_0,HEX_4}, arch_sh_up}
	rotr r4                   ;!/* 0100nnnn00000101 rotr <REG_N>        */{"rotr",{A_REG_N},{HEX_4,REG_N,HEX_0,HEX_5}, arch_sh_up}
	rte                       ;!/* 0000000000101011 rte                 */{"rte",{0},{HEX_0,HEX_0,HEX_2,HEX_B}, arch_sh_up}
	rts                       ;!/* 0000000000001011 rts                 */{"rts",{0},{HEX_0,HEX_0,HEX_0,HEX_B}, arch_sh_up}
	sets                      ;!/* 0000000001011000 sets                */{"sets",{0},{HEX_0,HEX_0,HEX_5,HEX_8}, arch_sh_up}
	sett                      ;!/* 0000000000011000 sett                */{"sett",{0},{HEX_0,HEX_0,HEX_1,HEX_8}, arch_sh_up}
	shad r5,r4                ;!/* 0100nnnnmmmm1100 shad <REG_M>,<REG_N>*/{"shad",{ A_REG_M,A_REG_N},{HEX_4,REG_N,REG_M,HEX_C}, arch_sh2a_nofpu_or_sh3_nommu_up}
	shld r5,r4                ;!/* 0100nnnnmmmm1101 shld <REG_M>,<REG_N>*/{"shld",{ A_REG_M,A_REG_N},{HEX_4,REG_N,REG_M,HEX_D}, arch_sh2a_nofpu_or_sh3_nommu_up}
	shal r4                   ;!/* 0100nnnn00100000 shal <REG_N>        */{"shal",{A_REG_N},{HEX_4,REG_N,HEX_2,HEX_0}, arch_sh_up}
	shar r4                   ;!/* 0100nnnn00100001 shar <REG_N>        */{"shar",{A_REG_N},{HEX_4,REG_N,HEX_2,HEX_1}, arch_sh_up}
	shll r4                   ;!/* 0100nnnn00000000 shll <REG_N>        */{"shll",{A_REG_N},{HEX_4,REG_N,HEX_0,HEX_0}, arch_sh_up}
	shll16 r4                 ;!/* 0100nnnn00101000 shll16 <REG_N>      */{"shll16",{A_REG_N},{HEX_4,REG_N,HEX_2,HEX_8}, arch_sh_up}
	shll2 r4                  ;!/* 0100nnnn00001000 shll2 <REG_N>       */{"shll2",{A_REG_N},{HEX_4,REG_N,HEX_0,HEX_8}, arch_sh_up}
	shll8 r4                  ;!/* 0100nnnn00011000 shll8 <REG_N>       */{"shll8",{A_REG_N},{HEX_4,REG_N,HEX_1,HEX_8}, arch_sh_up}
	shlr r4                   ;!/* 0100nnnn00000001 shlr <REG_N>        */{"shlr",{A_REG_N},{HEX_4,REG_N,HEX_0,HEX_1}, arch_sh_up}
	shlr16 r4                 ;!/* 0100nnnn00101001 shlr16 <REG_N>      */{"shlr16",{A_REG_N},{HEX_4,REG_N,HEX_2,HEX_9}, arch_sh_up}
	shlr2 r4                  ;!/* 0100nnnn00001001 shlr2 <REG_N>       */{"shlr2",{A_REG_N},{HEX_4,REG_N,HEX_0,HEX_9}, arch_sh_up}
	shlr8 r4                  ;!/* 0100nnnn00011001 shlr8 <REG_N>       */{"shlr8",{A_REG_N},{HEX_4,REG_N,HEX_1,HEX_9}, arch_sh_up}
	sleep                     ;!/* 0000000000011011 sleep               */{"sleep",{0},{HEX_0,HEX_0,HEX_1,HEX_B}, arch_sh_up}
	stc SR,r4                 ;!/* 0000nnnn00000010 stc SR,<REG_N>      */{"stc",{A_SR,A_REG_N},{HEX_0,REG_N,HEX_0,HEX_2}, arch_sh_up}
	stc GBR,r4                ;!/* 0000nnnn00010010 stc GBR,<REG_N>     */{"stc",{A_GBR,A_REG_N},{HEX_0,REG_N,HEX_1,HEX_2}, arch_sh_up}
	stc VBR,r4                ;!/* 0000nnnn00100010 stc VBR,<REG_N>     */{"stc",{A_VBR,A_REG_N},{HEX_0,REG_N,HEX_2,HEX_2}, arch_sh_up}
	stc SSR,r4                ;!/* 0000nnnn00110010 stc SSR,<REG_N>     */{"stc",{A_SSR,A_REG_N},{HEX_0,REG_N,HEX_3,HEX_2}, arch_sh3_nommu_up}
	stc SPC,r4                ;!/* 0000nnnn01000010 stc SPC,<REG_N>     */{"stc",{A_SPC,A_REG_N},{HEX_0,REG_N,HEX_4,HEX_2}, arch_sh3_nommu_up}
	stc SGR,r4                ;!/* 0000nnnn00111010 stc SGR,<REG_N>     */{"stc",{A_SGR,A_REG_N},{HEX_0,REG_N,HEX_3,HEX_A}, arch_sh4_nommu_nofpu_up}
	stc DBR,r4                ;!/* 0000nnnn11111010 stc DBR,<REG_N>     */{"stc",{A_DBR,A_REG_N},{HEX_0,REG_N,HEX_F,HEX_A}, arch_sh4_nommu_nofpu_up}
	stc r1_bank,r4            ;!/* 0000nnnn1xxx0010 stc Rn_BANK,<REG_N> */{"stc",{A_REG_B,A_REG_N},{HEX_0,REG_N,REG_B,HEX_2}, arch_sh3_nommu_up}
	stc.l SR,@-r4             ;!/* 0100nnnn00000011 stc.l SR,@-<REG_N>  */{"stc.l",{A_SR,A_DEC_N},{HEX_4,REG_N,HEX_0,HEX_3}, arch_sh_up}
	stc.l VBR,@-r4            ;!/* 0100nnnn00100011 stc.l VBR,@-<REG_N> */{"stc.l",{A_VBR,A_DEC_N},{HEX_4,REG_N,HEX_2,HEX_3}, arch_sh_up}
	stc.l SSR,@-r4            ;!/* 0100nnnn00110011 stc.l SSR,@-<REG_N> */{"stc.l",{A_SSR,A_DEC_N},{HEX_4,REG_N,HEX_3,HEX_3}, arch_sh3_nommu_up}
	stc.l SPC,@-r4            ;!/* 0100nnnn01000011 stc.l SPC,@-<REG_N> */{"stc.l",{A_SPC,A_DEC_N},{HEX_4,REG_N,HEX_4,HEX_3}, arch_sh3_nommu_up}
	stc.l GBR,@-r4            ;!/* 0100nnnn00010011 stc.l GBR,@-<REG_N> */{"stc.l",{A_GBR,A_DEC_N},{HEX_4,REG_N,HEX_1,HEX_3}, arch_sh_up}
	stc.l SGR,@-r4            ;!/* 0100nnnn00110010 stc.l SGR,@-<REG_N> */{"stc.l",{A_SGR,A_DEC_N},{HEX_4,REG_N,HEX_3,HEX_2}, arch_sh4_nommu_nofpu_up}
	stc.l DBR,@-r4            ;!/* 0100nnnn11110010 stc.l DBR,@-<REG_N> */{"stc.l",{A_DBR,A_DEC_N},{HEX_4,REG_N,HEX_F,HEX_2}, arch_sh4_nommu_nofpu_up}
	stc.l r1_bank,@-r4        ;!/* 0100nnnn1xxx0011 stc.l Rn_BANK,@-<REG_N> */{"stc.l",{A_REG_B,A_DEC_N},{HEX_4,REG_N,REG_B,HEX_3}, arch_sh3_nommu_up}
	sts MACH,r4               ;!/* 0000nnnn00001010 sts MACH,<REG_N>    */{"sts",{A_MACH,A_REG_N},{HEX_0,REG_N,HEX_0,HEX_A}, arch_sh_up}
	sts MACL,r4               ;!/* 0000nnnn00011010 sts MACL,<REG_N>    */{"sts",{A_MACL,A_REG_N},{HEX_0,REG_N,HEX_1,HEX_A}, arch_sh_up}
	sts PR,r4                 ;!/* 0000nnnn00101010 sts PR,<REG_N>      */{"sts",{A_PR,A_REG_N},{HEX_0,REG_N,HEX_2,HEX_A}, arch_sh_up}
	sts.l MACH,@-r4           ;!/* 0100nnnn00000010 sts.l MACH,@-<REG_N>*/{"sts.l",{A_MACH,A_DEC_N},{HEX_4,REG_N,HEX_0,HEX_2}, arch_sh_up}
	sts.l MACL,@-r4           ;!/* 0100nnnn00010010 sts.l MACL,@-<REG_N>*/{"sts.l",{A_MACL,A_DEC_N},{HEX_4,REG_N,HEX_1,HEX_2}, arch_sh_up}
	sts.l PR,@-r4             ;!/* 0100nnnn00100010 sts.l PR,@-<REG_N>  */{"sts.l",{A_PR,A_DEC_N},{HEX_4,REG_N,HEX_2,HEX_2}, arch_sh_up}
	sub r5,r4                 ;!/* 0011nnnnmmmm1000 sub <REG_M>,<REG_N> */{"sub",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_8}, arch_sh_up}
	subc r5,r4                ;!/* 0011nnnnmmmm1010 subc <REG_M>,<REG_N>*/{"subc",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_A}, arch_sh_up}
	subv r5,r4                ;!/* 0011nnnnmmmm1011 subv <REG_M>,<REG_N>*/{"subv",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_B}, arch_sh_up}
	swap.b r5,r4              ;!/* 0110nnnnmmmm1000 swap.b <REG_M>,<REG_N>*/{"swap.b",{ A_REG_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_8}, arch_sh_up}
	swap.w r5,r4              ;!/* 0110nnnnmmmm1001 swap.w <REG_M>,<REG_N>*/{"swap.w",{ A_REG_M,A_REG_N},{HEX_6,REG_N,REG_M,HEX_9}, arch_sh_up}
	tas.b @r4                 ;!/* 0100nnnn00011011 tas.b @<REG_N>      */{"tas.b",{A_IND_N},{HEX_4,REG_N,HEX_1,HEX_B}, arch_sh_up}
	trapa #4                  ;!/* 11000011i8*1.... trapa #<imm>        */{"trapa",{A_IMM},{HEX_C,HEX_3,IMM0_8}, arch_sh_up}
	tst #4,R0                 ;!/* 11001000i8*1.... tst #<imm>,R0       */{"tst",{A_IMM,A_R0},{HEX_C,HEX_8,IMM0_8}, arch_sh_up}
	tst r5,r4                 ;!/* 0010nnnnmmmm1000 tst <REG_M>,<REG_N> */{"tst",{ A_REG_M,A_REG_N},{HEX_2,REG_N,REG_M,HEX_8}, arch_sh_up}
	tst.b #4,@(R0,GBR)        ;!/* 11001100i8*1.... tst.b #<imm>,@(R0,GBR)*/{"tst.b",{A_IMM,A_R0_GBR},{HEX_C,HEX_C,IMM0_8}, arch_sh_up}
	xor #4,R0                 ;!/* 11001010i8*1.... xor #<imm>,R0       */{"xor",{A_IMM,A_R0},{HEX_C,HEX_A,IMM0_8}, arch_sh_up}
	xor r5,r4                 ;!/* 0010nnnnmmmm1010 xor <REG_M>,<REG_N> */{"xor",{ A_REG_M,A_REG_N},{HEX_2,REG_N,REG_M,HEX_A}, arch_sh_up}
	xor.b #4,@(R0,GBR)        ;!/* 11001110i8*1.... xor.b #<imm>,@(R0,GBR)*/{"xor.b",{A_IMM,A_R0_GBR},{HEX_C,HEX_E,IMM0_8}, arch_sh_up}
	xtrct r5,r4               ;!/* 0010nnnnmmmm1101 xtrct <REG_M>,<REG_N>*/{"xtrct",{ A_REG_M,A_REG_N},{HEX_2,REG_N,REG_M,HEX_D}, arch_sh_up}
	dt r4                     ;!/* 0100nnnn00010000 dt <REG_N>          */{"dt",{A_REG_N},{HEX_4,REG_N,HEX_1,HEX_0}, arch_sh2_up}
	dmuls.l r5,r4             ;!/* 0011nnnnmmmm1101 dmuls.l <REG_M>,<REG_N>*/{"dmuls.l",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_D}, arch_sh2_up}
	dmulu.l r5,r4             ;!/* 0011nnnnmmmm0101 dmulu.l <REG_M>,<REG_N>*/{"dmulu.l",{ A_REG_M,A_REG_N},{HEX_3,REG_N,REG_M,HEX_5}, arch_sh2_up}
	mac.l @r5+,@r4+           ;!/* 0000nnnnmmmm1111 mac.l @<REG_M>+,@<REG_N>+*/{"mac.l",{A_INC_M,A_INC_N},{HEX_0,REG_N,REG_M,HEX_F}, arch_sh2_up}
	braf r4                   ;!/* 0000nnnn00100011 braf <REG_N>       */{"braf",{A_REG_N},{HEX_0,REG_N,HEX_2,HEX_3}, arch_sh2_up}
	bsrf r4                   ;!/* 0000nnnn00000011 bsrf <REG_N>       */{"bsrf",{A_REG_N},{HEX_0,REG_N,HEX_0,HEX_3}, arch_sh2_up}
