
#include "gba/mode8/mode8.h"
#include "game/resource/model.h"
#include "game/resource/texture.h"
#include "game/resource/animation.h"
#include "game/scene/Scene.h"
#include "game/scene/SceneA.h"
#include "gba/gbadef.h"
#include <stdio.h>
#include "gba/mode8/mode8.h"
#include "gba/gba.h"

void optimize_ewram() {
    REG_WAITCNT = (REG_WAITCNT & ~0x0030) | 0x000E;  // EWRAM wait state를 0x0E로 설정
}

#define DCNT_MODE4			0x0004	//!< Mode 4; bg2: 240x160\@8 bitmap
#define DCNT_BG2			0x0400	//!< Enable bg 2

char debug_buffer[200];

int	main() {
	// optimize_ewram(); // mgba에서는 더 느려짐!
	REG_DISPCNT = DCNT_MODE4 | DCNT_BG2; // 화면 모드 설정
	gba::init();

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


