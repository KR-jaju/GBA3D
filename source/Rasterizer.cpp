
#include "Rasterizer.hpp"
#include "Edge.hpp"
#include "util.hpp"
#include <stdio.h>
#include "debug.hpp"
#include "clock.hpp"
#include "DepthTable.hpp"
#include "GBAlib.hpp"

void	Rasterizer::render(DepthTable const &table, u8 *out) {
	int start = clock_get();
	Triangle const*const	*bucket = table.getBucket();
	u16						*result = (u16 *)out;

	// for (u32 i = 0; i < 160 * 240 / 32; ++i) {
	// 	((u32*)result)[i * 8] = 0; //검은색 초기화
	// 	((u32*)result)[i * 8 + 1] = 0;
	// 	((u32*)result)[i * 8 + 2] = 0;
	// 	((u32*)result)[i * 8 + 3] = 0;
	// 	((u32*)result)[i * 8 + 4] = 0;
	// 	((u32*)result)[i * 8 + 5] = 0;
	// 	((u32*)result)[i * 8 + 6] = 0;
	// 	((u32*)result)[i * 8 + 7] = 0;
	// } //TODO: dma로 대체
	log_ptr += sprintf(log_ptr, "clear : %d\n", clock_get() - start);
	start = clock_get();
	for (u32 i = DEPTH_LAYER_SIZE - 1; i != u32(-1); i -= 1) { // 멀리 있는 삼각형부터
		for (Triangle const *t = bucket[i]; t != NULL; t = t->next) {
			Rasterizer::render(*t, (u8 *)out); // 그리기
		}
	}
	log_ptr += sprintf(log_ptr, "render : %d\n", clock_get() - start);
}

static inline
void	renderSpan(u32 x0, u32 x1, u32 y, u8 *out, Triangle const &triangle) {
	u32 const		x0_low = x0 & 0b11;
	u32 const		x1_low = x1 & 0b11;
	u32 const		x0_high = x0 >> 2;
	u32 const		x1_high = x1 >> 2;
	Vertex const	&v0 = triangle.vertex[0];
	// fixed		u = (triangle.dudx * (x0 * 8 - v0.x) + triangle.dudy * (y * 8 - v0.y)) + v0.attr.u;
	// fixed		v = (triangle.dvdx * (x0 * 8 - v0.x) + triangle.dvdy * (y * 8 - v0.y)) + v0.attr.v;
	fixed		u = 0;
	fixed		v = 0;
	u32			*ptr = (u32 *)&out[y * 240 + (x0 & ~0b11)];
	u32 		color = *ptr;
	u32			count;

	if (count = x1_high - x0_high, count != 0) {
		u32	x = x0;
		switch (x0 & 0b11) // x0의 위치
		{
		case 0: do {
					color = (color & 0xFFFFFF00) | Shader::pixelShader(&triangle, u, v);
					// u += triangle.dudx * 8;
					// v += triangle.dvdx * 8;
		case 1:	
					color = (color & 0xFFFF00FF) | (Shader::pixelShader(&triangle, u, v) << 8);
					// u += triangle.dudx * 8;
					// v += triangle.dvdx * 8;
		case 2:		
					color = (color & 0xFF00FFFF) | (Shader::pixelShader(&triangle, u, v) << 16);
					// u += triangle.dudx * 8;
					// v += triangle.dvdx * 8;
		case 3:		
					color = (color & 0x00FFFFFF) | (Shader::pixelShader(&triangle, u, v) << 24);
					// u += triangle.dudx * 8;
					// v += triangle.dvdx * 8;
					*ptr = color;
					ptr += 1;
				} while ((count -= 1) > 0);
		}
		color = *ptr;
		switch (x1_low)
		{
		case 3:
			color |= Shader::pixelShader(&triangle, u, v) << 16;
		case 2:
			color |= Shader::pixelShader(&triangle, u, v) << 8;
		case 1:
			color |= Shader::pixelShader(&triangle, u, v);
			*ptr = color;
		}
	} else {
		for (int i = x0_low; i < x1_low; ++i) {
			color |= Shader::pixelShader(&triangle, u, v) << (i * 8);
		}
		*ptr = color;
	}
}



// #define INTERLACED_RENDERING
#ifdef INTERLACED_RENDERING

IWRAM_CODE
static void	renderTrapezoid(Triangle const &triangle, Edge edge[2], i32 y_min, i32 y_max, u8 *out) {
	i32 const	mov = max(-y_min, 0);
	i32	x0;
	i32	x1;

	edge[0].x += edge[0].dxdy * mov;
	edge[1].x += edge[1].dxdy * mov;
	y_min += mov;
	y_max = min(y_max, 160); //TODO : Refactor
	if (y_max < y_min + 2)
		return ;
	switch (y_min & 0b1)
	{
		case 1: do { //그려야할 때는 그리고 스킵*2
					x0 = clamp(i32(edge[0].x), 0, 240);
					x1 = clamp(i32(edge[1].x), x0, 240);
					renderSpan(x0, x1, y_min, out, triangle);
					edge[0].move();
					edge[1].move();
					y_min += 1;
		case 0: // 그리지 말아야할 때는 스킵
					edge[0].move();
					edge[1].move();
					y_min += 1;
				} while (y_min < y_max); // 스킵한 좌표가 그려야하는 곳일 때
	}
}

#else

IWRAM_CODE
static void	renderTrapezoid(Triangle const &triangle, Edge edge[2], i32 y_min, i32 y_max, u8 *out) {
	i32 const	mov = max(-y_min, 0);

	edge[0].x += edge[0].dxdy * mov;
	edge[1].x += edge[1].dxdy * mov;
	y_min += mov;
	y_max = min(y_max, 160); //TODO : Refactor
	for (i32 y = y_min; y < y_max; ++y) {
		i32 const	x0 = clamp(i32(edge[0].x), 0, 240);
		i32 const	x1 = clamp(i32(edge[1].x), x0, 240);
		renderSpan(x0, x1, y, out, triangle);
		edge[0].move(); //다음 y로 이동
		edge[1].move();
	}
}

#endif





void	Rasterizer::render(Triangle const &triangle, u8 *out) {
	Vertex const	&a = triangle.vertex[0];
	Vertex const	&b = triangle.vertex[1];
	Vertex const	&c = triangle.vertex[2];
	u32 const		ac_orientation = triangle.ac_orientation;// y축 방향으로 가장 긴 변이 왼쪽에 있는가 오른쪽에 있는가
	i32 const		a_y = i32(a.y + fixed::from(0x7FFF));
	i32 const		b_y = i32(b.y + fixed::from(0x7FFF));
	i32 const		c_y = i32(c.y + fixed::from(0x7FFF));
	Edge			edge[2]; // [0]은 왼쪽, [1]은 오른쪽

	edge[ac_orientation].init(a, c);
	edge[!ac_orientation].init(a, b);
	renderTrapezoid(triangle, edge, a_y, b_y, out); // 삼각형을 중간점을 기준으로 갈랐을 때 윗 삼각형 그리기
	edge[!ac_orientation].init(b, c);
	renderTrapezoid(triangle, edge, b_y, c_y, out);// 아랫삼각형 그리기
}