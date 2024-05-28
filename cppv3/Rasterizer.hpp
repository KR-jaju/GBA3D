
#ifndef RASTERIZER_HPP
# define RASTERIZER_HPP

# include "type.hpp"
# include "Triangle.hpp"
# include "Scanline.hpp"
# include "RasterSubject.hpp"
# include "Shader.hpp"
# include <iostream>

class Rasterizer {
public:
	void	render(RasterSubject const &subject) {
		Scanline	scan(subject);
		int			out[240];

		while (scan.getY() < 160) {
			// this->renderScanline(0, 240, scan.getY(), NULL, scan.begin(), scan.end(), out, 0);
			scan.render(out);
			for (int i = 0; i < 240; ++i)
				std::cout << out[i];
			std::cout << std::endl;
			
			scan.move();
		}
	}
private:
};

#endif