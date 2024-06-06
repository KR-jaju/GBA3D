
#include "Rasterizer.hpp"
#include "Edge.hpp"
#include "util.hpp"
#include <stdio.h>
#include "debug.hpp"
#include "clock.hpp"
#include "DepthTable.hpp"
#include "GBAlib.hpp"

#ifdef INTERLACED_RENDERING

void	Rasterizer::render(DepthTable const &table, u8 *out) {
	int start = clock_get();
	Triangle const*const	*bucket = table.getBucket();
	u16						*result = (u16 *)out;

	for (u32 i = 0; i < 160 * 240 / 2; ++i) {
		result[i] = 0; //검은색 초기화
	} //dma로 대체

	// for (u32 i = 0; i < 160 * 240 / 2; ++i) {
	// 	i16 *src = (i16*)((unsigned int)vid_page ^ VRAM_PAGE_SIZE);
	// 	i16 *dst = vid_page;
	// 	dst[i] = src[i];
	// }

	for(u32 i = 0; i < DEPTH_LAYER_SIZE; ++i) {
		for (Triangle const *t = bucket[DEPTH_LAYER_SIZE - i]; t != NULL; t = t->next) {
			Rasterizer::render(*t, (u8 *)out);
		}
	}
	int e0 = clock_get();
	sprintf(debug_text, "(%d) ", e0 - start);
}

static INLINE void	renderTrapezoid(Triangle const &triangle, Edge edge[2], u32 y0, u32 y1, u8 *out) {	
	Vertex const	&v0 = triangle.vertex[0];

	y0 += ((y0 & 0b1) == (vid_page == vid_mem_back));
	y1 += ((y1 & 0b1) == (vid_page == vid_mem_back));
	for (u32 y = y0; y < y1; y += 2) {
		u32 const	x0 = edge[0].x();
		u32 const	x1 = edge[1].x();
		u32			width = x1 - x0;
		u32			u = (triangle.dudx * (x0 * 8 - v0.x) + triangle.dudy * (y * 8 - v0.y)) + v0.attr.u;
		u32			v = (triangle.dvdx * (x0 * 8 - v0.x) + triangle.dvdy * (y * 8 - v0.y)) + v0.attr.v;

		if (width != 0) {
			u8	*ptr = &out[y * 240 + x0];
			if ((x0 & 0b1) == 1) { // 홀수번째에서 시작
				ptr -= 1; // 한 칸 이전으로 이동(2바이트 경계 맞춤)
				*(u16 *)ptr = *ptr | (Shader::pixelShader(&triangle, u, v) << 8);
				ptr += 2; // 다음 픽셀로 이동
				width -= 1;
				u += triangle.dudx * 8;
				v += triangle.dvdx * 8;
			}
			width >>= 1; // 시작도 2바이트 경계, 가야할 거리도 2의 배수이므로 반으로 나눔
			while (width != 0)
			{
				*(u16 *)ptr = Shader::pixelShader(&triangle, u, v) | (Shader::pixelShader(&triangle, u + triangle.dudx * 8, v + triangle.dvdx * 8) << 8);
				ptr += 2; // 2픽셀 이동
				width -= 1;
				u += triangle.dudx * 2 * 8;
				v += triangle.dvdx * 2 * 8;
			}
			if ((x1 & 0b1) == 1) { // 홀수번째에서 끝남
				*(u16 *)ptr = (Shader::pixelShader(&triangle, u, v) | (ptr[1] << 8));
			}
		}
		edge[0].move();
		edge[0].move();
		edge[1].move();
		edge[1].move();
	}
}

void	Rasterizer::render(Triangle const &triangle, u8 *out) {
	Vertex const	&a = triangle.vertex[0];
	Vertex const	&b = triangle.vertex[1];
	Vertex const	&c = triangle.vertex[2];
	u32 const		ac_orientation = ((b.x - a.x) * (c.y - a.y) <= (c.x - a.x) * (b.y - a.y));
	u32 			y_start = (a.y + 3) >> 3;
	u32 			y_center = (b.y + 3) >> 3;
	u32 const		y_end = (c.y + 3) >> 3;
	Edge			edge[2];

	edge[ac_orientation].init(a, c);
	edge[!ac_orientation].init(a, b);
	renderTrapezoid(triangle, edge, y_start, y_center, out);
	edge[!ac_orientation].init(b, c);
	renderTrapezoid(triangle, edge, y_center, y_end, out);
}

#else

