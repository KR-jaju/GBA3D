
// #include "gbavfx/gbavfx.h"
// #include <algorithm>

// namespace gbavfx {
// 	void	rasterize(u32 a, u32 b) {
// 		u32 t0 = vertex_buffer[(a & 0xFFFF) * 2 + 1];
// 		u32 t1 = vertex_buffer[(a >> 16) * 2 + 1];
// 		u32 t2 = vertex_buffer[(b & 0xFFFF) * 2 + 1];

// 		u32 va0 = vertex_buffer[(a & 0xFFFF) * 2];
// 		u32 va1 = vertex_buffer[(a >> 16) * 2];
// 		u32 va2 = vertex_buffer[(b & 0xFFFF) * 2];

// 		i32 a_h, b_h;
// 		i32 a_x, b_x, l_u, l_v;
// 		i32 a_dx, b_dx, a_du, a_dv, b_du, b_dv;
// 		i32 h;
		
// 		i32 dudx;
// 		i32 dvdx;
// 		u8* base;
// 		u32 texture_id = (b & 0x001F0000) >> 16;
// 		u8* texture = texture_slot[texture_id];

// 		{
// 			a_x = (i32(va0 & 0x0000FFFF) - 32768) << 16;
// 			a_h = (i32(va1 >> 16) - 32768) - (i32(va0 >> 16) - 32768);
// 			b_x = a_x;
// 			b_h = (i32(va2 >> 16) - 32768) - (i32(va0 >> 16) - 32768);
// 			l_u = (t0 & 0x00FF0000);
// 			l_v = (t0 & 0x000000FF) << 16;

// 			i32 dx01 = ((i32(va1 & 0x0000FFFF) - 32768) << 16) - a_x;
// 			i32 du01 = i32(t1 >> 16) - i32(t0 >> 16);
// 			i32 dv01 = (i32(t1 << 16) >> 16) - (i32(t0 << 16) >> 16);

// 			i32 dx02 = ((i32(va2 & 0x0000FFFF) - 32768) << 16) - a_x;
// 			i32 du02 = i32(t2 >> 16) - i32(t0 >> 16);
// 			i32 dv02 = (i32(t2 << 16) >> 16) - (i32(t0 << 16) >> 16);

// 			{
// 				i32 det = (dx01 >> 16) * b_h - (dx02 >> 16) * a_h;
// 				if (det == 0)
// 					return;
// 				i32 inv_det = i32((1LL << 32) / det);
// 				dudx = i32((i64(i32(du01 * b_h - du02 * a_h)) * inv_det) >> 16);
// 				dvdx = i32((i64(i32(dv01 * b_h - dv02 * a_h)) * inv_det) >> 16);
// 			}
// 			{
// 				u32 inv_a_dy = (1 << 16) / std::max(a_h, 1);
// 				u32 inv_b_dy = (1 << 16) / std::max(b_h, 1);
// 				a_dx = ((i32(va1 & 0x0000FFFF) - 32768) - (i32(va0 & 0x0000FFFF) - 32768)) * inv_a_dy;
// 				b_dx = ((i32(va2 & 0x0000FFFF) - 32768) - (i32(va0 & 0x0000FFFF) - 32768)) * inv_b_dy;
// 				a_du = (du01 * inv_a_dy);
// 				b_du = (du02 * inv_b_dy);
// 				a_dv = (dv01 * inv_a_dy);
// 				b_dv = (dv02 * inv_b_dy);
// 			}
// 		}

// 		i32 top = std::max(i32(va0 >> 16) - 32768, 0);
// 		i32 clipped_y = top - (i32(va0 >> 16) - 32768);

// 		a_x += a_dx * clipped_y;
// 		b_x += b_dx * clipped_y;
// 		base = color + top * 240;
// 		if (a_dx < b_dx) { // 01엣지가 왼쪽, 02엣지가 오른쪽, 01이 평평하면 02가 항상 왼쪽엣지임
// 			l_u += a_du * clipped_y; // 잘린 y만큼 내려가기
// 			l_v += a_dv * clipped_y;

// 			i32 height = std::min(i32(va1 >> 16) - 32768, 160) - top;
// 			while (height-- > 0) {
// 				i32 left = std::max(a_x >> 16, 0);
// 				i32 width = std::min(b_x >> 16, 240) - left;
				
// 				if (width > 0) {
// 					u8 *ptr = base + left;
// 					i32 clipped_x = (left - (a_x >> 16));
// 					i32 u = l_u + dudx * clipped_x;
// 					i32 v = l_v + dvdx * clipped_x;

