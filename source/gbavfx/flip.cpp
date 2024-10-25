#include "gbavfx/gbavfx.h"

namespace gbavfx {
	void	flip() {
		i32 i = MAX_DEPTH_VARIATION;
		while (--i) {
			i32	face_idx = ordering_table[i];

			while (face_idx != -1) {
				u32 const	a = face_buffer[face_idx * 2];
				i32 const	b = face_buffer[face_idx * 2 + 1];

				face_idx = (b >> 21); // upper 11bit
				rasterize(a, b);
			}
		}
		// video page flip
	}
}
