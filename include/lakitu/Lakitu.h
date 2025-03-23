#pragma once

#include "common.h"
#include "gbamath/gbamath.h"
#include "gbamath/mat4.h"
#include "InputState.h"

class Lakitu
{
public:
	Lakitu();
	void	update(InputState *input);
	mat4 const &getViewMatrix() const;
private:
	typedef bool (Lakitu::*LakituAction)(InputState *);
	LakituAction action;
	// f32	position[3];
	short	yaw;
	short	pitch;
	mat4	view_matrix;
	u8 const	*background;

	bool	actionRHold(InputState *input);
	bool	actionRHoldOld(InputState *input);
	bool	actionRAHold(InputState *input);
	bool	actionRBHold(InputState *input);
	bool	actionRABHold(InputState *input);
	bool	actionCameraReset(InputState *input);
	bool	actionIdle(InputState *input);

	void	updateViewMatrix();
};