#pragma once

#include "gbamath/gbamath.h"
#include "InputState.h"
#include "component/Transform.h"
#include "component/Animator.h"

class Lakitu;

class Mario
{
public:
	static void	animationEntry(AnimationState* state, void const* parameter);

	Mario();
	
	void	update(InputState *input);
	void	render();
private:
	Transform	transform;
	Animator	animator;
	i32	yaw;
	i32	pitch;
	i32	roll;

	i32	intended_yaw;
};
