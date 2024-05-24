
#ifndef RASTERIZER_HPP
# define RASTERIZER_HPP

# include "type.hpp"
# include "Triangle.hpp"
# include "Scanline.hpp"
# include "RasterSubject.hpp"
#include <iostream>
static
void	clear(int *o){
	for (int i = 0; i <240; ++i)
		o[i] = 0;
}
class Rasterizer {
public:
	void	render(RasterSubject const &subject) {
		Scanline	scan(subject);
		int			x;
		int			out[240];

		while (scan.getY() < 160) {
			x = 0;
			clear(out);
			for (Segment *s = scan.begin(); s != scan.end(); s = s->next) {
				this->renderRow(s, scan.end(), x, out);	
			}
			for (int i = 0; i < 240; ++i)
				std::cout << out[i];
			std::cout << std::endl;
			
			scan.move();
		}
	}
private:
	void	renderRow(Segment const *begin, Segment const *end, int &x, int *out) {
		if (begin == end)
			return;
		for (x = begin->edge[0].x; x < begin->edge[1].x; ++x) {
			Segment const	*next = begin->next;

			if (x == next->edge[0].x) {
				renderRow(next, end, x, out);
				continue;
			}
			if (!(0 <= x && x < 240))
				continue;
			out[x] = 1;
		}
	}
};

#endif