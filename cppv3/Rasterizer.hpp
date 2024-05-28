
#ifndef RASTERIZER_HPP
# define RASTERIZER_HPP

# include "type.hpp"
# include "Triangle.hpp"
# include "Scanline.hpp"
# include "RasterSubject.hpp"
# include <iostream>

class Rasterizer {
public:
	void	render(RasterSubject const &subject) {
		Scanline	scan(subject);
		int			out[240];

		while (scan.getY() < 160) {
			this->renderScanline(0, 240, scan.begin(), scan.end(), out, 0);
			for (int i = 0; i < 240; ++i)
				std::cout << out[i];
			std::cout << std::endl;
			
			scan.move();
		}
	}
private:
	void	renderScanline(int l, int r, Segment const *incoming, Segment const *end, int *out, int depth) const {
		Segment const	*next;
		static int		x; // TODO: threadlocal을 쓰면 더 멋질지도
	
		next = incoming;
		x = l;
		while (x < r) {
			while (next != end && x > next->edge[0].x) {
				next = next->next;
			}
			if (next != end && x == next->edge[0].x) {
				int const	nl = next->edge[0].x;
				int const	nr = next->edge[1].x;

				next = next->next;
				this->renderScanline(nl, nr, next, end, out, depth + 1);
				continue;
			}
			out[x] = depth; // Assign color
			x += 1;
		}
	}
	/*
	Fragment {
		u32 u;
		u32 v;
		u32 w;
		u32 texture_u;
		u32 texture_v;
		u32 color;
	}
	*/
};

#endif