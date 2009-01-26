# name: attributes for -march=armv4txm
# source: blank.s
# as: -march=armv4txm
# readelf: -A
# This test is only valid on ELF based ports.
# not-target: *-*-*coff *-*-pe *-*-wince *-*-*aout* *-*-netbsd *-*-riscix*

Attribute Section: aeabi
File Attributes
  Tag_CPU_name: "4TXM"
  Tag_CPU_arch: v4T
  Tag_ARM_ISA_use: Yes
  Tag_THUMB_ISA_use: Thumb-1
