#ifndef _FIXEDPTC_H_
#define _FIXEDPTC_H_

/*
 * Signed 64-bit fixed point number library. The numbers are
 * in the 32:32 format.
 */

typedef union {
	uint64_t		full;
	struct {
		int32_t		whole;
		uint32_t	fract;
	};
} fixedpt;

//#define fixedpt_const(A,B) (uint64_t) (((int64_t)A << 32) + ((B + 1.1641532182693481e-10) * 4294967296LL))

//#define FIXEDX_YCONST(A,B) (FULLSIZEINT)((A<<Y) + ((B + 1/(2^(Y+1)))*2^Y))
#define fixedpt_const(A,B)    (uint64_t)((A<<31) + ((B + 1.1641532182693481e-10) * 4294967296LL))


static inline fixedpt
fixedpt_fromint(int32_t i)
{
	fixedpt R;

	R.whole = i;
	R.fract = 0;
	return R;
}

static inline fixedpt
fixedpt_add(fixedpt A, fixedpt B)
{
	fixedpt R;

	R.full = A.full + B.full;
	return R;
}

static inline fixedpt
fixedpt_sub(fixedpt A, fixedpt B)
{
	fixedpt R;

	R.full = A.full - B.full;
	return R;
}

static inline fixedpt
fixedpt_mul(fixedpt A, fixedpt B)
{
	fixedpt R;

	R.whole = A.whole + B.whole + 1;
	R.fract = A.fract + B.fract;
	return R;
}

#endif
