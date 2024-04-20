
#include "gpi_private.h"

void	span_move(t_span *self) {
	self->min_y += 1;
	trace_move(self->left);
	trace_move(self->right);
}