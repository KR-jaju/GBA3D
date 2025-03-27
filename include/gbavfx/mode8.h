#pragma once

#include "common.h"
#include "TestVertex.h"

namespace mode8
{
	typedef struct s_texture_slot	t_texture_slot;
	typedef struct s_ptb			t_ptb;
	typedef struct s_context 		t_context;
	typedef struct s_vertex			t_vertex;
	typedef struct s_matrix			t_matrix;

	struct s_texture_slot
	{
		u8 const	*textures[32]; // 0x0000 ~ 0x0080 (128 bytes)
	};

	struct s_matrix
	{
		u32	data[12];
		// t_matrix	operator*(t_matrix const& other) const;
	};

	struct s_context
	{
		u16				ordering_table[768];			// 0x0000 ~ 0x05FF (1536 bytes)
		t_matrix		matrix_slot[30];				// 0x0600 ~ 0x0B9F (1440 bytes)
		t_matrix		view_matrix;					// 0x0BA0 ~ 0x0BC9 (48 bytes)
		i32				padding[7];						// 0x0BD0 ~ 0x0BEB (28 bytes)
		u8 const*		background;						// 0x0BEC ~ 0x0BEF (4 bytes)
		u32				background_offset;				// 0x0BF0 ~ 0x0BF3 (4 bytes)
		u32				vblank_coutner;					// 0x0BF4 ~ 0x0BF7 (4 bytes)
		u32*			ptb_top;						// 0x0BF8 ~ 0x0BFB (4 bytes)
		u32*			fb_top;							// 0x0BFC ~ 0x0BFF (4 bytes)
		u32				post_transform_buffer[2048];	// 0x0C00 ~ 0x2BFF (8192 bytes)
		u32				face_buffer[2048];				// 0x2C00 ~ 0x4BFF (8192 bytes)
	}; // sizeof(t_context) = 19464 bytes

	struct s_vertex
	{
		u32 x;
		u32 y;
		u32 z;
		u32 uv;
	}; // sizeof(vertex) = 16 bytes

	extern t_context	context;
	/**
	 * @brief ewram texture storage which mode8 fetches texture data from
	 * @var u8 textures[32][4096];
	 */
	extern u8			textures[32][4096] EWRAM;

	/**
	 * @brief initialize mode8 library
	 * @return none
	 */
	void	init();
	/**
	 * @brief set camera position and rotation
	 * @param x Q15.16
	 * @param y Q15.16
	 * @param z Q15.16
	 * @param yaw Q15.16
	 * @param pitch Q15.16 (-0.5 ~ 0.5)
	 * @return none
	 */
	void	setCamera(i32 x, i32 y, i32 z, i32 yaw, i32 pitch); // 카메라 정보 설정
	/**
	 * @brief clear current render target
	 * @return none
	 */
	void	clear(); // 현재 render_target을 초기화

	// vertices는 정점 배열로, 정점의 위치와 uv를 가진다.
	// vertex_count는 각 본의 정점 개수를 담는 배열로, 이 순서대로 변환 행렬이 결정된다. 0이 나올 때까지 읽는다.
	// indices는 삼각형을 정의하는 세 점을 담는 배열로, 모든 면들이 나온 후 마지막에 추가로 -1이 3개 붙어야한다.
	void	drawIndexed(t_vertex const* vertices, i32 const* vertex_count, i32 const* indices, u32 texture_id);
	void	flush();
	void	flip();
}

/*

mode8::init();

while(true)
{
	mode8::clear();
	memcpy(context.texture_slot[0], texture, sizeof(t_texture));
	memcpy(context.matrix_slot[0], transform, 48);
	mode8::drawIndexed(vertices, vertex_count, indices, texture_id);
	mode8::flush();
}

*/
