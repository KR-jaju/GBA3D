#pragma once

#include "common.h"
struct AnimationState;

typedef void (*AnimationController)(AnimationState* state, void const* parameter);

struct AnimationState
{
	AnimationController	next_state;
	u32 const*			animation;
	u32					bone_count;
	u32					frame_left;
	u32					time;
};// bone_count * 

struct Animator
{
	AnimationState state;
	void*	parameter;
	u32		time;

	Animator();
	void	update(u32 const* base_matrix, u32* matrix_slot);
};
