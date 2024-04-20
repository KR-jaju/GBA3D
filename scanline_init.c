
#include "gpi_private.h"

t_scanline	*scanline_init(t_scanline *self) {
	self->global = NULL;
	self->active = &self->active_end;
	self->end_trace = (t_trace) {
		.dx = 0,
		.dy = 0,
		.error = 0,
		.x = 2147483647
	};
	span_init(&self->active_end, &self->end_trace, NULL, 0, 0);
	self->y = -1;
	return (self);
}