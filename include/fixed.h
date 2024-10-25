
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
	// constexpr fixed	operator*(fixed other) const {
	// 	return fixed::from(int((i64(num) * other.num) >> FIX_SHIFT));
	// }

	// 16.16 고정소수점 곱셈 함수 - 인라인 어셈블리 사용
	// constexpr fixed operator*(fixed other) const {
    // i64 result = static_cast<i64>(num) * other.num;
    // return fixed::from(static_cast<i32>(result >> FIX_SHIFT));
	// }

	
// 16.16 고정소수점 곱셈 함수 - 인라인 어셈블리 사용
	// fixed operator*(fixed other) const {
	// 	i32 result;
	// 	i32 a = num;
	// 	i32 b = other.num;
	// 	__asm__ volatile (
	// 		"smull %0, %1, %2, %3\n"  // a와 b를 곱하여 64비트 결과 생성 (rLo, rHi)
	// 		"mov %0, %0, lsr #16\n"   // 하위 32비트(rLo)를 16비트 시프트하여 고정소수점 정규화
	// 		"orr %0, %0, %1, asl #16\n" // 상위 32비트(rHi)를 사용해 결과의 나머지 부분을 처리
	// 		: "=&r" (result), "=&r" (b)
	// 		: "r" (a), "r" (b)
	// 		: "cc"
	// 	);
	// 	return fixed::from(result);
	// }
	constexpr fixed   operator*(fixed other) const {
	return fixed::from(int((i64(num) * i64(other.num)) >> FIX_SHIFT));
	}
	constexpr fixed	operator/(fixed other) const {
		return fixed::from(int(((1 << FIX_SHIFT) * i64(num)) / other.num));
	}

	// // 역수를 근사하기 위한 뉴턴-랩슨 방식
	// static constexpr fixed reciprocal(fixed d) {
	// 	fixed x = fixed::from(1 << FIX_SHIFT);  // 초기 근사값을 1로 설정 (16.16 고정소수점)
	// 	for (int i = 0; i < 3; ++i) {  // 반복 수렴 (3번 반복으로도 충분히 근사 가능)
	// 		x = x * (fixed::from(2 << FIX_SHIFT) - d * x);
	// 	}
	// 	return x;  // 근사된 1/d
	// }

	// // 나눗셈 구현
	// constexpr fixed operator/(fixed other) const {
	// 	return *this * reciprocal(other);  // n/d = n * (1/d)
	// }
	// 16.16 고정소수점 나눗셈 함수 - 인라인 어셈블리 사용
	// constexpr fixed operator/(fixed other) const {
	// 	// 나눗셈을 대신하여 역수를 미리 곱하는 방식으로 최적화
	// 	i64 dividend = static_cast<i64>(num) << 16; // 16비트를 왼쪽으로 쉬프트하여 정밀도를 높임
	// 	i32 result = static_cast<i32>(dividend / other.num);
	// 	return fixed::from(result);
	// }
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
