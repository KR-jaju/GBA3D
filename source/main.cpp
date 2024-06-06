
#include "Mesh.hpp"
#include "Rasterizer.hpp"
#include "GBAlib.hpp"
#include "Camera.hpp"
#include "Screen.hpp"
#define REG_VCOUNT *(volatile u16*)0x04000006
//TODO: 언젠가 지운다

int	main() {
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2; // 화면 모드 설정
// 	Mesh<5, 6>      Pyramid2_mesh = {
// 		{{-2.999138f, 0.004364f, -2.999138f, 21845, 32768},
//       {2.999138f, 0.004364f, -2.999138f, 32768, 0},
//       {2.999138f, 0.004364f, 2.999138f, 43690, 32768},
//       {-2.999138f, 0.004364f, 2.999138f, 54613, 0},
//       {0.0f, 3.096816f, 0.0f, 65536, 32768}},
//         {0, 4, 1, 1, 4, 2, 2, 4, 3, 3, 4, 0, 0, 1, 2, 0, 2, 3}
// 	};
	
Mesh<10, 240>      untitled_mesh = { // 정점은 10개, 삼각형은 240개인 그냥 상자
        {      {1.0f, 1.0f, -1.0f, 40960, 32768},
      {1.0f, -1.0f, -1.0f, 24576, 32768},
      {1.0f, 1.0f, 1.0f, 40960, 49152},
      {1.0f, -1.0f, 1.0f, 24576, 49152},
      {-1.0f, 1.0f, -1.0f, 57344, 32768},
      {-1.0f, -1.0f, -1.0f, 40960, 16384},
      {-1.0f, 1.0f, 1.0f, 8192, 32768},
      {-1.0f, -1.0f, 1.0f, 24576, 16384},
      {1.0f, 1.0f, 1.0f, 57344, 49152},
      {-1.0f, 1.0f, -1.0f, 40960, 65536}},
        {4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7,
		}
};

Mesh<10, 12> box = { // 정상적인 그냥 상자

        {      {1.0f, 1.0f, -1.0f, 40960, 32768},
      {1.0f, -1.0f, -1.0f, 24576, 32768},
      {1.0f, 1.0f, 1.0f, 40960, 49152},
      {1.0f, -1.0f, 1.0f, 24576, 49152},
      {-1.0f, 1.0f, -1.0f, 57344, 32768},
      {-1.0f, -1.0f, -1.0f, 40960, 16384},
      {-1.0f, 1.0f, 1.0f, 8192, 32768},
      {-1.0f, -1.0f, 1.0f, 24576, 16384},
      {1.0f, 1.0f, 1.0f, 57344, 49152},
      {-1.0f, 1.0f, -1.0f, 40960, 65536}},
        {4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 4, 0, 1, 0, 2, 3, 1, 3, 7}
};
#include "SwordModell.cpp" // 부하가 엄청난 모델

	Camera	camera;

	init_palettes();
	while(true) {
		// while(REG_VCOUNT >= 160);   // wait till VDraw
		// while(REG_VCOUNT < 160);    // wait till VBlank
		camera.update();
		// camera.push(Pyramid2_mesh);
		camera.push(untitled_mesh);
		// camera.push(sword_mesh);
		// camera.push(box);
		camera.render(Screen::current);
		Screen::flip();
	}
}
