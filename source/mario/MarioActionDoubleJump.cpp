#include "mario/Mario.h"

MarioAction	Mario::actionDoubleJump(InputState *input)
{
	(void)input;
		return (ACTION_DOUBLE_JUMP);
}

MarioAction	Mario::transitionToDoubleJump(InputState *input)
{
	(void)input;
		return (ACTION_DOUBLE_JUMP);
}