
#include "gpi_private.h"

void	scanline_remove(t_scanline *self, t_span *span) {
	t_span*const	prev = span->prev;
	t_span*const	next = span->next;

	next->prev = prev;
	if (prev == NULL)
		self->active = next;
	else
		prev->next = next;
}
