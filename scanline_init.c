
#include "gpi_private.h"

t_scanline	*scanline_init(t_scanline *self) {
	self->global = NULL;
	self->active = NULL;
	self->y = -1;
	return (self);
}