
#include "gpi_private.h"

static
void	swap(t_span *prev, t_span *next) {
	prev->next = next->next;
	next->prev = prev->prev;
	prev->prev = next;
	next->next = prev;
}

void	scanline_realign(t_scanline *self, t_span *span) {
	i32 const	y = self->y;
	i32 const	curr_x = span->x[0];
	t_span	*prev = span->prev;

	while (prev != NULL && prev->x[0] > curr_x) {
		swap(prev, span);
		prev = span->prev;
	}
	if (prev == NULL)
		self->active = span;
}
