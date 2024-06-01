
#ifndef SHADER_HPP
# define SHADER_HPP

# include "Triangle.hpp"
# include "Fragment.hpp"
# include "Texture.hpp"

/*
1. MVP mul (Vertex shader)
2. clip
3. Rasterize (fragment shader)
*/

class Shader {
public:
	INLINE static u8	pixelShader(Triangle const *tri, u32 u, u32 v) {
		return (Texture::sample(u, v));
	}
private:
	IWRAM_CODE
	static u16	pixelMain(Fragment const &fragment);
};

#endif