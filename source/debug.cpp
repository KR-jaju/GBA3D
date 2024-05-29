
#include <tonc.h>
#include "debug.hpp"

char	debug_text[320];
int		debug_offset;

void	debug_init() {
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
	tte_init_se_default(0, BG_CBB(0) | BG_SBB(31));
}

void	debug_view() {
	tte_write(debug_text);
}