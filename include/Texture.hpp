
#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include "type.hpp"

# define TEXTURE_UV_SHIFT	16

namespace Texture {
	INLINE
	u8	sample(u32 u, u32 v) {
		return u8((u + v) >> 14);
	}
}


#endif
