
#ifndef UTIL_HPP
# define UTIL_HPP

template <typename T>
void	swap(T &a, T &b) {
	T	tmp = a;

	a = b;
	b = tmp;
}

template <typename T>
T	min(T a, T b) {
	if (a < b)
		return (a);
	return (b);
}

template <typename T>
T	max(T a, T b) {
	if (a > b)
		return (a);
	return (b);
}

template <typename T>
T	clamp(T a, T low, T high) {
	if (a < low)
		return (low);
	if (high < a)
		return (high);
	return (a);
}

#endif
