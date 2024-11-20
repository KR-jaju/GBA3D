#include "scene/Scene.h"
#include "gbavfx/gbavfx.h"

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
