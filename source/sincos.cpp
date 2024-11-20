#include "gba_math.h"
#include <algorithm>

IWRAM_CODE
void	sincos(int angle, fixed &sine, fixed &cosine) {
	angle = angle << 16 >> 16;
	int shift = (angle ^ (angle << 1)) & 0xC000;
	int x = (angle + shift) << 17 >> 17;
	fixed c = fixed::from((1 << FIX_SHIFT) - x * x / 3448); // TODO: div
	//FFFFC000
	fixed s = sqrt_fx(fixed(1) - c * c);

	if (shift & 0x4000)
		std::swap(c, s);
	if (angle < 0)
		s = -s;
	if (shift & 0x8000)
		c = -c;
	cosine = c;
	sine = s;
}