#include "component/Animator.h"

Animator::Animator()
	: state(), parameter()
{
}

void	Animator::update(u32 const* base_matrix, u32* matrix_slot)
{
	AnimationState* state = &this->state;

	this->state.next_state(state, this->parameter);
	for (int bone_id = 0; bone_id < state->bone_count; ++bone_id)
	{
		i32	i00 = (i32)state->animation->data[0] >> 16;
		i32	i10 = ((i32)state->animation->data[0] << 16) >> 16;
		i32	i20 = (i32)state->animation->data[1] >> 16;
		i32	i01 = ((i32)state->animation->data[1] << 16) >> 16;
		i32	i11 = (i32)state->animation->data[2] >> 16;
		i32	i21 = ((i32)state->animation->data[2] << 16) >> 16;
		i32	i02 = (i32)state->animation->data[3] >> 16;
		i32	i12 = ((i32)state->animation->data[3] << 16) >> 16;
		i32	i22 = (i32)state->animation->data[4] >> 16;
		i32	i03 = ((i32)state->animation->data[4] << 16) >> 16;
		i32	i13 = (i32)state->animation->data[5] >> 16;
		i32	i23 = ((i32)state->animation->data[5] << 16) >> 16;
		state->animation += 1; // next bone

		matrix_slot[0] = (i00 * base_matrix[0] + i10 * base_matrix[1] + i20 * base_matrix[2]) >> 14;
		matrix_slot[1] = (i01 * base_matrix[0] + i11 * base_matrix[1] + i21 * base_matrix[2]) >> 14;
		matrix_slot[2] = (i02 * base_matrix[0] + i12 * base_matrix[1] + i22 * base_matrix[2]) >> 14;
		matrix_slot[3] = ((i03 * base_matrix[0] + i13 * base_matrix[1] + i23 * base_matrix[2]) >> 14) + base_matrix[3];

		matrix_slot[4] = (i00 * base_matrix[4] + i10 * base_matrix[5] + i20 * base_matrix[6]) >> 14;
		matrix_slot[5] = (i01 * base_matrix[4] + i11 * base_matrix[5] + i21 * base_matrix[6]) >> 14;
		matrix_slot[6] = (i02 * base_matrix[4] + i12 * base_matrix[5] + i22 * base_matrix[6]) >> 14;
		matrix_slot[7] = ((i03 * base_matrix[4] + i13 * base_matrix[5] + i23 * base_matrix[6]) >> 14) + base_matrix[7];

		matrix_slot[8] = (i00 * base_matrix[8] + i10 * base_matrix[9] + i20 * base_matrix[10]) >> 14;
		matrix_slot[9] = (i01 * base_matrix[8] + i11 * base_matrix[9] + i21 * base_matrix[10]) >> 14;
		matrix_slot[10] = (i02 * base_matrix[8] + i12 * base_matrix[9] + i22 * base_matrix[10]) >> 14;
		matrix_slot[11] = ((i03 * base_matrix[8] + i13 * base_matrix[9] + i23 * base_matrix[10]) >> 14) + base_matrix[11];
		matrix_slot += 12;
	}
	state->frame_left -= 1; // one frame consumed
}