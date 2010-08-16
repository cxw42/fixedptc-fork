#ifndef _FIXEDPTC_H_
#define _FIXEDPTC_H_

#define fixedpt fixedpt_64_32

typedef union {
	uint64_t		packed;
	struct {
		uint32_t	whole;
		uint32_t	fract;
	} parts;
} fixedpt_64_32;

#endif
