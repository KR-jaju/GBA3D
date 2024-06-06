
# include "math.hpp"
# include "vec2.hpp"
# include "vec3.hpp"
# include "vec4.hpp"
# include "mat4.hpp"

fixed	sqrt(fixed f) {
	u64 const	a = u64(f.num) << FIX_SHIFT;
	u64		l = 0;
	u64		r = u64(f.num) + (1 << FIX_SHIFT);
	u64   	m;

	while(l != r - 1) {
		m = (l + r) >> 1;
		if (m * m <= a)
			l = m;
		else
			r = m;
	}
	return (fixed::from(l));
}

fixed	abs(fixed f) {
	if (f > 0)
		return (f);
	return (-f);
}

//FIX_SHIFT가 16 -> 3448
//FIX_SHIFT가 8 ->882673
vec2	sincos(int angle) {
	angle = angle << 16 >> 16;
	int shift = (angle ^ (angle << 1)) & 0xC000;
	int x = (angle + shift) << 17 >> 17;
	fixed c = fixed::from((1 << FIX_SHIFT) - x * x / 3448); // TODO: div
	
	fixed s = sqrt(fixed(1) - c * c);

	if (shift & 0x4000)
		swap(c, s);
	if (angle < 0)
		s = -s;
	if (shift & 0x8000)
		c = -c;
	return {c, s};
}
