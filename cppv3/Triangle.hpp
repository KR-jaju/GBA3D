
#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include "Vertex.hpp"
# include <algorithm>

struct Triangle {
	Vertex	vertex[3];
	// 정렬기준: y 작을수록 앞, y가 같으면 x가 작은게 앞
	void	sort() {
		Vertex	&v0 = this->vertex[0];
		Vertex	&v1 = this->vertex[1];
		Vertex	&v2 = this->vertex[2];

		if (v0.y > v1.y || (v0.y == v1.y && v0.x > v1.x))
			std::swap(v0, v1);
		if (v1.y > v2.y || (v1.y == v2.y && v1.x > v2.x))
			std::swap(v1, v2);
		if (v0.y > v1.y || (v0.y == v1.y && v0.x > v1.x))
			std::swap(v0, v1);
	}
};

#endif
