
#include "gpi_private.h"

static
void	swap(t_vertex **a, t_vertex **b) {
	t_vertex	*tmp = *a;
	*a = *b;
	*b = tmp;
}

void	triangle_init(t_triangle *self, t_vertex *a, t_vertex *b, t_vertex *c) {
	if (a->y > b->y)
		swap(a, b);
	if (b->y > c->y)
		swap(b, c);
	if (a->y > b->y)
		swap(a, b);
	self->vertices[0] = a;
	self->vertices[1] = b;
	self->vertices[2] = c;
	return (self);
}
