
#include "gpi_private.h"

void	span_move(t_span *self, i32 y) {
	i32 const		ac_orientation = self->ac_orientation;
	t_vertex*const	v1 = self->triangle->vertices[1];
	t_vertex*const	v2 = self->triangle->vertices[2];

	if (y != self->breakpoint) {
		trace_move(&self->trace[0]);
		trace_move(&self->trace[1]);
		return ;
	}
	trace_init(&self->trace[!ac_orientation], v1->x, v1->y, v2->x, v2->y);
	trace_move(&self->trace[ac_orientation]);
}
