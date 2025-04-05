#pragma once

#include "common.h"

extern "C" {
	extern u16 const division_lut[32768];

	i32 reciprocal(i32 d);
	u32 reciprocal_u16(u32 u);
	void	sincos(int angle, i32 &sine, i32 &cosine);
	f32	sqrt_fx(f32 f);
	i32  sqrt_16(i32 i);
}
