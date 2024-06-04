
#ifndef VERTEX_HPP
# define VERTEX_HPP

# include "type.hpp"

struct Vertex {
	enum Flag {
		CLIP_LEFT = 1,
		CLIP_RIGHT = 1 << 1,
		CLIP_TOP = 1 << 2,
		CLIP_BOTTOM = 1 << 3,
		CLIP_NEAR = 1 << 4,
		CLIP_FAR = 1 << 5,
		DISCARDED = (CLIP_LEFT | CLIP_RIGHT | CLIP_BOTTOM | CLIP_TOP | CLIP_NEAR | CLIP_FAR),
		CLIP_X = CLIP_LEFT | CLIP_RIGHT,
		CLIP_Y = CLIP_TOP | CLIP_BOTTOM
	};
	struct Attribute {
		i32	u;
		i32	v;
	};

	i32			x;
	i32			y;
	i32			z;
	u32		 	flag;
	Attribute	attr;
};

#endif
