
#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include "Vertex.hpp"
# include "util.hpp"

struct Triangle {
	Vertex	vertex[3];
	//u32 barycentric_all
	/*
	u32	barycentric_area; - 모든 질량중심좌표계 weight의 합
	u32	db[2] - du/dx, du/dy, dv/dx, du/dy -- 메모리 너무 씀..?
	u32	b[2] - u, v, 1 - u - v
	x, y만 있으면 가져올 수는 있음.
	*/


	// 정렬기준: y 작을수록 앞, y가 같으면 x가 작은게 앞
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