// 					if (intptr_t(ptr) & 1) {
// 						ptr--;
// 						u32 uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 						*(u16 *)ptr = *ptr | (texture[uv] << 8);
// 						ptr += 2;
// 						u += dudx;
// 						v += dvdx;
// 						width--;
// 					}
// 					if (width & 1) {
// 						u32 tmp_u = u + (width - 1) * dudx;
// 						u32 tmp_v = v + (width - 1) * dvdx;
// 						u32 uv = ((tmp_u & 0x003F0000) >> 16) | ((tmp_v & 0x003F0000) >> 10);

// 						*(u16*)(ptr + width - 1) = (ptr[width] << 8) | texture[uv];
// 					}
// 					width >>= 1;
// 					while (width--) {
// 						u32 uv;
// 						u8 color_id;
// 						u16 color;
						
// 						uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 						color_id = texture[uv];
// 						color = color_id;
// 						u += dudx;
// 						v += dvdx;
						
// 						uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 						color_id = texture[uv];
// 						color |= color_id << 8;
// 						u += dudx;
// 						v += dvdx;
						
// 						*(u16 *)ptr = color;
// 						ptr += 2;
// 					}
// 				}
// 				base += 240;
// 				a_x += a_dx;
// 				b_x += b_dx;
// 				l_u += a_du;
// 				l_v += a_dv;
// 			}
// 			{
// 				a_h = ((va2 >> 16) - 32768) - ((va1 >> 16) - 32768);
// 				u32 inv_a_dy = (1 << 16) / std::max(a_h, 1);
// 				i32 dx12 = ((i32(va2 & 0x0000FFFF) - 32768) << 16) - ((i32(va1 & 0x0000FFFF) - 32768) << 16);
// 				i32 du12 = i32(t2 >> 16) - i32(t1 >> 16);
// 				i32 dv12 = (i32(t2 << 16) >> 16) - (i32(t1 << 16) >> 16);
// 				a_x = (i32(va1 & 0x0000FFFF) - 32768) << 16;
// 				a_dx = ((i32(va2 & 0x0000FFFF) - 32768) - (i32(va1 & 0x0000FFFF) - 32768)) * inv_a_dy;
// 				a_du = (du12 * inv_a_dy);
// 				a_dv = (dv12 * inv_a_dy);
// 			}
// 			height = std::min(i32(va2 >> 16) - 32768, 160) - std::max(i32(va1 >> 16) - 32768, 0);
// 			while (height-- > 0) {
// 				i32 left = std::max(a_x >> 16, 0);
// 				i32 width = std::min(b_x >> 16, 240) - left;
				
// 				if (width > 0) {
// 					u8 *ptr = base + left;
// 					i32 clipped_x = (left - (a_x >> 16));
// 					i32 u = l_u + dudx * clipped_x;
// 					i32 v = l_v + dvdx * clipped_x;

// 					if (intptr_t(ptr) & 1) {
// 						ptr--;
// 						u32 uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 						*(u16 *)ptr = *ptr | (texture[uv] << 8);
// 						ptr += 2;
// 						u += dudx;
// 						v += dvdx;
// 						width--;
// 					}
// 					if (width & 1) {
// 						u32 tmp_u = u + (width - 1) * dudx;
// 						u32 tmp_v = v + (width - 1) * dvdx;
// 						u32 uv = ((tmp_u & 0x003F0000) >> 16) | ((tmp_v & 0x003F0000) >> 10);

// 						*(u16*)(ptr + width - 1) = (ptr[width] << 8) | texture[uv];
// 					}
// 					width >>= 1;
// 					while (width--) {
// 						u32 uv;
// 						u8 color_id;
// 						u16 color;
						
// 						uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 						color_id = texture[uv];
// 						color = color_id;
// 						u += dudx;
// 						v += dvdx;
						
// 						uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 						color_id = texture[uv];
// 						color |= color_id << 8;
// 						u += dudx;
// 						v += dvdx;
						
// 						*(u16 *)ptr = color;
// 						ptr += 2;
// 					}
// 				}
// 				base += 240;
// 				a_x += a_dx;
// 				b_x += b_dx;
// 				l_u += a_du;
// 				l_v += a_dv;
// 			}
// 		} else { // 윗면이 평평하거나, 01이 오른쪽임











// 			l_u += b_du * clipped_y; // 잘린 y만큼 내려가기
// 			l_v += b_dv * clipped_y;

