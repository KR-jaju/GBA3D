#pragma once

struct fixed16
{
	constexpr static int FIX_SHIFT = 8;
	short num;
	
	fixed16() = default;
	constexpr	fixed16(int d): num(d << FIX_SHIFT) {}
	constexpr	fixed16(float f): num(f * (1 << FIX_SHIFT)) {}

	constexpr explicit operator	float() const {
		return float(num) / (1 << FIX_SHIFT);
	}
	constexpr explicit operator int() const {
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
		return fixed16::from(short((int(num) * int(other.num)) >> FIX_SHIFT));
	}
	constexpr fixed16	operator>>(int shift) const {
		return fixed16::from(this->num >> shift);
	}
	constexpr fixed16	operator<<(int shift) const {
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
	constexpr fixed16	&operator>>=(int shift) {
		*this = *this >> shift;
		return (*this);
	}
	constexpr fixed16	&operator<<=(int shift) {
		*this = *this << shift;
		return (*this);
	}

	static constexpr fixed16	from(int other) {
		fixed16   ret;

		ret.num = other;
		return (ret);
	}
};