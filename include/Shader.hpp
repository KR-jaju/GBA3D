
#ifndef SHADER_HPP
# define SHADER_HPP

# include "Triangle.hpp"
# include "Texture.hpp"
# include "fixed.hpp"
# include "mat4.hpp"
# include "Mesh.hpp"
# include "SkeletalMesh.hpp"
# include "Clipper.hpp"
# include "Fragment.hpp"

/*
1. MVP mul (Vertex shader)
2. clip
3. Rasterize (fragment shader)
*/

namespace Shader {
	extern mat4	matrix[10];

	template <u32 V, u32 F>
	static INLINE Fragment	vertexShader(typename Mesh<V, F>::Vertex const &in) {
		mat4 const	&vp_matrix = matrix[0];
		// vec4 const	position = Clipper::clampDepth(vp_matrix * (vec4){in.x, in.y, in.z, 1}, 1, 512);
		vec4 const	position = vp_matrix * (vec4){in.x, in.y, in.z, 1};
		i32 const	viewport_x = (i32)(position.x / position.z * 960) + 960;
		i32 const	viewport_y = (i32)(-position.y / position.z * 640) + 640;
	
		return {viewport_x, viewport_y, 0, in.u, in.v};
	}




	static INLINE u8	pixelShader(Triangle const *tri, u32 u, u32 v) {
		// return (5);
		return (Texture::sample(u, v));
	}
}

#endif