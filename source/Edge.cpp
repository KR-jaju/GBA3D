
#include "Rasterizer.hpp"
#include "Edge.hpp"
#include "GBAlib.hpp"

Edge	&Edge::init(Vertex const &a, Vertex const &b) {
	i32 const	dx = b.x - a.x;
	i32 const	dy = b.y - a.y;
	i8 const	step = (dx < 0) ? -1 : 1;
	i32 const	round_x = ((a.x + 3) & ~0b111) + 4;
	//  - step * 8;
	i32 const	round_y = ((a.y + 3) & ~0b111) + 4;
	i32 const	scaled_dx = dx << 3;
	i32 const	scaled_dy = dy << 3;
	i32 		error = dy * (round_x - a.x) - dx * (round_y - a.y);
	i32			x = round_x >> 3;

	if (scaled_dy != 0) {
		while (error < 0 || error - scaled_dy >= 0) { // x < min_x || x >= (min_x + 8)
			error += step * scaled_dy;
			x += step;
		}
	}
	this->scaled_dx = scaled_dx;
	this->scaled_dy = scaled_dy;
	this->error = error;
	this->pack = (u8(step) << 24) | u16(x); //shade here
	#ifdef INTERLACED_RENDERING
	if (((round_y >> 3) & 0b1) == (vid_page == vid_mem_back)) { //홀수번째에서 시작하면 다음으로
		this->move();
	}
	#endif
	return (*this);
}

void	Edge::move() {
	i32 const	dx = this->scaled_dx;
	i32 const	dy = this->scaled_dy;
	u32 const	pack = this->pack;
	i32 const	step = i8(pack >> 24);
	i32			x = i16(u16(pack));
	i32			error = this->error - dx;

	if (this->scaled_dy == 0)
		return ;
	while (error < 0 || error - dy >= 0) {
		error += step * dy;
		x = min(max(x + step, 0), 1919); // TODO: 하드코딩
	}
	this->error = error;
	this->pack = (pack & 0xFFFF0000) | u16(x);
}
