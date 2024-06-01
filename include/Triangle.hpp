
#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include "Vertex.hpp"
# include "util.hpp"
# include <cmath>

struct Triangle {
	Triangle	*next; // RasterSubject에서 다음 삼각형에 대한 포인터
	Vertex		vertex[3];
	//u32 barycentric_all
	/*
	u32	barycentric_area; - 모든 질량중심좌표계 weight의 합
	u32	db[2] - du/dx, du/dy, dv/dx, du/dy -- 메모리 너무 씀..?
	u32	b[2] - u, v, 1 - u - v
	x, y만 있으면 가져올 수는 있음.
	*/
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

	INLINE
	void	precalculate() {
		Vertex const	&a = this->vertex[0];
		Vertex const	&b = this->vertex[1];
		Vertex const	&c = this->vertex[2];
		i32 const		determinant = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
		i32 const		m11 = c.y - a.y;
		i32 const		m12 = a.x - c.x;
		i32 const		m21 = a.y - b.y;
		i32 const		m22 = b.x - a.x;

		this->dudx = (m11 * (b.u - a.u) + m21 * (c.u - a.u)) / determinant;
		this->dudy = (m12 * (b.u - a.u) + m22 * (c.u - a.u)) / determinant;
		this->dvdx = (m11 * (b.v - a.v) + m21 * (c.v - a.v)) / determinant;
		this->dvdy = (m12 * (b.v - a.v) + m22 * (c.v - a.v)) / determinant;
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
