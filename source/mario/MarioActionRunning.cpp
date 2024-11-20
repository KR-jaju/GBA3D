#include "mario/Mario.h"
#include "gbamath/gbamath.h"
#include "resource/animation.h"

#include <cmath>

constexpr f32 dcos = cosf(6.0f / 180 * 3.141592f);
constexpr f32 dsin = sinf(6.0f / 180 * 3.141592f);

MarioAction	Mario::actionRunning(InputState *input)
{
	if (input->h_raw == 0 && input->v_raw == 0) {
		if (this->forward_velocity < 3.0f)
			return (this->transitionToWalking(input));
		else
			return (this->transitionToStopping(input));
	}
	f32	dx = this->forward[0];
	f32	dz = this->forward[1];
	f32	horizontal = input->h;
	f32	vertical = -input->v;

	f32 sin_theta = horizontal * dz - vertical * dx;
	if (this->forward[0] * horizontal + this->forward[1] * vertical < -0.95f)
	{
		if(this->forward_velocity >= 5.0f)
			return (this->transitionToTurningAround(input));
	}
	if (sin_theta < 0){ // turn left
		this->forward[0] = dcos * dx - dsin * dz;
		this->forward[1] = dsin * dx + dcos * dz;
	} else {
		this->forward[0] = dcos * dx + dsin * dz;
		this->forward[1] = dcos * dz - dsin * dx;
	}
	if (this->forward_velocity <= 0) {
		this->forward_velocity += 0.2f;
	} else if (this->forward_velocity <= 6.0f) {
		this->forward_velocity += f32(0.2f) - this->forward_velocity * f32(0.0043f);
	} else {
		this->forward_velocity -= 0.187f;
	}
	if (this->forward_velocity > 9.0f) {
		this->forward_velocity = 9.0f;
	}
	this->pos[0] += this->forward[0] * this->forward_velocity * f32(0.033f);
	this->pos[2] += this->forward[1] * this->forward_velocity * f32(0.033f);

	if (this->animation_time >= (71 << 16))
		this->animation_time -= (71 << 16);
	return (ACTION_RUNNING);
}

MarioAction	Mario::transitionToRunning(InputState *input)
{
	f32	dx = this->forward[0];
	f32	dz = this->forward[1];
	f32	horizontal = input->h;
	f32	vertical = -input->v;

	f32 sin_theta = horizontal * dz - vertical * dx;
	// this->forward[0] = horizontal;
	// this->forward[1] = vertical;
	// this->forward_velocity = 0.0f;

	this->animation = mario_running;
	this->animation_time = 0;
	this->animation_dt = (8 << 16);
	return (ACTION_RUNNING);
}
