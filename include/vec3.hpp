
#ifndef VEC3_HPP
# define VEC3_HPP

#include "fixed.hpp"

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

	static vec3		one() {
		return {1, 1, 1};
	}
};


#endif