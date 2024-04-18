
#include "gpi_private.h"

t_trace	*trace_init(t_trace *self, i32 x, i32 y, i32 dx, i32 dy) {
	i32 const	floor_x = ((x + 3) & ~0b111) + 4; //x보다 큰 픽셀의 중심
	i32 const	floor_y = ((y + 3) & ~0b111) + 4;

	self->next = NULL;
	self->pair = NULL;
	self->dx = dx; // 이건 미정
	self->dy = dy; // 이건 당연히 양수
	self->error = dy * (floor_x - x) - dx * (floor_y - y); // 양수 * 양수 - ? * 양수 = ?
	self->step = (dx < 0) ? -1 : 1; // 선의 진행방향
	// error = dy * x - dx * y
	// error < 0 // 선보다 x-
	// error > 0 // 선보다 x+
	self->x = floor_x >> 3; // 정수 x좌표
	while (self->error < 0) { //선보다 왼쪽이면
		self->error += dy * 8; // 1픽셀 이동
		self->x += 1;
	}
	while (self->error - dy * 8 >= 0) { // 1픽셀 왼쪽으로 가도 선보다 오른쪽이면
		self->error -= dy * 8; // 1픽셀 왼쪽으로
		self->x -= 1;
	}
}
