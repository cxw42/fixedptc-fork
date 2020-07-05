all: test test-separate test-sqrt verify_32 verify_64
	true

test: test.c fixedptc.h
	gcc -o test -O3 -Wall $(CFLAGS) $(LDFLAGS) test.c

verify_32: verify.c fixedptc.h
	gcc -o verify_32 -O3 -Wall -DFIXEDPT_BITS=32 $(CFLAGS) $(LDFLAGS) -lm verify.c

verify_64: verify.c fixedptc.h
	gcc -o verify_64 -O3 -Wall -DFIXEDPT_BITS=64 $(CFLAGS) $(LDFLAGS) -lm verify.c

test-separate: test-separate.c test-separate-impl.c fixedptc.h
	gcc -o test-separate -O3 -Wall $(CFLAGS) $(LDFLAGS) \
		test-separate.c test-separate-impl.c

test-sqrt: test-sqrt.c fixedptc.h
	gcc -o test-sqrt -O3 -Wall $(CFLAGS) $(LDFLAGS) -lm test-sqrt.c
