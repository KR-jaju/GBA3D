
#ifndef SHADER_HPP
# define SHADER_HPP

# include "Triangle.hpp"
# include "Texture.hpp"

/*
1. MVP mul (Vertex shader)
2. clip
3. Rasterize (fragment shader)
*/

namespace Shader {
	INLINE u8	pixelShader(Triangle const *tri, u32 u, u32 v) {
		return (Texture::sample(u, v));
	}
}

#endif