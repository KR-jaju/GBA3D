#pragma once

#include "gbamath/fixed32.h"

struct Matrix4x4
{
	fixed32 m[12];

	static void	identityMatrix(Matrix4x4& matrix);
};
