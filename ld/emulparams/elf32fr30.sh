MACHINE=
SCRIPT_NAME=elf
OUTPUT_FORMAT="elf32-fr30"
TEXT_START_ADDR=0x10000
ARCH=fr30
MAXPAGESIZE=256
ENTRY=_start
EMBEDDED=yes
NOP=0x9fa09fa0
OTHER_RELOCATING_SECTIONS='PROVIDE (__stack = 0x200000);'