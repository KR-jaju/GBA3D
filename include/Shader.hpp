
#ifndef SHADER_HPP
# define SHADER_HPP

# include "Triangle.hpp"
# include "Texture.hpp"
# include "fixed.hpp"
# include "mat4.hpp"
# include "VertexAttribute.hpp"

/*
1. MVP mul (Vertex shader)
2. clip
3. Rasterize (fragment shader)
*/

namespace Shader {
	static INLINE VertexAttribute	vertexShader(Vertex const &in, mat4 const &matrix) {
		vec4 const	position = (matrix * (vec4){in.x, in.y, in.z, 1});
		vec2 const	ndc = {position.x / position.w, position.y / position.w};
		vec2 const	viewport = {ndc.x * 960 + 960, -ndc.y * 640 + 640};
		return {(int)viewport.x, (int)viewport.y, 0, in.u, in.v};
	}
	static INLINE u8	pixelShader(Triangle const *tri, u32 u, u32 v) {
		// return (5);
		return (Texture::sample(u, v));
	}
}

#endif