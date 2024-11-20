
#ifndef VEC4_HPP
# define VEC4_HPP

# include "gbamath/gbamath.h"
# include "math.hpp"

struct vec4
{
	f32	x;
	f32	y;
	f32	z;
	f32	w;
	
	vec4	operator-() const {
		return {-this->x, -this->y, -this->z, -this->w};
	}

	vec4	operator+(vec4 const &other) const {
		return {this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w};
	}
	vec4	operator-(vec4 const &other) const {
		return {this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w};
	}
	vec4	operator*(vec4 const &other) const {
		return {this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w};
	}
	vec4	operator/(vec4 const &other) const {
		return {this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w};
	}
	
	vec4	operator*(f32 other) const {
		return {this->x * other, this->y * other, this->z * other, this->w * other};
	}
	vec4	operator/(f32 other) const {
		return {this->x / other, this->y / other, this->z / other, this->w / other};
	}

	static vec4	one() {
		return {1, 1, 1, 1};
	}
};

static INLINE f32	dot(vec4 const &a, vec4 const &b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

static INLINE f32	length(vec4 const &a) {
	return (sqrt(dot(a, a)));
}

static INLINE vec4	normalize(vec4 const &a) {
	return (a / length(a));
}

#endif
