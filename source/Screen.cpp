
#include "Screen.hpp"

u32 &Screen::flag = *(u32 *)(0x04000000);
u8	*Screen::current = (u8 *)Screen::back;
