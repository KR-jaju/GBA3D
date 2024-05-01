#include "gpi_private.h"

void	pixel_move(t_pixel *self) {
	i32*const	dwdx = self->ref->ref->dwdx;

	self->w[0] += dwdx[0];
	self->w[1] += dwdx[1];
	self->w[2] += dwdx[2];
}
