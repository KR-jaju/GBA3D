
#include "gpi_private.h"

void	scanpixel_move(t_scanpixel *self) {
	i32 const	x = self->x;
	t_pixel		*next;
	t_pixel		*curr;

	curr = self->active;
	while (curr != &self->active_end) {
		next = curr->next;
		if (x == curr->end_x)
			scanpixel_remove(self, curr);
		else {
			pixel_move(curr);
			scanpixel_realign(self, curr);
			scanpixel_splice(self, curr);
		}
		curr = next;
	}
	scanpixel_splice_back(self);
	self->x += 1;
}