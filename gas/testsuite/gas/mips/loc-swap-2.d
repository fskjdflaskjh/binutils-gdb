#PROG: readelf
#readelf: -wl
#name: MIPS DWARF-2 location information with branch swapping (2)
#as: -32
#source: loc-swap-2.s

Raw dump of debug contents of section .debug_line:

  Offset:                      0x0
  Length:                      60
  DWARF Version:               2
  Prologue Length:             35
  Minimum Instruction Length:  1
  Initial value of 'is_stmt':  1
  Line Base:                   -5
  Line Range:                  14
  Opcode Base:                 13

 Opcodes:
  Opcode 1 has 0 args
  Opcode 2 has 1 args
  Opcode 3 has 1 args
  Opcode 4 has 1 args
  Opcode 5 has 1 args
  Opcode 6 has 0 args
  Opcode 7 has 0 args
  Opcode 8 has 0 args
  Opcode 9 has 1 args
  Opcode 10 has 0 args
  Opcode 11 has 0 args
  Opcode 12 has 1 args

 The Directory Table is empty.

 The File Name Table:
  Entry	Dir	Time	Size	Name
  1	0	0	0	loc-swap-2.s

 Line Number Statements:
  Extended opcode 2: set Address to 0x0
  Special opcode 11: advance Address by 0 to 0x0 and Line by 6 to 7
  Special opcode 7: advance Address by 0 to 0x0 and Line by 2 to 9
  Special opcode 6: advance Address by 0 to 0x0 and Line by 1 to 10
  Special opcode 120: advance Address by 8 to 0x8 and Line by 3 to 13
  Special opcode 62: advance Address by 4 to 0xc and Line by 1 to 14
  Special opcode 6: advance Address by 0 to 0xc and Line by 1 to 15
  Special opcode 119: advance Address by 8 to 0x14 and Line by 2 to 17
  Advance PC by 4 to 0x18
  Extended opcode 1: End of Sequence
