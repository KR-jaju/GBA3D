#include "common.h"
#include "gbamath/gbamath.h"
#include <algorithm>

IWRAM_CODE
void	sincos(int angle, f32 &sine, f32 &cosine) {
	angle = angle << 16 >> 16;
	int shift = (angle ^ (angle << 1)) & 0xC000;
	int x = (angle + shift) << 17 >> 17;
	f32 c = f32::from((1 << f32::FIX_SHIFT) - x * x / 3448); // TODO: div
	//FFFFC000
	f32 s = sqrt_fx(f32(1) - c * c);

	if (shift & 0x4000)
		std::swap(c, s);
	if (angle < 0)
		s = -s;
	if (shift & 0x8000)
		c = -c;
	cosine = c;
	sine = s;
}