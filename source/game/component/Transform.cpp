#include "game/component/Transform.h"
#include "gba/math/fixed.h"


Transform::Transform()
	: x(0), y(0), z(0), yaw(0), pitch(0)
{}
/*
 T * R
 T * Ry * Rx
*/
void	Transform::update(u32* result)
{
	u32 sincos_yaw = fixed::sincos(this->yaw);
	u32 sincos_pitch = fixed::sincos(this->pitch);
	i32 sin_yaw = ((i32)sincos_yaw) >> 16; // Q1.14
	i32 cos_yaw = ((i32)sincos_yaw << 16) >> 16; // Q1.14
	i32 sin_pitch = ((i32)sincos_pitch) >> 16; // Q1.14
	i32 cos_pitch = ((i32)sincos_pitch << 16) >> 16; // Q1.14

	result[0] = cos_yaw;
	result[1] = (-sin_yaw * sin_pitch) >> 14;
	result[2] = (-sin_yaw * cos_pitch) >> 14;
	result[3] = this->x >> 8;

	result[4] = 0;
	result[5] = cos_pitch;
	result[6] = -sin_pitch;
	result[7] = this->y >> 8;

	result[8] = sin_yaw;
	result[9] = (cos_yaw * sin_pitch) >> 14;
	result[10] = (cos_yaw * cos_pitch) >> 14;
	result[11] = this->z >> 8;
}


