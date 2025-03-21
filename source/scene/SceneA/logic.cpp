#include "scene/SceneA.h"
#include "gbavfx/gbavfx.h"
#include "gbadef.h"
#include "gbavfx/mode8.h"
#include "resource/texture.h"
#include "resource/model.h"
#include "clock.h"

#include <cstdio>
#include <cstring>

char log1[100];
char log2[100];
char log3[100];
int	scroll;
extern int value;
int	value;

SceneA::SceneA()
{
	i16	*palette = (i16 *)MEM_PAL;

	for (i32 i = 0; i < 256; ++i) {
		palette[i] = SceneA::palette[i];
	}

	clock_init();
	mode8::init();
	sprintf(log3, "context (%p)", &mode8::context);
	scroll = 0;

	this->vertices[0].uv = (63<<5)<<16;
	this->vertices[0].x = -2 << 8;
	this->vertices[0].y = 0 << 7;
	this->vertices[0].z = (1 << 8);

	this->vertices[1].uv = (63<<5);
	this->vertices[1].x = 1 << 8;
	this->vertices[1].y = 1 << 8; //1 0000 0000 
	this->vertices[1].z = 1 << 8;

	this->vertices[2].uv = 0;
	this->vertices[2].x = 0;
	this->vertices[2].y = 1 << 8; //1010 1111
	this->vertices[2].z = 1 << 8;

	this->vertex_count[0] = 3;
	this->vertex_count[1] = 0;

	this->indices[0] = 0;
	this->indices[1] = 1;
	this->indices[2] = 2;
	this->indices[3] = -1;
	this->indices[4] = -1;
	this->indices[5] = -1;

	for (int r = 0; r < 3; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if (r != c)
				mode8::context.matrix_slot[0][r * 4 + c] = 0;
			else
				mode8::context.matrix_slot[0][r * 4 + c] = 32767;
		}
	}
	memcpy(mode8::textures[0], mario_test, 4096);
}

void	SceneA::update()
{
	InputState	input;

	scroll += 1;
	pollInput(&input);
	int t0 = clock_get();
	mode8::clear(skybg, (scroll) & 0xFF, 160);
	// mode8::context.matrix_slot[]
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

	// this->mario.update(&input);
	// this->lakitu.update(&input);
	// gbavfx_clear();
	// this->mario.render(&this->lakitu);
	// gbavfx_flip_interlaced();
}
