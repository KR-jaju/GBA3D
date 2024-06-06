
#ifndef VEC2_HPP
# define VEC2_HPP

# include "type.hpp"
# include "fixed.hpp"
# include "math.hpp"

struct vec2
{
	fixed	x;
	fixed	y;

	vec2	operator-() const {
		return {-this->x, -this->y};
	}

	vec2	operator+(vec2 const &other) const {
		return {this->x + other.x, this->y + other.y};
	}
	vec2	operator-(vec2 const &other) const {
		return {this->x - other.x, this->y - other.y};
	}
	vec2	operator*(vec2 const &other) const {
		return {this->x * other.x, this->y * other.y};
	}
	vec2	operator/(vec2 const &other) const {
		return {this->x / other.x, this->y / other.y};
	}
	vec2	operator*(fixed other) const {
		return {this->x * other, this->y * other};
	}
	vec2	operator/(fixed other) const {
		return {this->x / other, this->y / other};
	}
	static vec2	one() {
		return {1, 1};
	}
};

static INLINE fixed	dot(vec2 const &a, vec2 const &b) {
	return (a.x * b.x + a.y * b.y);
}
static INLINE fixed	length(vec2 const &a) {
	return (sqrt(dot(a, a)));
}
static INLINE vec2	normalize(vec2 const &a) {
	return (a / length(a));
}

#endif
