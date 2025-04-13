#include "game/scene/SceneA.h"
#include "gba/mode8/mode8.h"
#include "gba/gbadef.h"
#include "gba/mode8/mode8.h"
#include "game/resource/texture.h"
#include "game/resource/model.h"
#include "clock.h"
#include "gba/io/Controller.h"

#include "gba/gbadef.h"

#include <cstdio>
#include <cstring>
#include "gba/math/fixed.h"

#include "gba/math/math.h"
#include "gba/gba.h"

char log1[100];
char log2[100];
char log3[100];
int	scroll;
extern int value;
int	value;
extern int value1;
int	value1;

SceneA::SceneA()
{
	i16	*palette = (i16 *)MEM_PAL;

	for (i32 i = 0; i < 256; ++i) {
		palette[i] = SceneA::palette[i];
	}
	scroll = 0;

	this->vertices[0].uv = 0;
	this->vertices[0].x = -256;
	this->vertices[0].y = 256;
	this->vertices[0].z = (1 << 9);

	this->vertices[1].uv = (63<<5) << 16;
	this->vertices[1].x = 256;
	this->vertices[1].y = 256;
	this->vertices[1].z = 1 << 9;

	this->vertices[2].uv = 63 << 5;
	this->vertices[2].x = -256;
	this->vertices[2].y = -256;
	this->vertices[2].z = 1 << 9;

	this->vertices[3].uv = ((63 << (5 + 16)) | 63 << 5);
	this->vertices[3].x = 256;
	this->vertices[3].y = -256;
	this->vertices[3].z = 1 << 9;

	this->vertex_count[0] = 4;
	this->vertex_count[1] = 0;

	this->indices[0] = 0;
	this->indices[1] = 2;
	this->indices[2] = 1;
	this->indices[3] = 1;
	this->indices[4] = 2;
	this->indices[5] = 3;
	this->indices[6] = -1;
	this->indices[7] = -1;
	this->indices[8] = -1;
	// this->indices[3] = -1;
	// this->indices[4] = -1;
	// this->indices[5] = -1;
	memcpy(mode8::textures[0], mario_test, 4096);
	mode8::context.background = skybg;
	mode8::context.padding[5] = 0;
	mode8::context.padding[6] = -1;


	SOUNDCNT_X = 0;          // 반드시 0 → 0x0080 순서
    SOUNDCNT_X = 0x0080;     // bit7 = 1 : 사운드 회로 전원 ON

    SOUNDCNT_L = (7<<8)|(7<<12)|(1<<1)|(1<<5);  // CH2 L/R 연결 + 볼륨 7/7
	SOUNDCNT_H = 0x01;
}

void	SceneA::update()
{
	static i32 angle = 0;

	g_controller.update();
	sprintf(log3, "KEY DOWN : %p", g_controller.button_pressed);
	// sprintf(log3, "controller: %d %d %d", g_controller.stick_x, g_controller.stick_y, g_controller.stick_angle);

	if (g_controller.button_pressed & KEY_A)
	{
		/* NR21/NR22 : duty 50%(2), length 32, init vol 15, env hold */
		REG_SND2_CNT_L = (2<<6)        // duty 50 %
						| (64-32)      // length
						| (0xF<<12);   // initial volume 15, env dir 0, step 0
	
		/* NR23/NR24 : freq + start */
		REG_SND2_CNT_H = 1911 | (1 << 14) | (1<<15);
	}

	// scroll += 1; // 프레임당 360/65536도 회전, 초당 약 0.33도 회전 * 30 -> 초당 10도 화전
	scroll += 2;
	angle += 60;
	{
		i32 sine, cosine;

		u32 value = fixed::sincos(angle);
		sine = (((i32)value) >> 16) >> 6; // 14비트 소수점을 8비트로 낮추기
		cosine = (((i32)value << 16) >> 16) >> 6;
		
		this->vertices[0].x = -cosine - sine;
		this->vertices[0].y = -sine + cosine;
		this->vertices[0].z = (1 << 9);
	
		this->vertices[1].x = cosine - sine;
		this->vertices[1].y = sine + cosine;
		this->vertices[1].z = 1 << 9;
	
		this->vertices[2].x = -cosine + sine;
		this->vertices[2].y = -sine - cosine;
		this->vertices[2].z = 1 << 9;
	
		this->vertices[3].x = cosine + sine;
		this->vertices[3].y = sine - cosine;
		this->vertices[3].z = 1 << 9;
	}
	// pollInput(&input);
	// int t0 = clock_get();
	// mode8::setCamera(-(scroll & 0xFF), (scroll & 0xFF) + 200, -200, 0, 8192);
	mode8::setCamera(0, 400, -500, 0, 0);
	this->mario.update();
	mode8::clear();
	this->mario.render();
	mode8::flush();

	// int t1 = clock_get();
	// sprintf(log1, "Frametime: %dus", t1 - t0);
	mode8::flip();
	// int t2 = clock_get();
	// sprintf(log2, "Frametime: %dus", t2 - t0);
	sprintf(log2, "context : %p, value : %d, value1 : %d", &mode8::context, value, value1);
}
