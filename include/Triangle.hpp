
#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include "Fragment.hpp"
# include "util.hpp"
# include "VertexShader.hpp"
# include <cmath>

struct Triangle {
	Triangle	*next;
	VertexShader::Output	vertex[3];
	i32	dudx;
	i32	dudy;
	i32	dvdx;
	i32	dvdy;

	Triangle	&init(VertexShader::Output const &a, VertexShader::Output const &b, VertexShader::Output const &c) {
		this->vertex[0] = a;
		this->vertex[1] = b;
		this->vertex[2] = c;
		this->sort();
		this->precalculate();
		return (*this);
	}

	IWRAM_CODE
	void	precalculate() {
		VertexShader::Output const	&v0 = this->vertex[0];
		VertexShader::Output const	&v1 = this->vertex[1];
		VertexShader::Output const	&v2 = this->vertex[2];
		i32 const		a = v1.x - v0.x;
		i32 const		b = v2.x - v0.x;
		i32 const		c = v1.y - v0.y;
		i32 const		d = v2.y - v0.y;
		i32 const		det = a * d - b * c;
		i32 const		v0v1u = v1.u - v0.u;
		i32 const		v0v1v = v1.v - v0.v;
		i32 const		v0v2u = v2.u - v0.u;
		i32 const		v0v2v = v2.v - v0.v;

		this->dudx = (d * v0v1u - c * v0v2u) / det;
		this->dudy = (-b * v0v1u + a * v0v2u) / det;
		this->dvdx = (d * v0v1v - c * v0v2v) / det;
		this->dvdy = (-b * v0v1v + a * v0v2v) / det;
	} //x, y증가량에 따른 u, v증가량

	// 정렬기준: y 작을수록 앞, y가 같으면 x가 작은게 앞
	IWRAM_CODE
	void	sort() {
		VertexShader::Output	&v0 = this->vertex[0];
		VertexShader::Output	&v1 = this->vertex[1];
		VertexShader::Output	&v2 = this->vertex[2];

		if (v0.y > v1.y || (v0.y == v1.y && v0.x > v1.x))
			swap(v0, v1);
		if (v1.y > v2.y || (v1.y == v2.y && v1.x > v2.x))
			swap(v1, v2);
		if (v0.y > v1.y || (v0.y == v1.y && v0.x > v1.x))
			swap(v0, v1);
	}
};

#endif
