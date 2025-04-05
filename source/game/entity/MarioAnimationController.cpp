#include "game/entity/Mario.h"
#include "game/resource/animation.h"

static void	idleLeft(AnimationState* state, void const* parameter);
static void	idleRight(AnimationState* state, void const* parameter);
static void	idleCenter(AnimationState* state, void const* parameter);

static void	running(AnimationState* state, void const* parameter);

static void	idleLeft(AnimationState* state, void const* parameter)
{
	MarioControl const* control = reinterpret_cast<MarioControl const*>(parameter);

	if (state->frame_left == 0)
	{
		state->next_state = idleRight;
		state->frame_left = 29;
		state->animation = mario_animation_idle_right;
	}
	if (control->forward_vel > 0)
	{
		state->next_state = running;
		state->frame_left = 9;
		state->animation = mario_animation_running;
	}
}

static void	idleRight(AnimationState* state, void const* parameter)
{
	MarioControl const* control = reinterpret_cast<MarioControl const*>(parameter);

	if (state->frame_left == 0)
	{
		state->next_state = idleCenter;
		state->frame_left = 29;
		state->animation = mario_animation_idle_center;
	}
	if (control->forward_vel > 0)
	{
		state->next_state = running;
		state->frame_left = 9;
		state->animation = mario_animation_running;
	}
}

static void	idleCenter(AnimationState* state, void const* parameter)
{
	MarioControl const* control = reinterpret_cast<MarioControl const*>(parameter);

	if (state->frame_left == 0)
	{
		state->next_state = idleLeft;
		state->frame_left = 29;
		state->animation = mario_animation_idle_left;
	}
	if (control->forward_vel > 0)
	{
		state->next_state = running;
		state->frame_left = 9;
		state->animation = mario_animation_running;
	}
}

static void	running(AnimationState* state, void const* parameter)
{
	MarioControl const* control = reinterpret_cast<MarioControl const*>(parameter);

	if (control->forward_vel == 0)
	{
		state->next_state = idleLeft;
		state->frame_left = 29;
		state->animation = mario_animation_idle_left;
	}

	if (state->frame_left == 0)
	{
		state->next_state = running;
		state->frame_left = 9;
		state->animation = mario_animation_running;
	}
}

void	Mario::animationEntry(AnimationState* state, void const* parameter)
{
	state->next_state = idleLeft;
	state->animation = mario_animation_idle_left;
	state->bone_count = 17;
	state->frame_left = 29;
	idleLeft(state, parameter);
}
