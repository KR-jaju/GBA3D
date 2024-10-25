#pragma once

# include "common.h"
# include "fixed.h"
/*
vertex with brightness {
position, (2 + 2 + 2 byte)
uv, (2 + 2 byte)
brightness (1 byte)
additional (1 byte)
} // total 12 byte

vertex {
position(2 + 2 + 2 byte)
uv (2 + 2 byte)
brightness (1 byte)
} // total 11 bytes

Vertex after transformation
{
	position (2 + 2 + 1 bytes)
	flag(1 byte)
	uv, (2 + 2 byte)
}
position(2, 2, 1)
flag(1)
uv(1, 1)

31 :(y | x): 0
63 :(u | v): 32
63 :(flag | u | v | z): 32
0x0F000000
0x00FFF000

//fragment
// 31 : (x) : 0 ----  x
// 63 :(u | | v) : 32 ----- t
// u: sign 1bit, int 7bit, fract 8bit - 16bit
// v: sign 1bit, int 6bit, fract 8bit - 15bit
// total  8 byte 
31 :(y | x | idx): 0 - sort structure

Face
{
	vertices (2 + 2 + 2 bytes)
	texture_id (5 bit) - 14bit
	next(11 bit)
}
31 :(v2 | v1): 0
63 :(next | texture_id | v3): 32

// total 8 bytes
*/

namespace gbavfx {
	enum Stride {
		STRIDE_128 = 1,
		STRIDE_64 = 2,
		STRIDE_32 = 3,
		STRIDE_16 = 4
	};

	constexpr i32	MAX_VERTEX_COUNT = 1024;
	constexpr i32	MAX_FACE_COUNT = 1024;
	constexpr i32	MAX_DEPTH_VARIATION = 1024;

	extern u8		*color; // 240 * 160 * 1 byte
	extern u32		vertex_buffer[MAX_VERTEX_COUNT * 2]; // max 65536
	extern u8		vertex_depth_buffer[MAX_VERTEX_COUNT]; // only stores z
	extern u32		vertex_count;
	extern u32		face_buffer[MAX_FACE_COUNT * 2]; // max 2048
	extern u32		face_buffer_size;
	extern i16		ordering_table[MAX_DEPTH_VARIATION]; // 1024 depth variation

	extern u8		texture_slot[32][64 * 64];
	extern Stride	stride_slot[32];
	extern fixed	*matrix_slot[32];

	void	clear();

	template <typename T>
	void	drawIndexed(T const *vertices, u32 vertex_count, i32 const *indices, u32 face_count, u32 texture_id);


	template <typename T>
	void	drawSkinned(T const *vertices, i32* vertex_count, i32 const *indices, u32 face_count, u32 texture_id, i32 bone_count);

	void	flip();
	void	rasterize(u32 a, u32 b);
}