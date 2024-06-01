
#ifndef CLOCK_HPP
# define CLOCK_HPP

static __attribute__((always_inline)) void	clock_init() {
	//REG_TM2D : 0x04000108
	//REG_TM2D : 0x0400010A
	*(volatile unsigned short *)(0x04000108) = -263;//-263
	*(volatile unsigned short *)(0x0400010A) = 0x1 | 0x80; // TM2D_CNT
	*(volatile unsigned short *)(0x0400010E) = 0x80 | 0x4;
}
static __attribute__((always_inline)) int		clock_get() {
	return (*(volatile unsigned short *)(0x0400010C));
}

#endif
