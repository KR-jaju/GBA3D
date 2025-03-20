#pragma once

#include "common.h"
#include "TestVertex.h"

namespace mode8
{
	typedef struct s_texture_slot	t_texture_slot;
	typedef struct s_ptb			t_ptb;
	typedef struct s_context 		t_context;
	typedef struct s_vertex			t_vertex;

	struct s_texture_slot
	{
		u8 const	*textures[32]; // 0x0000 ~ 0x0080 (128 bytes)
	};

	struct s_context
	{
		u16				ordering_table[768];			// 0x0000 ~ 0x05FF (1536 bytes)
		i32				matrix_slot[31][12];			// 0x0600 ~ 0x0BCF (1488 bytes)
		i32				padding[9];						// 0x0BD0 ~ 0x0BF3 (36 bytes)
		t_texture_slot	*texture_slot;					// 0x0BF4 ~ 0x0BF7 (4 bytes)
		u32				*ptb_top;						// 0x0BF8 ~ 0x0BFB (4 bytes)
		u32				*fb_top;						// 0x0BFC ~ 0x0BFF (4 bytes)
		u32				post_transform_buffer[2048];	// 0x0C00 ~ 0x2BFF (8192 bytes)
		u32				face_buffer[2048];				// 0x2C00 ~ 0x4BFF (8192 bytes)
	}; // sizeof(t_context) = 19464 bytes

	struct s_vertex
	{
		i32 x;
		i32 y;
		i32 z;
		u32 uv;
	}; // sizeof(vertex) = 16 bytes

	extern t_context	context;
	extern u32			vblank_counter;

	void	init();
	void	clear(u8 const* background, u32 offset_x, u32 offset_y); // 현재 render_target을 초기화
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
