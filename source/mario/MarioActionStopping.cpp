#include "mario/Mario.h"
#include "resource/animation.h"

MarioAction	Mario::actionStopping(InputState *input)
{
	i32 raw_horizontal = input->h_raw;
	i32 raw_vertical = -input->v_raw;

	if (raw_horizontal != 0 || raw_vertical != 0)
		return (this->transitionToRunning(input));

	fixed	horizontal = input->h;
	fixed	vertical = -input->v;
	if (this->forward[0] * horizontal + this->forward[1] * vertical < -0.95f)
	{
		if(this->forward_velocity >= 5.0f)
			return (this->transitionToTurningAround(input));
	}

	this->forward_velocity -= 1.125f;
	if (this->forward_velocity < 0)
		this->forward_velocity = 0;
	if (this->forward_velocity == 0)
		this->animation_dt = (1 << 16);
	this->pos[0] += this->forward[0] * this->forward_velocity * fixed(0.033f);
	this->pos[2] += this->forward[1] * this->forward_velocity * fixed(0.033f);
	if (this->animation_time >= (18 << 16))
		return (this->transitionToIdleLeft(input));
	return (ACTION_STOPPING);
}

MarioAction	Mario::transitionToStopping(InputState *input)
{
	this->animation = mario_stopping;
	this->animation_time = 0;
	this->animation_dt = 0;
	return (ACTION_STOPPING);
}