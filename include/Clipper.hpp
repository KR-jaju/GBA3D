
#ifndef CLIPPER_HPP
# define CLIPPER_HPP

# include "vec4.hpp"
# include "math.hpp"
# include "Vertex.hpp"

namespace Clipper
{
	bool	isClockwise(Vertex const &a, Vertex const &b, Vertex const &c);
	void	clipX(Vertex *polygon, u32 &n);
	void	clipY(Vertex *polygon, u32 &n);
}


#endif
