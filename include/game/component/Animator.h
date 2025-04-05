#pragma once

#include "common.h"
struct AnimationState;

typedef void (*AnimationController)(AnimationState* state, void const* parameter);

struct AnimationMatrix
{
	u32	data[6];

	constexpr AnimationMatrix(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23)
		: data()
	{
		u32 i00 = static_cast<i32>(m00 * 16384);
		u32 i01 = static_cast<i32>(m01 * 16384);
		u32 i02 = static_cast<i32>(m02 * 16384); // Q1.14
		u32 i03 = static_cast<i32>(m03 * 256); // Q7.8
		u32 i10 = static_cast<i32>(m10 * 16384);
		u32 i11 = static_cast<i32>(m11 * 16384);
		u32 i12 = static_cast<i32>(m12 * 16384); // Q1.14
		u32 i13 = static_cast<i32>(m13 * 256); // Q7.8
		u32 i20 = static_cast<i32>(m20 * 16384);
		u32 i21 = static_cast<i32>(m21 * 16384);
		u32 i22 = static_cast<i32>(m22 * 16384); // Q1.14
		u32 i23 = static_cast<i32>(m23 * 256); // Q7.8

		this->data[0] = (i00 << 16) | (i10 << 16 >> 16);
		this->data[1] = (i20 << 16) | (i01 << 16 >> 16);
		this->data[2] = (i11 << 16) | (i21 << 16 >> 16);
		this->data[3] = (i02 << 16) | (i12 << 16 >> 16);
		this->data[4] = (i22 << 16) | (i03 << 16 >> 16);
		this->data[5] = (i13 << 16) | (i23 << 16 >> 16);
	} // row major + bit packing
};


struct AnimationState
{
	AnimationController		next_state;
	AnimationMatrix const*	animation;
	u32						bone_count;
	u32						frame_left;
};

struct Animator
{
	AnimationState state;
	void*	parameter;

	Animator();
	void	update(u32 const* base_matrix, u32* matrix_slot);
};
