
// #include "gbavfx/gbavfx.h"
// #include <algorithm>
// #include "division.h"
// #include <cstdio>



// IWRAM_CODE
// void	gbavfx_rasterize(u32 a, u32 b) {
// 	u32 t0 = gbavfx_vbo.vertex[(a & 0xFFFF) * 2 + 1];
// 	u32 t1 = gbavfx_vbo.vertex[(a >> 16) * 2 + 1];
// 	u32 t2 = gbavfx_vbo.vertex[(b & 0xFFFF) * 2 + 1];

// 	u32 va0 = gbavfx_vbo.vertex[(a & 0xFFFF) * 2];
// 	u32 va1 = gbavfx_vbo.vertex[(a >> 16) * 2];
// 	u32 va2 = gbavfx_vbo.vertex[(b & 0xFFFF) * 2];

// 	i32 a_h, b_h;
// 	i32 a_x, b_x, l_u, l_v;
// 	i32 a_dx, b_dx, a_du, a_dv, b_du, b_dv;
// 	//a, b중 왼쪽에 있는 것만 uv를 사용함
	
// 	i32 dudx;
// 	i32 dvdx;
// 	u8* base;
// 	u32 texture_id = (b & 0x001F0000) >> 16;
// 	u8* texture = gbavfx_texture_slot[texture_id];

// 	i32	x0, y0, x1, y1, x2, y2;
// 	i32	u0, v0, u1, v1, u2, v2;

// 	{
// 		x0 = (i32(va0 << 16 >> 16)) - 32768;
// 		x1 = (i32(va1 << 16 >> 16)) - 32768;
// 		x2 = (i32(va2 << 16 >> 16)) - 32768;

// 		y0 = i32(va0 >> 16) - 32768;
// 		y1 = i32(va1 >> 16) - 32768;
// 		y2 = i32(va2 >> 16) - 32768;

// 		u0 = i32(t0 & 0xFFFF0000) >> 16;
// 		u1 = i32(t1 & 0xFFFF0000) >> 16;
// 		u2 = i32(t2 & 0xFFFF0000) >> 16;

// 		v0 = i32(t0 & 0xFFFF);
// 		v1 = i32(t1 & 0xFFFF);
// 		v2 = i32(t2 & 0xFFFF);

// 		a_x = x0 << 16; //0.x << 16 (fixed)
// 		a_h = y1 - y0; // 1.y - 0.y
// 		b_x = a_x;
// 		b_h = y2 - y0; // 2.y - 0.y
// 		l_u = u0 << 16;
// 		l_v = v0 << 16;
// 		// l_u = (t0 & 0xFFFF0000); // 0.u (r7)
// 		// l_v = (t0 & 0x0000FFFF) << 16; //0.v (r1)

// 		i32 dx01 = x1 - x0;
// 		i32 dy01 = y1 - y0;
// 		i32 du01 = u1 - u0;
// 		i32 dv01 = v1 - v0;

// 		i32 dx02 = x2 - x0;
// 		i32 dy02 = y2 - y0;
// 		i32 du02 = u2 - u0;
// 		i32 dv02 = v2 - v0;
// 		{
// 			i32 det = dx01 * dy02 - dx02 * dy01;
// 			if (det == 0)
// 				return;
// 			i32 inv_det = 0;
// 			inv_det = reciprocal(det);

// 			// 행렬식이 음수면
// 			// dx01 * dy02 < dx02 * dy01
// 			//d01 < d02
// 			//01이 02보다 왼쪽이다

