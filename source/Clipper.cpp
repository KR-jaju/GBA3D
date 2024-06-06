
#include "Clipper.hpp"

#define SWIDTH 1920
#define SHEIGHT 1280
//TODO : 이거 어떻게든 해줘

//-----------------이 소스파일은 성능 문제로 사용되지 않습니다------------
//-----------------일단 명목 상 유지 중-----------------

static
Vertex	intersectionLeft(Vertex const &a, Vertex const &b) {
	Vertex	intersection;
	//TODO : x의 차이가 0인 경우 div by zero나옴

	intersection.x = 0;
	intersection.y = (b.y - a.y) * (-a.x) / (b.x - a.x) + a.y; // TODO : div
	intersection.z = 0;
	intersection.attr.u = (b.attr.u - a.attr.u) * (-a.x) / (b.x - a.x) + a.attr.u;
	intersection.attr.v = (b.attr.v - a.attr.v) * (-a.x) / (b.x - a.x) + a.attr.v;
	return (intersection);
}
// y = dy/dx(X - x0) + y0

static
Vertex	intersectionRight(Vertex const &a, Vertex const &b) {
	i32 const	x = SWIDTH - 1;
	Vertex		intersection;

	intersection.x = x; // 240 * 8
	intersection.y = (b.y - a.y) * (x-a.x) / (b.x - a.x) + a.y; // div
	intersection.z = 0;
	intersection.attr.u = (b.attr.u - a.attr.u) * (x-a.x) / (b.x - a.x) + a.attr.u;
	intersection.attr.v = (b.attr.v - a.attr.v) * (x-a.x) / (b.x - a.x) + a.attr.v;
	return (intersection);
}

static
Vertex	intersectionTop(Vertex const &a, Vertex const &b) {
	Vertex	intersection;

	intersection.x = (b.x - a.x) * (-a.y) / (b.y - a.y) + a.x; // div
	intersection.y = 0;
	intersection.z = 0;
	intersection.attr.u = (b.attr.u - a.attr.u) * (-a.y) / (b.y - a.y) + a.attr.u;
	intersection.attr.v = (b.attr.v - a.attr.v) * (-a.y) / (b.y - a.y) + a.attr.v;
	return (intersection);
}

static
Vertex	intersectionBottom(Vertex const &a, Vertex const &b) {
	i32 const	y = SHEIGHT - 1;
	Vertex	intersection;

	intersection.x = (b.x - a.x) * (y-a.y) / (b.y - a.y) + a.x; // div
	intersection.y = y; // 160 * 8
	intersection.z = 0;
	intersection.attr.u = (b.attr.u - a.attr.u) * (y-a.y) / (b.y - a.y) + a.attr.u;
	intersection.attr.v = (b.attr.v - a.attr.v) * (y-a.y) / (b.y - a.y) + a.attr.v;
	return (intersection);
}

bool	Clipper::isClockwise(Vertex const &a, Vertex const &b, Vertex const &c) {
	i32 const	abx = b.x - a.x;
	i32 const	aby = b.y - a.y;
	i32 const	acx = c.x - a.x;
	i32 const	acy = c.y - a.y;

	return (abx * acy - aby * acx <= 0);
}

void	Clipper::clipX(Vertex *polygon, u32 &n) {
	Vertex	buffer[7];
	Vertex	*ptr = buffer;
	u32		count = n;
	Vertex const	*curr = polygon;
	Vertex const	*prev = polygon + count - 1;

	for (u32 i = 0; i < count; ++i) { // left clip
		if (curr->x >= 0) {
			if (prev->x < 0)
				*(ptr++) = intersectionLeft(*prev, *curr);
			*(ptr++) = *curr;
		} else if (prev->x >= 0)
			*(ptr++) = intersectionLeft(*prev, *curr);
		prev = curr;
		curr += 1;
	}
	count = ptr - buffer;
	ptr = polygon;
	curr = buffer;
	prev = buffer + count - 1;
	for (u32 i = 0; i < count; ++i) { // right clip
		if (curr->x < SWIDTH) {
			if (prev->x >= SWIDTH)
				*(ptr++) = intersectionRight(*prev, *curr);
			*(ptr++) = *curr;
		} else if (prev->x < SWIDTH)
			*(ptr++) = intersectionRight(*prev, *curr);
		prev = curr;
		curr += 1;
	}
	n = ptr - polygon;
}

void	Clipper::clipY(Vertex *polygon, u32 &n) {
	Vertex	buffer[7];
	Vertex	*ptr = buffer;
	u32		count = n;
	Vertex const	*curr = polygon;
	Vertex const	*prev = polygon + count - 1;

	for (u32 i = 0; i < count; ++i) {
		if (curr->y >= 0) {
			if (prev->y < 0)
				*(ptr++) = intersectionTop(*prev, *curr);
			*(ptr++) = *curr;
		} else if (prev->y >= 0)
			*(ptr++) = intersectionTop(*prev, *curr);
		prev = curr;
		curr += 1;
	}
	count = ptr - buffer;
	ptr = polygon;
	curr = buffer;
	prev = buffer + count - 1;
	for (u32 i = 0; i < count; ++i) {
		if (curr->y < SHEIGHT) {
			if (prev->y >= SHEIGHT)
				*(ptr++) = intersectionBottom(*prev, *curr);
			*(ptr++) = *curr;
		} else if (prev->y < SHEIGHT)
			*(ptr++) = intersectionBottom(*prev, *curr);
		prev = curr;
		curr += 1;
	}
	n = ptr - polygon;
}