
#ifndef SEGMENT_HPP
# define SEGMENT_HPP

# include "type.hpp"
# include "Edge.hpp"
# include "Triangle.hpp"

struct Segment {
	Segment			*prev;
	Segment			*next;
	Triangle const	*triangle;
	Edge			trace[2];
	u32				breakpoint;
	i32				ac_orientation; // TODO: u8에 저장해도 됨

	Segment();
	Segment	&init(Triangle const *triangle);
	void	move();
};

#endif