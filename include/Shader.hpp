
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

namespace Shader {
	static INLINE u8	pixelShader(Triangle const *tri, u32 u, u32 v) {
		return (5);
		// return (Texture::sample(u, v));
	}
}

#endif