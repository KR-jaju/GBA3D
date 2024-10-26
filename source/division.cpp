#include "division.h"

i32 reciprocal(i32 d)
{
	if (d < 0) {
		d = ~d;
		u32 lz = __builtin_clz(d);
		u32 key = d << (lz + 1);
		i32 value = division_lut[key >> 17];

		return (~(value << (lz - 16)));
	} else {
		u32 lz = __builtin_clz(d);
		u32 key = d << (lz + 1);
		i32 value = division_lut[key >> 17];

		return (value << (lz - 16));
	}
}

u32 reciprocal(u32 d)
{
	u32 lz = __builtin_clz(d);
	u32 key = d << (lz + 1);
	u32 value = division_lut[key >> 17];

	if (lz == 31)
		return (4294967295);
	return (value << (lz - 16));
}

fixed reciprocal(fixed d) {
	u32 lz = __builtin_clz(d.num);
	u32 key = d.num << (lz + 1);
	u32 value = division_lut[key >> 17];

	if (lz < 16)
		value >>= (16 - lz);
	else
		value <<= (lz - 16);
	fixed x = fixed::from(value);
	x = x * (fixed(2) - d * x);
	x = x * (fixed(2) - d * x);
	x = x * (fixed(2) - d * x);
	return x;
}