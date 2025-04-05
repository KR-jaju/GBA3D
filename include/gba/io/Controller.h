// struct Controller {
// 	/*0x00*/ s16 rawStickX;       //
// 	/*0x02*/ s16 rawStickY;       //
// 	/*0x04*/ float stickX;        // [-64, 64] positive is right
// 	/*0x08*/ float stickY;        // [-64, 64] positive is up
// 	/*0x0C*/ float stickMag;      // distance from center [0, 64]
// 	/*0x10*/ u16 buttonDown;
// 	/*0x12*/ u16 buttonPressed;
// 	/*0x14*/ OSContStatus *statusData;
// 	/*0x18*/ OSContPad *controllerData;
//   #if ENABLE_RUMBLE
// 	/*0x1C*/ s32 port;
//   #endif
//   };

#pragma once

#include "common.h"

struct Controller
{
	i16	stick_x;
	i16	stick_y;
	i16 stick_mag;
	u16	stick_angle;
	u16	button_down;
	u16	button_pressed;

	void	update();
};

extern Controller g_controller;