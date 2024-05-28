
#include "gpi_private.h"

void	trace_move(t_trace *self) {
	i32 const	step = self->step;
	i32 const	dx = self->scaled_dx;
	i32 const	dy = self->scaled_dy;
	i32			error = self->error + dx;
	i32			x = self->x;

	while (error < 0 || error - dy) {
		error += step * dy;
		x += step;
	}
	self->error = error;
	self->x = x;
}
