
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
// #include "resource/model.h"

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

void	qtor(fixed* dst, fixed x, fixed y, fixed z, fixed w)
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


void	view(fixed *matrix, fixed pos[3], fixed dir[3]) {
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

// TestVertex box_vertices[] = {
// 	{ 1.0f, 1.0f, 1.0f, 56, 32 },
// 	{ 1.0f, -1.0f, 1.0f, 40, 48 },
// 	{ 1.0f, 1.0f, -1.0f, 40, 32 },
// 	{ 1.0f, -1.0f, -1.0f, 24, 64 },
// 	{ -1.0f, 1.0f, 1.0f, 24, 48 },
// 	{ -1.0f, -1.0f, 1.0f, 40, 0 },
// 	{ -1.0f, 1.0f, -1.0f, 24, 16 },
// 	{ -1.0f, -1.0f, -1.0f, 24, 0 }};

// i32 box_indices[] = {4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 1, 3, 7, 0, 2, 3, 4, 0, 1};


void	multiply_matrix(fixed *dst, fixed *a, fixed *b)
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

int	main() {
	// optimize_ewram(); // mgba에서는 더 느려짐!
	clock_init();
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
	fixed mat[12];
	control cnt;
	// fixed pos[] = { 0, 1, -4 };
	fixed model_matrix[32][12];
	fixed pos[] = { 0, 0, -4 };
	fixed dir[] = { 0, 0, 1 };
	char buffer[2][40];
	fixed matrix[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 10
	};

	// float T = ((0.0f / 100.0f + 179.5f) / 180.f) * 3.141592f;
	float T = ((30.0f) / 180.f) * 3.141592f;
	float a = cos(T) - sin(T);
	float b = sin(T) + cos(T);
	// TestVertex plane_vertices[] = {
	// 	{-a, b, 0, 0, 0},
	// 	// {-a, 0.3f, 0, 0, 0},
	// 	{b, a, 0, 63, 0},
	// 	{-b, -a, 0, 0, 63},
	// 	{a, -b, 0, 63, 63},
	// };
	// i32 plane_indices[] = {0, 1, 2, 1, 2, 3};


	int frame = 0;
	clock_init();
	while(true) {
		// int start = clock_get();
		// if(key_held(KEY_A)) cnt.clickJump = true;
		// cnt.playerControll();
		// cnt.checkCollision();
		gbavfx_clear();
		// gbavfx_drawSkinned(vertices, vertex_count, indices, 368, 0, 17);
		gbavfx_color = (u8*)vid_page;
		// pos[0] += 0.01f;
		// pos[2] += 0.02f;
		// pos[2] = 0.5f;
		// pos[2] = -1.0f;
		view(matrix, pos, dir);
		// gbavfx_matrix_slot[0] = mat;
		// gbavfx_drawIndexed(box_vertices, 8, box_indices, 12, 0);
		// gbavfx_drawIndexed(vertices, 306, indices, 368, 0);
		// gbavfx_drawIndexed(plane_vertices, 4, plane_indices, 2, 0);
		int neo = clock_get();
		// gbavfx_drawIndexed(vertices, 306, indices, 368, 0); // 얘만으로 16ms씀....
		int vc[] = {306};
		// gbavfx_drawSkinned(vertices, vc, indices, 368, 0, 1);
		fixed const (*data)[7] = animation[frame];
		for (int bone = 0; bone < 17; bone++)
		{
			fixed model[12] = {1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,};
			fixed* dst = gbavfx_matrix_slot[0];
			fixed x = data[bone][0];
			fixed y = data[bone][1];
			fixed z = data[bone][2];

			fixed rx = data[bone][3];
			fixed ry = data[bone][4];
			fixed rz = data[bone][5];
			fixed rw = data[bone][6];

			qtor(model, rx, ry, rz, rw);
			model[3] = x;
			model[7] = y;
			model[11] = z;

			multiply_matrix(model_matrix[bone], matrix, model);
			gbavfx_matrix_slot[bone] = model_matrix[bone];
			// gbavfx::matrix_slot[bone] = matrix;
		}

		gbavfx_drawSkinned(vertices, vertex_count, indices, 368, 0, 17);
		int start = clock_get();
		gbavfx_flip();
		int end = clock_get();
		sprintf(buffer[0], "drawIndexed TIME : %dus ", start - neo);
		sprintf(buffer[1], "rasterize TIME : %dus ", end - start);
		// sprintf(buffer[0], "COUNT : %d -- ", gbavfx_vbo.size);

		frame = frame + 1;
		if (frame == 31)
			frame = 0;
		while(REG_VCOUNT >= 160);
    	while(REG_VCOUNT < 160);
		vid_page = (i16*)((u32)vid_page ^ 0xA000);
		REG_DISPCNT ^= DCNT_PAGE;
	}
}
