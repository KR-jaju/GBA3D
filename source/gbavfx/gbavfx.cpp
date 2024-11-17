#include "common.h"
#include "gbavfx/gbavfx.h"

u8		*gbavfx_color = nullptr; // 240 * 160 * 1 byte
vbo		gbavfx_vbo;
fbo		gbavfx_fbo;
i16		ordering_table[MAX_DEPTH_VARIATION]; // 1024 depth variation

u8 const	*gbavfx_skybg;
u8			gbavfx_texture_slot[32][64 * 64] EWRAM;
fixed		*gbavfx_matrix_slot[32];

