
#include "gpi_private.h"

static
void	swap(t_span *prev, t_span *next) {
	prev->next = next->next;
	next->prev = prev->prev;
	prev->prev = next;
	next->next = prev;
}

void	scanline_realign(t_scanline *self, t_span *span, i32 y) {
	i32		curr_x = span_left(span, y < span->y[1])->x;
	t_span	*prev = span->prev;

	while (prev != NULL && span_left(prev, y < prev->y[1])->x > curr_x) {
		swap(prev, span);
		prev = span->prev;
	}
	if (prev == NULL)
		self->active = span;
}
