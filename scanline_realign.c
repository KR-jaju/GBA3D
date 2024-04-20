
#include "gpi_private.h"

void	scanline_realign(t_scanline *self, t_span *span) {
	int		curr_x = span->left->x;
	t_span	*prev = span->prev;

	while (prev != NULL && prev->left->x > curr_x) {
		prev->next = span->next;
		span->prev = prev->prev;
		prev->prev = span;
		span->next = prev;
		prev = span->prev;
	}
	if (prev == NULL)
		self->active = span;
}