// 			i32 height = std::min(i32(va1 >> 16) - 32768, 160) - top;
// 			while (height-- > 0) {
// 				i32 left = std::max(b_x >> 16, 0);
// 				i32 width = std::min(a_x >> 16, 240) - left;
				
// 				if (width > 0) {
// 					u8 *ptr = base + left;
// 					i32 clipped_x = (left - (b_x >> 16));
// 					i32 u = l_u + dudx * clipped_x;
// 					i32 v = l_v + dvdx * clipped_x;

// 					if (intptr_t(ptr) & 1) {
// 						ptr--;
// 						u32 uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 						*(u16 *)ptr = *ptr | (texture[uv] << 8);
// 						ptr += 2;
// 						u += dudx;
// 						v += dvdx;
// 						width--;
// 					}
// 					if (width & 1) {
// 						u32 tmp_u = u + (width - 1) * dudx;
// 						u32 tmp_v = v + (width - 1) * dvdx;
// 						u32 uv = ((tmp_u & 0x003F0000) >> 16) | ((tmp_v & 0x003F0000) >> 10);

// 						*(u16*)(ptr + width - 1) = (ptr[width] << 8) | texture[uv];
// 					}
// 					width >>= 1;
// 					while (width--) {
// 						u32 uv;
// 						u8 color_id;
// 						u16 color;
						
// 						uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 						color_id = texture[uv];
// 						color = color_id;
// 						u += dudx;
// 						v += dvdx;
						
// 						uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 						color_id = texture[uv];
// 						color |= color_id << 8;
// 						u += dudx;
// 						v += dvdx;
						
// 						*(u16 *)ptr = color;
// 						ptr += 2;
// 					}
// 				}
// 				base += 240;
// 				a_x += a_dx;
// 				b_x += b_dx;
// 				l_u += b_du;
// 				l_v += b_dv;
// 			}
// 			{
// 				a_h = (i32(va2 >> 16) - 32768) - (i32(va1 >> 16) - 32768);
// 				u32 inv_a_dy = (1 << 16) / std::max(a_h, 1);
// 				a_dx = ((i32(va2 & 0x0000FFFF) - 32768) - (i32(va1 & 0x0000FFFF) - 32768)) * inv_a_dy;
// 				a_x = ((i32(va1 & 0x0000FFFF) - 32768) << 16);
// 				// b_du = (du12 * inv_a_dy);
// 				// b_dv = (dv12 * inv_a_dy);
// 			}
// 			height = 0;
// 			height = std::min(i32(va2 >> 16) - 32768, 160) - std::max(i32(va1 >> 16) - 32768, 0);
// 			while (height-- > 0) {
// 				i32 left = std::max(b_x >> 16, 0);
// 				i32 width = std::min(a_x >> 16, 240) - left;
				
// 				if (width > 0) {
// 					u8 *ptr = base + left;
// 					i32 clipped_x = (left - (b_x >> 16));
// 					i32 u = l_u + dudx * clipped_x;
// 					i32 v = l_v + dvdx * clipped_x;

// 					if (intptr_t(ptr) & 1) {
// 						ptr--;
// 						u32 uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 						*(u16 *)ptr = *ptr | (texture[uv] << 8);
// 						ptr += 2;
// 						u += dudx;
// 						v += dvdx;
// 						width--;
// 					}
// 					if (width & 1) {
// 						u32 tmp_u = u + (width - 1) * dudx;
// 						u32 tmp_v = v + (width - 1) * dvdx;
// 						u32 uv = ((tmp_u & 0x003F0000) >> 16) | ((tmp_v & 0x003F0000) >> 10);

// 						*(u16*)(ptr + width - 1) = (ptr[width] << 8) | texture[uv];
// 					}
// 					width >>= 1;
// 					while (width-- > 0) {
// 						u32 uv;
// 						u8 color_id;
// 						u16 color;
						
// 						uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 						color_id = texture[uv];
// 						color = color_id;
// 						u += dudx;
// 						v += dvdx;
						
// 						uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 						color_id = texture[uv];
// 						color |= color_id << 8;
// 						u += dudx;
// 						v += dvdx;
						
// 						*(u16 *)ptr = color;
// 						ptr += 2;
// 					}
// 				}
// 				base += 240;
// 				a_x += a_dx;
// 				b_x += b_dx;
// 				l_u += b_du;
// 				l_v += b_dv;
// 			}










// 		}
// 	}
// }