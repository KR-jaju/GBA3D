
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

fixed	sqrt(fixed f);

fixed	abs(fixed f);

void	sincos(int angle, fixed &sine, fixed &cosine);

#endif