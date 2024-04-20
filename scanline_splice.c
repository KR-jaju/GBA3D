
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

void	scanline_splice(t_scanline *self, t_span *span) {
	t_span	*src = self->global;
	t_span	*next;

	while (src != NULL && src->y == self->y && src->left->x < span->left->x) {
		next = src->next;
		push_front(self, span, src);
		src = next;
	}
	self->global = src;
}
