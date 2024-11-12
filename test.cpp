#include <iostream>

int	clz(unsigned int d) {
	if (d == 0)
		return (32);
	unsigned int count = 0;
	if ((d & 0xFFFF0000) == 0) {
		d <<= 16;
		count += 16;
	}
	if ((d & 0xFF000000) == 0) {
		d <<= 8;
		count += 8;
	}
	if ((d & 0xF0000000) == 0) {
		d <<= 4;
		count += 4;
	}
	if ((d & 0xC0000000) == 0) {
		d <<= 2;
		count += 2;
	}
	if ((d & 0x80000000) == 0) {
		count += 1;
	}
	return (count);
}

int	main(void) {
	int a = 2;
	std::cout << clz(a) << " and " << __builtin_clz(a);
}