
#include "Rasterizer.hpp"
#include <tonc.h>

void	Rasterizer::render(RasterSubject const &subject) {
	Scanline	scan(subject);
	// int			out[240];
	u16			*out;

	out = vid_mem;
	while (scan.getY() < 160) {
		scan.render(out);
		out += 240;
		scan.move();
	}
}