
#ifndef RASTERIZER_HPP
# define RASTERIZER_HPP

# include "type.hpp"
# include "Triangle.hpp"
# include "RasterSubject.hpp"
# include "Shader.hpp"
# include "Edge.hpp"

namespace Rasterizer {
	IWRAM_CODE
	void	render(RasterSubject const &subject, u8 *out);
	IWRAM_CODE
	void	render(Triangle const &triangle, u8 *out);
}


#endif