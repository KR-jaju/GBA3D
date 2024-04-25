
#include "gpi_private.h"
#include <stdlib.h>
#include <stdio.h>

void	scanline_test(void) {
	typedef struct {int	x; int	y;}	t_point;
	t_vertex	points[] = {
		{(int)(25.4f * 8), (int)(9.5f * 8), 0},
		{(int)(86.4f * 8), (int)(12.7f * 8), 0},
		{(int)(34.4f * 8), (int)(66.7f * 8), 0}
	};
	t_span	triangle;
	t_scanline	scanline;

	span_init(&triangle, points, (int []){0, 1, 2});
	scanline_init(&scanline, points, &triangle);
	for (int y = 0; y < 160; ++y) {
		scanline_move(&scanline, y);
		for (int x = 0; x < 100; ++x) {
			if (scanline.active != &scanline.active_end) {
				t_span	*span = scanline.active;
				t_trace	*left = span_left(span, y < span->y[1]);
				t_trace	*right = span_right(span, y < span->y[1]);

				if (left->x <= x && x < right->x)
					printf("#");
				else
					printf(" ");
			}
			else
				printf(" ");
		}
		printf("\n");
	}
}

int	main(void) {
	scanline_test();
}
