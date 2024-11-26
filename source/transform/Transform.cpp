#include "transform/Transform.h"
#include "gbamath/gbamath.h"

mat4	Transform::composite(mat4 const &view_matrix)
{
	mat4	result;

	result.m[0] = this->right[0] * view_matrix.m[0] + this->right[1] * view_matrix.m[1] + this->right[2] * view_matrix.m[2];
	result.m[1] = this->up[0] * view_matrix.m[0] + this->up[1] * view_matrix.m[1] + this->up[2] * view_matrix.m[2];
	result.m[2] = this->forward[0] * view_matrix.m[0] + this->forward[1] * view_matrix.m[1] + this->forward[2] * view_matrix.m[2];
	result.m[3] = this->position[0] * view_matrix.m[0] + this->position[1] * view_matrix.m[1] + this->position[2] * view_matrix.m[2] + view_matrix.m[3];

	result.m[4] = this->right[0] * view_matrix.m[4] + this->right[1] * view_matrix.m[5] + this->right[2] * view_matrix.m[6];
	result.m[5] = this->up[0] * view_matrix.m[4] + this->up[1] * view_matrix.m[5] + this->up[2] * view_matrix.m[6];
	result.m[6] = this->forward[0] * view_matrix.m[4] + this->forward[5] * view_matrix.m[1] + this->forward[2] * view_matrix.m[6];
	result.m[7] = this->position[0] * view_matrix.m[4] + this->position[5] * view_matrix.m[1] + this->position[2] * view_matrix.m[6] + view_matrix.m[7];

	result.m[8] = this->right[0] * view_matrix.m[8] + this->right[1] * view_matrix.m[9] + this->right[2] * view_matrix.m[10];
	result.m[9] = this->up[0] * view_matrix.m[8] + this->up[1] * view_matrix.m[9] + this->up[2] * view_matrix.m[10];
	result.m[10] = this->forward[0] * view_matrix.m[8] + this->forward[1] * view_matrix.m[9] + this->forward[2] * view_matrix.m[10];
	result.m[11] = this->position[0] * view_matrix.m[8] + this->position[1] * view_matrix.m[9] + this->position[2] * view_matrix.m[10] + view_matrix.m[11];

	return (result);
}

void	Transform::recalculateDirection(i32 yaw, i32 pitch, i32 roll)
{
	f32	sin_yaw;
	f32	cos_yaw;
	f32	sin_pitch;
	f32	cos_pitch;
	f32	sin_roll;
	f32	cos_roll;

	sincos(yaw, sin_yaw, cos_yaw);
	sincos(pitch, sin_pitch, cos_pitch);
	sincos(roll, sin_roll, cos_roll);
	this->right[0] = cos_roll * cos_yaw + sin_roll * sin_yaw * sin_pitch;
	this->right[1] = sin_roll * cos_pitch;
	this->right[2] = sin_roll * cos_yaw * sin_pitch - sin_yaw * cos_roll;

	this->up[0] = cos_roll * sin_yaw * sin_pitch - cos_yaw * sin_roll;
	this->up[1] = cos_roll * cos_pitch;
	this->up[2] = sin_roll * sin_yaw + sin_pitch * cos_roll * cos_yaw;

	this->forward[0] = sin_yaw * cos_pitch;
	this->forward[1] = sin_pitch;
	this->forward[2] = cos_yaw * cos_pitch;
}