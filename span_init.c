
#include "gpi_private.h"

t_span	*span_init(t_span *self, t_trace *left, t_trace *right, int ) {
	self->left = left;
	self->right = right;
}
