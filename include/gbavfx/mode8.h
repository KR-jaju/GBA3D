#pragma once

#include "common.h"
#include "TestVertex.h"

namespace mode8
{
	typedef struct s_ptb			t_ptb;
	typedef struct s_context 		t_context;
	typedef struct s_vertex			t_vertex;

	struct s_context
	{
		u16				ordering_table[768];			// 0x0000 ~ 0x05FF (1536 bytes)
		u32				matrix_slot[30][12];			// 0x0600 ~ 0x0B9F (1440 bytes)
		u32				view_matrix[12];				// 0x0BA0 ~ 0x0BC9 (48 bytes)
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
		
		constexpr s_vertex() = default;
		constexpr s_vertex(float x, float y, float z, float u, float v)
			: x(0), y(0), z(0), uv(0)
		{
			i32 ix = static_cast<i32>(x * 256 + 0.5f);
			i32 iy = static_cast<i32>(y * 256 + 0.5f);
			i32 iz = static_cast<i32>(z * 256 + 0.5f);
			i32	iu = static_cast<i32>((u * 64 + 0.5f) * 32);
			i32 iv = static_cast<i32>(((1-v) * 64 + 0.5f) * 32);
			
			this->x = ix;
			this->y = iy;
			this->z = iz;
			this->uv = ((iu << 16) | ((u16)iv));
		}
	}; // sizeof(vertex) = 16 bytes

	/**
	 * @brief rendering context, contains all the data needed for rendering
	 * @var t_context context;
	 */
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

	/**
	 * @brief request to draw indexed vertices
	 * @param vertices array of vertices
	 * @param vertex_count array of vertex count, 0 indicates end of bone
	 * @param indices array of indices, (three consecutive) -1 indicates end of face
	 * @param texture_id texture id, 0 ~ 31
	 * @return none
	 */
	void	drawIndexed(t_vertex const* vertices, i32 const* vertex_count, i32 const* indices, u32 texture_id);

	/**
	 * @brief flush all the rendering data to the framebuffer
	 * @return none
	 */
	void	flush();

	/**
	 * @brief mode4 page flip and etc
	 * @return none
	 */
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
