
#include "gpi_private.h"

void	span_move(t_span *self, i32 y) {
	i32 const		is_upper = y < self->y[1];
	t_trace*const	left = span_left(self, is_upper);
	t_trace*const	right = span_right(self, is_upper);

	trace_move(left);
	trace_move(right);
}
