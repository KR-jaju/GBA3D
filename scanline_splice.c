
#include "gpi_private.h"

static
void	push_front(t_span *dst, t_span *src) {
	t_span	*prev = dst->prev;

	src->prev = prev;
	src->next = dst;
	prev->next = src;
	dst->prev = src;
}

void	scanline_splice(t_scanline *self, t_span *span) {
	t_span	*src = self->global;

	while (src->y == self->y && src->left->x < span->left->x) {
		push_front(span, src);
		src = src->next;
	}
	self->global = src;
}
