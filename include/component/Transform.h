#pragma once

#include "common.h"

struct Transform
{
	/**
	 * @brief x coordinate (Q15.16)
	 * @var i32 x;
	 */
	i32	x;
	/**
	 * @brief y coordinate (Q15.16)
	 * @var i32 y;
	 */
	i32	y;
	/**
	 * @brief z coordinate (Q15.16)
	 * @var i32 z;
	 */
	i32	z;
	/**
	 * @brief eulerAngles.y (Q15.16)
	 * @var i32 yaw;
	 */
	i32	yaw;
	/**
	 * @brief eulerAngles.x (Q15.16)
	 * @var i32 pitch;
	 */
	i32	pitch;

	/**
	 * @brief construct zero initialized Transform
	 */
	Transform();
	/**
	 * @brief update transformation matrix
	 * @param result output matrix (12 * 4 bytes)
	 */
	void	update(u32* result);
};