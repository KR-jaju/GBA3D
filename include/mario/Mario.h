#pragma once

#include "fixed.h"
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
	fixed	pos[3];

	void	update(InputState *input);
	void	render(Lakitu const* lakitu);
private:
	typedef fixed const (*MarioPose)[7];
	typedef fixed const (*MarioAnimation)[17][7];
	MarioAction	action;
	fixed	forward[2];
	fixed	forward_velocity;

	MarioAnimation animation;
	u32		animation_time;
	u32		animation_dt;
	fixed	model_matrix[12];

	void	constructModelMatrix(fixed *dst);

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
	

	void	updateAnimation(fixed const *mv);
};