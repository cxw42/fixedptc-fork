#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "fixedptc.h"

void
verify_numbers()
{
	float pi_f = 3.14159265358979323846264338;
	double pi_d = 3.14159265358979323846264338;
	fixedpt pi_x = fixedpt_rconst(3.14159265358979323846264338);

	float e_f = 2.71828182845904523536028747;
	double e_d = 2.71828182845904523536028747;
	fixedpt e_x = fixedpt_rconst(2.71828182845904523536028747);

	printf("pi as string:\t3.14159265358979323846264338\n");
	printf("pi as float:\t%0.6f\n", pi_f);
	printf("pi as double:\t%0.15lf\n", pi_d);
	printf("pi as fixedpt:\t%s\n", fixedpt_cstr(pi_x, -1));

	printf("e as string:\t2.71828182845904523536028747\n");
	printf("e as float:\t%0.6f\n", e_f);
	printf("e as double:\t%0.15lf\n", e_d);
	printf("e as fixedpt:\t%s\n", fixedpt_cstr(e_x, -1));

	printf("\n");
}


int
main() 
{
	verify_numbers();

	return (0);
}

