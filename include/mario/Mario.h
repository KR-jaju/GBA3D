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

	/*
	1. 달리기나 멈추기 등등, 액션 종류
	애니매이션이랑 업데이트가 긴밀하게 연결되게 하는게 맞을까?
	애니매이션은 애니매이션 만의 상태머신을 가지고,
	업데이트는 상태머신 없이 수행하는게 좋지 않을까? 변수만 써서도 상태머신을 만들 수 있기도 하고.
	그렇다 애니매이션은 나누는 것이 좋은 것이었던 것이다.
	그렇다면 트랜지션은 어떻게 표현하지.
	강제로 애니매이션과 프레임을 넣는다면?
	애니매이션 클립과 애니매이션 상태가 결합돼있을 필요는 없다. 하지만 정적인 것은 정적으로 두는게 좋을거같은데
	
	*/
	
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