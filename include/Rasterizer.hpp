
#ifndef RASTERIZER_HPP
# define RASTERIZER_HPP

# include "type.hpp"
# include "Triangle.hpp"
# include "Scanline.hpp"
# include "RasterSubject.hpp"
# include "Shader.hpp"

class Rasterizer {
public:
	IWRAM_CODE
	void	render(RasterSubject const &subject);
private:
};

#endif