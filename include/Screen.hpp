
#ifndef SCREEN_HPP
# define SCREEN_HPP

# include "type.hpp"

namespace Screen {
	static constexpr u32	width = 240;
	static constexpr u32	height = 160;
	static constexpr u32	subpixel = 8;
	static constexpr u32	size = 0xA000;
	static constexpr u32	page_flag = 0x0010;
	static constexpr u32	front = 0x06000000;
	static constexpr u32	back = front + size;

	extern u32	&flag;
	extern u8	*current;

	static inline void	flip(void) {
		Screen::current = (u8 *)(u32(Screen::current) ^ Screen::size);
		Screen::flag ^= Screen::page_flag;
	}
}

#endif
