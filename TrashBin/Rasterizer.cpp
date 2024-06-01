
#include "Rasterizer.hpp"
#include "debug.hpp"
#include "clock.hpp"

//13122 -> 13.122 milliseconds
//8580 -> 8.58 milliseconds
//37000 -> 37milliseconds

void	Rasterizer::render(RasterSubject const &subject) {
	Scanline	scan(subject);
	u16			aout[256];
	u16	*out;

	out = (u16 *)0x06000F00;//VRAM의 아무 지점
	// out = (u16 *)0x06000000;//VRAM의 아무 지점
	// out = aout;
	int start = clock_get();
	while (scan.getY() < 160) {
		scan.render(out);
		scan.move();
		out += 240;
		scan.render(out);
		scan.move();
		out += 240;
		scan.render(out);
		scan.move();
		out += 240;
		scan.render(out);
		scan.move();
		out += 240;
		// scan.render(out);
		// scan.move();
		
		// scan.render(out + 240);
		// scan.move();
		
		// scan.render(out + 480);
		// scan.move();

		// scan.render(out + 720);
		// scan.move();
		// out += 960;
	}
	int e0 = clock_get();
	debug_offset += sprintf(debug_text + debug_offset, "(%d) ", e0 - start);
	// for (int i = 0; i < 240; ++i)
		debug_offset += sprintf(debug_text + debug_offset, "aout : %d ", aout[5]);
	// float(e0 - start) / 263);
	// int((end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec)));
}