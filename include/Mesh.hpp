
#ifndef MESH_HPP
# define MESH_HPP

# include "type.hpp"
# include "fixed.hpp"

template <u32 V, u32 F>
struct Mesh {
	struct Vertex {
		fixed	x;
		fixed	y;
		fixed	z;
		i32		u;
		i32		v;
	};
	Vertex	vertex[V];
	u32		index[F * 3];
};

#endif
