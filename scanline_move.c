
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

static
void	swap_span(t_span *prev, t_span *next) {
	next->prev = prev->prev;
	prev->next = next->next;
	prev->next = next;
	next->prev = prev;
}

void	scanline_move(t_scanline *self) {
	t_span	*curr = self->active->next;
	t_span	*next;

	self->y += 1;
	while (curr != &self->aet_tail) {
		next = curr->next;
		t_span	*prev = curr->prev;
		if (span_end(curr)) {
			prev->next = next;
			next->prev = prev;
		} else {
			span_move(curr);
			while (prev->left->x > curr->left->x) {
				swap_span(prev, curr);
				prev = curr->prev;
			} //올바른 위치까지 스왑
			t_span	*span = self->global;
			while (span->y == self->y && span->left->x < curr->left->x) { // 넣을 조건
				span->next = curr;
				span->prev = prev;
				prev->next = span;
				curr->prev = span;
				prev = span; // prev = curr->prev;
				span = span->next; // GET.pop_front();
			}
			self->global = span; // dereference 줄이기
		}
		curr = next;
	}
}