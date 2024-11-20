#pragma once
#include "common.h"

typedef struct f32 f32;

struct f32
{
	constexpr static i32 FIX_SHIFT = 16;
	i32 num;
	
	f32() = default;
	constexpr	f32(i32 d): num(d << FIX_SHIFT) {}
	constexpr	f32(float f): num(f * (1 << FIX_SHIFT)) {}

	constexpr explicit operator	float() const {
		return float(num) / (1 << FIX_SHIFT);
	}
	constexpr explicit operator i32() const {
		return (num >> FIX_SHIFT);
	}
	
	constexpr f32	operator-() const {
		return f32::from(-this->num);
	}

	constexpr f32	operator+(f32 other) const {
		return f32::from(num + other.num);
	}
	constexpr f32	operator-(f32 other) const {
		return f32::from(num - other.num);
	}
	constexpr f32   operator*(f32 other) const {
		return f32::from(i32((i64(num) * i64(other.num)) >> FIX_SHIFT));
	}
	constexpr f32	operator>>(i32 shift) const {
		return f32::from(this->num >> shift);
	}
	constexpr f32	operator<<(i32 shift) const {
		return f32::from(this->num << shift);
	}
	template <typename T>
	bool    operator<(T other) const {
		return (this->num < (i32(other) << FIX_SHIFT));
	}
	template <typename T>
	bool    operator>(T other) const {
		return (this->num > (i32(other) << FIX_SHIFT));
	}
	template <typename T>
	bool    operator<=(T other) const {
		return (this->num <= (i32(other) << FIX_SHIFT));
	}
	template <typename T>
	bool    operator>=(T other) const {
		return (this->num >= (i32(other) << FIX_SHIFT));
	}
	template <typename T>
	bool    operator==(T other) const {
		return (this->num == (i32(other) << FIX_SHIFT));
	}
	template <typename T>
	bool    operator!=(T other) const {
		return (this->num != (i32(other) << FIX_SHIFT));
	}

	constexpr bool	operator<(f32 other) const {
		return (this->num < other.num);
	}
	constexpr bool	operator>(f32 other) const {
		return (this->num > other.num);
	}
	constexpr bool	operator<=(f32 other) const {
		return (this->num <= other.num);
	}
	constexpr bool	operator>=(f32 other) const {
		return (this->num >= other.num);
	}
	constexpr bool	operator==(f32 other) const {
		return (this->num == other.num);
	}
	constexpr bool	operator!=(f32 other) const {
		return (this->num != other.num);
	}

	constexpr f32	&operator+=(f32 other) {
		*this = *this + other;
		return (*this);
	}
	constexpr f32	&operator-=(f32 other) {
		*this = *this - other;
		return (*this);
	}
	constexpr f32	&operator*=(f32 other) {
		*this = *this * other;
		return (*this);
	}
	constexpr f32	&operator>>=(i32 shift) {
		*this = *this >> shift;
		return (*this);
	}
	constexpr f32	&operator<<=(i32 shift) {
		*this = *this << shift;
		return (*this);
	}

	static constexpr f32	from(i32 other) {
		f32   ret;

		ret.num = other;
		return (ret);
	}
};