#include "common.h"
#include "gbavfx/gbavfx.h"

namespace gbavfx {
	u8		*color = nullptr; // 240 * 160 * 1 byte
	u32		vertex_buffer[MAX_VERTEX_COUNT * 2]; // max 65536
	u8		vertex_depth_buffer[MAX_VERTEX_COUNT]; // only stores z
	u32		vertex_count = 0;
	u32		face_buffer[MAX_FACE_COUNT * 2]; // max 2048
	u32		face_buffer_size = 0;
	i16		ordering_table[MAX_DEPTH_VARIATION]; // 1024 depth variation

	u8		texture_slot[32][64 * 64] EWRAM;
	Stride	stride_slot[32];
	fixed	*matrix_slot[32];
}
