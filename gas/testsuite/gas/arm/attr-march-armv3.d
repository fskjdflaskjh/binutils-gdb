# name: attributes for -march=armv3
# source: blank.s
# as: -march=armv3
# readelf: -A
# This test is only valid on ELF based ports.
# not-target: *-*-*coff *-*-pe *-*-wince *-*-*aout* *-*-netbsd *-*-riscix*

Attribute Section: aeabi
File Attributes
  Tag_CPU_name: "3"
  Tag_CPU_arch: v4
  Tag_ARM_ISA_use: Yes
