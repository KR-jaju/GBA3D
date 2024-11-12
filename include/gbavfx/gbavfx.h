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

constexpr i32	MAX_VERTEX_COUNT = 1024;
constexpr i32	MAX_FACE_COUNT = 1024;
constexpr i32	MAX_DEPTH_VARIATION = 1024;

struct vbo {
	u32	vertex[MAX_VERTEX_COUNT * 2];
	u8	depth[MAX_VERTEX_COUNT];
	u32	size;
};

extern u8		*gbavfx_color; // 240 * 160 * 1 byte
extern vbo		gbavfx_vbo;
extern u32		gbavfx_fbo[MAX_FACE_COUNT * 2]; // max 2048
extern u32		gbavfx_fbo_size;
extern i16		ordering_table[MAX_DEPTH_VARIATION]; // 1024 depth variation

extern u8		gbavfx_texture_slot[32][64 * 64];
extern fixed	*gbavfx_matrix_slot[32];

void	gbavfx_clear();

template <typename T>
void	gbavfx_drawIndexed(T const *vertices, u32 vertex_count, i32 const *indices, u32 face_count, u32 texture_id);

template <typename T>
void	gbavfx_drawSkinned(T const *vertices, i32* vertex_count, i32 const *indices, u32 face_count, u32 texture_id, i32 bone_count);

void	gbavfx_flip();


#include "gbavfx/TestVertex.h"
extern "C"
{
	void	gbavfx_rasterize(u32 a, u32 b);
	void transformVertex_A(TestVertex const* vertices, u32 count, fixed* matrix);
}
