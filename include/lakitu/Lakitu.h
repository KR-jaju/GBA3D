#pragma once

#include "common.h"

class Lakitu
{
public:
	Lakitu();
	void	update();
	fixed const	*getViewMatrix() const;
private:
	fixed	pos[3];
	fixed	dir[3];
	short	yaw;
	short	pitch;
	fixed	view_matrix[12];
	u8 const	*background;

	void	updateViewMatrix();
};