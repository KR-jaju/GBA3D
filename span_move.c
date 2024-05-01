
#include "gpi_private.h"

/*

Edge(AB, AP)
AB.x * AP.y - AB.y * AP.x

Edge(AB, AP) < 0 == 삼각형 내부


w0 = Edge(AB, AP)
nw0 = w0 / area

cres = nw0 * c0 + nw1 * c1 + nw2 * c2
or
cres = nw0 / z0 * c0 + nw1 / z1 * c1 + nw2 / z2 * c2
invz = nw0 / z0 + nw1 / z1 + nw2 / z2
cres /= invz
결론 : nwn / zn 을 구하면 된다

nwn / zn = wn / zn / area
dw/d(P.x) = -AB.y
dw/d(P.y) = AB.x


*/

static
i32	clamp(i32 a) {
	if (a < 0)
		return (0);
	if (a >= 8)
		return (8);
	return (a);
}

void	span_move(t_span *self) {
	// i32 const		is_upper = y < self->y[1];
	i32 const		x_old = self->x[0];
	i32*const		dwdx = self->ref->dwdx;
	i32*const		dwdy = self->ref->dwdy;
	i32 const		y = (*self->y << 3) + 4;
	i32 const		step[2] = {
		clamp(self->y_center - y),
		clamp(y + 8 - self->y_center)
	};
	i32 const		up = step[0] < 4;
	i32 const		x_sign = (self->dx[up][0] < 0) ? -1 : 1;
	i32 const		*dy = self->dy[up];
	i32				dx;

	self->error[0] += step[0] * self->dx[0][0] + step[1] * self->dx[1][0];
	self->error[1] += step[0] * self->dx[0][1] + step[1] * self->dx[1][1];
	while (self->error[0] < 0 || dy[0] * 8 <= self->error[0]) {
		self->error[0] += dy[0] * x_sign * 8;
		self->x[1] += x_sign;
	}
	while (self->error[1] < 0 || dy[1] * 8 <= self->error[1]) {
		self->error[1] += dy[1] * x_sign * 8;
		self->x[1] += x_sign;
	}



	// i32 const		a_z = self->vertex[0]->z;
	// i32 const		b_z = self->vertex[1]->z;
	// i32 const		c_z = self->vertex[2]->z;
	// i32 const		ab_x = self->vertex[1]->x - self->vertex[0]->x;
	// i32 const		ab_y = self->vertex[1]->y - self->vertex[0]->y;
	// i32 const		bc_x = self->vertex[2]->x - self->vertex[1]->x;
	// i32 const		bc_y = self->vertex[2]->y - self->vertex[1]->y;
	// i32 const		ca_x = self->vertex[0]->x - self->vertex[2]->x;
	// i32 const		ca_y = self->vertex[0]->y - self->vertex[2]->y;
	// TODO: precalculate, 8 precision vs 1precision

	// trace_move(left);
	// trace_move(right);
	// self->weight[0] += (bc_x - bc_y * (left->x - x_old)) * a_z;
	// self->weight[1] += (ca_x - ca_y * (left->x - x_old)) * b_z;
	// self->weight[2] += (ab_x - ab_y * (left->x - x_old)) * c_z;
	dx = self->x[0] - x_old;
	self->w[0] += dwdx[0] * dx + dwdy[0];
	self->w[0] += dwdx[1] * dx + dwdy[1];
	self->w[0] += dwdx[2] * dx + dwdy[2];
}
