#pragma once

#include "gba/math/math.h"
#include "game/component/Transform.h"
#include "game/component/Animator.h"
#include "game/component/MarioControl.h"

class Lakitu;

class Mario
{
public:
	static void	animationEntry(AnimationState* state, void const* parameter);

	Mario();
	
	// void	update(InputState *input);
	void	update();
	void	render();
private:
	Transform		transform;
	Animator		animator;
	MarioControl	control;

	i32	yaw;
	i32	pitch;
	i32	roll;

	i32	intended_yaw;
};
