#pragma once

#include "common.h"
#include "gbamath/gbamath.h"

constexpr i32	MAX_VERTEX_COUNT = 1024;
constexpr i32	MAX_FACE_COUNT = 1024;
constexpr i32	MAX_DEPTH_VARIATION = 1024;

struct vbo {
	u32	vertex[MAX_VERTEX_COUNT * 2];
	u8	depth[MAX_VERTEX_COUNT];
	u32	size;
};

struct fbo {
	u32	face[MAX_FACE_COUNT * 2];
	u32	size;
};

extern u8		*gbavfx_color; // 240 * 160 * 1 byte
extern vbo		gbavfx_vbo;
extern fbo		gbavfx_fbo;
extern i16		ordering_table[MAX_DEPTH_VARIATION]; // 1024 depth variation

extern u16		gbavfx_vblank_counter;

extern u8		gbavfx_texture_slot[32][64 * 64];
extern f32		gbavfx_matrix_slot[32][12];

extern u8 const	*gbavfx_background; // background texture (240 * 160 * (4 hscroll))

void	gbavfx_init();
void	gbavfx_clear();
void	gbavfx_flip();

#include "gbavfx/TestVertex.h"
extern "C"
{
	void	transformVertex_A(TestVertex const* vertices, u32 count, f32* matrix);
	void	gbavfx_drawIndexed(TestVertex const *vertices, u32 vertex_count, i32 const *indices, u32 face_count, u32 texture_id);
	void	gbavfx_drawSkinned(TestVertex const *vertices, i32 const *vertex_count, i32 const *indices, u32 face_count, u32 texture_id, i32 bone_count);

	void	gbavfx_rasterize(u32 a, u32 b);
	void	gbavfx_rasterize_interlaced_even(u32 a, u32 b);
	void	gbavfx_rasterize_interlaced_odd(u32 a, u32 b);

	void	gbavfx_interlace();
	void	gbavfx_flip_interlaced();
}

struct RenderingContext
{
	u8		*gbavfx_color; // 240 * 160 * 1 byte
	vbo		vertex_buffer; // vertex buffer
	fbo		face_buffer; // face buffer
	i16		ordering_table[MAX_DEPTH_VARIATION]; // 1024 depth variation
	u8		texture_slot[32]; // 32 * 64 * 64 * 1 = 128KB
	f32		matrix_slot[32][12]; //max 32 matrices (3 * 4)

	void	drawIndexed(TestVertex const* vertices, i32 const* vertex_count, i32 const* indices, u32 texture_id);
};

extern "C"
{
	void	gbavfx_execute(RenderingContext const* context);
}
