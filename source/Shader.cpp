
#include "Shader.hpp"

/*
bc.x * bp.y - bc.y * bp.x
ca.x * cp.y - ca.y * cp.x
ab.x * ap.y - ab.y * ap.x
*/

// u16	Shader::pixelShader(Segment const *segment, u32 x, u32 y) {
	// if (segment == NULL)
	// 	return (0);
	// u32 const		scaled_x = x << 3;
	// u32 const		scaled_y = y << 3;
	// Triangle const	*tri = segment->triangle;
	// i32 const tx[] = {
	// 	tri->vertex[0].x,
	// 	tri->vertex[1].x,
	// 	tri->vertex[2].x
	// };
	// i32 const ty[] = {
	// 	tri->vertex[0].y,
	// 	tri->vertex[1].y,
	// 	tri->vertex[2].y
	// };
	// u32 const		bu = (tx[2] - tx[1]) * (scaled_y - ty[1]) - (ty[2] - ty[1]) * (scaled_x - tx[1]);
	// u32 const		bv = (tx[0] - tx[2]) * (scaled_y - ty[2]) - (ty[0] - ty[2]) * (scaled_x - tx[2]);
	// u32 const		bw = (tx[1] - tx[0]) * (scaled_y - ty[0]) - (ty[1] - ty[0]) * (scaled_x - tx[0]);
	// u32 const		b = bu + bv + bw;
	// Fragment fragment = {
	// 	(bu * tri->vertex[0].v + bv * tri->vertex[1].v + bw * tri->vertex[2].v) / b
	// };
	// return ((segment == NULL) * 15);
		// Shader::pixelMain(fragment));
// }

u16	Shader::pixelMain(Fragment const &fragment) {
	return fragment.value;
}
