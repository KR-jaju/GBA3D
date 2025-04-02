#pragma once

#include "mario/Mario.h"
#include "lakitu/Lakitu.h"
#include "mode8/mode8.h"

class SceneA
{
public:
	SceneA();
	void	update();
private:
	static const u16 palette[256];

	mode8::t_vertex	vertices[4];
	i32				vertex_count[4];
	i32				indices[9];
	
	Mario	mario;

	// Lakitu	lakitu;
};