
#include "gpi_private.h"

void	scanline_move(t_scanline *self) {
	t_span	*next;

	self->y += 1;
	for (t_span *curr = self->active; curr != &self->active_end; curr = next) {
		next = curr->next;
		if (curr->max_y == self->y) {
			scanline_remove(self, curr);
			continue;
		}
		span_move(curr);
		scanline_realign(self, curr);
		scanline_splice(self, curr);
	}
	scanline_splice(self, &self->active_end);
}