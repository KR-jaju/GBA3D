
#include "gpi_private.h"

t_span	*span_init(t_span *self, t_vertex *vertices, i32 indices[3]) {
	t_vertex*const	a = &vertices[indices[0]];
	t_vertex*const	b = &vertices[indices[1]];
	t_vertex*const	c = &vertices[indices[2]];
	t_trace*const	ab = &self->traces[0];
	t_trace*const	ac = &self->traces[1];
	t_trace*const	bc = &self->traces[2];

	trace_init(ab, a->x, a->y, b->x, b->y);
	trace_init(ac, a->x, a->y, c->x, c->y);
	trace_init(bc, b->x, b->y, c->x, c->y);
	self->prev = NULL;
	self->next = NULL;
	self->shape = (b->x <= c->x);
	self->y[0] = ((a->y + 3) & ~0b111) >> 3; //TODO: &연산이 필요하지 않을것으로 보임
	self->y[1] = ((b->y + 3) & ~0b111) >> 3;
	self->y[2] = ((c->y + 3) & ~0b111) >> 3;
	self->indices[0] = indices[0];
	self->indices[1] = indices[1];
	self->indices[2] = indices[2];
	// TODO: normal설정하기
	return (self);
}
