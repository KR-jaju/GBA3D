
#ifndef FRAGMENT_HPP
# define FRAGMENT_HPP

# include "type.hpp"

struct Fragment
{
	enum Flag {
		LEFT_CLIPPED = 1,
		RIGHT_CLIPPED = 1 << 1,
		BOTTOM_CLIPPED = 1 << 2,
		TOP_CLIPPED = 1 << 3,
		NEAR_CLIPPED = 1 << 4,
		FAR_CLIPPED = 1 << 5
	};

	i32	x;
	i32	y;
	i32	z;
	i32	u;
	i32	v;
	i32 clip_flag;
};


#endif
