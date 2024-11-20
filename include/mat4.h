#pragma once

#include "gbamath/gbamath.h"

struct mat4
{
	f32	m[12];

	void	translate(f32 x, f32 y, f32 z) {
		m[3] += x;
		m[7] += y;
		m[11] += z;
	}
};

extern "C"
{
	// mat4	
}
