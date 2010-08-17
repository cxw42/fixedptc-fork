#ifndef _FIXEDPTC_H_
#define _FIXEDPTC_H_

/*
 * Signed 32-bit fixed point number library for the 24.8 format.
 * This means that the numbers cannot be larger than approximately
 * 8 million or smaller than 1/256. In practice, you should not count
 * on working with numbers larger than a million or to the precision
 * of more than 2 decimal places. Make peace with the fact that PI
 * is 3.14 here. :)
 */

/*-
 * Copyright (c) 2010 Ivan Voras <ivoras@freebsd.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

typedef int32_t fixedpt;

/* Actually, you can redefine the FIXEDPT_WBITS constant to support other
 * divisions of the 32-bit integer, but who wants to work with 16-bit integers
 * these days? :) */

#define FIXEDPT_BITS	32
#ifndef FIXEDPT_WBITS
#define FIXEDPT_WBITS	24
#endif
#define FIXEDPT_FBITS	(FIXEDPT_BITS - FIXEDPT_WBITS)
#define FIXEDPT_FMASK	((1 << FIXEDPT_FBITS) - 1)

#define fixedpt_rconst(R) (int32_t)(R * (1LL << FIXEDPT_FBITS) + (R >= 0 ? 0.5 : -0.5))
#define fixedpt_fromint(I) ((int64_t)I << FIXEDPT_FBITS)
#define fixedpt_toint(F) (F >> FIXEDPT_FBITS)
#define fixedpt_add(A,B) (A + B)
#define fixedpt_sub(A,B) (A - B)
#define fixedpt_mul(A,B) (int32_t)(((int64_t)A * (int64_t)B) >> FIXEDPT_FBITS)
#define fixedpt_div(A,B) (int32_t)(((int64_t)A << FIXEDPT_FBITS) / B)
#define fixedpt_fracpart(A) (A & FIXEDPT_FMASK)

#define FIXEDPT_ONE	(1 << FIXEDPT_FBITS)
#define FIXEDPT_ONE_HALF (FIXEDPT_ONE >> 1)
#define FIXEDPT_PI	fixedpt_rconst(3.14159265)
#define FIXEDPT_TWO_PI	fixedpt_rconst(2*3.14159265)
#define FIXEDPT_HALF_PI fixedpt_rconst(3.14159265/2)
#define FIXEDPT_E	fixedpt_rconst(2.71828183)

#define fixedpt_abs(A) (A < 0 ? -A : A)

static void
fixedpt_str(fixedpt A, char *str)
{
	int ndec = 0, slen = 0;
	char tmp[12] = {0};
	uint64_t fr, ip;
	const uint64_t one = 1LL << FIXEDPT_BITS;
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

	fr = (fixedpt_fracpart(A) << FIXEDPT_WBITS) & mask;
	do {
		fr = (fr & mask) * 10;

		str[slen++] = '0' + (fr >> FIXEDPT_BITS) % 10;
		ndec++;
	} while (fr != 0);

	if (ndec > 1 && str[slen-1] == '0')
		str[slen-1] = '\0'; /* cut off trailing 0 */
	else
		str[slen] = '\0';
}

static inline fixedpt
fixedpt_sqrt(fixedpt A)
{
	int invert = 0;
	int iter = FIXEDPT_FBITS;
	int l, i;

	if (A < 0)
		return (-1);
	if (A == 0 || A == FIXEDPT_ONE)
		return (A);
	if (A < FIXEDPT_ONE && A > 6) {
		invert = 1;
		A = fixedpt_div(FIXEDPT_ONE, A);
	}
	if (A > FIXEDPT_ONE) {
		int s = A;

		iter = 0;
		while (s > 0) {
			s >>= 2;
			iter++;
		}
	}

	/* Newton's iterations */
	l = (A >> 1) + 1;
	for (i = 0; i < iter; i++)
		l = (l + fixedpt_div(A, l)) >> 1;
	if (invert)
		return (fixedpt_div(FIXEDPT_ONE, l));
	return (l);
}

static inline fixedpt
fixedpt_sin(fixedpt A)
{
	int s;
	fixedpt Asq, a, b, c, d, sine;
	const int INTERNAL_BITS = 24;

	if (A == 0)
		return (0);

	s = A / FIXEDPT_TWO_PI;
	if (fixedpt_abs(s) >= (1 << 6)) 
		A -= s * FIXEDPT_TWO_PI + (s >> 6) * -11;
	else
		A -= s * FIXEDPT_TWO_PI;
	
	if (A > FIXEDPT_PI)
		A -= FIXEDPT_TWO_PI;
	else if (A < -FIXEDPT_PI)
		A += FIXEDPT_TWO_PI;

	if (A > FIXEDPT_HALF_PI)
		A = FIXEDPT_PI - A;
	else if (A < -FIXEDPT_HALF_PI)
		A = -FIXEDPT_PI - A;

	if (A == 0)
		return (0);

	printf("A=%d, half_pi=%d\n", A, FIXEDPT_HALF_PI);
	/* Maclaurin power series */
	Asq = fixedpt_mul(A, A);
	d = fixedpt_mul((1 << INTERNAL_BITS) / (2*3*4*5*6*7*8*9), Asq);
	c = fixedpt_mul(d - (1 << INTERNAL_BITS) / (2*3*4*5*6*7), Asq);
	b = fixedpt_mul(c + (1 << INTERNAL_BITS) / (2*3*4*5), Asq);
	a = fixedpt_mul(b - (1 << INTERNAL_BITS) / (2*3), Asq);
	sine = fixedpt_mul(a + (1 << INTERNAL_BITS), A);
	return sine >> (INTERNAL_BITS - FIXEDPT_FBITS);
}


#endif
