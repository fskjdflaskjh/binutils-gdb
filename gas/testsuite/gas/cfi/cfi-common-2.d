#readelf: -wf
#name: CFI common 2
The section .eh_frame contains:

00000000 0000000d 00000000 CIE
  Version:               1
  Augmentation:          "zR"
  Code alignment factor: .*
  Data alignment factor: .*
  Return address column: .*
  Augmentation data:     1b


00000011 0000001[bf] 00000015 FDE cie=00000000 pc=.*
  DW_CFA_advance_loc: 4 to .*
  DW_CFA_def_cfa: r0 ofs 16
  DW_CFA_advance_loc: 4 to .*
  DW_CFA_remember_state
  DW_CFA_advance_loc: 4 to .*
  DW_CFA_def_cfa_offset: 0
  DW_CFA_advance_loc: 4 to .*
  DW_CFA_restore_state
  DW_CFA_advance_loc: 4 to .*
  DW_CFA_def_cfa_offset: 0
# 64-bit arches will have here 4 times DW_CFA_nop
#...
