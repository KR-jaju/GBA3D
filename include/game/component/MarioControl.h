#pragma once

#include "common.h"
#include "game/entity/MarioAction.h"

#define ACT_GROUP_MASK 0x000001C0

#define ACT_GROUP_STATIONARY (0 << 6)
#define ACT_GROUP_MOVING (1 << 6)
#define ACT_GROUP_AIRBORNE (2 << 6)
#define ACT_GROUP_SUBMERGED (3 << 6)
#define ACT_GROUP_CUTSCENE (4 << 6)
#define ACT_GROUP_AUTOMATIC (5 << 6)
#define ACT_GROUP_OBJECT (6 << 6)

struct MarioControl
{
	i32			yaw;
	i32			intended_mag;
	i32			intended_yaw;
	i32			squish_timer;
	i32			forward_vel;

	i32			action_state;
	// i32			action_argument;


	i32			velocity_x;
	i32			velocity_y;
	i32			velocity_z;

	MarioAction	action;

	MarioControl();
	void	update();
private:
	void	updateInputs();
	void	updateJoystickInputs();
	
	

	// bool	executeStationary();
	bool	actGroupStationary();

	bool	actGroupMoving();
	bool	actWalking();
	void	actBraking();
	void	actDecelerating();

	void	setMarioAction(MarioAction action);
	void	setMarioActionMoving(MarioAction action);


	void	beginBraking();
	void	updateWalkingSpeed();
	void	applySlopeAccel();

	void	applyAcceleration();
};
