#name: MIPS undefined reference
#source: undefined.s
#ld: -e foo
#error: \A[^\n]*\.o: In function `foo':\n\(\.text\+0x0\): undefined reference to `bar'\Z
