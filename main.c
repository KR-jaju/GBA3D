
#include "gpi_private.h"
#include <stdlib.h>
#include <stdio.h>

void	span_test(void) {
	t_trace	a;
	t_trace	b;
	t_span	span;

	trace_init(&a,
		(int)(25.4f * 8), (int)(9.5f * 8),
		(int)(34.4f * 8), (int)(128.7f * 8)
	);
	trace_init(&b,
		(int)(25.4f * 8), (int)(9.5f * 8),
		(int)(86.4f * 8), (int)(128.7f * 8)
	);

	span_init(&span, &a, &b, 25, 34-25 + 1);

	for (int i = 0; i < 40; ++i) {
		for (int j = 0; j < 100; ++j) {
			if (span.left->x <= j && j < span.right->x) {
				printf("#");
			} else {
				printf(" ");
			}
		}
		printf("\n");
		span_move(&span);
	}
}

void	scanline_test(void) {
	typedef struct {int	x; int	y;}	t_point;
	t_point	points[] = {
		{(int)(25.4f * 8), (int)(9.5f * 8)},
		{(int)(34.4f * 8), (int)(66.7f * 8)},
		{(int)(86.4f * 8), (int)(12.7f * 8)},
	};

	{
		if (points[0].y > points[1].y) {
			t_point	tmp = points[0];
			points[0] = points[1];
			points[1] = tmp;
		}
		if (points[1].y > points[2].y) {
			t_point	tmp = points[1];
			points[1] = points[2];
			points[2] = tmp;
		}
		if (points[0].y > points[1].y) {
			t_point	tmp = points[0];
			points[0] = points[1];
			points[1] = tmp;
		}
	}//sort vertices

	t_trace	ab;
	t_trace	ac;
	t_trace	bc;
	t_span	top;
	t_span	bottom;
	t_scanline	scanline;

	trace_init(&ab,
		points[0].x, points[0].y,
		points[1].x, points[1].y
	);
	trace_init(&ac,
		points[0].x, points[0].y,
		points[2].x, points[2].y
	);
	trace_init(&bc,
		points[1].x, points[1].y,
		points[2].x, points[2].y
	);

	int	high = ((points[0].y + 3) & ~0b111) + 4;
	int	mid = ((points[1].y + 3) & ~0b111) + 4;
	int	low = ((points[2].y + 3) & ~0b111) + 4;

	if (points[1].x < points[2].x) {
		span_init(&top, &ab, &ac, high, mid);
		span_init(&bottom, &bc, &ac, mid, low);
	} else {
		span_init(&top, &ac, &ab, high, mid);
		span_init(&bottom, &ac, &bc, mid, low);
	}
	scanline_init(&scanline);
	scanline_push(&scanline, &bottom);
	scanline_push(&scanline, &top);
	scanline_sort(&scanline); //귀찮아서 아직 구현 안 함
	for (int y = 0; y < 160; ++y) {
		scanline_move(&scanline);
		for (int x = 0; x < 240; ++x) {
			if (scanline.active != NULL && scanline.active->left->x <= x && x < scanline.active->right->x)
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}
}

int	main(void) {
	// span_test();
	scanline_test();
}
