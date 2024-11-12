// #include "division.h"

// i32 reciprocal(i32 i) {
// 	if (i == 0)
// 		return (u32(-1)>>1);
// 	bool is_negative = i < 0;
// 	if (is_negative)
// 		i *= -1;
// 	i32 x = i;
// 	i32 lz = 0;
// 	if ((x & 0xFFFF0000) == 0) {
// 		x <<= 16;
// 		lz += 16;
// 	}
// 	if ((x & 0xFF000000) == 0) {
// 		x <<= 8;
// 		lz += 8;
// 	}
// 	if ((x & 0xF0000000) == 0) {
// 		x <<= 4;
// 		lz += 4;
// 	}
// 	if ((x & 0xC0000000) == 0) {
// 		x <<= 2;
// 		lz += 2;
// 	}
// 	if ((x & 0x80000000) == 0) {
// 		lz += 1;
// 	}
// 	i32 result = 0;
// 	if (lz <= 16) { // divisor가 큰 경우
// 		u32 key = (u32(i) >> (16 - lz)) - 32768;
// 		i32 value = division_lut[key];
		
// 		result = value >> (16 - lz);
// 	} else { // divisor가 작은 경우
// 		u32 key = (u32(i) << (lz - 16)) - 32768; // poor approximation
// 		i32 value = division_lut[key];
		
// 		result = value << (lz - 16);
// 	}
// 	if (is_negative)
// 		return -result;
// 	return result;
// }

// // i32 reciprocal(i32 i) {
// //    if (i == 0 || i == 1)
// //       return i32(u32(-1) >> 1);
// //    if (i == -1)
// //       return (u32(1 << 31));
// // 	return i32((1LL << 31) / i);
// // }
