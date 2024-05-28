
#include "Rasterizer.hpp"

void	Rasterizer::render(RasterSubject const &subject) {
	Scanline	scan(subject);
	// int			out[240];
	u16			*out;

	out = (u16 *)0x06000000;
	while (scan.getY() < 160) {
		scan.render(out);
		out += 240;
		scan.move();
	}
}