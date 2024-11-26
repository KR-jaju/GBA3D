#include "mario/Mario.h"
#include "resource/animation.h"
#include "InputState.h"

bool	Mario::actionRunning(InputState *input)
{
	i32 raw_horizontal = input->h_raw;
	i32 raw_vertical = -input->v_raw;

	if (raw_horizontal == 0 && raw_vertical == 0)
	{
		this->action = &Mario::actionStopping;
		this->animation = mario_stopping;
		this->animation_time = 0;
		this->animation_dt = (1 << 16);
		return (false);
	}



	if (this->animation_time >= (71 << 16))
	{
		this->animation_time -= (71 << 16);
	}
	return (false);
}
