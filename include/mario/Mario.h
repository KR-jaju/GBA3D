#pragma once

#include "gbamath/gbamath.h"
#include "InputState.h"

class Lakitu;
enum MarioAction
{
	ACTION_IDLE_LEFT,
	ACTION_IDLE_RIGHT,
	ACTION_IDLE_CENTER,
	ACTION_RUNNING,
	ACTION_WALKING,
	ACTION_SINGLE_JUMP,
	ACTION_DOUBLE_JUMP,
	ACTION_STOPPING,
	ACTION_TURNING_AROUND
};

class Mario
{
public:
	Mario();
	f32	pos[3];

	void	update(InputState *input);
	void	render(Lakitu const* lakitu);
private:
	typedef f32 const (*MarioPose)[7];
	typedef f32 const (*MarioAnimation)[17][7];
	MarioAction	action;
	f32	forward[2];
	f32	forward_velocity;

	MarioAnimation animation;
	u32		animation_time;
	u32		animation_dt;
	f32	model_matrix[12];

	void	constructModelMatrix(f32 *dst);

	MarioAction	actionIdleLeft(InputState *input);
	MarioAction	actionIdleRight(InputState *input);
	MarioAction	actionIdleCenter(InputState *input);
	MarioAction	transitionToIdleLeft(InputState *input);
	MarioAction	transitionToIdleRight(InputState *input);
	MarioAction	transitionToIdleCenter(InputState *input);


	MarioAction	actionRunning(InputState *input);
	MarioAction	transitionToRunning(InputState *input);

	MarioAction	actionWalking(InputState *input);
	MarioAction	transitionToWalking(InputState *input);

	MarioAction	actionSingleJump(InputState *input);
	MarioAction	transitionToSingleJump(InputState *input);

	MarioAction	actionDoubleJump(InputState *input);
	MarioAction	transitionToDoubleJump(InputState *input);

	MarioAction	actionStopping(InputState *input);
	MarioAction	transitionToStopping(InputState *input);
	
	MarioAction	actionTurningAround(InputState *input);
	MarioAction	transitionToTurningAround(InputState *input);
	

	void	updateAnimation(f32 const *mv);
};