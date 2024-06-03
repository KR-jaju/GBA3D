
#ifndef CLIPPER_HPP
# define CLIPPER_HPP

# include "vec4.hpp"
# include "math.hpp"

namespace Clipper
{
	vec4	&clampDepth(vec4 const &in, i32 near, i32 far);
}


#endif
