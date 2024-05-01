
#include "gpi_private.h"

void	scanpixel_realign(t_scanpixel *self, t_pixel *pixel) {
	i32 const	x = self->x;
	i32			curr_z = pixel->z;
	t_pixel		*prev = pixel->prev;

	while (prev != NULL && prev->z > curr_z) {
		swap(prev, pixel);
		prev = pixel->prev;
	}
	if (prev == NULL)
		self->active = pixel;
}
