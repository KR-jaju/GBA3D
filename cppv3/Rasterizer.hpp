
#ifndef RASTERIZER_HPP
# define RASTERIZER_HPP

# include "type.hpp"
# include "Triangle.hpp"
# include "Scanline.hpp"
# include "RasterSubject.hpp"

class Rasterizer {
public:
	void	render(RasterSubject const &subject) {
		Scanline	scan(subject);
		int			x;
		int			out[240];

		while (scan.getY() < 160) {
			x = 0;
			this->renderRow(scan.begin(), scan.end(), x, out);
			scan.move();
		}
	}
private:
	void	renderRow(Segment const *begin, Segment const *end, int &x, int *out) {
		if (begin == end)
			return;
		for (x = begin->trace[0].x; x < begin->trace[1].x; ++x) {
			Segment const	*next = begin->next;

			if (x == next->trace[0].x) {
				renderRow(next, end, x, out);
			} else {
				out[x] = 1;
			}
		}
	}
};

#endif
