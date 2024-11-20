#pragma once

#include "fixed.h"

struct mat4
{
	fixed	m[12];

	void	translate(fixed x, fixed y, fixed z) {
		m[3] += x;
		m[7] += y;
		m[11] += z;
	}
};

extern "C"
{
	// mat4	
}
