
#include "Rasterizer.hpp"

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
	rasterizer.render(rs); //여기서 바로 vram에 씀
}