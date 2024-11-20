#pragma once

#include "common.h"
#include "gbamath/gbamath.h"

class Lakitu
{
public:
	Lakitu();
	void	update();
	f32 const	*getViewMatrix() const;
private:
	f32	pos[3];
	f32	dir[3];
	short	yaw;
	short	pitch;
	f32	view_matrix[12];
	u8 const	*background;

	void	updateViewMatrix();
};