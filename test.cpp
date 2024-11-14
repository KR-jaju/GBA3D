#include <iostream>

void	sort(int *arr, int i, int j, int k)
{
	int a = arr[i];
	int b = arr[j];
	int c = arr[k];

	if (a > b) { // a(1), b(0), c(2) -> [b, a, c]
		if (a > c) { // a(2), b(0), c(1) -> [b, c, a]

		}
	} else {
		if (b > c) { // a(0), b(2), c(1) -> [a, c, b]

		}
	}
}

int	main(void) {
	int a = 2;
	std::cout << clz(a) << " and " << __builtin_clz(a);
}