#include "scene/SceneA.h"
#include "gbavfx/gbavfx.h"
#include "gbadef.h"
#include "gbavfx/mode8.h"
#include "resource/texture.h"
#include "resource/model.h"
#include "clock.h"

#include <cstdio>
#include <cstring>
#include "gbamath/fixed.h"

#include "gbamath/gbamath.h"

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

	clock_init();
	mode8::init();

	sprintf(log3, "%d %d %d", fixed::sqrt(0), fixed::sqrt(255), fixed::sqrt(1 << 16));
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
}

void	SceneA::update()
{
	static i32 angle = 0;
	InputState	input;

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

	for (int r = 0; r < 3; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (r == c)
				mode8::context.matrix_slot[0].data[r * 4 + c] = 16384;
			else
				mode8::context.matrix_slot[0].data[r * 4 + c] = 0;
		}
	}

	pollInput(&input);
	int t0 = clock_get();
	mode8::setCamera(0, 0, 0, 0, 0);
	// mode8::setCamera(0, -(scroll & 0xFFFF), -300, 0, 0);
	mode8::clear();
	mode8::drawIndexed(this->vertices, this->vertex_count, this->indices, 0);
	// mode8::drawIndexed(::vertices, ::vertex_count, ::indices, 0);
	mode8::flush();
	// sprintf(log3, "triangle depth : %p, %p", value, &mode8::context.texture_slot);
	// sprintf(log3, "triangle depth : %d, %p", value, (int)&mode8::context.texture_slot - (int)&mode8::context);
	// mode8::clear(skybg, 50, 0);
	// mode8::context.render_target = (u8*)(reinterpret_cast<ptrdiff_t>(mode8::context.render_target) ^ 0xA000);
	// REG_DISPCNT ^= DCNT_PAGE;
	int t1 = clock_get();
	sprintf(log1, "Frametime: %dus", t1 - t0);
	mode8::flip();
	int t2 = clock_get();
	sprintf(log2, "Frametime: %dus", t2 - t0);
	sprintf(log3, "context : %p, value : %d, value1 : %d", &mode8::context, value, value1);

	// this->mario.update(&input);
	// this->lakitu.update(&input);
	// gbavfx_clear();
	// this->mario.render(&this->lakitu);
	// gbavfx_flip_interlaced();
}
