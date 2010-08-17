#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
#define FIXEDPT_WBITS 16
*/

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

	fixedpt_print(fixedpt_rconst(143.125));
	fixedpt_print(FIXEDPT_PI);
	fixedpt_print(FIXEDPT_E);
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

	puts("");
	puts("sqrt(pi)=");
	fixedpt_print(fixedpt_sqrt(FIXEDPT_PI));

	puts("");
	puts("sin(pi/2)=");
	fixedpt_print(fixedpt_sin(FIXEDPT_HALF_PI));

	puts("");
	puts("sin(3.5*pi)=");
	fixedpt_print(fixedpt_sin(fixedpt_mul(fixedpt_rconst(3.5), FIXEDPT_PI)));
	fixedpt_print(fixedpt_sin(fixedpt_rconst(1000)));

	return (0);
}
