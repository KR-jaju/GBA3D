
#include "gpi_private.h"

t_pixel	*pixel_init(t_pixel *self, t_span *span) {
	self->next = NULL;
	self->prev = NULL;
	self->ref = span;
	self->w[0] = span->w[0];
	self->w[1] = span->w[1];
	self->w[2] = span->w[2];
}
