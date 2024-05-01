
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

char	pixel_shader(i32 x, i32 y, t_pixel *pixels, t_pixel *end) {
	if (pixels == NULL)
		return ' ';
	return '#';
}

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
	t_scanpixel	scanpixel;

	for (scanline_init(&scanline, triangles, 1); scanline.y < 160; scanline_move(&scanline)) {
		i32 const	y = scanline.y;
		for (scanpixel_init(&scanpixel, scanline.active); scanpixel.x < 100; scanpixel_move(&scanpixel)) {
			i32 const	x = scanpixel.x;
			printf("%c", pixel_shader(x, y, scanpixel.active, &scanpixel.active_end));
		}
		printf("\n");
	}
}

int	main(void) {
	scanline_test();
}
