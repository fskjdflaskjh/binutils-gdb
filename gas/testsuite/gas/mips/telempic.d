#objdump: -rst -mmips:4000
#name: MIPS empic
#as: -mabi=o64 -membedded-pic -mips3
#source: empic.s
#stderr: empic.l

# Check GNU-specific embedded relocs, for ELF.

.*: +file format elf.*mips.*

SYMBOL TABLE:
0+0000000 l    d  \.text	0+0000000 
0+0000000 l    d  \.data	0+0000000 
0+0000000 l    d  \.bss	0+0000000 
0+0000004 l       \.text	0+0000000 l2
0+0000100 l       \.foo	0+0000000 l1
0+0000034 l       \.text	0+0000000 l3
0+0000098 l       \.text	0+0000000 l5
0+0000000 l    d  \.foo	0+0000000 
0+0000004 l       \.foo	0+0000000 l4
0+0000000 l    d  \.reginfo	0+0000000 
0+0000000 l    d  \.(mdebug|pdr)	0+0000000 
0+0000000         \*UND\*	0+0000000 g1
0+0000000         \*UND\*	0+0000000 g2


RELOCATION RECORDS FOR \[\.text\]:
OFFSET [ ]+ TYPE              VALUE 
0+0000004 R_MIPS_GNU_REL16_S2  g1
0+000000c R_MIPS_GNU_REL16_S2  g2
0+0000014 R_MIPS_GNU_REL16_S2  g2
0+000001c R_MIPS_GNU_REL16_S2  \.foo
0+0000024 R_MIPS_GNU_REL16_S2  \.text
0+000002c R_MIPS_GNU_REL16_S2  \.foo
0+0000034 R_MIPS_GNU_REL16_S2  \.text
0+000003c R_MIPS_GNU_REL_HI16  g1
0+0000040 R_MIPS_GNU_REL_LO16  g1
0+0000044 R_MIPS_GNU_REL_HI16  \.foo
0+0000048 R_MIPS_GNU_REL_LO16  \.foo
0+0000050 R_MIPS_32         g1
0+0000054 R_MIPS_32         \.foo
0+0000058 R_MIPS_32         \.text
0+000005c R_MIPS_PC32       g1
0+0000060 R_MIPS_PC32       \.foo
0+0000068 R_MIPS_64         g1
0+0000070 R_MIPS_64         \.foo
0+0000078 R_MIPS_64         \.text
0+0000080 R_MIPS_PC64       g1
0+0000088 R_MIPS_PC64       \.foo
0+0000098 R_MIPS_GNU_REL16_S2  \.text
0+000009c R_MIPS_GNU_REL16_S2  \.text
0+00000a0 R_MIPS_GNU_REL_HI16  \.text
0+00000a4 R_MIPS_GNU_REL_LO16  \.text
0+00000a8 R_MIPS_GNU_REL_HI16  \.text
0+00000ac R_MIPS_GNU_REL_LO16  \.text
0+00000b0 R_MIPS_32         \.text
0+00000b8 R_MIPS_64         \.text
0+00000cc R_MIPS_GNU_REL16_S2  \.text
0+00000d0 R_MIPS_GNU_REL16_S2  \.text
0+00000d4 R_MIPS_GNU_REL_HI16  \.text
0+00000d8 R_MIPS_GNU_REL_LO16  \.text
0+00000dc R_MIPS_GNU_REL_HI16  \.text
0+00000e0 R_MIPS_GNU_REL_LO16  \.text
0+00000e4 R_MIPS_32         \.text
0+00000f0 R_MIPS_64         \.text


