#name: C6X arch attribute merging, c64x+ c674x
#as: -mlittle-endian
#ld: -r -melf32_tic6x_le
#source: attr-arch-c64x+.s
#source: attr-arch-c674x.s
#readelf: -A

Attribute Section: c6xabi
File Attributes
  Tag_C6XABI_Tag_CPU_arch: C674x
