#pragma once

struct fixed32
{
	constexpr static int FIX_SHIFT = 16;
	int num;
	
	fixed32() = default;
	constexpr	fixed32(int d): num(d << FIX_SHIFT) {}
	constexpr	fixed32(float f): num(f * (1 << FIX_SHIFT)) {}

	constexpr explicit operator	float() const {
		return float(num) / (1 << FIX_SHIFT);
	}
	constexpr explicit operator int() const {
		return (num >> FIX_SHIFT);
	}
	
	constexpr fixed32	operator-() const {
		return fixed32::from(-this->num);
	}

	constexpr fixed32	operator+(fixed32 other) const {
		return fixed32::from(num + other.num);
	}
	constexpr fixed32	operator-(fixed32 other) const {
		return fixed32::from(num - other.num);
	}
	constexpr fixed32   operator*(fixed32 other) const {
		return fixed32::from(int(((long long)(num) * (long long)(other.num)) >> FIX_SHIFT));
	}
	constexpr fixed32	operator>>(int shift) const {
		return fixed32::from(this->num >> shift);
	}
	constexpr fixed32	operator<<(int shift) const {
		return fixed32::from(this->num << shift);
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

	constexpr bool	operator<(fixed32 other) const {
		return (this->num < other.num);
	}
	constexpr bool	operator>(fixed32 other) const {
		return (this->num > other.num);
	}
	constexpr bool	operator<=(fixed32 other) const {
		return (this->num <= other.num);
	}
	constexpr bool	operator>=(fixed32 other) const {
		return (this->num >= other.num);
	}
	constexpr bool	operator==(fixed32 other) const {
		return (this->num == other.num);
	}
	constexpr bool	operator!=(fixed32 other) const {
		return (this->num != other.num);
	}

	constexpr fixed32	&operator+=(fixed32 other) {
		*this = *this + other;
		return (*this);
	}
	constexpr fixed32	&operator-=(fixed32 other) {
		*this = *this - other;
		return (*this);
	}
	constexpr fixed32	&operator*=(fixed32 other) {
		*this = *this * other;
		return (*this);
	}
	constexpr fixed32	&operator>>=(int shift) {
		*this = *this >> shift;
		return (*this);
	}
	constexpr fixed32	&operator<<=(int shift) {
		*this = *this << shift;
		return (*this);
	}

	static constexpr fixed32	from(int other) {
		fixed32   ret;

		ret.num = other;
		return (ret);
	}
};