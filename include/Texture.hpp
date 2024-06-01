
#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include "type.hpp"

# define TEXTURE_UV_SHIFT	16

class Texture {
public:
	INLINE
	static u8	sample(u32 u, u32 v) {
		return u8(float(u + v)/ (1 << 14));
		// return u8(v >> 4);
		// u8((u + v) >> 14) & 0b111;
		// u8((u + v) >> 8) & 0b11111111U;
	}
};


#endif
