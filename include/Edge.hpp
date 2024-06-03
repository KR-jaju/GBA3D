
#ifndef EDGE_HPP
# define EDGE_HPP

# include "type.hpp"
# include "Fragment.hpp"

/*
x = 240 * 8 < 16bit
shade - 16bit
uv = 32bit
*/

struct Edge {
	i32	scaled_dx;
	i32	scaled_dy; // 너무 큰가??
	i32	error;
	u32	pack; // 31 {i8 step; u8 shade; u16 x;} 0

	IWRAM_CODE
	Edge	&init(Fragment const &a, Fragment const &b);
	IWRAM_CODE
	void	move();
	i32		x() const {
		return (i16(u16(this->pack)));
	}
};

#endif
