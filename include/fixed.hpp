
#ifndef FIXED_HPP
# define FIXED_HPP

# include "type.hpp"

#define FIX_SHIFT   16

struct fixed
{
	i32 num;
	
	fixed() = default;
	constexpr	fixed(int d): num(d << FIX_SHIFT) {}
	constexpr	fixed(float f): num(f * (1 << FIX_SHIFT)) {}

	constexpr explicit operator	float() const {
		return float(num) / (1 << FIX_SHIFT);
	}
	constexpr explicit operator    int() const {
		return (num >> FIX_SHIFT);
	}
	
	constexpr fixed	operator-() const {
		return fixed::from(-this->num);
	}

	constexpr fixed	operator+(fixed other) const {
		return fixed::from(num + other.num);
	}
	constexpr fixed	operator-(fixed other) const {
		return fixed::from(num - other.num);
	}
	constexpr fixed	operator*(fixed other) const {
		return fixed::from(int((i64(num) * other.num) >> FIX_SHIFT));
	}
	constexpr fixed	operator/(fixed other) const {
		return fixed::from(int(((1 << FIX_SHIFT) * i64(num)) / other.num));
	}
	constexpr fixed	operator>>(int shift) const {
		return fixed::from(this->num >> shift);
	}
	constexpr fixed	operator<<(int shift) const {
		return fixed::from(this->num << shift);
	}

	template <typename T>
	bool    operator<(T other) const {
		return (this->num < (int(other) << FIX_SHIFT));
	}
	template <typename T>
	bool    operator>(T other) const {
		return (this->num > (int(other) << FIX_SHIFT));
	}
	template <typename T>
	bool    operator<=(T other) const {
		return (this->num <= (int(other) << FIX_SHIFT));
	}
	template <typename T>
	bool    operator>=(T other) const {
		return (this->num >= (int(other) << FIX_SHIFT));
	}
	template <typename T>
	bool    operator==(T other) const {
		return (this->num == (int(other) << FIX_SHIFT));
	}
	template <typename T>
	bool    operator!=(T other) const {
		return (this->num != (int(other) << FIX_SHIFT));
	}

	constexpr bool	operator<(fixed other) const {
		return (this->num < other.num);
	}
	constexpr bool	operator>(fixed other) const {
		return (this->num > other.num);
	}
	constexpr bool	operator<=(fixed other) const {
		return (this->num <= other.num);
	}
	constexpr bool	operator>=(fixed other) const {
		return (this->num >= other.num);
	}
	constexpr bool	operator==(fixed other) const {
		return (this->num == other.num);
	}
	constexpr bool	operator!=(fixed other) const {
		return (this->num != other.num);
	}

	constexpr fixed	&operator+=(fixed other) {
		*this = *this + other;
		return (*this);
	}
	constexpr fixed	&operator-=(fixed other) {
		*this = *this - other;
		return (*this);
	}
	constexpr fixed	&operator*=(fixed other) {
		*this = *this * other;
		return (*this);
	}
	constexpr fixed	&operator/=(fixed other) {
		*this = *this / other;
		return (*this);
	}
	constexpr fixed	&operator>>=(int shift) {
		*this = *this >> shift;
		return (*this);
	}
	constexpr fixed	&operator<<=(int shift) {
		*this = *this << shift;
		return (*this);
	}

	static constexpr fixed	from(int other) {
		fixed   ret;

		ret.num = other;
		return (ret);
	}
};

#endif
