
#include "gpi_private.h"

static
void	push_front(t_scanline *self, t_span *dst, t_span *src) {
	t_span	*prev = dst->prev;

	src->prev = prev;
	src->next = dst;
	dst->prev = src;
	if (prev != NULL)
		prev->next = src;
	else
		self->active = src;
}

static
i32	min(i32 a, i32 b) {
	if (a < b)
		return (a);
	return (b);
}

void	scanline_splice(t_scanline *self, t_span *dst) {
	i32 const	y = self->y;
	i32	const	dst_x = min(dst->traces[0].x, dst->traces[1].x);
	t_span		*src = self->global;
	t_span		*next;

	while (src != NULL && (src->y[0] == y & min(src->traces[0].x, src->traces[1].x) < dst_x)) {
		next = src->next;
		push_front(self, dst, src);
		src = next;
	}
	self->global = src;
}