RELOCATION RECORDS FOR \[\.foo\]:
OFFSET [ ]+ TYPE              VALUE 
0+0000004 R_MIPS_GNU_REL_HI16  g1
0+0000008 R_MIPS_GNU_REL_LO16  g1
0+000000c R_MIPS_GNU_REL_HI16  \.foo
0+0000010 R_MIPS_GNU_REL_LO16  \.foo
0+0000014 R_MIPS_GNU_REL_HI16  \.text
0+0000018 R_MIPS_GNU_REL_LO16  \.text
0+000001c R_MIPS_GNU_REL_HI16  g1
0+0000020 R_MIPS_GNU_REL_LO16  g1
0+0000024 R_MIPS_GNU_REL_HI16  g1
0+0000028 R_MIPS_GNU_REL_LO16  g1
0+000002c R_MIPS_GNU_REL_HI16  \.foo
0+0000030 R_MIPS_GNU_REL_LO16  \.foo
0+0000034 R_MIPS_GNU_REL_HI16  \.text
0+0000038 R_MIPS_GNU_REL_LO16  \.text
0+000003c R_MIPS_32         g1
0+0000040 R_MIPS_32         \.foo
0+0000044 R_MIPS_32         \.text
0+0000048 R_MIPS_PC32       g1
0+0000050 R_MIPS_PC32       \.text
0+0000058 R_MIPS_64         g1
0+0000060 R_MIPS_64         \.foo
0+0000068 R_MIPS_64         \.text
0+0000070 R_MIPS_PC64       g1
0+0000080 R_MIPS_PC64       \.text
0+0000088 R_MIPS_GNU_REL_HI16  g1
0+000008c R_MIPS_GNU_REL_LO16  g1
0+0000090 R_MIPS_GNU_REL_HI16  \.foo
0+0000094 R_MIPS_GNU_REL_LO16  \.foo
0+0000098 R_MIPS_GNU_REL_HI16  \.text
0+000009c R_MIPS_GNU_REL_LO16  \.text
0+00000a0 R_MIPS_GNU_REL_HI16  g1
0+00000a4 R_MIPS_GNU_REL_LO16  g1
0+00000a8 R_MIPS_GNU_REL_HI16  \.foo
0+00000ac R_MIPS_GNU_REL_LO16  \.foo
0+00000b0 R_MIPS_GNU_REL_HI16  \.text
0+00000b4 R_MIPS_GNU_REL_LO16  \.text
0+00000b8 R_MIPS_32         g1
0+00000bc R_MIPS_32         \.foo
0+00000c0 R_MIPS_32         \.text
0+00000c4 R_MIPS_PC32       g1
0+00000cc R_MIPS_PC32       \.text
0+00000d0 R_MIPS_64         g1
0+00000d8 R_MIPS_64         \.foo
0+00000e0 R_MIPS_64         \.text
0+00000e8 R_MIPS_PC64       g1
0+00000f8 R_MIPS_PC64       \.text

Contents of section \.text:
 0000 00000000 ffff1104 00000000 ffff0010  .*
 0010 00000000 ffff0010 00000000 3f001104  .*
 0020 00000000 00001104 00000000 41000010  .*
 0030 00000000 00000010 00000000 0000033c  .*
 0040 0c0063[26]4 0000033c 140163[26]4 d0ff03[26]4  .*
 0050 00000000 00010000 04000000 28000000  .*
 0060 2c010000 d0ffffff 00000000 00000000  .*
 0070 00010000 00000000 04000000 00000000  .*
 0080 4c000000 00000000 54010000 00000000  .*
 0090 d0ffffff ffffffff 32000010 33000010  .*
 00a0 0000033c d80063[26]4 0000033c e80063[26]4  .*
 00b0 cc000000 34000000 cc000000 00000000  .*
 00c0 34000000 00000000 00000000 32000010  .*
 00d0 33000010 0000033c 0c0163[26]4 0000033c  .*
 00e0 1c0163[26]4 cc000000 34000000 00000000  .*
 00f0 cc000000 00000000 34000000 00000000  .*
Contents of section \.reginfo:
 0000 08000080 00000000 00000000 00000000  .*
 0010 00000000 00000000                    .*
Contents of section \.foo:
 0000 00000000 0000033c 040063[26]4 0000033c  .*
 0010 0c0163[26]4 0000033c 180063[26]4 0000033c  .*
 0020 1c0063[26]4 0000033c 240063[26]4 0000033c  .*
 0030 2c0163[26]4 0000033c 380063[26]4 00000000  .*
 0040 00010000 04000000 44000000 fc000000  .*
 0050 50000000 00000000 00000000 00000000  .*
 0060 00010000 00000000 04000000 00000000  .*
 0070 6c000000 00000000 fc000000 00000000  .*
 0080 80000000 00000000 0000033c 8c0063[26]4  .*
 0090 0000033c 940163[26]4 0000033c a00063[26]4  .*
 00a0 0000033c a40063[26]4 0000033c ac0163[26]4  .*
 00b0 0000033c b80063[26]4 04000000 04010000  .*
 00c0 08000000 c4000000 00010000 d0000000  .*
 00d0 04000000 00000000 04010000 00000000  .*
 00e0 08000000 00000000 e8000000 00000000  .*
 00f0 00010000 00000000 fc000000 00000000  .*
 0100 00000000 00000000 00000000 00000000  .*

