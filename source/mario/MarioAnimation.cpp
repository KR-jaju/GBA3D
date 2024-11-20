#include "mario/Mario.h"
#include "resource/animation.h"
#include "gbavfx/gbavfx.h"

static void	qtor(f32* dst, f32 x, f32 y, f32 z, f32 w)
{
	f32 xx = x * x;
	f32 yy = y * y;
	f32 zz = z * z;
	f32 wx = w * x;
	f32 wy = w * y;
	f32 wz = w * z;
	f32 xy = x * y;
	f32 xz = x * z;
	f32 yz = y * z;
	dst[0] = f32(1) - (yy + zz) * 2;
	dst[1] = (xy - wz) * 2;
	dst[2] = (xz + wy) * 2;
	dst[3] = 0;
	dst[4] = (xy + wz) * 2;
	dst[5] = f32(1) - (xx + zz) * 2;
	dst[6] = (yz - wx) * 2;
	dst[3] = 0;
	dst[8] = (xz - wy) * 2;
	dst[9] = (yz + wx) * 2;
	dst[10] = f32(1) - (xx + yy) * 2;
	dst[11] = 0;
}

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

void	Mario::updateAnimation(f32 const *mv)
{
	MarioPose pose = this->animation[this->animation_time >> 16];
	for (int bone = 0; bone < 17; bone++)
	{
		f32 bone_matrix[12] = {1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0};
		f32 x = pose[bone][0];
		f32 y = pose[bone][1];
		f32 z = pose[bone][2];

		f32 rx = pose[bone][3];
		f32 ry = pose[bone][4];
		f32 rz = pose[bone][5];
		f32 rw = pose[bone][6];

		qtor(bone_matrix, rx, ry, rz, rw);
		bone_matrix[3] = x;
		bone_matrix[7] = y;
		bone_matrix[11] = z;

		multiply_matrix(gbavfx_matrix_slot[bone], mv, bone_matrix);
	}
	this->animation_time += animation_dt;
}