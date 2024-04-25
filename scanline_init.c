
#include "gpi_private.h"

t_scanline	*scanline_init(t_scanline *self, t_vertex *vertices, t_span *span_set) {
	self->global = span_set;
	self->active = (t_span *)&self->active_end;
	self->active_end = NULL;
	self->vertices = vertices;
	return (self);
}