
#include "gpi_private.h"
#include <stdlib.h>
#include <stdio.h>

/*
void	draw(t_triangle *triangle, i32 count) {
	t_scanline	scanline;
	t_scanpixel	scanpixel;

	scanline_init(&scanline, triangle, count, 160);
	while (!scanline_end()) {
		scanpixel_init(&scanpixel, &scanpixel, 270);
		while (!scanpixel_end()) {

		}
	}
	for (scanline_init(&scanline, triangle, count);
		scanline.y < 160;
		scanline_move(&scanline)) {

	}
}
*/

void	scanline_test(void) {
	typedef struct {int	x; int	y;}	t_point;
	t_vertex	points[] = {
		{(int)(25.4f * 8), (int)(9.5f * 8), 0},
		{(int)(86.4f * 8), (int)(12.7f * 8), 0},
		{(int)(34.4f * 8), (int)(66.7f * 8), 0}
	};
	t_triangle	triangles[] = {
		{&points[0], &points[1], &points[2]}
	};
	t_scanline	scanline;

	// scanline_init(&scanline, triangles, 1);
	// while (scanline.y < 160) {
	for (scanline_init(&scanline, triangles, 1);
		scanline.y < 160;
		scanline_move(&scanline)) {
		i32 const	y = scanline.y;
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
