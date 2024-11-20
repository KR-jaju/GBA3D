#pragma once

#include "mario/Mario.h"
#include "lakitu/Lakitu.h"

enum SceneId
{
	SCENE_A
};

class SceneA
{
public:
	void	update();
private:
	Mario	mario;

	Lakitu	lakitu;
};