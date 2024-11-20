#include "mario/Mario.h"
#include "resource/animation.h"
#include "InputState.h"

MarioAction	Mario::actionIdleLeft(InputState *input)
{
	i32 raw_horizontal = input->h_raw;
	i32 raw_vertical = -input->v_raw;

	if (raw_horizontal != 0 || raw_vertical != 0)
		return (transitionToRunning(input));

	if (this->animation_time >= (29 << 16))
		return (this->transitionToIdleRight(input));
	return (ACTION_IDLE_LEFT);
}
MarioAction	Mario::actionIdleRight(InputState *input)
{
	i32 raw_horizontal = input->h_raw;
	i32 raw_vertical = -input->v_raw;

	if (raw_horizontal != 0 || raw_vertical != 0)
		return (transitionToRunning(input));
	if (this->animation_time >= (29 << 16))
		return (this->transitionToIdleCenter(input));
	return (ACTION_IDLE_RIGHT);
}
MarioAction	Mario::actionIdleCenter(InputState *input)
{
	i32 raw_horizontal = input->h_raw;
	i32 raw_vertical = -input->v_raw;

	if (raw_horizontal != 0 || raw_vertical != 0)
		return (transitionToRunning(input));
	if (this->animation_time >= (29 << 16))
		return (this->transitionToIdleLeft(input));
	return (ACTION_IDLE_CENTER);
}


MarioAction	Mario::transitionToIdleLeft(InputState *input)
{
	this->animation = mario_idle_left;
	this->animation_time = 0;
	this->animation_dt = (1 << 16);
	return (ACTION_IDLE_LEFT);
}
MarioAction	Mario::transitionToIdleRight(InputState *input)
{
	this->animation = mario_idle_right;
	this->animation_time = 0;
	this->animation_dt = (1 << 16);
	return (ACTION_IDLE_RIGHT);
}
MarioAction	Mario::transitionToIdleCenter(InputState *input)
{
	this->animation = mario_idle_center;
	this->animation_time = 0;
	this->animation_dt = (1 << 16);
	return (ACTION_IDLE_CENTER);
}
