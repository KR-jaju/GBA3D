#pragma once

#include "common.h"

#define ACT_GROUP_MASK 0x000001C0

#define ACT_GROUP_STATIONARY (0 << 6)
#define ACT_GROUP_MOVING (1 << 6)
#define ACT_GROUP_AIRBORNE (2 << 6)
#define ACT_GROUP_SUBMERGED (3 << 6)
#define ACT_GROUP_CUTSCENE (4 << 6)
#define ACT_GROUP_AUTOMATIC (5 << 6)
#define ACT_GROUP_OBJECT (6 << 6)

// enum class GroupStep
// {
// 	LeftGround,
// 	StepNone,
// 	StepHitWall
// };

struct MarioControl
{
	i32		yaw;
	i32		intended_mag;
	i32		intended_yaw;
	i32		squish_timer;
	i32		forward_vel;

	i32		velocity_x;
	i32		velocity_y;
	i32		velocity_z;

	u32		action;

	MarioControl();
	void	update();
private:
	void	updateInputs();
	void	updateJoystickInputs();
	

	// bool	executeStationary();
	bool	actGroupStationary();

	bool	actGroupMoving();
	bool	actWalking();
	void	updateWalkingSpeed();
	void	applySlopeAccel();

	void	applyAcceleration();
};
