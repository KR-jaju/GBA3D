#pragma once

#include "common.h"

extern "C" {
	extern u16 const division_lut[32768];

	i32 reciprocal(i32 d);
	u32 reciprocal_u16(u32 u);
	void	sincos(int angle, fixed &sine, fixed &cosine);
	fixed	sqrt_fx(fixed f);
}
