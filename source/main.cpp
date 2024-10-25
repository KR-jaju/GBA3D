
//#include "Mesh.hpp"
//#include "Rasterizer.hpp"
#include "control.hpp"
// #include <gba_systemcalls.h>
#include "clock.hpp"
#include "debug.hpp"

#include "gbavfx/gbavfx.h"


#include <stdio.h>
#define REG_VCOUNT *(volatile u16*)0x04000006
//TODO: 언젠가 지운다

char	debug_log[2048];
char	*log_ptr = debug_log;
INLINE void m4_plot(int x, int y, u8 clrid)
{
	COLOR *dst= &vid_page[(y*M4_WIDTH+x)>>1];
	if(x&1)
		*dst= (*dst& 0xFF) | (clrid<<8);
	else
		*dst= (*dst&~0xFF) |  clrid;
}

int	main() {
	clock_init();
	//initDeltaTimer();
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2; // 화면 모드 설정
	init_palettes();
	
	control cnt;
	while(true) {
		if(key_held(KEY_A)) cnt.clickJump = true;
		cnt.playerControll();
		cnt.checkCollision();
		gbavfx::clear();

		vid_page = (i16*)((u32)vid_page ^ 0xA000);
		REG_DISPCNT ^= DCNT_PAGE;
	}
}
