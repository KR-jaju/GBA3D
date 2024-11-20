#include "lakitu/Lakitu.h"
#include "gbavfx/gbavfx.h"
#include "resource/texture.h"
#include "gbamath/gbamath.h"

Lakitu::Lakitu()
	: pos(),
	yaw(0),
	pitch(0),
	background(skybg)
{
	this->pos[0] = 0;
	this->pos[1] = 1;
	this->pos[2] = -4;
}

void	Lakitu::updateViewMatrix() {
	this->view_matrix[0] = this->dir[2];
	this->view_matrix[1] = 0;
	this->view_matrix[2] = -this->dir[0];
	this->view_matrix[3] = -(pos[0] * this->view_matrix[0] + pos[2] * this->view_matrix[2]);

	this->view_matrix[4] = this->dir[0] * this->dir[1];
	this->view_matrix[5] = -(this->dir[0] * this->dir[0] + this->dir[2] * this->dir[2]);
	this->view_matrix[6] = this->dir[1] * this->dir[2];
	this->view_matrix[7] = -(pos[0] * this->view_matrix[4] + pos[1] * this->view_matrix[5] + pos[2] * this->view_matrix[6]);

	this->view_matrix[8] = this->dir[0];
	this->view_matrix[9] = this->dir[1];
	this->view_matrix[10] = this->dir[2];
	this->view_matrix[11] = -(pos[0] * this->view_matrix[8] + pos[1] * this->view_matrix[9] + pos[2] * this->view_matrix[10]);
}

f32 const	*Lakitu::getViewMatrix() const
{
	return (this->view_matrix);
}

void	Lakitu::update()
{
	/*
		angle / 65536 * 240 * 4
		(pitch / 16384 * 160) * 3 + 160
	*/
	f32	sin_yaw;
	f32	cos_yaw;
	f32	sin_pitch;
	f32	cos_pitch;
	sincos(this->yaw, sin_yaw, cos_yaw);
	sincos(this->pitch, sin_pitch, cos_pitch);
	dir[0] = sin_yaw * cos_pitch;
	dir[1] = sin_pitch;
	dir[2] = cos_yaw * cos_pitch;
	this->updateViewMatrix();
	// gbavfx_background = background;
	// gbavfx_background = skybg;
	gbavfx_background = background + ((u16(this->yaw) * 960) >> 16) + (((this->pitch * 320) >> 15) + 160) * 1200;
}