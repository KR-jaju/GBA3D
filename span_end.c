
#include "gpi_private.h"

i32		span_end(t_span *self) {
	return (self->y >= self->max_y);
}
