#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

/* Test for square root function for 64 bits */

#define FIXEDPT_BITS 64
#define FIXEDPT_WBITS 14

#include "fixedptc.h"

int main() {

	fixedpt A = fixedpt_rconst(0.154632);

	printf("fixedptc library version: %s\n", FIXEDPT_VCSID);
	printf("Using %d-bit precision, %d.%d format\n\n", FIXEDPT_BITS, FIXEDPT_WBITS, FIXEDPT_FBITS);

	printf("sqrt(%lf)= %lf\n", fixedpt_tofloat(A), sqrt(fixedpt_tofloat(A)));
	printf("fixedpt_sqrt(%f) = %s\n", fixedpt_tofloat(A), fixedpt_cstr(fixedpt_sqrt(A), -1));

	return (0);
}
