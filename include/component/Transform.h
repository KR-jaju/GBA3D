#pragma once

#include "common.h"

struct Transform
{
	i32	x;
	i32	y;
	i32	z;
	i32	yaw;
	i32	pitch;

	Transform();
	void	update(u32* result);
};