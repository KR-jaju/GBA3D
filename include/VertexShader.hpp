
#ifndef VERTEX_SHADER_HPP
# define VERTEX_SHADER_HPP

# include "type.hpp"
# include "mat4.hpp"
# include "Mesh.hpp"

namespace VertexShader {
	struct Output {
		enum Flag {
			LEFT_CLIPPED = 1,
			RIGHT_CLIPPED = 1 << 1,
			BOTTOM_CLIPPED = 1 << 2,
			TOP_CLIPPED = 1 << 3,
			NEAR_CLIPPED = 1 << 4,
			FAR_CLIPPED = 1 << 5
		};
		~Output(){}
		union {
			fixed	real_x;
			i32		x;
		};
		union {
			fixed	real_y;
			i32		y;
		};
		fixed	z;
		i32		u;
		i32		v;
		i32		clip_flag;
	};
	extern mat4	matrix[10];
	
	template <u32 V, u32 F>
	static INLINE Output	main(typename Mesh<V, F>::Vertex const &in) {
		mat4 const	&vp_matrix = matrix[0];
		// vec4 const	position = Clipper::clampDepth(vp_matrix * (vec4){in.x, in.y, in.z, 1}, 1, 512);
		vec4 const	position = vp_matrix * (vec4){in.x, in.y, in.z, 1};
	
		return {position.x, position.y, position.z, in.u, in.v};
	}
}

#endif
