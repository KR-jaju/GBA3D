
#ifndef MATH_HPP
# define MATH_HPP

# include <cmath>
# include "fixed.h"
# include "util.hpp"

// #define PI_FLT 3.14159265f
# define TAU 0xFFFF
# define PI 0x8000 // round(TAU / 2)
# define ONE_DEGREE  0xB6
# define FIXED_12_SCALE (1 << 12)

// static INLINE fixed  sqrt(fixed f) {
//    fixed l = 0;
//    fixed r = (f.num < (1 << FIX_SHIFT)) ? 1 : fixed::from(f.num + 1);
//    fixed m;

//    while (l.num != r.num - 1) {
//       m = (l + r) >> 1;
//       if (m * m <= f)
//          l = m;
//       else
//          r = m;
//    }
//    return (l);
// }

static INLINE fixed	abs(fixed f) {
	if (f > 0)
		return (f);
	return (-f);
}

static INLINE fixed limit(fixed current, fixed stop)
{
	return current > stop ? stop : current;
}

static INLINE fixed reciprocal(fixed d) {
    fixed x = fixed(1);  // 초기 근사값을 1로 설정
    x = (x * (fixed(2) - (d * x)));
	x = (x * (fixed(2) - (d * x)));
	x = (x * (fixed(2) - (d * x)));
    return x;  // 근사된 1/d
}

// 나눗셈 구현
static INLINE fixed divide(fixed n, fixed d) {
    return (n * reciprocal(d));  // n/d = n * (1/d)
}

extern "C"
{
	i32	approach_i32(i32 value, i32 increment, i32 decrement);
}

#endif