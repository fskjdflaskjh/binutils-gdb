#source: tlsbinpic.s
#source: tlsbin.s
#as: --64
#ld: -shared -melf_x86_64
#readelf: -WSsrl
#target: x86_64-*-*

There are 19 section headers, starting at offset 0x[0-9a-f]+:

Section Headers:
  \[Nr\] Name +Type +Address +Off +Size +ES Flg Lk Inf Al
  \[ 0\] +NULL +0+ 0+ 0+ 00 +0 +0 +0
  \[ 1\] .interp +.*
  \[ 2\] .hash +.*
  \[ 3\] .dynsym +.*
  \[ 4\] .dynstr +.*
  \[ 5\] .rela.dyn +.*
  \[ 6\] .rela.plt +.*
  \[ 7\] .plt +.*
  \[ 8\] .text +PROGBITS +0+401000 0+1000 0+22a 00 +AX +0 +0 +4096
  \[ 9\] .tdata +PROGBITS +0+50122a 0+122a 0+60 00 WAT +0 +0 +1
  \[10\] .tbss +NOBITS +0+50128a 0+128a 0+40 00 WAT +0 +0 +1
  \[11\] .dynamic +DYNAMIC +0+501290 0+1290 0+140 10 +WA +4 +0 +8
  \[12\] .got +PROGBITS +0+5013d0 0+13d0 0+20 08 +WA +0 +0 +8
  \[13\] .got.plt +PROGBITS +0+5013f0 0+13f0 0+20 08 +WA +0 +0 +8
  \[14\] .data +.*
  \[15\] .bss +.*
  \[16\] .shstrtab +.*
  \[17\] .symtab +.*
  \[18\] .strtab +.*
Key to Flags:
.*
.*
.*

Elf file type is EXEC \(Executable file\)
Entry point 0x40113c
There are 6 program headers, starting at offset [0-9]+

Program Headers:
  Type +Offset +VirtAddr +PhysAddr +FileSiz +MemSiz +Flg Align
  PHDR +0x0+40 0x0+400040 0x0+400040 0x0+150 0x0+150 R E 0x8
  INTERP +0x0+190 0x0+400190 0x0+400190 0x0+f 0x0+f R +0x1
.*Requesting program interpreter.*
  LOAD +0x0+ 0x0+400000 0x0+400000 0x0+122a 0x0+122a R E 0x100000
  LOAD +0x0+122a 0x0+50122a 0x0+50122a 0x0+dd6 0x0+dd6 RW  0x100000
  DYNAMIC +0x0+1290 0x0+501290 0x0+501290 0x0+140 0x0+140 RW  0x8
  TLS +0x0+122a 0x0+50122a 0x0+50122a 0x0+60 0x0+a0 R +0x1

 Section to Segment mapping:
  Segment Sections...
   00 *
   01 +.interp *
   02 +.interp .hash .dynsym .dynstr .rela.dyn .rela.plt .plt .text *
   03 +.tdata .dynamic .got .got.plt *
   04 +.dynamic *
   05 +.tdata .tbss *

Relocation section '.rela.dyn' at offset 0x328 contains 4 entries:
 +Offset +Info +Type +Symbol's Value  Symbol's Name \+ Addend
0+5013d0  0+100000012 R_X86_64_TPOFF64 +0+ sG5 \+ 0
0+5013d8  0+300000012 R_X86_64_TPOFF64 +0+ sG2 \+ 0
0+5013e0  0+600000012 R_X86_64_TPOFF64 +0+ sG6 \+ 0
0+5013e8  0+700000012 R_X86_64_TPOFF64 +0+ sG1 \+ 0

Relocation section '.rela.plt' at offset 0x388 contains 1 entries:
 +Offset +Info +Type +Symbol's Value  Symbol's Name \+ Addend
0+[0-9a-f]+  0+400000007 R_X86_64_JUMP_SLOT +0+[0-9a-f]+ __tls_get_addr \+ 0

Symbol table '.dynsym' contains 10 entries:
 +Num: +Value +Size Type +Bind +Vis +Ndx Name
 +[0-9]+: 0+ +0 NOTYPE  LOCAL  DEFAULT  UND *
 +[0-9]+: 0+ +0 TLS +GLOBAL DEFAULT  UND sG5
 +[0-9]+: 0+501290 +0 OBJECT  GLOBAL DEFAULT  ABS _DYNAMIC
 +[0-9]+: 0+ +0 TLS +GLOBAL DEFAULT  UND sG2
 +[0-9]+: 0+[0-9a-f]+ +0 FUNC +GLOBAL DEFAULT  UND __tls_get_addr
 +[0-9]+: 0+[0-9a-f]+ +0 NOTYPE  GLOBAL DEFAULT  ABS __bss_start
 +[0-9]+: 0+ +0 TLS +GLOBAL DEFAULT  UND sG6
 +[0-9]+: 0+ +0 TLS +GLOBAL DEFAULT  UND sG1
 +[0-9]+: 0+[0-9a-f]+ +0 NOTYPE  GLOBAL DEFAULT  ABS _edata
 +[0-9]+: 0+[0-9a-f]+ +0 NOTYPE  GLOBAL DEFAULT  ABS _end

