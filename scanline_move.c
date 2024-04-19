
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
	for (t_span *curr = self->active; curr != NULL; curr = next) {
		next = curr->next;
		if (span_end(curr)) {
			span_link(curr->prev, curr->next);
			curr = next;
			continue;
		}
		span_move(curr);
		span_realign(curr);
		t_span	*span = self->global;
		while (span->y == self->y && span->left->x < curr->left->x) { // 넣을 조건
			span_unshift(curr, span);
			span = span->next; // GET.pop_front();
		}
		self->global = span; // dereference 줄이기
	}
}