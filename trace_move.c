
#include "gpi_private.h"

void	trace_move(t_trace *self) {
	self->error -= self->dx * 8; // 1픽셀만큼 y+
	if (self->step < 0) { // -x 방향으로 이동해야한다면
		while (self->error - self->step * self->dy * 8 >= 0) {
			self->error -= self->step * self->dy * 8;
			self->x -= 1;
		}
	} else {
		while (self->error < 0) {
			self->error -= self->step * self->dy * 8;
			self->x -= 1;
		}
	}
}
