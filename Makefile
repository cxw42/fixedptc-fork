all: test verify_32 verify_64
	true

test: test.c fixedptc.h
	gcc -o test -O3 -Wall test.c

verify_32: verify.c fixedptc.h
	gcc -o verify_32 -O3 -Wall -DFIXEDPT_BITS=32 verify.c

verify_64: verify.c fixedptc.h
	gcc -o verify_64 -O3 -Wall -DFIXEDPT_BITS=64 verify.c
