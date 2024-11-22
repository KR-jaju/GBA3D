#include "scene/SceneA.h"
#include "gbavfx/gbavfx.h"
#include "gbadef.h"

SceneA::SceneA()
{
	i16	*palette = (i16 *)MEM_PAL;

	for (i32 i = 0; i < 256; ++i) {
		palette[i] = SceneA::palette[i];
	}
}

void	SceneA::update()
{
	InputState	input;

	pollInput(&input);

	this->mario.update(&input);
	this->lakitu.update();
	gbavfx_clear();
	this->mario.render(&this->lakitu);
	gbavfx_flip_interlaced();
}
