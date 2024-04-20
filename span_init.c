
#include "gpi_private.h"

t_span	*span_init(t_span *self, t_trace *left, t_trace *right, i32 min_y, i32 max_y) {
	self->prev = NULL;
	self->next = NULL;
	self->left = left;
	self->right = right;
	self->y = min_y;
	self->max_y = max_y;
	return (self);
}
