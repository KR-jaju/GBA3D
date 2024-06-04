
#include "Clipper.hpp"

static
Vertex	intersectionLeft(Vertex const &a, Vertex const &b) {

}

static
Vertex	intersectionRight(Vertex const &a, Vertex const &b) {

}

static
Vertex	intersectionTop(Vertex const &a, Vertex const &b) {

}

static
Vertex	intersectionBottom(Vertex const &a, Vertex const &b) {

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
	for (u32 i = 0; i < count; ++i) { // left clip
		Vertex const	&curr = buffer[i];
		Vertex const	&prev = buffer[(i - 1) % count]; // TODO: div
		
		if (curr.x >= 0) {
			if (prev.x < 0)
				*(ptr++) = intersectionRight(prev, curr);
			*(ptr++) = curr;
		} else if (prev.x >= 0)
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
		
		if (curr.x >= 0) {
			if (prev.x < 0)
				*(ptr++) = intersectionTop(prev, curr);
			*(ptr++) = curr;
		} else if (prev.x >= 0)
			*(ptr++) = intersectionTop(prev, curr);
	}
	count = ptr - buffer;
	ptr = polygon;
	for (u32 i = 0; i < count; ++i) {
		Vertex const	&curr = buffer[i];
		Vertex const	&prev = buffer[(i - 1) % count]; // TODO: div
		
		if (curr.x >= 0) {
			if (prev.x < 0)
				*(ptr++) = intersectionBottom(prev, curr);
			*(ptr++) = curr;
		} else if (prev.x >= 0)
			*(ptr++) = intersectionBottom(prev, curr);
	}
	n = ptr - polygon;
}