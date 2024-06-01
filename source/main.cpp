
#include "Mesh.hpp"
#include "Rasterizer.hpp"
#include "GBAlib.hpp"

/*
00000,00000,11111 - 31
00000,00000,01111 - 15
*/


int	main() {
	// *(u16 *)(0x04000000) = 0b0000010000000011;
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2;
	Mesh<4, 2>		mesh = {
		{{0, 100, 0, 0, 0},
		{234, 145, 0, 0xFF, 0},
		{560, 634, 0, 0, 0xFF},
		{650, 400, 0, 0xFF, 0xFF}},
		{1, 2, 3, 0, 1, 2}
	};
	RasterSubject	rs;
	Rasterizer	rasterizer;

	rs.push(mesh);
	init_palettes();
	while(true) {
		rasterizer.render(rs, (u8*)vid_page);
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
// 		{{0, 100, 0, 31},
// 		{234, 145, 0, 15},
// 		{560, 634, 0, 7},
// 		{650, 400, 0, 3}},
// 		{1, 2, 3, 0, 1, 2}
// 	};
// 	RasterSubject	rs;
// 	Rasterizer	rasterizer;

// 	rs.push(mesh);
// 	while(true) {
// 		rasterizer.render(rs, (u8*)0x06000F00);
// 		debug_offset = 0;
// 		debug_view();
// 	}
// }
