#include "common.h"
#include "gbavfx/gbavfx.h"

u8		*gbavfx_color = (u8 *)(0x06000000 + 0x0A000); // 240 * 160 * 1 byte
// u8		*gbavfx_color = (u8 *)(0x06000000); // 240 * 160 * 1 byte
vbo		gbavfx_vbo;
fbo		gbavfx_fbo;
i16		ordering_table[MAX_DEPTH_VARIATION]; // 1024 depth variation

u8 const	*gbavfx_background;
u16			gbavfx_vblank_counter = 0;
u8			gbavfx_texture_slot[32][64 * 64] EWRAM;
fixed		gbavfx_matrix_slot[32][12];

