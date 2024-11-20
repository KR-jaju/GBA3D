#pragma once

#include "fixed32.h"
#include "fixed16.h"

extern "C" {
	extern u16 const division_lut[32768];

	i32 reciprocal(i32 d);
	u32 reciprocal_u16(u32 u);
	void	sincos(int angle, f32 &sine, f32 &cosine);
	f32	sqrt_fx(f32 f);
}
