#include <stdio.h>
#include <unistd.h>

#include "fixedptc.h"

void
fixedpt_print(fixedpt A)
{
	printf("%d.%u\n", A.whole, A.fract);
}

int main() {

	fixedpt A, B, C;

	A = fixedpt_fromint(2);
	B = fixedpt_fromint(3);

	fixedpt_print(A);
	puts("+");
	fixedpt_print(B);
	C = fixedpt_add(A, B);
	puts("=");
	fixedpt_print(C);
	puts("");

	fixedpt_print(A);
	puts("*");
	fixedpt_print(B);
	puts("=");
	C = fixedpt_mul(A, B);
	fixedpt_print(C);
	puts("");

	return (0);
}
