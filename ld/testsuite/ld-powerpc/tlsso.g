#source: tls.s
#as: -a64
#ld: -shared -melf64ppc
#objdump: -sj.got
#target: powerpc64*-*-*

.*: +file format elf64-powerpc

Contents of section \.got:
 10818 00000000 00018818 00000000 00000000  .*
 10828 00000000 00000000 00000000 00000000  .*
 10838 00000000 00000000 00000000 00000000  .*
 10848 00000000 00000000 00000000 00000000  .*
 10858 00000000 00000000 00000000 00000000  .*
 10868 00000000 00000000 00000000 00000000  .*
