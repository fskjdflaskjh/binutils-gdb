	.text
	.globl main
main:
	.rept 0x4000 - 0x15
	.long 0xfedcba98
	.endr
	.data
	.long 0x76543210
