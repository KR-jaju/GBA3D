#include "gbavfx/gbavfx.h"

void	gbavfx_clear() {
	gbavfx_vbo.size = 0;
	gbavfx_fbo.size = 0;
	for (i32 i = 0; i < MAX_DEPTH_VARIATION; ++i) {
		ordering_table[i] = -1;
	}
}