Symbol table '.symtab' contains 71 entries:
 +Num: +Value +Size Type +Bind +Vis +Ndx Name
 +[0-9]+: 0+ +0 NOTYPE  LOCAL  DEFAULT  UND *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +1 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +2 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +3 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +4 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +5 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +6 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +7 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +8 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +9 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +10 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +11 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +12 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +13 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +14 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +15 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +16 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +17 *
 +[0-9]+: [0-9a-f]+ +0 SECTION LOCAL  DEFAULT +18 *
 +[0-9]+: 0+20 +0 TLS +LOCAL  DEFAULT +9 sl1
 +[0-9]+: 0+24 +0 TLS +LOCAL  DEFAULT +9 sl2
 +[0-9]+: 0+28 +0 TLS +LOCAL  DEFAULT +9 sl3
 +[0-9]+: 0+2c +0 TLS +LOCAL  DEFAULT +9 sl4
 +[0-9]+: 0+30 +0 TLS +LOCAL  DEFAULT +9 sl5
 +[0-9]+: 0+34 +0 TLS +LOCAL  DEFAULT +9 sl6
 +[0-9]+: 0+38 +0 TLS +LOCAL  DEFAULT +9 sl7
 +[0-9]+: 0+3c +0 TLS +LOCAL  DEFAULT +9 sl8
 +[0-9]+: 0+80 +0 TLS +LOCAL  DEFAULT +10 bl1
 +[0-9]+: 0+84 +0 TLS +LOCAL  DEFAULT +10 bl2
 +[0-9]+: 0+88 +0 TLS +LOCAL  DEFAULT +10 bl3
 +[0-9]+: 0+8c +0 TLS +LOCAL  DEFAULT +10 bl4
 +[0-9]+: 0+90 +0 TLS +LOCAL  DEFAULT +10 bl5
 +[0-9]+: 0+94 +0 TLS +LOCAL  DEFAULT +10 bl6
 +[0-9]+: 0+98 +0 TLS +LOCAL  DEFAULT +10 bl7
 +[0-9]+: 0+9c +0 TLS +LOCAL  DEFAULT +10 bl8
 +[0-9]+: 0+1c +0 TLS +GLOBAL DEFAULT +9 sg8
 +[0-9]+: 0+7c +0 TLS +GLOBAL DEFAULT +10 bg8
 +[0-9]+: 0+74 +0 TLS +GLOBAL DEFAULT +10 bg6
 +[0-9]+: 0+ +0 TLS +GLOBAL DEFAULT  UND sG5
 +[0-9]+: 0+68 +0 TLS +GLOBAL DEFAULT +10 bg3
 +[0-9]+: 0+501290 +0 OBJECT  GLOBAL DEFAULT  ABS _DYNAMIC
 +[0-9]+: 0+8 +0 TLS +GLOBAL DEFAULT +9 sg3
 +[0-9]+: 0+48 +0 TLS +GLOBAL HIDDEN +9 sh3
 +[0-9]+: 0+ +0 TLS +GLOBAL DEFAULT  UND sG2
 +[0-9]+: 0+c +0 TLS +GLOBAL DEFAULT +9 sg4
 +[0-9]+: 0+10 +0 TLS +GLOBAL DEFAULT +9 sg5
 +[0-9]+: 0+70 +0 TLS +GLOBAL DEFAULT +10 bg5
 +[0-9]+: [0-9a-f]+ +0 FUNC +GLOBAL DEFAULT  UND __tls_get_addr
 +[0-9]+: 0+58 +0 TLS +GLOBAL HIDDEN +9 sh7
 +[0-9]+: 0+5c +0 TLS +GLOBAL HIDDEN +9 sh8
 +[0-9]+: 0+ +0 TLS +GLOBAL DEFAULT +9 sg1
 +[0-9]+: 0+40113c +0 FUNC +GLOBAL DEFAULT +8 _start
 +[0-9]+: 0+4c +0 TLS +GLOBAL HIDDEN +9 sh4
 +[0-9]+: 0+78 +0 TLS +GLOBAL DEFAULT +10 bg7
 +[0-9]+: 0+50 +0 TLS +GLOBAL HIDDEN +9 sh5
 +[0-9]+: [0-9a-f]+ +0 NOTYPE  GLOBAL DEFAULT  ABS __bss_start
 +[0-9]+: 0+ +0 TLS +GLOBAL DEFAULT  UND sG6
 +[0-9]+: 0+401000 +0 FUNC +GLOBAL DEFAULT +8 fn2
 +[0-9]+: 0+4 +0 TLS +GLOBAL DEFAULT +9 sg2
 +[0-9]+: 0+ +0 TLS +GLOBAL DEFAULT  UND sG1
 +[0-9]+: 0+40 +0 TLS +GLOBAL HIDDEN +9 sh1
 +[0-9]+: 0+14 +0 TLS +GLOBAL DEFAULT +9 sg6
 +[0-9]+: 0+18 +0 TLS +GLOBAL DEFAULT +9 sg7
 +[0-9]+: [0-9a-f]+ +0 NOTYPE  GLOBAL DEFAULT  ABS _edata
 +[0-9]+: 0+5013f0 +0 OBJECT  GLOBAL HIDDEN   13 _GLOBAL_OFFSET_TABLE_
 +[0-9]+: [0-9a-f]+ +0 NOTYPE  GLOBAL DEFAULT  ABS _end
 +[0-9]+: 0+44 +0 TLS +GLOBAL HIDDEN +9 sh2
 +[0-9]+: 0+54 +0 TLS +GLOBAL HIDDEN +9 sh6
 +[0-9]+: 0+64 +0 TLS +GLOBAL DEFAULT +10 bg2
 +[0-9]+: 0+60 +0 TLS +GLOBAL DEFAULT +10 bg1
 +[0-9]+: 0+6c +0 TLS +GLOBAL DEFAULT +10 bg4
