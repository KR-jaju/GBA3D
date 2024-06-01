
#ifndef TEXTURE_HPP
# define TEXTURE_HPP

# include "type.hpp"

# define TEXTURE_UV_SHIFT	16

class Texture {
public:
	IWRAM_CODE
	static u8	sample(u32 u, u32 v) {
		// return u8(float(u + v)/ (1 << 14));
		// return u8(v >> 4);
		return u8((u + v) >> 14);
		// u8((u + v) >> 8) & 0b11111111U;
	}
};


#endif
