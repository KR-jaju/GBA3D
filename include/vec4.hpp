
#ifndef VEC4_HPP
# define VEC4_HPP

#include "fixed.hpp"

struct vec4
{
	fixed	x;
	fixed	y;
	fixed	z;
	fixed	w;
	
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
	
	vec4	operator*(fixed other) const {
		return {this->x * other, this->y * other, this->z * other, this->w * other};
	}
	vec4	operator/(fixed other) const {
		return {this->x / other, this->y / other, this->z / other, this->w / other};
	}

	static vec4	one() {
		return {1, 1, 1, 1};
	}
};

#endif
