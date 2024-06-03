
# include "math.hpp"
# include "vec2.hpp"
# include "vec3.hpp"
# include "vec4.hpp"
# include "mat4.hpp"

fixed	sqrt(fixed f) {
	u64 const	a = u64(f.num) << FIX_SHIFT;
	u64		l = 0;
	u64		r = u64(f.num) + (1 << FIX_SHIFT);
	// fixed   l = 0;
	// fixed   r = f + 1;
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
//  if (m * m <= ((long long)(f.num) << 16))
//             l = fixed::from((int)m);
//         else
//             r = fixed::from((int)m);

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
	fixed c = fixed::from((1 << FIX_SHIFT) - x * x / 3448);
	fixed s = sqrt(fixed(1) - c * c);

	if (shift & 0x4000)
		swap(c, s);
	if (angle < 0)
		s = -s;
	if (shift & 0x8000)
		c = -c;
	return {c, s};
}

fixed	dot(vec2 const &a, vec2 const &b) {
	return (a.x * b.x + a.y * b.y);
}

fixed	dot(vec3 const &a, vec3 const &b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

fixed	dot(vec4 const &a, vec4 const &b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

vec3	cross(vec3 const &a, vec3 const &b) {
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
	};
}

fixed	length(vec2 const &a) {
	return (sqrt(dot(a, a)));
}

fixed	length(vec3 const &a) {
	return (sqrt(dot(a, a)));
}

fixed	length(vec4 const &a) {
	return (sqrt(dot(a, a)));
}

vec2	normalize(vec2 const &a) {
	return (a / length(a));
}

vec3	normalize(vec3 const &a) {
	return (a / length(a));
}

vec4	normalize(vec4 const &a) {
	return (a / length(a));
}
