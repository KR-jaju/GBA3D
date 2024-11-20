#include "mario/Mario.h"
#include "resource/model.h"
#include "gbavfx/gbavfx.h"
#include "lakitu/Lakitu.h"

#include "resource/animation.h"

#include "GBAinput.hpp"


static void	multiply_matrix(fixed *dst, fixed const *a, fixed const *b)
{
	dst[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8];
	dst[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9];
	dst[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10];
	dst[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3];

	dst[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8];
	dst[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9];
	dst[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10];
	dst[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7];

	dst[8] = a[8] * b[0] + a[9] * b[4] + a[10] * b[8];
	dst[9] = a[8] * b[1] + a[9] * b[5] + a[10] * b[9];
	dst[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10];
	dst[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11];
}

Mario::Mario()
{
	this->action = ACTION_IDLE_LEFT;

	this->forward[0] = 0;
	this->forward[1] = 1;

	this->forward_velocity = 0;

	this->pos[0] = 0;
	this->pos[1] = 0;
	this->pos[2] = 0;

	this->animation = mario_idle_left;
	this->animation_time = 0;
	this->animation_dt = (1 << 16);
}

/*
1. 액션 실행
2. 트랜지션
*/
void	Mario::update(InputState *input)
{
	switch (this->action)
	{
	case ACTION_IDLE_LEFT:
		this->action = actionIdleLeft(input);
		break;
	case ACTION_IDLE_RIGHT:
		this->action = actionIdleRight(input);
		break;
	case ACTION_IDLE_CENTER:
		this->action = actionIdleCenter(input);
		break;
	case ACTION_RUNNING:
		this->action = actionRunning(input);
		break;
	case ACTION_WALKING:
		this->action = actionWalking(input);
		break;
	case ACTION_SINGLE_JUMP:
		this->action = actionSingleJump(input);
		break;
	case ACTION_DOUBLE_JUMP:
		this->action = actionDoubleJump(input);
		break;
	case ACTION_STOPPING:
		this->action = actionStopping(input);
		break;
	case ACTION_TURNING_AROUND:
		this->action = this->actionTurningAround(input);
		break;
	}
}

void	Mario::render(Lakitu const* lakitu)
{
	fixed	mv[12];
	fixed	model_matrix[12];

	this->constructModelMatrix(model_matrix);
	multiply_matrix(mv, lakitu->getViewMatrix(), model_matrix);
	this->updateAnimation(mv);
	gbavfx_drawSkinned(vertices, vertex_count, indices, 368, 0, 17);
}

void	Mario::constructModelMatrix(fixed *dst)
{
	fixed *forward = this->forward;

	dst[0] = forward[1];
	dst[1] = 0;
	dst[2] = forward[0];
	dst[3] = this->pos[0];

	dst[4] = 0;
	dst[5] = 1;
	dst[6] = 0;
	dst[7] = this->pos[1];

	dst[8] = -forward[0];
	dst[9] = 0;
	dst[10] = forward[1];
	dst[11] = this->pos[2];
}
