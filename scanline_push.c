
#include "gpi_private.h"

void		scanline_push(t_scanline *self, t_span *span) {
	span->next = self->global;
	self->global = span;
}
