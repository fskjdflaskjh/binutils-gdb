#objdump: -h
#source: textalign-xcoff-001.s
#as: 

.*:     file format aixcoff-rs6000

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 \.text         00000004  0+0  0+0  000000a8  2\*\*2
                  CONTENTS, ALLOC, LOAD, CODE
  1 \.data         00000008  0+08  0+08  000000ac  2\*\*3
                  CONTENTS, ALLOC, LOAD, RELOC, DATA
  2 \.bss          00000000  0+10  0+10  00000000  2\*\*3
                  ALLOC
