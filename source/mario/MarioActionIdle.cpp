// #include "mario/Mario.h"
// #include "resource/animation.h"
// #include "InputState.h"

// bool	Mario::actionIdleLeft(InputState *input)
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

// 	if (this->animation_time >= (29 << 16))
// 	{
// 		this->action = &Mario::actionIdleRight;
// 		this->animation = mario_idle_right;
// 		this->animation_time = 0;
// 		this->animation_dt = (1 << 16);
// 		return (true);
// 	}
// 	return (false);
// }
// bool	Mario::actionIdleRight(InputState *input)
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
		
// 	if (this->animation_time >= (29 << 16))
// 	{
// 		this->action = &Mario::actionIdleCenter;
// 		this->animation = mario_idle_center;
// 		this->animation_time = 0;
// 		this->animation_dt = (1 << 16);
// 		return (true);
// 	}
// 	return (false);
// }
// bool	Mario::actionIdleCenter(InputState *input)
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
// 	if (this->animation_time >= (29 << 16))
// 	{
// 		this->action = &Mario::actionIdleLeft;
// 		this->animation = mario_idle_left;
// 		this->animation_time = 0;
// 		this->animation_dt = (1 << 16);
// 		return (true);
// 	}
// 	return (false);
// }
