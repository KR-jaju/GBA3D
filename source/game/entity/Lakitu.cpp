// #include "lakitu/Lakitu.h"
// #include "mode8/mode8.h"
// #include "resource/texture.h"
// #include "math/mat4.h"

// Lakitu::Lakitu()
// 	: position(0, 1, -4), //TODO : non standard
// 	yaw(0),
// 	pitch(0),
// 	background(skybg)
// {
// 	this->action = &Lakitu::actionIdle;
// }

// mat4 const&	Lakitu::getViewMatrix() const
// {
// 	return (this->view_matrix);
// }

// void	Lakitu::update(InputState *input)
// {
	
// 	while (true)
// 	{
// 		if (!(this->*(this->action))(input))
// 			break;
// 	}
// 	// this->view_matrix = mat4::createViewMatrix(this->position, this->yaw, this->pitch);
// 	// mode8_background = background + ((u16(this->yaw) * 960) >> 16) + (((this->pitch * 320) >> 15) + 160) * 1200;
// }

// bool	Lakitu::actionRHold(InputState *input)
// {
// 	if (input->curr & KEY_A)
// 		this->action = &Lakitu::actionRAHold;
// 	else if (input->curr & KEY_B)
// 		this->action = &Lakitu::actionRBHold;
// 	else if (!(input->curr & KEY_R))
// 		this->action = &Lakitu::actionCameraReset;
// 	else
// 		return (false);
// 	return (true);
// }

// bool	Lakitu::actionRHoldOld(InputState *input)
// {
// 	if (input->curr & KEY_A)
// 		this->action = &Lakitu::actionRAHold;
// 	else if (input->curr & KEY_B)
// 		this->action = &Lakitu::actionRBHold;
// 	else if (!(input->curr & KEY_R))
// 		this->action = &Lakitu::actionIdle;
// 	else
// 		return (false);
// 	return (true);
// }

// bool	Lakitu::actionRAHold(InputState *input)
// {
// 	if (!(input->curr & KEY_A))
// 		this->action = &Lakitu::actionRHoldOld;
// 	else if (input->curr & KEY_B)
// 		this->action = &Lakitu::actionRABHold;
// 	else
// 	{
// 		this->yaw += 500;
// 		return (false);
// 	}
// 	return (true);
// }
// bool	Lakitu::actionRBHold(InputState *input)
// {
// 	if (input->curr & KEY_A)
// 		this->action = &Lakitu::actionRABHold;
// 	else if (!(input->curr & KEY_B))
// 		this->action = &Lakitu::actionRHoldOld;
// 	else
// 	{
// 		this->yaw -= 500;
// 		return (false);
// 	}
// 	return (true);
// }
// bool	Lakitu::actionRABHold(InputState *input)
// {
// 	if (!(input->curr & KEY_A))
// 		this->action = &Lakitu::actionRBHold;
// 	else if (!(input->curr & KEY_B))
// 		this->action = &Lakitu::actionRAHold;
// 	else
// 		return (false);
// 	return (true);
// }
// bool	Lakitu::actionCameraReset(InputState *input)
// {
// 	this->action = &Lakitu::actionIdle;
// 	this->yaw = 0;
// 	return (true);
// }
// bool	Lakitu::actionIdle(InputState *input)
// {
// 	if (input->curr & KEY_R)
// 		this->action = &Lakitu::actionRHold;
// 	return (false);
// }