// 			dudx = i32((i64(i32(du01 * dy02 - du02 * dy01)) * inv_det) >> 15);
// 			dvdx = i32((i64(i32(dv01 * dy02 - dv02 * dy01)) * inv_det) >> 15);
// 			// u32 inv_a_dy = reciprocal(std::max(dy01, 1)) >> 15;
// 			// u32 inv_b_dy = reciprocal(std::max(dy02, 1)) >> 15;
// 			u32 inv_a_dy = reciprocal(dy01) >> 15;
// 			u32 inv_b_dy = reciprocal(dy02) >> 15;
// 			a_dx = dx01 * inv_a_dy;
// 			b_dx = dx02 * inv_b_dy;
// 			a_du = (du01 * inv_a_dy);
// 			b_du = (du02 * inv_b_dy);
// 			a_dv = (dv01 * inv_a_dy);
// 			b_dv = (dv02 * inv_b_dy);
// 		}
// 	}

// 	i32 top = std::max(y0, 0);
// 	i32 clipped_y = top - (y0); //0.y

// 	a_x += a_dx * clipped_y;
// 	b_x += b_dx * clipped_y;
// 	base = gbavfx_color + top * 240;
// 	if (a_dx < b_dx) { // 01엣지가 왼쪽, 02엣지가 오른쪽, 01이 평평하면 02가 항상 왼쪽엣지임
// 		// l_u += a_du * clipped_y; // 잘린 y만큼 내려가기
// 		// l_v += a_dv * clipped_y;

// 		// i32 height = std::min(y1, 160) - top; //1.y
// 		// while (height) { // (left, width, u, v)
// 		// 	i32 left = std::max(a_x >> 16, 0); //r0
// 		// 	i32 width = std::min(b_x >> 16, 240) - left; //r1
			
// 		// 	if (width > 0) {
// 		// 		u8 *ptr = base + left; //r5
// 		// 		i32 clipped_x = (left - (a_x >> 16));
// 		// 		i32 u = l_u + dudx * clipped_x; // r2
// 		// 		i32 v = l_v + dvdx * clipped_x; // r3

// 		// 		if (intptr_t(ptr) & 1) {
// 		// 			ptr--;
// 		// 			u32 uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 		// 			*(u16 *)ptr = *ptr | (texture[uv] << 8);
// 		// 			// *(u16 *)ptr = *ptr | (texture[2072] << 8);
// 		// 			// *(u16 *)ptr = *ptr | (1 << 8);
// 		// 			ptr += 2;
// 		// 			u += dudx;
// 		// 			v += dvdx;
// 		// 			width--;
// 		// 		}
// 		// 		if (width & 1) {
// 		// 			u32 tmp_u = u + (width - 1) * dudx;
// 		// 			u32 tmp_v = v + (width - 1) * dvdx;
// 		// 			u32 uv = ((tmp_u & 0x003F0000) >> 16) | ((tmp_v & 0x003F0000) >> 10);

// 		// 			*(u16*)(ptr + width - 1) = (ptr[width] << 8) | texture[uv];
// 		// 			// *(u16*)(ptr + width - 1) = (ptr[width] << 8) | 1;
// 		// 			width -= 1;
// 		// 		}
// 		// 		// width >>= 1;
// 		// 		while (width) { // uv, ptr, u, v, dudx,dvdx, texture, color_id, color
// 		// 			u32 uv;
// 		// 			u8 color_id;
// 		// 			u16 color;
					
// 		// 			uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 		// 			color_id = texture[uv];
// 		// 			color = color_id;
// 		// 			u += dudx;
// 		// 			v += dvdx;
					
