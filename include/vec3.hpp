
#ifndef VEC3_HPP
# define VEC3_HPP

# include "gbamath/gbamath.h"

struct vec3
{
	f32	x;
	f32	y;
	f32	z;
	
	vec3	operator-() const {
		return {-this->x, -this->y, -this->z};
	}

	vec3	operator+(vec3 const &other) const {
		return {this->x + other.x, this->y + other.y, this->z + other.z};
	}
	vec3	operator-(vec3 const &other) const {
		return {this->x - other.x, this->y - other.y, this->z - other.z};
	}
	vec3	operator*(vec3 const &other) const {
		return {this->x * other.x, this->y * other.y, this->z * other.z};
	}
	
	vec3	operator*(f32 other) const {
		return {this->x * other, this->y * other, this->z * other};
	}

	static vec3		zero() {
		return {f32(0), f32(0), f32(0)};
	}
	static vec3		one() {
		return {f32(1), f32(1), f32(1)};
	}
	static vec3		UP() {
		return {f32(0), f32(1), f32(0)};
	}
	static vec3		DOWN() {
		return {f32(0), f32(-1), f32(0)};
	}
	static vec3		FRONT() {
		return {f32(0), f32(0), f32(1)};
	}
	static vec3		BACK() {
		return {f32(0), f32(0), f32(-1)};
	}
	static vec3		LEFT() {
		return {f32(-1), f32(0), f32(0)};
	}
	static vec3		RIGHT() {
		return {f32(1), f32(0), f32(0)};
	}
};

static inline f32	dot(vec3 const &a, vec3 const &b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
static inline vec3	cross(vec3 const &a, vec3 const &b) {
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
	};
}
static inline f32	length(vec3 const &a) {
	return (sqrt_fx(dot(a, a)));
}
static inline vec3	normalize(vec3 const &a) {
	f32	hypot = length(a);
	f32 inv_hypot = f32::from(reciprocal(hypot.num) << 1);
	return (a * inv_hypot);
}

#endif