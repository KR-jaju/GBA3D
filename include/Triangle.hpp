
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
		i32 const		abx = b.x - a.x;
		i32 const		aby = b.y - a.y;
		i32 const		acx = c.x - a.x;
		i32 const		acy = c.y - a.y;
		i32 const		dau = (b.u - a.u);
		i32 const		dav = (b.v - a.v);
		i32 const		dbu = (c.u - a.u);
		i32 const		dbv = (c.v - a.v);
		i32 const		ab_mag = (abx * abx + aby * aby);
		i32 const		ac_mag = (acx * acx + acy * acy);

		this->dudx = (abx * dau * ac_mag + acx * dbu * ab_mag) / (ab_mag * ac_mag);
		this->dudy = (aby * dau * ac_mag + acy * dbu * ab_mag) / (ab_mag * ac_mag);
		this->dvdx = (abx * dav * ac_mag + acx * dbv * ab_mag) / (ab_mag * ac_mag);
		this->dvdy = (aby * dav * ac_mag + acy * dbv * ab_mag) / (ab_mag * ac_mag);
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
