// #include "mario/Mario.h"
// #include "resource/animation.h"
// #include "InputState.h"

// bool	Mario::actionStopping(InputState *input)
// {
// 	i32 raw_horizontal = input->h_raw;
// 	i32 raw_vertical = -input->v_raw;

// 	if (raw_horizontal != 0 || raw_vertical != 0)
// 	{
// 		this->action = &Mario::actionRunning;
// 		this->animation = mario_running;
// 		this->animation_time = 0;
// 		this->animation_dt = (1 << 16);
// 		return (true);
// 	}

// 	if (this->animation_time >= (18 << 16))
// 	{
// 		this->action = &Mario::actionIdleLeft;
// 		this->animation = mario_idle_left;
// 		this->animation_time = 0;
// 		this->animation_dt = (1 << 16);
// 		return (true);
// 	}
// 	return (false);
// }
