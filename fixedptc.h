#ifndef _FIXEDPTC_H_
#define _FIXEDPTC_H_

/*
 * Signed 32-bit fixed point number library for the 24.8 format.
 * This means that the numbers cannot be larger than approximately
 * 8 million or smaller than 1/256.
 */

typedef int32_t fixedpt;

#define fixedpt_rconst(R) (R * (1LL << 8) + (R >= 0 ? 0.5 : -0.5))
#define fixedpt_fromint(I) ((int64_t)I << 8)
#define fixedpt_toint(F) (F >> 8)
#define fixedpt_add(A,B) (A + B)
#define fixedpt_sub(A,B) (A - B)
#define fixedpt_mul(A,B) (int32_t)(((int64_t)A * (int64_t)B) >> 8)
#define fixedpt_div(A,B) (int32_t)(((int64_t)A << 8) / B)
#define fixedpt_fracpart(A) (A & 0xff)


static void
fixedpt_str(fixedpt A, char *str)
{
	int ndec = 0, slen = 0;
	char tmp[12] = {0};
	uint64_t fr, ip;
	char digit;
	const uint64_t one = 1LL << 32;
	const uint64_t mask = one - 1;

	if (A < 0) {
		str[slen++] = '-';
		A *= -1;
	}

	ip = fixedpt_toint(A);
	do {
		tmp[ndec++] = '0' + ip % 10;
		ip /= 10;
	} while (ip != 0);

	while (ndec > 0)
		str[slen++] = tmp[--ndec];
	str[slen++] = '.';

	fr = (fixedpt_fracpart(A) << 24) & mask;
	do {
		fr = (fr & mask) * 10;

		digit = '0' + (fr >> 32) % 10;
		str[slen++] = digit;
		ndec++;
	} while (fr != 0);

	if (ndec > 1 && digit == '0')
		str[slen-1] = '\0'; /* cut of trailing 0 */
	else
		str[slen] = '\0';
}

#endif
