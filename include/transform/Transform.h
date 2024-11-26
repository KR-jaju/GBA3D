#pragma once

#include "common.h"
#include "gbamath/mat4.h"

struct Transform
{
	f32 right[3];
	f32 up[3];
	f32 forward[3];
	f32	position[3];

	void	recalculateDirection(i32 yaw, i32 pitch, i32 roll);
	// mat4	transformMatrix(mat4 const& m);
	mat4	composite(mat4 const& view_matrix);
};

