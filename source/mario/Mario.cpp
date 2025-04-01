#include "mario/Mario.h"
#include "resource/model.h"
#include "gbavfx/gbavfx.h"
#include "lakitu/Lakitu.h"

#include "resource/animation.h"

Mario::Mario()
	: transform()
{
	// this->action = &Mario::actionIdleCenter;

	// this->forward[0] = 0;
	// this->forward[1] = 1;

	// this->forward_velocity = 0;

	// this->animation = mario_idle_center;
	// this->animation_time = 0;
	// this->animation_dt = (1 << 16);
}

/*
1. 액션 실행
2. 트랜지션
*/
void	Mario::update(InputState *input)
{

}

void	Mario::render()
{
	u32	base_matrix[12];

	// this->transform.update(base_matrix);
	this->transform.update(&mode8::context.matrix_slot[0][0]);
	// this->animator.update(base_matrix, &mode8::context.matrix_slot[0][0]);
	mode8::drawIndexed(::vertices, ::vertex_count, ::indices, 0);
	// this->transform.recalculateDirection(this->yaw, this->pitch, this->roll);
	// mv = this->transform.composite(lakitu->getViewMatrix());
	// this->updateAnimation(mv.m);
	// gbavfx_drawSkinned(vertices, vertex_count, indices, 368, 0, 17);
}
