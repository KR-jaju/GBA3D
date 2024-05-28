
#include "gpi_private.h"

t_span	*span_init(t_span *self, t_triangle *triangle) {
	i32 const	x[3] = {
		triangle->vertices[0]->x,
		triangle->vertices[1]->x,
		triangle->vertices[2]->x
	};
	i32 const	y[3] = {
		triangle->vertices[0]->y,
		triangle->vertices[1]->y,
		triangle->vertices[2]->y
	};
	i32 const	ac_orientation = (x[1] > x[2]) ? 1 : 0;

	trace_init(&self->trace[!ac_orientation], x[0], y[0], x[1], y[1]);
	trace_init(&self->trace[ac_orientation], x[0], y[0], x[2], y[2]);
	self->prev = NULL;
	self->next = NULL;
	self->triangle = triangle;
	self->ac_orientation = ac_orientation;
	self->entry = y[0];
	self->breakpoint = y[1];
	self->exit = y[2];
	return (self);
}
