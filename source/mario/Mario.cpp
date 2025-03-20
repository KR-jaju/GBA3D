#include "mario/Mario.h"
#include "resource/model.h"
#include "gbavfx/gbavfx.h"
#include "lakitu/Lakitu.h"

#include "resource/animation.h"


static void	multiply_matrix(f32 *dst, f32 const *a, f32 const *b)
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
	: transform()
{
	this->action = &Mario::actionIdleCenter;

	this->forward[0] = 0;
	this->forward[1] = 1;

	this->forward_velocity = 0;

	this->animation = mario_idle_center;
	this->animation_time = 0;
	this->animation_dt = (1 << 16);
}

/*
1. 액션 실행
2. 트랜지션
*/
void	Mario::update(InputState *input)
{
	do
	{
		if (!(this->*(this->action))(input))
			break;
	} while(true);
}

void	Mario::render(Lakitu const* lakitu)
{
	mat4	mv;

	this->transform.recalculateDirection(this->yaw, this->pitch, this->roll);
	mv = this->transform.composite(lakitu->getViewMatrix());
	this->updateAnimation(mv.m);
	// gbavfx_drawSkinned(vertices, vertex_count, indices, 368, 0, 17);
}
