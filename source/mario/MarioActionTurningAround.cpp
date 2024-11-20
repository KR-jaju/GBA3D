#include "mario/Mario.h"
#include "resource/animation.h"
#include <cmath>

constexpr f32 dcos = cosf(6.0f / 180 * 3.141592f);
constexpr f32 dsin = sinf(6.0f / 180 * 3.141592f);

MarioAction	Mario::actionTurningAround(InputState *input)
{
	// i32 raw_horizontal = input->h_raw;
	// i32 raw_vertical = -getVertical(input);

	// if (raw_horizontal == 0 && raw_vertical == 0) {
	// 	if (this->forward_velocity < 3.0f)
	// 		return (this->transitionToWalking(input));
	// 	else
	// 		return (this->transitionToStopping(input));
	// }
	f32	dx = this->forward[0];
	f32	dz = this->forward[1];
	f32	horizontal = input->h;
	f32	vertical = -input->v;

	if (this->animation_time <= (3 << 16)) {
		if (this->forward[0] * horizontal + this->forward[1] * vertical > 0.173f)
			return (this->transitionToWalking(input));
		this->forward_velocity -= 1.125f;
		if (this->forward_velocity < 0)
			this->forward_velocity = 0;
	} else {
		if (this->forward[0] * horizontal + this->forward[1] * vertical < -0.95f)
		{
			if(this->forward_velocity >= 5.0f)
				return (this->transitionToTurningAround(input));
		}
		f32 sin_theta = horizontal * dz - vertical * dx;
		if (sin_theta < 0){ // turn left
			this->forward[0] = dcos * dx + dsin * dz;
			this->forward[1] = dcos * dz - dsin * dx;
		} else {
			this->forward[0] = dcos * dx - dsin * dz;
			this->forward[1] = dsin * dx + dcos * dz;
		} 

		if (this->forward_velocity >= -4.0f) {
			this->forward_velocity = -4.0f;
		} else if (this->forward_velocity <= 6.0f) {
			this->forward_velocity -= f32(0.2f) + this->forward_velocity * f32(0.0043f);
		} else {
			this->forward_velocity += 0.187f;
		}
		if (this->forward_velocity < -9.0f) {
			this->forward_velocity = -9.0f;
		}
	}
	this->pos[0] += this->forward[0] * this->forward_velocity * f32(0.033f);
	this->pos[2] += this->forward[1] * this->forward_velocity * f32(0.033f);

	if (this->animation_time >= (17 << 16)) {
		this->forward[0] *= -1;
		this->forward[1] *= -1;
		this->forward_velocity *= -1;

		return (this->transitionToRunning(input));
	}
	return (ACTION_TURNING_AROUND);
}

MarioAction	Mario::transitionToTurningAround(InputState *input)
{
	this->animation = mario_turning_around;
	this->animation_time = 0;
	this->animation_dt = (1 << 16);
	return (ACTION_TURNING_AROUND);
}
