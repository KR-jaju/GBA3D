
#include "gpi_private.h"

t_span	*span_init(t_span *self, t_triangle *triangle) {
	t_vertex*const	a = vertices[0];
	t_vertex*const	b = vertices[1];
	t_vertex*const	c = vertices[2];
	i32 const		dx[] = {b->x - a->x, c->x - a->x, c->x - b->x};
	i32 const		dy[] = {b->y - a->y, c->y - a->y, c->y - b->y};


	self->ref = triangle;
	self->prev = NULL;
	self->next = NULL;
	self->y_start = ((a->y + 3) & ~0b111) >> 3; //TODO: &연산이 필요하지 않을것으로 보임
	self->y_center = ((b->y + 3) & ~0b111) >> 3;
	self->y_end = ((c->y + 3) & ~0b111) >> 3;
	self->ref = triangle;
	// TODO: normal설정하기

	self->ref = triangle;
	self->prev = NULL;
	self->next = NULL;
	if (dx[2] < 0) {
		self->dx[0][0] = dx[1];
		self->dx[0][1] = dx[0];
		self->dx[1][0] = dx[1];
		self->dx[1][1] = dx[2];
		self->dy[0][0] = dy[1];
		self->dy[0][1] = dy[0];
		self->dy[1][0] = dy[1];
		self->dy[1][1] = dy[2];
	} else {
		self->dx[0][0] = dx[0];
		self->dx[0][1] = dx[1];
		self->dx[1][0] = dx[2];
		self->dx[1][1] = dx[1];
		self->dy[0][0] = dy[0];
		self->dy[0][1] = dy[1];
		self->dy[1][0] = dy[2];
		self->dy[1][1] = dy[1];
	}
	i32 const	cy = ((a->y + 3) & ~0b111) + 4;
	i32 const	cx = ((a->x + 3) & ~0b111) + 4;
	i32 const	x_sign = (self->dx[0][0] < 0) ? -1 : 1;

	self->error[0] += self->dx[0][0] * (cy - a->y) - self->dy[0][0] * (cx - a->x);
	self->error[1] += self->dx[0][1] * (cy - a->y) - self->dy[0][1] * (cx - a->x);
	while (self->error[0] < 0 || dy[0] * 8 <= self->error[0]) {
		self->error[0] += dy[0] * x_sign * 8;
		self->x[1] += x_sign;
	}
	while (self->error[1] < 0 || dy[1] * 8 <= self->error[1]) {
		self->error[1] += dy[1] * x_sign * 8;
		self->x[1] += x_sign;
	}









	return (self);
}
