#include "mario/Mario.h"
#include "fixed.h"
#include "resource/animation.h"

#include <cmath>

constexpr fixed dcos = cosf(6.0f / 180 * 3.141592f);
constexpr fixed dsin = sinf(6.0f / 180 * 3.141592f);

MarioAction	Mario::actionRunning(InputState *input)
{
	if (input->h_raw == 0 && input->v_raw == 0) {
		if (this->forward_velocity < 3.0f)
			return (this->transitionToWalking(input));
		else
			return (this->transitionToStopping(input));
	}
	fixed	dx = this->forward[0];
	fixed	dz = this->forward[1];
	fixed	horizontal = input->h;
	fixed	vertical = -input->v;

	fixed sin_theta = horizontal * dz - vertical * dx;
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
		this->forward_velocity += fixed(0.2f) - this->forward_velocity * fixed(0.0043f);
	} else {
		this->forward_velocity -= 0.187f;
	}
	if (this->forward_velocity > 9.0f) {
		this->forward_velocity = 9.0f;
	}
	this->pos[0] += this->forward[0] * this->forward_velocity * fixed(0.033f);
	this->pos[2] += this->forward[1] * this->forward_velocity * fixed(0.033f);

	if (this->animation_time >= (71 << 16))
		this->animation_time -= (71 << 16);
	return (ACTION_RUNNING);
}

MarioAction	Mario::transitionToRunning(InputState *input)
{
	fixed	dx = this->forward[0];
	fixed	dz = this->forward[1];
	fixed	horizontal = input->h;
	fixed	vertical = -input->v;

	fixed sin_theta = horizontal * dz - vertical * dx;
	// this->forward[0] = horizontal;
	// this->forward[1] = vertical;
	// this->forward_velocity = 0.0f;

	this->animation = mario_running;
	this->animation_time = 0;
	this->animation_dt = (8 << 16);
	return (ACTION_RUNNING);
}
