
#include "Rasterizer.hpp"
#include "debug.hpp"
#include "clock.hpp"

//13122 -> 13.122 milliseconds
//8580 -> 8.58 milliseconds
//37000 -> 37milliseconds

void	Rasterizer::render(RasterSubject const &subject) {
	Scanline	scan(subject);
	// u16			aout[240];
	u16	*out;

	out = (u16 *)0x0600F000;//VRAM의 아무 지점
	// out = aout;
	int start = clock_get();
	while (scan.getY() < 160) {
		scan.render(out);
		// out += 240;
		scan.move();
	}
	int e0 = clock_get();
	debug_offset += sprintf(debug_text + debug_offset, "(%d) ", e0 - start);
	// int((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec)));
}