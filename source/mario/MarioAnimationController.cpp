#include "mario/Mario.h"
#include "resource/animation.h"

static void	idleLeft(AnimationState* state, void const* parameter);
static void	idleRight(AnimationState* state, void const* parameter);
static void	idleCenter(AnimationState* state, void const* parameter);

static void	idleLeft(AnimationState* state, void const* parameter)
{
	if (state->frame_left == 0)
	{
		state->next_state = idleRight;
		state->frame_left = 29;
		state->animation = mario_animation1;
	}
}

static void	idleRight(AnimationState* state, void const* parameter)
{
	if (state->frame_left == 0)
	{
		state->next_state = idleCenter;
		state->frame_left = 29;
		state->animation = mario_animation2;
	}
}

static void	idleCenter(AnimationState* state, void const* parameter)
{
	if (state->frame_left == 0)
	{
		state->next_state = idleLeft;
		state->frame_left = 29;
		state->animation = mario_animation0;
	}
}

void	Mario::animationEntry(AnimationState* state, void const* parameter)
{
	state->next_state = idleLeft;
	state->animation = mario_animation0;
	state->bone_count = 17;
	state->frame_left = 29;
	idleLeft(state, parameter);
}
