
#ifndef MATH_HPP
# define MATH_HPP

# include <cmath>

# include "fixed.hpp"
# include "util.hpp"

struct vec2;
struct vec3;
struct vec4;

// #define PI_FLT 3.14159265f
# define TAU 0xFFFF
# define PI 0x8000 // round(TAU / 2)
# define ONE_DEGREE  0xB6
# define FIXED_12_SCALE (1 << 12)

fixed	sqrt(fixed f);

fixed	abs(fixed f);

vec2	sincos(int angle);

fixed	dot(vec2 const &a, vec2 const &b);
fixed	dot(vec3 const &a, vec3 const &b);
fixed	dot(vec4 const &a, vec4 const &b);

vec3	cross(vec3 const &a, vec3 const &b);

fixed	length(vec2 const &a);
fixed	length(vec3 const &a);
fixed	length(vec4 const &a);

vec2	normalize(vec2 const &a);
vec3	normalize(vec3 const &a);
vec4	normalize(vec4 const &a);

#endif