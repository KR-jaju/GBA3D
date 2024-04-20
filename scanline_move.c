
#include "gpi_private.h"

/*

for a in active {
	if a.end() {
		remove(a);
		continue;
	}
	a.move();
	while (a.left.x < prev.left.x) {
		swap(a, prev);
		prev = a.prev;
	} // 위치 맞추기
	while (get.head.y == self.y && get.head.x < a.left.x) {
		get.pop();
		a.push_front(head);
	} // get 넣기
}

*/

void	scanline_move(t_scanline *self) {
	t_span	*next;

	self->y += 1;
	for (t_span *curr = self->active; curr != &self->active_end; curr = next) {
		next = curr->next;
		if (span_end(curr)) {
			scanline_remove(self, curr);
			continue;
		}
		span_move(curr);
		scanline_realign(self, curr);
		scanline_splice(self, curr);
	}
	scanline_splice(self, &self->active_end);
}