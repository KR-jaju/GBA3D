
#include "gpi_private.h"

void	span_unshift(t_span *self, t_span *other) {
	t_span	*prev = self->prev;

	self->prev = other;
	other->prev = prev;
	other->next = self;
	if (prev != NULL)
		prev->next = other;
}