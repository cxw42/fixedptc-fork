#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "fixedptc.h"



void
fixedpt_print(fixedpt A)
{
	char num[20];

	fixedpt_str(A, num);
	puts(num);
}

int main() {

	fixedpt A, B, C;

	A = fixedpt_rconst(143.125);
	fixedpt_print(A);
	puts("");

	A = fixedpt_rconst(2.5);
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

	A = fixedpt_rconst(1);
	B = fixedpt_rconst(4);
	C = fixedpt_div(A, B);

	fixedpt_print(A);
	puts("/");
	fixedpt_print(B);
	puts("=");
	fixedpt_print(C);

	return (0);
}
