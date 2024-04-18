
#include "gpi_private.h"

/*
step이 -방향이라면
1픽셀 움직인 자리가 선의 같거나 오른쪽이면 움직이기
step이 +1이라면
현재 자리가 선보다 왼쪽이면 움직이기

*/

void	trace_move(t_trace *self) {
	self->error -= self->dx * 8; // 1픽셀만큼 y+
	if (self->step == -1) {
		while (self->error - self->dy * 8 >= 0) { // 1픽셀 움직인 자리가 선보다 같거나 오른쪽
			self->error -= self->dy * 8;
			self->x -= 1;
		}
	} else {
		while (self->error < 0) { // 현재 자리가 선보다 왼쪽
			self->error += self->dy * 8;
			self->x += 1;
		}
	}
}
