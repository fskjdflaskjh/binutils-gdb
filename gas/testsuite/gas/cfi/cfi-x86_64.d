#readelf: -wf
#name: CFI on x86-64
The section .eh_frame contains:

00000000 00000014 00000000 CIE
  Version:               1
  Augmentation:          "zR"
  Code alignment factor: 1
  Data alignment factor: -8
  Return address column: 16
  Augmentation data:     1b

  DW_CFA_def_cfa: r7 \(rsp\) ofs 8
  DW_CFA_offset: r16 \(rip\) at cfa-8
  DW_CFA_nop
  DW_CFA_nop

00000018 00000014 0000001c FDE cie=00000000 pc=00000000..00000014
  DW_CFA_advance_loc: 7 to 00000007
  DW_CFA_def_cfa_offset: 4668
  DW_CFA_advance_loc: 12 to 00000013
  DW_CFA_def_cfa_offset: 8

00000030 0000001c 00000034 FDE cie=00000000 pc=00000014..00000022
  DW_CFA_advance_loc: 1 to 00000015
  DW_CFA_def_cfa_offset: 16
  DW_CFA_offset: r6 \(rbp\) at cfa-16
  DW_CFA_advance_loc: 3 to 00000018
  DW_CFA_def_cfa_register: r6 \(rbp\)
  DW_CFA_advance_loc: 9 to 00000021
  DW_CFA_def_cfa: r7 \(rsp\) ofs 8
  DW_CFA_nop
  DW_CFA_nop
  DW_CFA_nop

00000050 00000014 00000054 FDE cie=00000000 pc=00000022..00000035
  DW_CFA_advance_loc: 3 to 00000025
  DW_CFA_def_cfa_register: r8 \(r8\)
  DW_CFA_advance_loc: 15 to 00000034
  DW_CFA_def_cfa_register: r7 \(rsp\)
  DW_CFA_nop

00000068 00000010 0000006c FDE cie=00000000 pc=00000035..0000003b
  DW_CFA_nop
  DW_CFA_nop
  DW_CFA_nop

0000007c 00000010 00000080 FDE cie=00000000 pc=0000003b..0000004d
  DW_CFA_nop
  DW_CFA_nop
  DW_CFA_nop

00000090 00000010 00000000 CIE
  Version:               1
  Augmentation:          "zR"
  Code alignment factor: 1
  Data alignment factor: -8
  Return address column: 16
  Augmentation data:     1b

  DW_CFA_def_cfa: r7 \(rsp\) ofs 8

000000a4 00000030 00000018 FDE cie=00000090 pc=0000004d..00000058
  DW_CFA_advance_loc: 1 to 0000004e
  DW_CFA_def_cfa_offset: 16
  DW_CFA_advance_loc: 1 to 0000004f
  DW_CFA_def_cfa_register: r8 \(r8\)
  DW_CFA_advance_loc: 1 to 00000050
  DW_CFA_def_cfa_offset: 4676
  DW_CFA_advance_loc: 1 to 00000051
  DW_CFA_offset_extended_sf: r4 \(rsi\) at cfa\+16
  DW_CFA_advance_loc: 1 to 00000052
  DW_CFA_register: r8 \(r8\) in r9 \(r9\)
  DW_CFA_advance_loc: 1 to 00000053
  DW_CFA_remember_state
  DW_CFA_advance_loc: 1 to 00000054
  DW_CFA_restore: r6 \(rbp\)
  DW_CFA_advance_loc: 1 to 00000055
  DW_CFA_undefined: r16 \(rip\)
  DW_CFA_advance_loc: 1 to 00000056
  DW_CFA_same_value: r3 \(rbx\)
  DW_CFA_advance_loc: 1 to 00000057
  DW_CFA_restore_state
  DW_CFA_nop
  DW_CFA_nop
  DW_CFA_nop
  DW_CFA_nop
  DW_CFA_nop

