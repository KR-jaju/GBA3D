
#include "gpi_private.h"

void	scanpixel_remove(t_scanpixel *self, t_pixel *pixel) {
	t_pixel*const	prev = pixel->prev;
	t_pixel*const	next = pixel->next;

	next->prev = prev;
	if (prev == NULL)
		self->active = next;
	else
		prev->next = next;
}

