
#include "gpi_private.h"

void	span_link(t_span *self, t_span *next) {
	self->next = next;
	next->prev = self;
}