#objdump: -dr --prefix-addresses --show-raw-insn
#name:
#as: -march=c64x+ -mlittle-endian

.*: *file format elf32-tic6x-le


Disassembly of section .text:
[ \t]*\.\.\.
[0-9a-f]+[02468ace] <[^>]*> 0006[ \t]+mv \.L1 a0,a0
[0-9a-f]+[02468ace] <[^>]*> 000f[ \t]+mv \.S2 b0,b0
[0-9a-f]+[02468ace] <[^>]*> 0016[ \t]+mv \.D1 a0,a0
[0-9a-f]+[02468ace] <[^>]*> 0017[ \t]+mv \.D2 b0,b0
[0-9a-f]+[02468ace] <[^>]*> 000e[ \t]+mv \.S1 a0,a0
[0-9a-f]+[02468ace] <[^>]*> 0007[ \t]+mv \.L2 b0,b0
[0-9a-f]+[02468ace] <[^>]*> 0006[ \t]+mv \.L1 a0,a0
[0-9a-f]+[02468ace] <[^>]*> 100f[ \t]+mv \.S2X a0,b0
[0-9a-f]+[02468ace] <[^>]*> 1016[ \t]+mv \.D1X b0,a0
[0-9a-f]+[02468ace] <[^>]*> 1017[ \t]+mv \.D2X a0,b0
[0-9a-f]+[02468ace] <[^>]*> 100e[ \t]+mv \.S1X b0,a0
[0-9a-f]+[02468ace] <[^>]*> 1007[ \t]+mv \.L2X a0,b0
[0-9a-f]+[02468ace] <[^>]*> 1006[ \t]+mv \.L1X b0,a0
[0-9a-f]+[02468ace] <[^>]*> 100f[ \t]+mv \.S2X a0,b0
[0-9a-f]+[02468ace] <[^>]*> efe00000[ \t]+<fetch packet header 0xefe00000>
[0-9a-f]+[02468ace] <[^>]*> 0046[ \t]+mv \.L1 a0,a0
[0-9a-f]+[02468ace] <[^>]*> 004f[ \t]+mv \.S2 b0,b0
[0-9a-f]+[02468ace] <[^>]*> 0056[ \t]+mv \.D1 a0,a0
[0-9a-f]+[02468ace] <[^>]*> 0057[ \t]+mv \.D2 b0,b0
[0-9a-f]+[02468ace] <[^>]*> 004e[ \t]+mv \.S1 a0,a0
[0-9a-f]+[02468ace] <[^>]*> 0047[ \t]+mv \.L2 b0,b0
[0-9a-f]+[02468ace] <[^>]*> 0046[ \t]+mv \.L1 a0,a0
[0-9a-f]+[02468ace] <[^>]*> 104f[ \t]+mv \.S2X a0,b0
[0-9a-f]+[02468ace] <[^>]*> 1056[ \t]+mv \.D1X b0,a0
[0-9a-f]+[02468ace] <[^>]*> 1057[ \t]+mv \.D2X a0,b0
[0-9a-f]+[02468ace] <[^>]*> 104e[ \t]+mv \.S1X b0,a0
[0-9a-f]+[02468ace] <[^>]*> 1047[ \t]+mv \.L2X a0,b0
[0-9a-f]+[02468ace] <[^>]*> 1046[ \t]+mv \.L1X b0,a0
[0-9a-f]+[02468ace] <[^>]*> 104f[ \t]+mv \.S2X a0,b0
[0-9a-f]+[02468ace] <[^>]*> efe00000[ \t]+<fetch packet header 0xefe00000>
[0-9a-f]+[02468ace] <[^>]*> 0866[ \t]+\[a0\] mvk \.L1 0,a0
[0-9a-f]+[02468ace] <[^>]*> 4967[ \t]+\[!a0\] mvk \.L2 0,b2
[0-9a-f]+[02468ace] <[^>]*> 8ae6[ \t]+\[b0\] mvk \.L1 0,a5
[0-9a-f]+[02468ace] <[^>]*> cbe7[ \t]+\[!b0\] mvk \.L2 0,b7
[0-9a-f]+[02468ace] <[^>]*> 886e[ \t]+\[b0\] mvk \.S1 0,a0
[0-9a-f]+[02468ace] <[^>]*> 496f[ \t]+\[!a0\] mvk \.S2 0,b2
[0-9a-f]+[02468ace] <[^>]*> 0aee[ \t]+\[a0\] mvk \.S1 0,a5
[0-9a-f]+[02468ace] <[^>]*> 6bef[ \t]+\[!a0\] mvk \.S2 1,b7
[0-9a-f]+[02468ace] <[^>]*> a876[ \t]+\[b0\] mvk \.D1 1,a0
[0-9a-f]+[02468ace] <[^>]*> e977[ \t]+\[!b0\] mvk \.D2 1,b2
[0-9a-f]+[02468ace] <[^>]*> aaf6[ \t]+\[b0\] mvk \.D1 1,a5
[0-9a-f]+[02468ace] <[^>]*> 6bf7[ \t]+\[!a0\] mvk \.D2 1,b7
[0-9a-f]+[02468ace] <[^>]*> 2866[ \t]+\[a0\] mvk \.L1 1,a0
[0-9a-f]+[02468ace] <[^>]*> 6967[ \t]+\[!a0\] mvk \.L2 1,b2
[0-9a-f]+[02468ace] <[^>]*> efe00000[ \t]+<fetch packet header 0xefe00000>
[0-9a-f]+[02468ace] <[^>]*> 1866[ \t]+mvk \.L1 0,a0
[0-9a-f]+[02468ace] <[^>]*> 1867[ \t]+mvk \.L2 0,b0
[0-9a-f]+[02468ace] <[^>]*> 1866[ \t]+mvk \.L1 0,a0
[0-9a-f]+[02468ace] <[^>]*> 1867[ \t]+mvk \.L2 0,b0
[0-9a-f]+[02468ace] <[^>]*> 1866[ \t]+mvk \.L1 0,a0
[0-9a-f]+[02468ace] <[^>]*> 1867[ \t]+mvk \.L2 0,b0
[0-9a-f]+[02468ace] <[^>]*> 1866[ \t]+mvk \.L1 0,a0
[0-9a-f]+[02468ace] <[^>]*> 1867[ \t]+mvk \.L2 0,b0
[0-9a-f]+[02468ace] <[^>]*> 1866[ \t]+mvk \.L1 0,a0
[0-9a-f]+[02468ace] <[^>]*> 1867[ \t]+mvk \.L2 0,b0
[0-9a-f]+[02468ace] <[^>]*> 1866[ \t]+mvk \.L1 0,a0
[0-9a-f]+[02468ace] <[^>]*> 1867[ \t]+mvk \.L2 0,b0
[0-9a-f]+[02468ace] <[^>]*> 1866[ \t]+mvk \.L1 0,a0
[0-9a-f]+[02468ace] <[^>]*> 1867[ \t]+mvk \.L2 0,b0
[0-9a-f]+[02468ace] <[^>]*> efe00000[ \t]+<fetch packet header 0xefe00000>
[ \t]*\.\.\.
