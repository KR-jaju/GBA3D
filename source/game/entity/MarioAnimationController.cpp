#include "game/entity/Mario.h"
#include "game/resource/animation.h"
#include "gba/io/Controller.h"
#include "gba/gbadef.h"

static void	crouchStart(AnimationState* state, void const* parameter);
static void	crouching(AnimationState* state, void const* parameter);
static void	crouchEnd(AnimationState* state, void const* parameter);


static void	singleJump(AnimationState* state, void const* parameter);
static void	doubleJumpStart(AnimationState* state, void const* parameter);
static void	doubleJumpEnd(AnimationState* state, void const* parameter);
static void	tripleJump(AnimationState* state, void const* parameter);


static void	idleLeft(AnimationState* state, void const* parameter);
static void	idleRight(AnimationState* state, void const* parameter);
static void	idleCenter(AnimationState* state, void const* parameter);

static void	running(AnimationState* state, void const* parameter);
static void	skidOnGround(AnimationState* state, void const* parameter);



static void	crouchStart(AnimationState* state, void const* parameter)
{
	if (state->frame_left == 0)
	{
		state->next_state = crouching;
		state->animation = mario_animation_crouching;
		state->frame_left = 89;
	}
}

static void	crouching(AnimationState* state, void const* parameter)
{
	Controller* const	controller = &g_controller;

	if (state->frame_left == 0)
	{
		state->animation = mario_animation_crouching;
		state->frame_left = 89;
	}
	if (!(controller->button_down & KEY_L))
	{
		state->next_state = crouchEnd;
		state->animation = mario_animation_crouch_end;
		state->frame_left = 9;
	}
}

static void	crouchEnd(AnimationState* state, void const* parameter)
{
	if (state->frame_left == 0)
	{
		state->next_state = idleLeft;
		state->animation = mario_animation_idle_left;
		state->frame_left = 29;
	}
}

static void	idleLeft(AnimationState* state, void const* parameter)
{
	Controller* const	controller = &g_controller;
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
	if (controller->button_down & KEY_L)
	{
		state->next_state = crouchStart;
		state->frame_left = 5;
		state->animation = mario_animation_crouch_start;
	}
}

static void	idleRight(AnimationState* state, void const* parameter)
{
	Controller* const	controller = &g_controller;
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
	if (controller->button_down & KEY_L)
	{
		state->next_state = crouchStart;
		state->frame_left = 5;
		state->animation = mario_animation_crouch_start;
	}
}

static void	idleCenter(AnimationState* state, void const* parameter)
{
	Controller* const	controller = &g_controller;
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
	if (controller->button_down & KEY_L)
	{
		state->next_state = crouchStart;
		state->frame_left = 5;
		state->animation = mario_animation_crouch_start;
	}
}

static void	running(AnimationState* state, void const* parameter)
{
	MarioControl const* control = reinterpret_cast<MarioControl const*>(parameter);

	if (control->intended_mag == 0)
	{
		if (control->forward_vel >= 16 * 256)
		{
			state->next_state = skidOnGround;
			state->frame_left = 18;
			state->animation = mario_animation_skid_on_ground;
		}
		else
		{
			state->next_state = idleLeft;
			state->frame_left = 29;
			state->animation = mario_animation_idle_left;
		}
	}

	if (state->frame_left == 0)
	{
		state->next_state = running;
		state->frame_left = 9;
		state->animation = mario_animation_running;
	}
}

static void	skidOnGround(AnimationState* state, void const* parameter)
{
	MarioControl const* control = reinterpret_cast<MarioControl const*>(parameter);

	if (control->intended_mag != 0)
	{
		state->next_state = running;
		state->frame_left = 9;
		state->animation = mario_animation_running;
		return;
	}
	if (control->forward_vel != 0)
	{
		state->animation = mario_animation_skid_on_ground;
		state->frame_left = 18;
		return;
	}
	if (state->frame_left == 0)
	{
		state->next_state = idleLeft;
		state->frame_left = 29;
		state->animation = mario_animation_idle_left;
		return;
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
