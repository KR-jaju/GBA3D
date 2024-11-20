#include "mario/Mario.h"
#include "resource/animation.h"
#include "gbavfx/gbavfx.h"

static void	qtor(fixed* dst, fixed x, fixed y, fixed z, fixed w)
{
	fixed xx = x * x;
	fixed yy = y * y;
	fixed zz = z * z;
	fixed wx = w * x;
	fixed wy = w * y;
	fixed wz = w * z;
	fixed xy = x * y;
	fixed xz = x * z;
	fixed yz = y * z;
	dst[0] = fixed(1) - (yy + zz) * 2;
	dst[1] = (xy - wz) * 2;
	dst[2] = (xz + wy) * 2;
	dst[3] = 0;
	dst[4] = (xy + wz) * 2;
	dst[5] = fixed(1) - (xx + zz) * 2;
	dst[6] = (yz - wx) * 2;
	dst[3] = 0;
	dst[8] = (xz - wy) * 2;
	dst[9] = (yz + wx) * 2;
	dst[10] = fixed(1) - (xx + yy) * 2;
	dst[11] = 0;
}

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

void	Mario::updateAnimation(fixed const *mv)
{
	MarioPose pose = this->animation[this->animation_time >> 16];
	for (int bone = 0; bone < 17; bone++)
	{
		fixed bone_matrix[12] = {1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0};
		fixed x = pose[bone][0];
		fixed y = pose[bone][1];
		fixed z = pose[bone][2];

		fixed rx = pose[bone][3];
		fixed ry = pose[bone][4];
		fixed rz = pose[bone][5];
		fixed rw = pose[bone][6];

		qtor(bone_matrix, rx, ry, rz, rw);
		bone_matrix[3] = x;
		bone_matrix[7] = y;
		bone_matrix[11] = z;

		multiply_matrix(gbavfx_matrix_slot[bone], mv, bone_matrix);
	}
	this->animation_time += animation_dt;
}