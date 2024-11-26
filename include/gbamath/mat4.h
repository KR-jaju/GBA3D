#pragma once

#include "common.h"

struct mat4
{
	f32 m[12];

	mat4	operator*(mat4 const& other) const;

	static mat4	identity();
	static mat4	createViewMatrix(f32 const *position, i32 yaw, i32 pitch);
};
