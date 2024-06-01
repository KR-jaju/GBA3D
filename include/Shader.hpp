
#ifndef SHADER_HPP
# define SHADER_HPP

# include "Triangle.hpp"
# include "Fragment.hpp"
# include "Texture.hpp"

/*
1. MVP mul (Vertex shader)
2. clip
3. Rasterize (fragment shader)
*/

class Shader {
public:
	INLINE static u8	pixelShader(Triangle const *tri) {
		return (5);
	}
	INLINE static u8	pixelShader(Triangle const *tri, u32 u, u32 v) {
		// float ru = float(u) / (1 << 16);
		// float rv = float(v) / (1 << 16);
		// return (u8((ru + rv) * 255));
		// return u8(u + v);
		// return ()
		// return (3);
		// ((u + v) & 4);
		return (Texture::sample(u, v));
	}
		// u32 const		scaled_x = x << 3;
		// u32 const		scaled_y = y << 3;
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
		// return fragment.value;
		// return (2);
	// }
private:
	IWRAM_CODE
	static u16	pixelMain(Fragment const &fragment);
};

#endif
// 		if (segment == NULL)
// 			return (0);
// 		u32 const		scaled_x = x << 3;
// 		u32 const		scaled_y = y << 3;
// 		Triangle const	*tri = segment->triangle;
// 		i32 const tx[] = {
// 			tri->vertex[0].x,
// 			tri->vertex[1].x,
// 			tri->vertex[2].x
// 		};
// 		i32 const ty[] = {
// 			tri->vertex[0].y,
// 			tri->vertex[1].y,
// 			tri->vertex[2].y
// 		};
// 		u32 const		bu = (tx[2] - tx[1]) * (scaled_y - ty[1]) - (ty[2] - ty[1]) * (scaled_x - tx[1]);
// 		u32 const		bv = (tx[0] - tx[2]) * (scaled_y - ty[2]) - (ty[0] - ty[2]) * (scaled_x - tx[2]);
// 		u32 const		bw = (tx[1] - tx[0]) * (scaled_y - ty[0]) - (ty[1] - ty[0]) * (scaled_x - tx[0]);
// 		u32 const		b = bu + bv + bw;
// 		Fragment fragment = {
// 			(bu * tri->vertex[0].v + bv * tri->vertex[1].v + bw * tri->vertex[2].v) / b
// 		};
// 		return (fragment.value);