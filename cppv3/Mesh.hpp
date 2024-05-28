
#ifndef MESH_HPP
# define MESH_HPP

# include "type.hpp"
# include "Vertex.hpp"

template <u32 V, u32 F>
class Mesh {
public:
	Vertex	vertex[V];
	u32		index[F * 3];
};

#endif
