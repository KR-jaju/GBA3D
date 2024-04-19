
#include "gpi_private.h"

i32	compare(t_span const *a, t_span const *b) {
	return (a->y < b->y || (a->y == b->y && a->left->x < b->left->x));
}

void	scanline_sort(t_scanline *self) {
	// TOOD ; 병합정렬만들어야함
}
