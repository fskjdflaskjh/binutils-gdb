#name: C6X arch attribute merging, c67x+ c674x
#as: -mlittle-endian
#ld: -r -melf32_tic6x_le
#source: attr-arch-c67x+.s
#source: attr-arch-c674x.s
#readelf: -A

Attribute Section: c6xabi
File Attributes
  Tag_ISA: C674x
