#include "gbamath/mat4.h"
#include "gbamath/gbamath.h"

mat4	mat4::operator*(mat4 const& other) const
{
	mat4	result;

	result.m[0] = this->m[0] * other.m[0] + this->m[1] * other.m[4] + this->m[2] * other.m[8];
	result.m[1] = this->m[0] * other.m[1] + this->m[1] * other.m[5] + this->m[2] * other.m[9];
	result.m[2] = this->m[0] * other.m[2] + this->m[1] * other.m[6] + this->m[2] * other.m[10];
	result.m[3] = this->m[0] * other.m[3] + this->m[1] * other.m[7] + this->m[2] * other.m[11] + this->m[3];

	result.m[4] = this->m[4] * other.m[0] + this->m[5] * other.m[4] + this->m[6] * other.m[8];
	result.m[5] = this->m[4] * other.m[1] + this->m[5] * other.m[5] + this->m[6] * other.m[9];
	result.m[6] = this->m[4] * other.m[2] + this->m[5] * other.m[6] + this->m[6] * other.m[10];
	result.m[7] = this->m[4] * other.m[3] + this->m[5] * other.m[7] + this->m[6] * other.m[11] + this->m[7];

	result.m[8] = this->m[8] * other.m[0] + this->m[9] * other.m[4] + this->m[10] * other.m[8];
	result.m[9] = this->m[8] * other.m[1] + this->m[9] * other.m[5] + this->m[10] * other.m[9];
	result.m[10] = this->m[8] * other.m[2] + this->m[9] * other.m[6] + this->m[10] * other.m[10];
	result.m[11] = this->m[8] * other.m[3] + this->m[9] * other.m[7] + this->m[10] * other.m[11] + this->m[11];
	
	return (result);
}

mat4	mat4::identity()
{
	mat4	result = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0
	};
	return (result);
}

mat4	mat4::createViewMatrix(f32 const *position, i32 yaw, i32 pitch)
{
	mat4	result;
	f32		sin_yaw;
	f32		cos_yaw;
	f32		sin_pitch;
	f32		cos_pitch;

	sincos(yaw, sin_yaw, cos_yaw);
	sincos(pitch, sin_pitch, cos_pitch);
	result.m[8] = sin_yaw * cos_pitch;
	result.m[9] = sin_pitch;
	result.m[10] = cos_yaw * cos_pitch; // z
	result.m[11] = -(position[0] * result.m[8] + position[1] * result.m[9] + position[2] * result.m[10]);

	result.m[0] = result.m[10];
	result.m[1] = 0;
	result.m[2] = -result.m[8]; // x
	result.m[3] = -(position[0] * result.m[0] + position[1] * result.m[1] + position[2] * result.m[2]);

	result.m[4] = result.m[8] * result.m[9];
	result.m[5] = -(result.m[8] * result.m[8] + result.m[10] * result.m[10]);
	result.m[6] = result.m[9] * result.m[10]; // y
	result.m[7] = -(position[0] * result.m[4] + position[1] * result.m[5] + position[2] * result.m[6]);
	
	return (result);
}