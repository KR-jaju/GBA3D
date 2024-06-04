
#include "Clipper.hpp"

#define SWIDTH 1920
#define SHEIGHT 1280
//TODO : 이거 어떻게든 해줘


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
	Vertex	intersection;

	intersection.x = 1920; // 240 * 8
	intersection.y = (b.y - a.y) * (1920-a.x) / (b.x - a.x) + a.y; // div
	intersection.z = 0;
	intersection.attr.u = (b.attr.u - a.attr.u) * (1920-a.x) / (b.x - a.x) + a.attr.u;
	intersection.attr.v = (b.attr.v - a.attr.v) * (1920-a.x) / (b.x - a.x) + a.attr.v;
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
	Vertex	intersection;

	intersection.x = (b.x - a.x) * (1280-a.y) / (b.y - a.y) + a.x; // div
	intersection.y = 1280; // 160 * 8
	intersection.z = 0;
	intersection.attr.u = (b.attr.u - a.attr.u) * (1280-a.y) / (b.y - a.y) + a.attr.u;
	intersection.attr.v = (b.attr.v - a.attr.v) * (1280-a.y) / (b.y - a.y) + a.attr.v;
	return (intersection);
}

bool	Clipper::isClockwise(Vertex const &a, Vertex const &b, Vertex const &c) {
	i32 const	abx = b.x - a.x;
	i32 const	aby = b.y - a.y;
	i32 const	acx = c.x - a.x;
	i32 const	acy = c.y - a.y;

	return (abx * acy - aby * acx >= 0);
}

void	Clipper::clipX(Vertex *polygon, u32 &n) {
	Vertex	buffer[7];
	Vertex	*ptr = buffer;
	u32		count = n;

	for (u32 i = 0; i < count; ++i) { // left clip
		Vertex const	&curr = polygon[i];
		Vertex const	&prev = polygon[(i - 1) % count]; // TODO: div
		
		if (curr.x >= 0) {
			if (prev.x < 0)
				*(ptr++) = intersectionLeft(prev, curr);
			*(ptr++) = curr;
		} else if (prev.x >= 0)
			*(ptr++) = intersectionLeft(prev, curr);
	}
	count = ptr - buffer;
	ptr = polygon;
	for (u32 i = 0; i < count; ++i) { // right clip
		Vertex const	&curr = buffer[i];
		Vertex const	&prev = buffer[(i - 1) % count]; // TODO: div
		
		if (curr.x < SWIDTH) {
			if (prev.x >= SWIDTH)
				*(ptr++) = intersectionRight(prev, curr);
			*(ptr++) = curr;
		} else if (prev.x < SWIDTH)
			*(ptr++) = intersectionRight(prev, curr);
	}
	n = ptr - polygon;
}

void	Clipper::clipY(Vertex *polygon, u32 &n) {
	Vertex	buffer[7];
	Vertex	*ptr = buffer;
	u32		count = n;

	for (u32 i = 0; i < count; ++i) {
		Vertex const	&curr = polygon[i];
		Vertex const	&prev = polygon[(i - 1) % count]; // TODO: div
		
		if (curr.y >= 0) {
			if (prev.y < 0)
				*(ptr++) = intersectionTop(prev, curr);
			*(ptr++) = curr;
		} else if (prev.y >= 0)
			*(ptr++) = intersectionTop(prev, curr);
	}
	count = ptr - buffer;
	ptr = polygon;
	for (u32 i = 0; i < count; ++i) {
		Vertex const	&curr = buffer[i];
		Vertex const	&prev = buffer[(i - 1) % count]; // TODO: div
		
		if (curr.y < SHEIGHT) {
			if (prev.y >= SHEIGHT)
				*(ptr++) = intersectionBottom(prev, curr);
			*(ptr++) = curr;
		} else if (prev.y < SHEIGHT)
			*(ptr++) = intersectionBottom(prev, curr);
	}
	n = ptr - polygon;
}