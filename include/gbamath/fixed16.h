#pragma once
#include "common.h"

typedef struct fixed16 f16;

struct fixed16
{
	constexpr static i32 FIX_SHIFT = 8;
	i16 num;
	
	fixed16() = default;
	constexpr	fixed16(i32 d): num(d << FIX_SHIFT) {}
	constexpr	fixed16(float f): num(f * (1 << FIX_SHIFT)) {}

	constexpr explicit operator	float() const {
		return float(num) / (1 << FIX_SHIFT);
	}
	constexpr explicit operator i32() const {
		return (num >> FIX_SHIFT);
	}
	
	constexpr fixed16	operator-() const {
		return fixed16::from(-this->num);
	}

	constexpr fixed16	operator+(fixed16 other) const {
		return fixed16::from(num + other.num);
	}
	constexpr fixed16	operator-(fixed16 other) const {
		return fixed16::from(num - other.num);
	}
	constexpr fixed16   operator*(fixed16 other) const {
		return fixed16::from(i16((i32(num) * i32(other.num)) >> FIX_SHIFT));
	}
	constexpr fixed16	operator>>(i32 shift) const {
		return fixed16::from(this->num >> shift);
	}
	constexpr fixed16	operator<<(i32 shift) const {
		return fixed16::from(this->num << shift);
	}

	constexpr bool	operator<(fixed16 other) const {
		return (this->num < other.num);
	}
	constexpr bool	operator>(fixed16 other) const {
		return (this->num > other.num);
	}
	constexpr bool	operator<=(fixed16 other) const {
		return (this->num <= other.num);
	}
	constexpr bool	operator>=(fixed16 other) const {
		return (this->num >= other.num);
	}
	constexpr bool	operator==(fixed16 other) const {
		return (this->num == other.num);
	}
	constexpr bool	operator!=(fixed16 other) const {
		return (this->num != other.num);
	}

	constexpr fixed16	&operator+=(fixed16 other) {
		*this = *this + other;
		return (*this);
	}
	constexpr fixed16	&operator-=(fixed16 other) {
		*this = *this - other;
		return (*this);
	}
	constexpr fixed16	&operator*=(fixed16 other) {
		*this = *this * other;
		return (*this);
	}
	constexpr fixed16	&operator>>=(i32 shift) {
		*this = *this >> shift;
		return (*this);
	}
	constexpr fixed16	&operator<<=(i32 shift) {
		*this = *this << shift;
		return (*this);
	}

	static constexpr fixed16	from(i32 other) {
		fixed16   ret;

		ret.num = other;
		return (ret);
	}
};