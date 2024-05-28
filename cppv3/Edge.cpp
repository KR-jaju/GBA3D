
#include "Edge.hpp"

Edge	&Edge::init(i32 x0, i32 y0, i32 x1, i32 y1) {
	i32 const	dx = x1 - x0;
	i32 const	dy = y1 - y0;
	i32 const	round_x = (x0 & ~0b111) + 4;
	i32 const	round_y = (y0 & ~0b111) + 4;
	i32 const	step = (dx < 0) ? -1 : 1;
	i32 const	scaled_dx = dx << 3;
	i32 const	scaled_dy = dy << 3;
	i32 		error = dy * (round_x - x0) - dx * (round_y - y0);
	i32			x = round_x >> 3;

	if (scaled_dy != 0) {
		while (error < 0 || error - scaled_dy >= 0) {
			error += step * scaled_dy;
			x += step;
		}
	}
	// this->next = NULL;
	this->scaled_dx = scaled_dx;
	this->scaled_dy = scaled_dy;
	this->step = step;
	this->error = error;
	this->x = x;
	return (*this);
}

void	Edge::move() {
	i32 const	step = this->step;
	i32 const	dx = this->scaled_dx;
	i32 const	dy = this->scaled_dy;
	i32			error = this->error - dx;
	i32			x = this->x;

	if (this->scaled_dy == 0)
		return ;
	while (error < 0 || error - dy >= 0) {
		error += step * dy;
		x += step;
	}
	this->error = error;
	this->x = x;
}