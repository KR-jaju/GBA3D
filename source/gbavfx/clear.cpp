#include "gbavfx/gbavfx.h"

namespace gbavfx {
	void	clear() {
		vertex_count = 0;
		face_buffer_size = 0;
		for (i32 i = 0; i < MAX_DEPTH_VARIATION; ++i) {
			ordering_table[i] = -1;
		}
	}
}