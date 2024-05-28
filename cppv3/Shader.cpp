
#include "Shader.hpp"

/*
bc.x * bp.y - bc.y * bp.x
ca.x * cp.y - ca.y * cp.x
ab.x * ap.y - ab.y * ap.x
*/

u16	Shader::pixelShader(Segment const *segment, u32 x, u32 y) {
	if (segment == NULL)
		return (0);
	u32 const		scaled_x = x << 3;
	u32 const		scaled_y = y << 3;

	Triangle const	*tri = segment->triangle;
	u32 const		bu = (tri->vertex[2].x - tri->vertex[1].x) * (scaled_y - tri->vertex[1].y) - (tri->vertex[2].y - tri->vertex[1].y) * (scaled_x - tri->vertex[1].x);
	u32 const		bv = (tri->vertex[0].x - tri->vertex[2].x) * (scaled_y - tri->vertex[2].y) - (tri->vertex[0].y - tri->vertex[2].y) * (scaled_x - tri->vertex[2].x);
	u32 const		bw = (tri->vertex[1].x - tri->vertex[0].x) * (scaled_y - tri->vertex[0].y) - (tri->vertex[1].y - tri->vertex[0].y) * (scaled_x - tri->vertex[0].x);
	u32 const		b = bu + bv + bw;
	Fragment fragment = {
		(bu * tri->vertex[0].v + bv * tri->vertex[1].v + bw * tri->vertex[2].v) / b
	};
	return (Shader::pixelMain(fragment));
}

u16	Shader::pixelMain(Fragment const &fragment) {
	return fragment.value;
}
