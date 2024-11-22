#pragma once

#include "mario/Mario.h"
#include "lakitu/Lakitu.h"

class SceneA
{
public:
	SceneA();
	void	update();
private:
	static const u16 palette[256];
	Mario	mario;

	Lakitu	lakitu;
};