void	Rasterizer::render(DepthTable const &table, u8 *out) {
	int start = clock_get();
	Triangle const*const	*bucket = table.getBucket();
	u16						*result = (u16 *)out;

	for (u32 i = 0; i < 160 * 240 / 2; ++i) {
		result[i] = 0; //검은색 초기화
	} //dma로 대체
	for(u32 i = 0; i < DEPTH_LAYER_SIZE; ++i) {
		for (Triangle const *t = bucket[DEPTH_LAYER_SIZE - i]; t != NULL; t = t->next) {
			Rasterizer::render(*t, (u8 *)out);
		}
	}
	int e0 = clock_get();
	sprintf(debug_text, "(%d) ", e0 - start);
}

static INLINE void	renderTrapezoid(Triangle const &triangle, Edge edge[2], i32 y_min, i32 y_max, u8 *out) {	
	Vertex const	&v0 = triangle.vertex[0];
	y_max = min(y_max, 1919); //TODO : Refactor
	for (i32 y = y_min; y < y_max; ++y) {
		if (y < 0) {
			edge[0].move();
			edge[1].move();
			continue;
		}
		u32 const	x0 = edge[0].x();
		u32 const	x1 = edge[1].x();
		u32			width = x1 - x0; // 4 - 2 -> 2, 3
		u32			u = (triangle.dudx * (x0 * 8 - v0.x) + triangle.dudy * (y * 8 - v0.y)) + v0.attr.u;
		u32			v = (triangle.dvdx * (x0 * 8 - v0.x) + triangle.dvdy * (y * 8 - v0.y)) + v0.attr.v;

		if (width != 0) {
			u8	*ptr = &out[y * 240 + x0];
			if ((x0 & 0b1) == 1) { // 홀수번째에서 시작
				ptr -= 1; // 한 칸 이전으로 이동(2바이트 경계 맞춤)
				*(u16 *)ptr = *ptr | (3 << 8);
				// (Shader::pixelShader(&triangle, u, v) << 8);
				ptr += 2; // 다음 픽셀로 이동
				width -= 1;
				u += triangle.dudx * 8;
				v += triangle.dvdx * 8;
			}
			// if ((width & 0b1) == 1) { // 홀수번째에서 끝남
			// 	*(u16 *)(ptr + width - 1) = (Shader::pixelShader(&triangle, u + triangle.dudx * 8 * (width - 1), v + triangle.dvdx * 8 * (width - 1))) | (ptr[width] << 8);
			// }
			width >>= 1; // 시작도 2바이트 경계, 가야할 거리도 2의 배수이므로 반으로 나눔
			while (width != 0)
			{
				if ((x0 & 0b1) != 1 && ptr == &out[y * 240 + x0]) {
					*(u16 *)ptr = 3 | (Shader::pixelShader(&triangle, u + triangle.dudx * 8, v + triangle.dvdx * 8) << 8);
				} else if ((x1 & 0b1) != 1 && ptr == &out[y * 240 + (x1 - 2)]) {
					*(u16 *)ptr = (Shader::pixelShader(&triangle, u, v)) | (7 << 8);
				} else {
					*(u16 *)ptr = Shader::pixelShader(&triangle, u, v) | (Shader::pixelShader(&triangle, u + triangle.dudx * 8, v + triangle.dvdx * 8) << 8);
				}
				ptr += 2; // 2픽셀 이동
				width -= 1;
				u += triangle.dudx * 2 * 8;
				v += triangle.dvdx * 2 * 8;
			}
			if ((x1 & 0b1) == 1) { // 홀수번째에서 끝남
				// *(u16 *)ptr = (Shader::pixelShader(&triangle, u, v) | (ptr[1] << 8));
				*(u16 *)ptr = (7) | (ptr[1] << 8);
			}
		}
		edge[0].move();
		edge[1].move();
	}
}

void	Rasterizer::render(Triangle const &triangle, u8 *out) {
	Vertex const	&a = triangle.vertex[0];
	Vertex const	&b = triangle.vertex[1];
	Vertex const	&c = triangle.vertex[2];
	u32 const		ac_orientation = ((b.x - a.x) * (c.y - a.y) <= (c.x - a.x) * (b.y - a.y));
	Edge			edge[2];

	edge[ac_orientation].init(a, c);
	edge[!ac_orientation].init(a, b);
	renderTrapezoid(triangle, edge, (a.y + 3) >> 3, (b.y + 3) >> 3, out);
	edge[!ac_orientation].init(b, c);
	renderTrapezoid(triangle, edge, (b.y + 3) >> 3, (c.y + 3) >> 3, out);
}

#endif
