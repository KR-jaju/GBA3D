
#include "Segment.hpp"

Segment::Segment() {
	this->next = this;
	this->prev = this;
}

Segment	&Segment::init(Triangle const *triangle) {
	i32 const	x[3] = {
		triangle->vertex[0].x,
		triangle->vertex[1].x,
		triangle->vertex[2].x
	};
	i32 const	y[3] = {
		triangle->vertex[0].y,
		triangle->vertex[1].y,
		triangle->vertex[2].y
	};
	i32 const	ac_orientation = ((x[1] - x[0]) * (y[2] - y[0]) <= (x[2] - x[0]) * (y[1]- y[0]));

	i32	const	breakpoint = y[1] - y[0];

	if (breakpoint == 0)
		this->edge[!ac_orientation].init(x[1], y[1], x[2], y[2]);
	else
		this->edge[!ac_orientation].init(x[0], y[0], x[1], y[1]);
	this->edge[ac_orientation].init(x[0], y[0], x[2], y[2]);
	this->prev = this;
	this->next = this;
	this->triangle = triangle;
	this->breakpoint = breakpoint;
	this->ac_orientation = ac_orientation;
	return (*this);
}


void	Segment::move() {
	Vertex const	&v1 = this->triangle->vertex[1];
	Vertex const	&v2 = this->triangle->vertex[2];

	this->breakpoint -= 1;
	if (this->breakpoint == 0) {
		i32 const	ac_orientation = this->ac_orientation;

		this->edge[!ac_orientation].init(v1.x, v1.y, v2.x, v2.y);
		this->edge[ac_orientation].move();
	} else {
		this->edge[0].move();
		this->edge[1].move();
	}
}
