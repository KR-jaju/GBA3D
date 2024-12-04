#pragma once

#include "gbamath/gbamath.h"
#include "InputState.h"
#include "transform/Transform.h"

class Lakitu;

class Mario
{
public:
	Mario();
	
	void	update(InputState *input);
	void	render(Lakitu const* lakitu);
private:
	typedef f32 const (*MarioPose)[7];
	typedef f32 const (*MarioAnimation)[17][7];
	typedef bool (Mario::*MarioAction)(InputState *);
	MarioAction	action;
	Transform	transform;
	i32	yaw;
	i32	pitch;
	i32	roll;

	i32	intended_yaw;

	f32	forward[2];
	f32	forward_velocity;
	f32 velocity[3];
	MarioAnimation animation;
	u32		animation_time;
	u32		animation_dt;
	f32		model_matrix[12];
	
	bool	actionIdleLeft(InputState *input);
	bool	actionIdleRight(InputState *input);
	bool	actionIdleCenter(InputState *input);

	bool	actionReorient(InputState *input);

	bool	actionRunning(InputState *input);
	void	updateWalkingSpeed(InputState *input);

	bool	actionStopping(InputState *input);

	void	updateAnimation(f32 const *mv);

	void	performStep();
};