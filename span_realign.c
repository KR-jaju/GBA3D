
#include "gpi_private.h"

static
void	swap_node(t_span *prev, t_span *curr) {
	prev->next = curr->next;
	curr->prev = prev->prev;
	prev->prev = curr;
	curr->next = prev;
}

void	span_realign(t_span *curr) {
	t_span	*prev = curr->prev;

	while (prev != NULL && prev->left->x > curr->left->x) {
		swap_node(prev, curr);
		prev = curr->prev;
	} //올바른 위치까지 스왑
}