#include "common.h"
#include "gbavfx/gbavfx.h"

// namespace gbavfx {
// 	u8		*color = nullptr; // 240 * 160 * 1 byte
// 	u32		vertex_buffer[MAX_VERTEX_COUNT * 2]; // max 65536
// 	u8		vertex_depth_buffer[MAX_VERTEX_COUNT]; // only stores z
// 	u32		vertex_count = 0;
// 	u32		face_buffer[MAX_FACE_COUNT * 2]; // max 2048
// 	u32		face_buffer_size = 0;
// 	i16		ordering_table[MAX_DEPTH_VARIATION]; // 1024 depth variation

// 	u8		texture_slot[32][64 * 64] EWRAM;
// 	fixed	*matrix_slot[32];
// }

u8		*gbavfx_color = nullptr; // 240 * 160 * 1 byte
vbo		gbavfx_vbo;
u32		gbavfx_vbo_size = 0;
u32		gbavfx_fbo[MAX_FACE_COUNT * 2]; // max 2048
u32		gbavfx_fbo_size = 0;
i16		ordering_table[MAX_DEPTH_VARIATION]; // 1024 depth variation

u8		gbavfx_texture_slot[32][64 * 64] EWRAM;
fixed	*gbavfx_matrix_slot[32];
char		gbavfx_debug[2048] EWRAM;

