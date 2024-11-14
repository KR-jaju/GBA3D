
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
	fixed pos[] = { 0, 1, -4 };
	fixed dir[] = { 0, 0, 1 };
	char buffer[2][40];

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
		view(mat, pos, dir);
		gbavfx_matrix_slot[0] = mat;
		// gbavfx_drawIndexed(box_vertices, 8, box_indices, 12, 0);
		// gbavfx_drawIndexed(vertices, 306, indices, 368, 0);
		// gbavfx_drawIndexed(plane_vertices, 4, plane_indices, 2, 0);
		int neo = clock_get();
		gbavfx_drawIndexed(vertices, 306, indices, 368, 0); // 얘만으로 16ms씀....
		// int vc[] = {306};
		// gbavfx_drawSkinned(vertices, vc, indices, 368, 0, 1);
		int start = clock_get();
		gbavfx_flip();
		int end = clock_get();
		sprintf(buffer[0], "drawIndexed TIME : %dus ", start - neo);
		sprintf(buffer[1], "rasterize TIME : %dus ", end - start);
		// sprintf(buffer[0], "COUNT : %d -- ", gbavfx_vbo.size);


		while(REG_VCOUNT >= 160);
    	while(REG_VCOUNT < 160);
		vid_page = (i16*)((u32)vid_page ^ 0xA000);
		REG_DISPCNT ^= DCNT_PAGE;
	}
}