// 		// 			uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 		// 			color_id = texture[uv];
// 		// 			color |= color_id << 8;
// 		// 			u += dudx;
// 		// 			v += dvdx;
// 		// 			*(u16 *)ptr = color;
// 		// 			ptr += 2;
// 		// 			width -= 2;
// 		// 		}
// 		// 	}
// 		// 	base += 240;
// 		// 	a_x += a_dx;
// 		// 	b_x += b_dx;
// 		// 	l_u += a_du;
// 		// 	l_v += a_dv;
// 		// 	height -= 1;
// 		// }
// 		// {
// 		// 	a_h = (va2 >> 16) - (va1 >> 16);
// 		// 	// u32 inv_a_dy = (1 << 16) / std::max(a_h, 1);
// 		// 	// u32 inv_a_dy = reciprocal(a_h) >> 16;
// 		// 	// u32 inv_a_dy = reciprocal(std::max(a_h, 1)) >> 15;
// 		// 	u32 inv_a_dy = reciprocal(a_h) >> 15;
// 		// 	i32 du12 = i32(t2 >> 16) - i32(t1 >> 16);
// 		// 	i32 dv12 = (i32(t2 << 16) >> 16) - (i32(t1 << 16) >> 16);
// 		// 	a_x = (i32(va1 & 0x0000FFFF) - 32768) << 16;
// 		// 	a_dx = ((i32(va2 & 0x0000FFFF)) - (i32(va1 & 0x0000FFFF))) * inv_a_dy;
// 		// 	a_du = (du12 * inv_a_dy);
// 		// 	a_dv = (dv12 * inv_a_dy);
// 		// }
// 		// height = std::min(y2, 160) - std::max(y1, 0);
// 		// while (height-- > 0) {
// 		// 	i32 left = std::max(a_x >> 16, 0);
// 		// 	i32 width = std::min(b_x >> 16, 240) - left;
			
// 		// 	if (width > 0) {
// 		// 		u8 *ptr = base + left;
// 		// 		i32 clipped_x = (left - (a_x >> 16));
// 		// 		i32 u = l_u + dudx * clipped_x;
// 		// 		i32 v = l_v + dvdx * clipped_x;

// 		// 		if (intptr_t(ptr) & 1) {
// 		// 			ptr--;
// 		// 			u32 uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 		// 			*(u16 *)ptr = *ptr | (texture[uv] << 8);
// 		// 			ptr += 2;
// 		// 			u += dudx;
// 		// 			v += dvdx;
// 		// 			width--;
// 		// 		}
// 		// 		if (width & 1) {
// 		// 			u32 tmp_u = u + (width - 1) * dudx;
// 		// 			u32 tmp_v = v + (width - 1) * dvdx;
// 		// 			u32 uv = ((tmp_u & 0x003F0000) >> 16) | ((tmp_v & 0x003F0000) >> 10);

// 		// 			*(u16*)(ptr + width - 1) = (ptr[width] << 8) | texture[uv];
// 		// 		}
// 		// 		width >>= 1;
// 		// 		while (width--) {
// 		// 			u32 uv;
// 		// 			u8 color_id;
// 		// 			u16 color;
					
// 		// 			uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 		// 			color_id = texture[uv];
// 		// 			color = color_id;
// 		// 			u += dudx;
// 		// 			v += dvdx;
					
// 		// 			uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 		// 			color_id = texture[uv];
// 		// 			color |= color_id << 8;
// 		// 			u += dudx;
// 		// 			v += dvdx;
// 		// 			*(u16 *)ptr = color;
// 		// 			ptr += 2;
// 		// 		}
// 		// 	}
// 		// 	base += 240;
// 		// 	a_x += a_dx;
// 		// 	b_x += b_dx;
// 		// 	l_u += a_du;
// 		// 	l_v += a_dv;
// 		// }
// 	} else { // 윗면이 평평하거나, 01이 오른쪽임











// 		l_u += b_du * clipped_y; // 잘린 y만큼 내려가기
// 		l_v += b_dv * clipped_y;

// 		i32 height = std::min(y1, 160) - top;
// 		while (height) {
// 			i32 left = std::max(b_x >> 16, 0);
// 			i32 width = std::min(a_x >> 16, 240) - left;
			
// 			if (width > 0) {
// 				u8 *ptr = base + left;
// 				i32 clipped_x = (left - (b_x >> 16));
// 				i32 u = l_u + dudx * clipped_x;
// 				i32 v = l_v + dvdx * clipped_x;

