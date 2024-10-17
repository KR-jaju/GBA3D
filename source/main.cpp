
//#include "Mesh.hpp"
//#include "Rasterizer.hpp"
#include "control.hpp"
//#include "Camera.hpp"
#include "Screen.hpp"
// #include <gba_systemcalls.h>
#include "clock.hpp"
#include "debug.hpp"

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
	initDeltaTimer();
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2; // 화면 모드 설정
	// Mesh<5, 6>      Pyramid2_mesh = {
	// 	{{-2.999138f, 0.004364f, -2.999138f, 21845, 32768},
    //   {2.999138f, 0.004364f, -2.999138f, 32768, 0},
    //   {2.999138f, 0.004364f, 2.999138f, 43690, 32768},
    //   {-2.999138f, 0.004364f, 2.999138f, 54613, 0},
    //   {0.0f, 3.096816f, 0.0f, 65536, 32768}},
    //     {0, 4, 1, 1, 4, 2, 2, 4, 3, 3, 4, 0, 0, 1, 2, 0, 2, 3}
	// };
	
	// Camera	camera;

	// printf("hello world");

	init_palettes();
	
	control cnt;
	while(true) {
		//log_ptr = debug_log;
		// while(REG_VCOUNT >= 160);   // wait till VDraw
		// while(REG_VCOUNT < 160);    // wait till VBlank
		// log_ptr += sprintf(log_ptr, "--------------------log start ----------------- ");
		// camera.update();
		// camera.push(Pyramid2_mesh);
		// // camera.push(untitled_mesh);
		// // camera.push(sword_mesh);
		// // camera.push(box);
		// camera.render(Screen::current);
		// Screen::flip();
		if(key_held(KEY_LEFT)) cnt.clickJump = true;
		cnt.playerControll();
	
		cnt.checkCollision();
	
		Screen::flip();
	}
}
