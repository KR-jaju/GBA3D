
#ifndef EDGE_HPP
# define EDGE_HPP

# include "type.hpp"
# include "Fragment.hpp"
# include "Triangle.hpp"

/*
x = 240 * 8 < 16bit
shade - 16bit
uv = 32bit
*/

struct Edge {
	fixed	dxdy;
	fixed	x;

	Edge	&init(Vertex const &a, Vertex const &b);
	void	move();
};

inline Edge	&Edge::init(Vertex const &a, Vertex const &b) {
	fixed const	dx = b.x - a.x;
	fixed const	dy = b.y - a.y;

	this->x = a.x;
	if (dy == 0) {
		this->dxdy = 0;
		return (*this); // degeneracy
	}
	this->dxdy = dx / dy;
	this->x += (fixed::from(a.y.num + 0x7FFF) + 0.5f - a.y) * this->dxdy;
	return (*this);
}

inline void	Edge::move() {
	this->x += this->dxdy;
}


#endif
