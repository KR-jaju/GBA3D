
#ifndef SHADER_HPP
# define SHADER_HPP

# include "Triangle.hpp"
# include "Texture.hpp"
# include "fixed.hpp"
# include "mat4.hpp"

/*
1. MVP mul (Vertex shader)
2. clip
3. Rasterize (fragment shader)
*/

namespace Shader {
	static INLINE Vertex	vertexShader(Vertex const &in, mat4 const &matrix) {
		vec4 const	position = (matrix * (vec4){fixed::from(in.x), fixed::from(in.y), fixed::from(in.z), 1});
		vec2 const	ndc = {position.x / position.w, position.y / position.w};
		vec2 const	viewport = {(ndc.x + 1) * 120 * 8, (-ndc.y + 1) * 80 * 8};
		return {(int)viewport.x, (int)viewport.y, 0, in.u, in.v};
	}
	static INLINE u8	pixelShader(Triangle const *tri, u32 u, u32 v) {
		return (Texture::sample(u, v));
	}
}

#endif