// 				if (intptr_t(ptr) & 1) {
// 					ptr--;
// 					u32 uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 					*(u16 *)ptr = *ptr | (texture[uv] << 8);
// 					ptr += 2;
// 					u += dudx;
// 					v += dvdx;
// 					width--;
// 				}
// 				if (width & 1) {
// 					u32 tmp_u = u + (width - 1) * dudx;
// 					u32 tmp_v = v + (width - 1) * dvdx;
// 					u32 uv = ((tmp_u & 0x003F0000) >> 16) | ((tmp_v & 0x003F0000) >> 10);

// 					*(u16*)(ptr + width - 1) = (ptr[width] << 8) | texture[uv];
// 					width -= 1;
// 				}
// 				while (width) {
// 					u32 uv;
// 					u8 color_id;
// 					u16 color;
					
// 					uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 					color_id = texture[uv];
// 					color = color_id;
// 					u += dudx;
// 					v += dvdx;
					
// 					uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 					color_id = texture[uv];
// 					color |= color_id << 8;
// 					u += dudx;
// 					v += dvdx;
					
// 					*(u16 *)ptr = color;
// 					ptr += 2;
// 					width -= 2;
// 				}
// 			}
// 			base += 240;
// 			a_x += a_dx;
// 			b_x += b_dx;
// 			l_u += b_du;
// 			l_v += b_dv;
// 			height -= 1;
// 		}
// 		{
// 			a_h = (y2) - (y1);
// 			// u32 inv_a_dy = (1 << 16) / std::max(a_h, 1);
// 			u32 inv_a_dy = reciprocal(a_h) >> 15;
// 			// u32 inv_b_dy = reciprocal(b_h) >> 16;
// 			a_dx = ((i32(va2 & 0x0000FFFF) - 32768) - (i32(va1 & 0x0000FFFF) - 32768)) * inv_a_dy;
// 			a_x = ((i32(va1 & 0x0000FFFF) - 32768) << 16);
// 			// b_du = (du12 * inv_a_dy);
// 			// b_dv = (dv12 * inv_a_dy);
// 		}
// 		height = std::min(y2, 160) - std::max(y1, 0);
// 		while (height) {
// 			i32 left = std::max(b_x >> 16, 0);
// 			i32 width = std::min(a_x >> 16, 240) - left;
			
// 			if (width > 0) {
// 				u8 *ptr = base + left;
// 				i32 clipped_x = (left - (b_x >> 16));
// 				i32 u = l_u + dudx * clipped_x;
// 				i32 v = l_v + dvdx * clipped_x;

// 				if (intptr_t(ptr) & 1) {
// 					ptr--;
// 					u32 uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 					*(u16 *)ptr = *ptr | (texture[uv] << 8);
// 					ptr += 2;
// 					u += dudx;
// 					v += dvdx;
// 					width--;
// 				}
// 			// }
// 				if (width & 1) {
// 					u32 tmp_u = u + (width - 1) * dudx;
// 					u32 tmp_v = v + (width - 1) * dvdx;
// 					u32 uv = ((tmp_u & 0x003F0000) >> 16) | ((tmp_v & 0x003F0000) >> 10);

// 					*(u16*)(ptr + width - 1) = (ptr[width] << 8) | texture[uv];
// 					width -= 1;
// 				}
// 			// }
// 			// width >>= 1;
// 			// width = 30;

// 				while (width > 0) {
// 					u32 uv;
// 					u8 color_id;
// 					u16 color;
					
// 					uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 					color_id = texture[uv];
// 					color = color_id;
// 					u += dudx;
// 					v += dvdx;
					
// 					uv = ((u & 0x003F0000) >> 16) | ((v & 0x003F0000) >> 10);
// 					color_id = texture[uv];
// 					color |= color_id << 8;
// 					u += dudx;
// 					v += dvdx;
// 					// color = 0x0101;

// 					*(u16 *)ptr = color;
// 					ptr += 2;
// 					width -= 2;
// 				}
// 			}
// 			base += 240;
// 			a_x += a_dx;
// 			b_x += b_dx;
// 			l_u += b_du;
// 			l_v += b_dv;
// 			height -= 1;
// 		}










// 	}
// }