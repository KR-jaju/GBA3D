
#include "gpi_private.h"

void	span_move(t_span *self) {
	trace_move(self->left);
	trace_move(self->right);
}