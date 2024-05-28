
#include "gpi_private.h"

t_trace	*trace_init(t_trace *self, i32 x0, i32 y0, i32 x1, i32 y1) {
	i32 const	dx = x1 - x0;
	i32 const	dy = y1 - y0;
	i32 const	round_x = (x0 & ~0b111) + 4;
	i32 const	round_y = (y0 & ~0b111) + 4;
	i32 const	step = (dx < 0) ? -1 : 1;
	i32 		error = dx * (round_y - y0) - dy * (round_x - x0);
	i32			x = round_x >> 3;

	while (error < 0 || error - (dy << 3)) {
		error += step * (dy << 3);
		x += step;
	}

	self->scaled_dx = dx << 3;
	self->scaled_dy = dy << 3;
	self->step = step;
	self->error = error;
	self->x = x;
	return (self);
}
