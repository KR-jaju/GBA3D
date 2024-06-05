
#ifndef RASTERIZER_HPP
# define RASTERIZER_HPP

# include "type.hpp"
# include "Triangle.hpp"
# include "Shader.hpp"
# include "Edge.hpp"
# include "DepthTable.hpp"

#define INTERLACED_RENDERING
namespace Rasterizer {
	IWRAM_CODE
	void	render(DepthTable const &table, u8 *out);
	IWRAM_CODE
	void	render(Triangle const &triangle, u8 *out);
}


#endif