
#ifndef VERTEX_SHADER_HPP
# define VERTEX_SHADER_HPP

# include "type.hpp"
# include "mat4.hpp"
# include "Mesh.hpp"
# include "Vertex.hpp"

namespace VertexShader {
	IWRAM
	extern mat4	matrix[10];
	IWRAM
	extern vec4	out_position; // out
	
	template <u32 V, u32 F>
	static INLINE void	main(typename Mesh<V, F>::Vertex const &in, Vertex::Attribute &out) {
		mat4 const	&vp_matrix = matrix[0];

		out.u = in.u;
		out.v = in.v;
		out_position = vp_matrix * (vec4){in.x, in.y, in.z, 1};
	}
}

#endif
