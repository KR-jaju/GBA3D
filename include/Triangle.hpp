
#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include "Fragment.hpp"
# include "util.hpp"
# include "VertexShader.hpp"
# include "Vertex.hpp"
# include <cmath>

struct Triangle {
	Triangle	*next;
	Vertex	vertex[3];
	i32	dudx;
	i32	dudy;
	i32	dvdx;
	i32	dvdy;

	Triangle	&init(Vertex const &a, Vertex const &b, Vertex const &c) {
		this->vertex[0] = a;
		this->vertex[1] = b;
		this->vertex[2] = c;
		this->sort();
		this->precalculate();
		return (*this);
	}

	IWRAM_CODE
	void	precalculate() {
		Vertex const	&v0 = this->vertex[0];
		Vertex const	&v1 = this->vertex[1];
		Vertex const	&v2 = this->vertex[2];
		i32 const		a = v1.x - v0.x;
		i32 const		b = v2.x - v0.x;
		i32 const		c = v1.y - v0.y;
		i32 const		d = v2.y - v0.y;
		i32 const		det = a * d - b * c;
		i32 const		v0v1u = v1.attr.u - v0.attr.u;
		i32 const		v0v1v = v1.attr.v - v0.attr.v;
		i32 const		v0v2u = v2.attr.u - v0.attr.u;
		i32 const		v0v2v = v2.attr.v - v0.attr.v;

		this->dudx = (d * v0v1u - c * v0v2u) / det;
		this->dudy = (-b * v0v1u + a * v0v2u) / det;
		this->dvdx = (d * v0v1v - c * v0v2v) / det;
		this->dvdy = (-b * v0v1v + a * v0v2v) / det;
	} //x, y증가량에 따른 u, v증가량

	// 정렬기준: y 작을수록 앞, y가 같으면 x가 작은게 앞
	IWRAM_CODE
	void	sort() {
		Vertex	&v0 = this->vertex[0];
		Vertex	&v1 = this->vertex[1];
		Vertex	&v2 = this->vertex[2];

		if (v0.y > v1.y || (v0.y == v1.y && v0.x > v1.x))
			swap(v0, v1);
		if (v1.y > v2.y || (v1.y == v2.y && v1.x > v2.x))
			swap(v1, v2);
		if (v0.y > v1.y || (v0.y == v1.y && v0.x > v1.x))
			swap(v0, v1);
	}
};

#endif
