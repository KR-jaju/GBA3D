
#include "gpi_private.h"

t_scanline	*scanline_init(t_scanline *self) {
	self->global = NULL;
	self->active = &self->active_end;
	trace_init(&self->end_trace, 99999999, 0, 99999999, 0);
	span_init(&self->active_end, &self->end_trace, NULL, 0, 0);
	self->y = -1;
	return (self);
}