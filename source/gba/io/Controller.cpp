#include "gba/io/Controller.h"
#include "gba/gbadef.h"

Controller	g_controller;

void	Controller::update()
{
	static u8 const	angle_table[] = {5, 6, 7, 4, 0, 0, 3, 2, 1};
	u32	key_state = ~REG_KEYINPUT & KEY_MASK;
	i32 raw_stick_x = ((key_state >> KEY_RIGHT_IDX) & 1) - ((key_state >> KEY_LEFT_IDX) & 1);
	i32	raw_stick_y = ((key_state >> KEY_UP_IDX) & 1) - ((key_state >> KEY_DOWN_IDX) & 1);

	this->stick_x = raw_stick_x << 14;
	this->stick_y = raw_stick_y << 14; // 64 * 8bit fraction = 6+8 shift
	this->stick_mag = ((raw_stick_x | raw_stick_y) == 0) ? 0 : (1 << 14); // (64) Q7.8
	this->stick_angle = angle_table[raw_stick_x * 3 + raw_stick_y + 4] << 13;
	this->button_pressed = (this->button_down ^ key_state) & key_state;
	this->button_down = key_state;
}