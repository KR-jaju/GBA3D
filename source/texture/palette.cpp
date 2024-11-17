#include "resource/texture.h"

u16 const palette[256] = {
	0x61C0, 
	0x3A9E, 
	0x6667, 
	0x7800, 
	0x779A, 
	0x0026, 
	0x001E, 
	0x7AEB, 
	0x6622, 
	0x7B54, 
	0x65C3, 
	0x5A21, 
	0x6602, 
	0x03DE, 
	0x046D, 
	0x0000, 
	0x7287, 
	0x72F0, 
	0x65A2, 
	0x7ACA, 
	0x6242, 
	0x5E44, 
	0x6222, 
	0x7756, 
	0x61E0, 
	0x72A8, 
	0x6685, 
	0x7BDE, 
	0x4E49, 
	0x72CE, 
	0x02BC, 
	0x7779, 
	0x5DE1, 
	0x7313, 
	0x6A24, 
	0x6264, 
	0x61A1, 
	0x5A02, 
	0x76C9, 
	0x6D83, 
	0x7B0F, 
	0x3060, 
	0x6181, 
	0x5601, 
	0x72AB, 
	0x6A43, 
	0x66AB, 
	0x5E22, 
	0x0006, 
	0x5DA0, 
	0x6201, 
	0x65E1, 
	0x0009, 
	0x0010, 
	0x5DC1, 
	0x7777, 
	0x6E68, 
	0x2D7E, 
	0x770F, 
	0x6EF0, 
	0x76A9, 
	0x76ED, 
	0x5E01, 
	0x76CA, 
	0x4CE1, 
	0x7314, 
	0x7333, 
	0x6267, 
	0x6665, 
	0x6E45, 
	0x72CC, 
	0x72F1, 
	0x7711, 
	0x7732, 
	0x7778, 
	0x6EAC, 
	0x6643, 
	0x6E88, 
	0x7758, 
	0x4A6C, 
	0x6ECE, 
	0x5D80, 
	0x5ADE, 
	0x34C3, 
	0x7312, 
	0x5E66, 
	0x0279, 
	0x7B9A, 
	0x779B, 
	0x6687, 
	0x14A6, 
	0x4E06, 
	0x7629, 
	0x6E65, 
	0x1420, 
	0x7335, 
	0x6ED0, 
	0x7BBB, 
	0x7336, 
	0x7754, 
	0x6A04, 
	0x7BBC, 
	0x0004, 
	0x7A6D, 
	0x668B, 
	0x72EF, 
	0x7734, 
	0x000B, 
	0x0005, 
	0x76EC, 
	0x463E, 
	0x7AEC, 
	0x5E8A, 
	0x7B31, 
	0x035E, 
	0x7315, 
	0x7334, 
	0x7311, 
	0x7733, 
	0x6E8B, 
	0x000E, 
	0x0015, 
	0x6A69, 
	0x0007, 
	0x6627, 
	0x7B0E, 
	0x7757, 
	0x72ED, 
	0x5D22, 
	0x7799, 
	0x59CB, 
	0x7356, 
	0x5669, 
	0x6A8A, 
	0x7358, 
	0x5A24, 
	0x76EF, 
	0x7755, 
	0x72F2, 
	0x6581, 
	0x0008, 
	0x6243, 
	0x5E42, 
	0x76CB, 
	0x6ACE, 
	0x20FE, 
	0x7B55, 
	0x71A4, 
	0x6A85, 
	0x6224, 
	0x72CD, 
	0x5E46, 
	0x777A, 
	0x6EAE, 
	0x59E1, 
	0x6204, 
	0x3CC2, 
	0x2020, 
	0x0217, 
	0x72A9, 
	0x76AA, 
	0x61E2, 
	0x72CF, 
	0x6AA8, 
	0x6ECF, 
	0x5E49, 
	0x7710, 
	0x5E6B, 
	0x7AED, 
	0x76CC, 
	0x6288, 
	0x7B77, 
	0x7731, 
	0x5A22, 
	0x6265, 
	0x027B, 
	0x7B9B, 
	0x7735, 
	0x69C3, 
	0x6688, 
	0x76EB, 
	0x037E, 
	0x6EAD, 
	0x7ACB, 
	0x7B53, 
	0x7BDE, 
	0x7712, 
	0x6605, 
	0x6EF2, 
	0x6601, 
	0x7B99, 
	0x6244, 
	0x7B30, 
	0x6E66, 
	0x6AC9, 
	0x5E03, 
	0x7B32, 
	0x7267, 
	0x5606, 
	0x7357, 
	0x6266, 
	0x72CB, 
	0x6646, 
	0x72EE, 
	0x7337, 
	0x4A4A, 
	0x4D45, 
	0x7B15, 
	0x0400, 
	0x4628, 
	0x7BBA, 
	0x5207, 
	0x6EF4, 
	0x6246, 
	0x72CE, 
	0x7B56, 
	0x65C1, 
	0x628A, 
	0x72AA, 
	0x6A45, 
	0x77BD, 
	0x6625, 
	0x000F, 
	0x6A67, 
	0x65E3, 
	0x7776, 
	0x5E68, 
	0x7288, 
	0x6E44, 
	0x737E, 
	0x3DDE, 
	0x5EAB, 
	0x779C, 
	0x76B0, 
	0x7B98, 
	0x6269, 
	0x6EF1, 
	0x0003, 
	0x4A27, 
	0x6EAB, 
	0x7B75, 
	0x76EE, 
	0x77BA, 
	0x5606, 
	0x7B76, 
	0x5ECE, 
	0x61EA, 
	0x7B78, 
	0x6A8B, 
	0x0C43, 
	0x6E89, 
	0x6663, 
	0x7354, 
	0x61A2, 
	0x6A22, 
	0x6ACC
};
