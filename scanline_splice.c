
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

void	scanline_splice(t_scanline *self, t_span *dst, i32 y) {
	i32			dst_x = span_left(dst, y < dst->y[1])->x;
	t_span		*src = self->global;
	t_span		*next;

	while (src != NULL && (src->y[0] == y & span_left(src, y < src->y[1])->x < dst_x)) {
		next = src->next;
		push_front(self, dst, src);
		src = next;
	}
	self->global = src;
}
