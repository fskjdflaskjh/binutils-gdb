#name: C6X conformance attribute merging, 10 none
#as: -mlittle-endian
#ld: -r -melf32_tic6x_le
#source: attr-conformance-10.s
#source: attr-conformance-none.s
#readelf: -A

Attribute Section: c6xabi
File Attributes
  Tag_ISA: C674x
