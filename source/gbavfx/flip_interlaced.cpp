// #include "gbavfx/gbavfx.h"

// IWRAM_CODE void	gbavfx_flip_interlaced() {
// 	void (*rasterizer)(u32, u32);

// 	if ((u32)gbavfx_color & 0xA000) // drawing buffer[1]
// 		rasterizer = gbavfx_rasterize_interlaced_odd;
// 	else
// 		rasterizer = gbavfx_rasterize_interlaced;
	
// 	i32 i = MAX_DEPTH_VARIATION;
// 	while (--i) {
// 		i32	face_idx = ordering_table[i];

// 		while (face_idx != -1) {
// 			u32 const	a = gbavfx_fbo.face[face_idx * 2];
// 			i32 const	b = gbavfx_fbo.face[face_idx * 2 + 1];

// 			face_idx = (b >> 21); // upper 11bit
// 			rasterizer(a, b);
// 		}
// 	}
// 	gbavfx_interlace();
// }
