    .cpu arm7tdmi-s
    .fpu softvfp
    .file    "y.c"
    .bss
    .align    2
l:
    .space    4
    .text
    .align    2
    .global    f1
    .type    f1, %function
f1:
    str    fp, [sp, #-4]!
    add    fp, sp, #0
    sub    sp, sp, #12
    str    r0, [fp, #-8]
    add    sp, fp, #0
    ldmfd    sp!, {fp}
    bx    lr
    .align    2
    .word    l
    .size    f1, .-f1
    .align    2
    .global    main
    .type    main, %function
main:
    stmfd    sp!, {fp, lr}
    add    fp, sp, #4
    bx    lr
    .align    2
    .word    1717986919
    .word    -1840700269
    .word    l
    .size    main, .-main
    .ident    "GCC: (Sourcery G++ 2011.03) 4.5.1"
