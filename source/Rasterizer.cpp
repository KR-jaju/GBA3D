
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

	for (u32 i = 0; i < 160 * 240 / 32; ++i) {
		((u32*)result)[i * 8] = 0; //검은색 초기화
		((u32*)result)[i * 8 + 1] = 0;
		((u32*)result)[i * 8 + 2] = 0;
		((u32*)result)[i * 8 + 3] = 0;
		((u32*)result)[i * 8 + 4] = 0;
		((u32*)result)[i * 8 + 5] = 0;
		((u32*)result)[i * 8 + 6] = 0;
		((u32*)result)[i * 8 + 7] = 0;
	} //TODO: dma로 대체
	log_ptr += sprintf(log_ptr, "clear : %d\n", clock_get() - start);
	start = clock_get();
	for (u32 i = DEPTH_LAYER_SIZE - 1; i != u32(-1); i -= 1) { // 멀리 있는 삼각형부터
		for (Triangle const *t = bucket[i]; t != NULL; t = t->next) {
			Rasterizer::render(*t, (u8 *)out); // 그리기
		}
	}
	log_ptr += sprintf(log_ptr, "render : %d\n", clock_get() - start);
}

static IWRAM_CODE
void	renderSpan(u32 x0, u32 x1, u32 y, u8 *out, Triangle const &triangle) {
	Vertex const	&v0 = triangle.vertex[0];
	u32			u = (triangle.dudx * (x0 * 8 - v0.x) + triangle.dudy * (y * 8 - v0.y)) + v0.attr.u;
	u32			v = (triangle.dvdx * (x0 * 8 - v0.x) + triangle.dvdy * (y * 8 - v0.y)) + v0.attr.v;
	u32			*ptr = (u32 *)&out[y * 240 + (x0 & ~0b11)];
	u32 		color = *ptr;
	u32			count;

	if (count = (x1 >> 2) - (x0 >> 2), count != 0) {
		u32	x = x0;
		switch (x0 & 0b11) // x0의 위치
		{
		case 0: do {
					color = (color & 0xFFFFFF00) | Shader::pixelShader(&triangle, u, v);
					u += triangle.dudx * 8;
					v += triangle.dvdx * 8;
		case 1:	
					color = (color & 0xFFFF00FF) | (Shader::pixelShader(&triangle, u, v) << 8);
					u += triangle.dudx * 8;
					v += triangle.dvdx * 8;
		case 2:		
					color = (color & 0xFF00FFFF) | (Shader::pixelShader(&triangle, u, v) << 16);
					u += triangle.dudx * 8;
					v += triangle.dvdx * 8;
		case 3:		
					color = (color & 0x00FFFFFF) | (Shader::pixelShader(&triangle, u, v) << 24);
					u += triangle.dudx * 8;
					v += triangle.dvdx * 8;
					*ptr = color;
					ptr += 1;
				} while (--count > 0);
		}
		// color = *ptr;
		// switch (x1 & 0b11)
		// {
		// case 3:
		// 	color |= Shader::pixelShader(&triangle, u, v) << 16;
		// case 2:
		// 	color |= Shader::pixelShader(&triangle, u, v) << 8;
		// case 1:
		// 	color |= Shader::pixelShader(&triangle, u, v);
		// }
		// 	*ptr = color;
	} else {
		for (int i = x0 & 0b11; i < (x1 & 0b11); ++i) {
			color |= Shader::pixelShader(&triangle, u, v) << (i * 8);
		}
		*ptr = color;
	}
}

IWRAM_CODE
static void	renderTrapezoid(Triangle const &triangle, Edge edge[2], i32 y_min, i32 y_max, u8 *out) {
	y_max = min(y_max, 160); //TODO : Refactor
	while (y_min < 0) {
		edge[0].move();
		edge[1].move();
		y_min += 1;
	}
	for (i32 y = y_min; y < y_max; ++y) {
		u32 const	x0 = clamp(edge[0].x(), 0, 240);
		u32 const	x1 = clamp(edge[1].x(), 0, 240);
		renderSpan(x0, x1, y, out, triangle);
		edge[0].move(); //다음 y로 이동
		edge[1].move();
	}
}




void	Rasterizer::render(Triangle const &triangle, u8 *out) {
	Vertex const	&a = triangle.vertex[0];
	Vertex const	&b = triangle.vertex[1];
	Vertex const	&c = triangle.vertex[2];
	u32 const		ac_orientation = triangle.ac_orientation;// y축 방향으로 가장 긴 변이 왼쪽에 있는가 오른쪽에 있는가
	Edge			edge[2]; // [0]은 왼쪽, [1]은 오른쪽

	edge[ac_orientation].init(a, c);
	edge[!ac_orientation].init(a, b); // 삼각형을 중간점을 기준으로 갈랐을 때 윗 삼각형 그리기
	renderTrapezoid(triangle, edge, (a.y + 3) >> 3, (b.y + 3) >> 3, out);
	edge[!ac_orientation].init(b, c);
	renderTrapezoid(triangle, edge, (b.y + 3) >> 3, (c.y + 3) >> 3, out);// 아랫삼각형 그리기
}