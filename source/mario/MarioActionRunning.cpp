// #include "mario/Mario.h"
// #include "resource/animation.h"
// #include "InputState.h"
// #include "utils.h"

// void	Mario::updateWalkingSpeed(InputState* input)
// {
// 	this->intended_yaw = input->stick_angle;

// 	if (this->forward_velocity <= 0.0f) {
//         this->forward_velocity += 9.9f * DELTA_TIME;
//     } else if (this->forward_velocity <= 9.6f) {
//         this->forward_velocity += (f32(9.9f) - this->forward_velocity * 0.697f) * DELTA_TIME;
//     } else
// 	//  if (this->floor->normal.y >= 0.95f) {
// 	{
//         this->forward_velocity -= 9.0f * DELTA_TIME;
//     }

// 	if (this->forward_velocity > 14.4f)
// 		this->forward_velocity = 14.4f;

// 	this->yaw = this->intended_yaw - approach_i32((i16)(this->intended_yaw - this->yaw), 0, 0x800, 0x800);

// 	// sincos(this->yaw, this->velocity[0], this->velocity[2]);
// 	this->velocity[1] = 0.0f;
// }



// bool	Mario::actionRunning(InputState *input)
// {
// 	if (input->stick_mag == 0)
// 	{
// 		this->action = &Mario::actionStopping;
// 		this->animation = mario_stopping;
// 		this->animation_time = 0;
// 		this->animation_dt = (1 << 16);

// 		this->forward_velocity = 0;
// 		return (false);
// 	}
// 	this->animation_dt = (9 << 16);
// 	this->updateWalkingSpeed(input);
// 	this->performStep();

// 	if (this->animation_time >= (71 << 16))
// 	{
// 		this->animation_time -= (71 << 16);
// 	}
// 	return (false);
// }

// void	Mario::performStep()
// {
// 	this->transform.position[0] += this->velocity[0] * this->forward_velocity * DELTA_TIME;
// 	this->transform.position[1] += this->velocity[1] * DELTA_TIME;
// 	this->transform.position[2] += this->velocity[2] * this->forward_velocity * DELTA_TIME;
// }
