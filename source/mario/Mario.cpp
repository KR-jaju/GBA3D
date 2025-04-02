#include "mario/Mario.h"
#include "resource/model.h"
#include "mode8/mode8.h"
#include "lakitu/Lakitu.h"

#include "resource/animation.h"

Mario::Mario()
	: transform()
{
	this->animator.state.next_state = &Mario::animationEntry;
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

	this->transform.update(base_matrix);
	this->animator.update(base_matrix, &mode8::context.matrix_slot[0][0]);
	mode8::drawIndexed(::vertices, ::vertex_count, ::indices, 0);
}
