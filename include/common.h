#pragma once

#include "common/fixed16.h"
#include "common/fixed32.h"

typedef unsigned long long	u64;
typedef unsigned int	u32;
typedef unsigned short	u16;
typedef unsigned char	u8;
typedef signed long long	i64;
typedef signed int		i32;
typedef signed short	i16;
typedef signed char		i8;

typedef struct fixed32	f32;
typedef struct fixed16	f16;

#define EWRAM_BASE		(u8 *)0x02000000
#define IWRAM_BASE		(u8 *)0x03000000
#define IO_RAM_BASE		(u8 *)0x04000000
#define PAL_RAM_BASE	(u8 *)0x05000000
#define VRAM_BASE		(u8 *)0x06000000

#define IWRAM __attribute__((section(".iwram")))
#define IWRAM_CODE __attribute__((section(".iwram"), long_call))
#define EWRAM __attribute__((section(".ewram")))

#define VIEWPORT_WIDTH 240
#define VIEWPORT_HEIGHT 160

#define DELTA_TIME (1.0f/30.0f)

/*
mario_length = unit length * 100
mario_speed = unit speed * dt * 100 -> speed = mario_speed * 0.3
mario_acceleration = unit acceleration * dt * 100 -> speed = mario_acceleration * 0.3

s = vt + 1/2at^2

s / 100 = vt / 100 + 1/200 * at^2

*/

