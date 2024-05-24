
#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include "Vertex.hpp"

struct Triangle {
	Vertex	vertex[3];
	// 정렬기준: y 작을수록 앞, y가 같으면 x가 작은게 앞
};

#endif
