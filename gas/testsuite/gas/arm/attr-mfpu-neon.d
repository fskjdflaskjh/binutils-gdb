# name: attributes for -mfpu=neon
# source: blank.s
# as: -mfpu=neon
# readelf: -A
# This test is only valid on ELF based ports.
# not-target: *-*-*coff *-*-pe *-*-wince *-*-*aout* *-*-netbsd *-*-riscix*

Attribute Section: aeabi
File Attributes
  Tag_ARM_ISA_use: Yes
  Tag_THUMB_ISA_use: Thumb-1
  Tag_VFP_arch: VFPv3
  Tag_Advanced_SIMD_arch: NEONv1
