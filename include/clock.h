#pragma once

#include "common.h"

# define REG_TM0D *(volatile unsigned short *)0x04000100
# define REG_TM0CNT *(volatile unsigned short *)0x04000102
# define REG_TM0CNT_L *(volatile u16*)0x4000100
# define REG_TM1D *(volatile unsigned short *)0x04000104
# define REG_TM1CNT *(volatile unsigned short *)0x04000106
# define REG_TM2D *(volatile unsigned short *)0x04000108
# define REG_TM2CNT *(volatile unsigned short *)0x0400010A
# define REG_TM3D *(volatile unsigned short *)0x0400010C
# define REG_TM3CNT *(volatile unsigned short *)0x0400010E

#define TIMER_ON   0x0080
#define TIMER_FREQ_1024 0x0003

static inline void	clock_init() {
	REG_TM1D = -16; // 16 * 59.59ns = 1us
	REG_TM1CNT = 0x0 | 0x80; // 1cycle | enable
	REG_TM2D = -1000;
	REG_TM2CNT = 0x80 | 0x4; // enable | cascade
	REG_TM3CNT = 0x80 | 0x4; // enable | cascade
}
static inline int		clock_get() {
	short const	milli = REG_TM2D;
	short const	sec = REG_TM3D;
	// return (*(volatile unsigned short *)(0x0400010C));
	return (sec * 1000 + milli);
}

// static f32 deltaTime = f32(0.0166f);
static int prevTime = 0;

// 타이머 설정 상수
const int TIMER_FREQ = 16384; // 타이머 주파수 (Hz)
const int TIMER_MAX = 0x10000; // 타이머 최대 값 (65536)

// 타이머 값 읽기 함수
static int getTimerValue()
{
    // 타이머 레지스터의 하위 16비트 값을 읽어옵니다.
    return REG_TM0CNT_L & 0xFFFF;
}

// 타이머 초기화 함수
static void initDeltaTimer()
{
    REG_TM0CNT = 0;
    REG_TM0CNT = TIMER_FREQ_1024 | TIMER_ON;
}
