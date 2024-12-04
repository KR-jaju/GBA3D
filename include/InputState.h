#pragma once

#include "common.h"
#include "gbadef.h"

#define REG_KEYINPUT		*(unsigned short*)(REG_BASE+0x0130)	//!< Key status (read only??)
#define REG_KEYCNT			*(unsigned short*)(REG_BASE+0x0132)	//!< Key IRQ control

#define KEY_A_IDX        0
#define KEY_B_IDX        1
#define KEY_SELECT_IDX   2
#define KEY_START_IDX    3
#define KEY_RIGHT_IDX    4
#define KEY_LEFT_IDX     5
#define KEY_UP_IDX       6
#define KEY_DOWN_IDX     7
#define KEY_R_IDX        8
#define KEY_L_IDX        9

#define KEY_A        (1 << KEY_A_IDX)
#define KEY_B        (1 << KEY_B_IDX)
#define KEY_SELECT   (1 << KEY_SELECT_IDX)
#define KEY_START    (1 << KEY_START_IDX)
#define KEY_RIGHT    (1 << KEY_RIGHT_IDX)
#define KEY_LEFT     (1 << KEY_LEFT_IDX)
#define KEY_UP       (1 << KEY_UP_IDX)
#define KEY_DOWN     (1 << KEY_DOWN_IDX)
#define KEY_R        (1 << KEY_R_IDX)
#define KEY_L        (1 << KEY_L_IDX)

#define KEY_MASK     0x03FF

struct InputState
{
	u16		prev = 0;
	u16		curr;
	i32		stick_x;
	i32		stick_y;
	i32		stick_angle;
	i32		stick_mag;
	i8		h_raw;
	i8		v_raw;
};

void	pollInput(InputState *state);

/*
(0, 1) -> 0
(1, 1) -> 8192
(1, 0) -> 16384
(1, -1) -> 24576
(0, -1) -> -32768
(-1, -1) -> -24576
(-1, 0) -> -16384
(-1, 1) -> -8192

*/
