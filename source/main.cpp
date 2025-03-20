
//#include "Mesh.hpp"
//#include "Rasterizer.hpp"
#include "control.hpp"
// #include <gba_systemcalls.h>
#include "debug.hpp"

#include "gbavfx/gbavfx.h"
#include "gbavfx/TestVertex.h"
#include "resource/model.h"
#include "resource/texture.h"
#include "resource/animation.h"
#include "scene/Scene.h"
#include "scene/SceneA.h"
#include "gbadef.h"
#include <stdio.h>
#include "gbavfx/mode8.h"

void optimize_ewram() {
    REG_WAITCNT = (REG_WAITCNT & ~0x0030) | 0x000E;  // EWRAM wait state를 0x0E로 설정
}

#define DCNT_MODE4			0x0004	//!< Mode 4; bg2: 240x160\@8 bitmap
#define DCNT_BG2			0x0400	//!< Enable bg 2

char debug_buffer[200];

int	main() {
	// optimize_ewram(); // mgba에서는 더 느려짐!
	
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2; // 화면 모드 설정
	// init_palettes();
	// for (int i = 0; i < 64 * 64; ++i)
	// {
	// 	gbavfx_texture_slot[0][i] = mario_test[i];
	// }
	// control cnt;
	// int start = clock_get();
	// if(key_held(KEY_A)) cnt.clickJump = true;
	// cnt.playerControll();
	// cnt.checkCollision();
	gbavfx_init();
	SceneId scene_id = SCENE_A;

	mode8::init();
	while (true)
	{
		if (scene_id == SCENE_A)
		{
			SceneA scene;

			while (true)
			{
				scene.update();
			}
		}
	}
}



void	qtor(f32* dst, f32 x, f32 y, f32 z, f32 w)
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


void	view(f32 *matrix, f32 pos[3], f32 dir[3]) {
	matrix[0] = dir[2];
	matrix[1] = 0;
	matrix[2] = -dir[0];
	matrix[3] = -(pos[0] * matrix[0] + pos[2] * matrix[2]);

	matrix[4] = dir[0] * dir[1];
	matrix[5] = -(dir[0] * dir[0] + dir[2] * dir[2]);
	matrix[6] = dir[1] * dir[2];
	matrix[7] = -(pos[0] * matrix[4] + pos[1] * matrix[5] + pos[2] * matrix[6]);

	matrix[8] = dir[0];
	matrix[9] = dir[1];
	matrix[10] = dir[2];
	matrix[11] = -(pos[0] * matrix[8] + pos[1] * matrix[9] + pos[2] * matrix[10]);
}

void	multiply_matrix(f32 *dst, f32 *a, f32 *b)
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
