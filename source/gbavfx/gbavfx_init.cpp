#include "gbavfx/gbavfx.h"
#include "gbadef.h"

static void	frame_counter()
{
	gbavfx_vblank_counter += 1;
	REG_IF = 1;
}

void	gbavfx_init()
{

	REG_IME = 0;
	REG_IE = 1;
	REG_DISPSTAT |= (1 << 3);
	REG_IF = 0;
	REG_ISR_MAIN = frame_counter;
	REG_IME = 1;
}
