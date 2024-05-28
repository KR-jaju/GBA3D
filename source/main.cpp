
#include "Edge.hpp"
#include "Segment.hpp"
#include "Scanline.hpp"
#include "Rasterizer.hpp"
#include <tonc.h>

/*
00000,00000,11111 - 31
00000,00000,01111 - 15
*/

void	testRasterizer() {
	Mesh<4, 2>		mesh = {
		{{0, 100, 0, 31},
		{234, 145, 0, 15},
		{560, 634, 0, 7},
		{650, 400, 0, 3}},
		{1, 2, 3, 0, 1, 2}
	};
	RasterSubject	rs;
	Rasterizer	rasterizer;

	rs.push(mesh);
	rasterizer.render(rs);
}
int	main() {
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
	// pal_bg_mem[0] = CLR_BLACK;
	// pal_bg_mem[1] = CLR_WHITE;
	testRasterizer();
}
