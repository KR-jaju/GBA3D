
//#include "Mesh.hpp"
//#include "Rasterizer.hpp"
#include "control.hpp"
// #include <gba_systemcalls.h>
#include "clock.hpp"
#include "debug.hpp"

#include "gbavfx/gbavfx.h"
#include "gbavfx/TestVertex.h"
#include "resource/model.h"
#include "resource/texture.h"
#include "resource/animation.h"
#include "scene/Scene.h"

#include <stdio.h>
#define REG_VCOUNT *(volatile u16*)0x04000006
//TODO: 언젠가 지운다

char	debug_log[2048];
char	*log_ptr = debug_log;
INLINE void m4_plot(int x, int y, u8 clrid)
{
	COLOR *dst= &vid_page[(y*M4_WIDTH+x)>>1];
	if(x&1)
		*dst= (*dst& 0xFF) | (clrid<<8);
	else
		*dst= (*dst&~0xFF) |  clrid;
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

#include "clock.hpp"
#include "division.h"

#define REG_WAITCNT *(volatile unsigned short*)0x4000204
void optimize_ewram() {
    REG_WAITCNT = (REG_WAITCNT & ~0x0030) | 0x000E;  // EWRAM wait state를 0x0E로 설정
}

void	vblank()
{
	gbavfx_vblank_counter += 1;
	REG_IF = 1;
}

int	main() {
	// optimize_ewram(); // mgba에서는 더 느려짐!
	//initDeltaTimer();
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2; // 화면 모드 설정
	// init_palettes();
	// memcp
	for (int i = 0; i < 256; ++i) {
		pal_bg_mem[i] = palette[i];
	}
	for (int i = 0; i < 64 * 64; ++i) {
		gbavfx_texture_slot[0][i] = mario_test[i];
	}
	// f32 mat[12];
	// control cnt;
	// f32 pos[] = { 0, 1, -4 };
	// f32 model_matrix[32][12];
	// f32 pos[] = { 0, 0, -4 };
	// f32 dir[] = { 0, 0, 1 };
	char buffer[3][40];
	// clock_init();
		// int start = clock_get();
		// if(key_held(KEY_A)) cnt.clickJump = true;
		// cnt.playerControll();
		// cnt.checkCollision();
	REG_IME = 0;
	REG_IE = 1;
	REG_DISPSTAT |= (1 << 3);
	REG_IF = 0;
	REG_ISR_MAIN = vblank;
	REG_IME = 1;

	SceneId scene_id = SCENE_A;

	while (true) {
		if (scene_id == SCENE_A)
		{
			SceneA scene;

			while (true) {
				// int t = clock_get();
				scene.update();
				// int u = clock_get();

				// sprintf(buffer[0], "Frametime: %dus", u - t);
			}
		}
	}
}
