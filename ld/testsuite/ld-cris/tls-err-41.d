#source: start1.s
#source: tls-ie-10.s --pic
#as: --no-underscore --em=criself
#ld: -m crislinux
#error: \A[^\n]*\.o: In function[^\n]*\n[^\n]*undefined reference[^\n]*\Z

# Undefined reference for a R_CRIS_32_GOT_TPREL in an executable.
