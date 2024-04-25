 
#include "gpi_private.h"

void	scanline_move(t_scanline *self, i32 y) {
	t_span	*next;
	t_span	*curr;

	curr = self->active;
	while (curr != &self->active_end) {
		next = curr->next;
		if (y == curr->y[2]) {
			scanline_remove(self, curr);
		} else {
			span_move(curr, y);
			scanline_realign(self, curr, y);
			scanline_splice(self, curr, y);
		}
		curr = next;
	}
	scanline_splice_back(self, y);
	// scanline_splice(self, &self->active_end); // TODO: 대책마련 시급
}
