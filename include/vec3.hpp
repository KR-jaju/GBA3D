
#ifndef VEC3_HPP
# define VEC3_HPP

# include "fixed.h"
#include "gba_math.h"
# include "math.hpp"

struct vec3
{
	fixed	x;
	fixed	y;
	fixed	z;
	
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
	vec3	operator/(vec3 const &other) const {
		return {this->x / other.x, this->y / other.y, this->z / other.z};
	}
	
	vec3	operator*(fixed other) const {
		return {this->x * other, this->y * other, this->z * other};
	}
	vec3	operator/(fixed other) const {
		return {this->x / other, this->y / other, this->z / other};
	}

	static vec3		zero() {
		return {fixed(0), fixed(0), fixed(0)};
	}
	static vec3		one() {
		return {fixed(1), fixed(1), fixed(1)};
	}
	static vec3		UP() {
		return {fixed(0), fixed(1), fixed(0)};
	}
	static vec3		DOWN() {
		return {fixed(0), fixed(-1), fixed(0)};
	}
	static vec3		FRONT() {
		return {fixed(0), fixed(0), fixed(1)};
	}
	static vec3		BACK() {
		return {fixed(0), fixed(0), fixed(-1)};
	}
	static vec3		LEFT() {
		return {fixed(-1), fixed(0), fixed(0)};
	}
	static vec3		RIGHT() {
		return {fixed(1), fixed(0), fixed(0)};
	}
};

static INLINE fixed	dot(vec3 const &a, vec3 const &b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
static INLINE vec3	cross(vec3 const &a, vec3 const &b) {
	return {
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
	};
}
static INLINE fixed	length(vec3 const &a) {
	return (sqrt_fx(dot(a, a)));
}
static INLINE vec3	normalize(vec3 const &a) {
	return (a / length(a));
}

#endif