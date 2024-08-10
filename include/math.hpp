
#ifndef MATH_HPP
# define MATH_HPP

# include <cmath>
# include "fixed.hpp"
# include "util.hpp"

// #define PI_FLT 3.14159265f
# define TAU 0xFFFF
# define PI 0x8000 // round(TAU / 2)
# define ONE_DEGREE  0xB6
# define FIXED_12_SCALE (1 << 12)

static INLINE fixed	sqrt(fixed f) {
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

static INLINE fixed	abs(fixed f) {
	if (f > 0)
		return (f);
	return (-f);
}

static INLINE void	sincos(int angle, fixed &sine, fixed &cosine) {
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
	cosine = c;
	sine = s;
}

static INLINE fixed limit(fixed current, fixed stop)
{
	return current > stop ? stop : current;
}



#endif