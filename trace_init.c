
#include "gpi_private.h"
#include <stdio.h>

t_trace	*trace_init(t_trace *self, i32 x0, i32 y0, i32 x1, i32 y1) {
	i32 const	dx = x1 - x0;
	i32 const	dy = y1 - y0;
	i32 const	floor_x = ((x0 + 3) & ~0b111) + 4; //x보다 큰 픽셀의 중심
	i32 const	floor_y = ((y0 + 3) & ~0b111) + 4;

	self->dx = dx; // 이건 미정
	self->dy = dy; // 이건 당연히 양수
	self->error = dy * (floor_x - x0) - dx * (floor_y - y0);
	// error = dy * x - dx * y
	// error < 0 // 선보다 x-
	// error > 0 // 선보다 x+
	self->x = floor_x >> 3; // 정수 x좌표
	if (dy == 0)
		return (self); // #E
	while (self->error < 0) { //선보다 왼쪽이면
		self->error += dy * 8; // 1픽셀 이동
		self->x += 1;
	}
	while (self->error - dy * 8 >= 0) { // 1픽셀 왼쪽으로 가도 선보다 오른쪽이면
		self->error -= dy * 8; // 1픽셀 왼쪽으로
		self->x -= 1;
	}
	return (self);
}
