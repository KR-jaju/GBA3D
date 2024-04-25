
#include "gpi_private.h"

t_trace	*span_left(t_span *self, i32 is_upper) {
	i32 const	idx = (!self->shape) | (!(!self->shape | is_upper) << 1);

	return (&self->traces[idx]);
}