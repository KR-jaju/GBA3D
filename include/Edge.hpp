
#ifndef EDGE_HPP
# define EDGE_HPP

# include "type.hpp"

struct Edge {
	i32	scaled_dx;
	i32	scaled_dy;
	i32	step;
	i32	error;
	i32	x;
	i32	z;

	IWRAM_CODE
	Edge	&init(i32 x0, i32 y0, i32 x1, i32 y1);
	IWRAM_CODE
	void	move();
};

#endif
