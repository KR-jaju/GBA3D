
//#include "Mesh.hpp"
//#include "Rasterizer.hpp"
#include "control.hpp"
// #include <gba_systemcalls.h>
#include "debug.hpp"

#include "mode8/mode8.h"
#include "resource/model.h"
#include "resource/texture.h"
#include "resource/animation.h"
#include "scene/Scene.h"
#include "scene/SceneA.h"
#include "gbadef.h"
#include <stdio.h>
#include "mode8/mode8.h"

void optimize_ewram() {
    REG_WAITCNT = (REG_WAITCNT & ~0x0030) | 0x000E;  // EWRAM wait state를 0x0E로 설정
}

#define DCNT_MODE4			0x0004	//!< Mode 4; bg2: 240x160\@8 bitmap
#define DCNT_BG2			0x0400	//!< Enable bg 2

char debug_buffer[200];

int	main() {
	// optimize_ewram(); // mgba에서는 더 느려짐!
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2; // 화면 모드 설정
	SceneId scene_id = SCENE_A;

	mode8::init();
	while (true)
	{
		if (scene_id == SCENE_A)
		{
			SceneA scene;

			while (true)
			{
				scene.update();
			}
		}
	}
}


