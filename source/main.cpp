
#include "Mesh.hpp"
#include "Rasterizer.hpp"
#include "GBAlib.hpp"
#include "Camera.hpp"
/*
00000,00000,11111 - 31
00000,00000,01111 - 15
// */


int	main() {
	// *(u16 *)(0x04000000) = 0b0000010000000011;
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2;
	// Mesh<4, 2>		mesh = {
	// 	{{0, 100, 0, 0, 0},
	// 	{234, 145, 0, 0xFFFF, 0},
	// 	{560, 634, 0, 0, 0xFFFF},
	// 	{650, 400, 0, 0xFFFF, 0xFFFF}},
	// 	{1, 2, 3, 0, 1, 2}
	// };
	Mesh<4, 2>		mesh = {
		{{0.0f, 0.8f, 6.0f, 0, 0},
		{-0.8f, 0.0f, 6.0f, 0xFFFF, 0},
		{0.0f, -0.8f, 6.0f, 0, 0xFFFF},
		{0.8f, 0.0f, 6.0f, 0xFFFF, 0xFFFF}},
		{0, 1, 2, 0, 2, 3}
	};
	Camera	camera;

	init_palettes();
	while(true) {
		camera.update();
		camera.push(mesh);
		camera.render((u8 *)vid_page);
		// Rasterizer::render(rs, (u8*)vid_page);
		vid_flip();
	}
}
// #include <stdio.h>
// #include "debug.hpp"
// #include "clock.hpp"
// int	main(void) {
// 	clock_init();
// 	debug_init();
// 	Mesh<4, 2>		mesh = {
// 		{{0, 204, 1000, 0, 0},
// 		{-204, 0, 1000, 0xFFFF, 0},
// 		{0, -204, 1000, 0, 0xFFFF},
// 		{204, 0, 1000, 0xFFFF, 0xFFFF}},
// 		{0, 1, 2, 0, 2, 3}
// 	};
// 	Camera	camera;

// 	camera.update();
// 	camera.push(mesh);
// 	debug_view();
// 	while(true) {
// 		// camera.render((u8 *)0x06000F00);
// 		debug_offset = 0;
// 		// debug_view();
// 	}
// }
