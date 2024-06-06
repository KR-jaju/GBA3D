
#include "Mesh.hpp"
#include "Rasterizer.hpp"
#include "GBAlib.hpp"
#include "Camera.hpp"
#include "Screen.hpp"
#define REG_VCOUNT *(volatile u16*)0x04000006
COLOR *vid_page= vid_mem_back;

int	main() {
	// *(u16 *)(0x04000000) = 0b0000010000000011;
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2;
	Mesh<4, 2>		mesh = {
		{{0.0f, 0.8f, 6.0f, 0, 0},
		{-0.8f, 0.0f, 6.0f, 0xFFFF, 0},
		{0.0f, -0.8f, 6.0f, 0, 0xFFFF},
		{0.8f, 0.0f, 6.0f, 0xFFFF, 0xFFFF}},
		{0, 1, 2, 0, 2, 3}
	};
	Camera	camera;

	init_palettes();
	while(true) {
		while(REG_VCOUNT >= 160);   // wait till VDraw
		while(REG_VCOUNT < 160);    // wait till VBlank
		camera.update();
		camera.push(mesh);
		camera.render(Screen::current);
		// camera.render((u8 *)(vid_page));
		Screen::flip();
		// vid_flip();	
	}
}
