#include "mario/Mario.h"
#include "resource/animation.h"


MarioAction	Mario::actionWalking(InputState *input)
{
	i32 raw_horizontal = input->h_raw;
	i32 raw_vertical = -input->v_raw;

	if (raw_horizontal != 0 || raw_vertical != 0)
		return (this->transitionToRunning(input));
	this->forward_velocity -= 0.18f;
	if (this->forward_velocity <= 0)
		return (this->forward_velocity = 0, this->transitionToIdleLeft(input));
	this->pos[0] += this->forward[0] * this->forward_velocity * fixed(0.033f);
	this->pos[2] += this->forward[1] * this->forward_velocity * fixed(0.033f);
	if (this->animation_time >= (76 << 16))
		this->animation_time -= (76 << 16);
	return (ACTION_WALKING);
}

MarioAction	Mario::transitionToWalking(InputState *input)
{
	this->animation = mario_walking; // walking
	this->animation_time = 0;
	this->animation_dt = this->forward_velocity.num;
	return (ACTION_WALKING);
}
