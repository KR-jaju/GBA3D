
#include <iostream>
#include "Edge.hpp"
#include "Segment.hpp"
#include "Scanline.hpp"
#include "Rasterizer.hpp"

void	testEdge() {
	std::cout << "--testing edge--" << std::endl;
	Edge	edge;

	edge.init(0, 0, 50, 100);
	std::cout << "Edge test 1, x : " << edge.x << std::endl;
	edge.move();
	edge.move();
	std::cout << "Edge test 2, x : " << edge.x << std::endl;
	std::cout << "--edge test end--" << std::endl;
}

void	testSegment() {
	std::cout << "--testing segment" << std::endl;
	Vertex		v[3] = {
		{0, 0, 0},
		{100, 0, 0},
		{0, 100, 0}
	};
	Triangle	tri = {v[0], v[1], v[2]};
	Segment	segment;

	segment.init(&tri);
	std::cout << "segment test 1, x : " << segment.edge[0].x << ", " << segment.edge[1].x << std::endl;
	segment.move();
	segment.move();
	std::cout << "segment test 2, x : " << segment.edge[0].x << ", " << segment.edge[1].x << std::endl;
	std::cout << "--segment test end--" << std::endl;
}

void	testScanline() {
	std::cout << "--testing scanline" << std::endl;
	Mesh<4, 2>		mesh = {
		{0, 0, 0,
		100, 0, 0,
		0, 100, 0,
		100, 100, 0},
		{1, 2, 3, 0, 1, 2}
	};
	RasterSubject	rs;
	rs.push(mesh);

	Scanline	scan(rs);

	std::cout << "scanline test 1 :" << std::endl;
	for (Segment *s = scan.begin(); s != scan.end(); s = s->next)
		std::cout << "segment x: (" << s->edge[0].x << ", " << s->edge[1].x << ")" << std::endl;
	scan.move();
	scan.move();
	std::cout << "scanline test 2 :" << std::endl;
	for (Segment *s = scan.begin(); s != scan.end(); s = s->next)
		std::cout << "segment x: (" << s->edge[0].x << ", " << s->edge[1].x << ")" << std::endl;
	std::cout << "scanline test 3 :" << std::endl;
	int o[240];
	for (int i = 0; i < 240; ++i)
		o[i] = 0;
	std::cout << "--scanline test end--" << std::endl;
}

void	testRasterizer() {
	std::cout << "--testing rasterizer" << std::endl;
	Mesh<4, 1>		mesh = {
		{0, 0, 0,
		100, 0, 0,
		0, 100, 0,
		100, 100, 0},
		{1, 2, 3}
	};
	//  0, 1, 2
	RasterSubject	rs;
	rs.push(mesh);

	Rasterizer	rasterizer;

	std::cout << "rasterizer test 1 :" << std::endl;
	rasterizer.render(rs);
	std::cout << "--rasterizer test end--" << std::endl;
}
int	main() {
	// testEdge();
	// testSegment();
	// testScanline();
	testRasterizer();
}
