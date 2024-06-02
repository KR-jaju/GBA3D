
#ifndef SHADER_HPP
# define SHADER_HPP

# include "Triangle.hpp"
# include "Texture.hpp"
# include "fixed.hpp"

/*
1. MVP mul (Vertex shader)
2. clip
3. Rasterize (fragment shader)
*/

namespace Shader {
	INLINE Vertex	vertexShader(Vertex const &in) {
		fixed	x = fixed(in.x) * 0.5f;
		fixed y = fixed(in.y) * 0.5f;

		return {(int)x, (int)y, 0, in.u, in.v};
		// return in;
	}
	INLINE u8	pixelShader(Triangle const *tri, u32 u, u32 v) {
		return (Texture::sample(u, v));
	}
}

#endif