
#include "Camera.hpp"

Camera::Camera(): position({0, 0, 0}), lookat({0, 0, 1}), rs(), aspect(1) {
	this->near = 0.3f;
	this->far = 100.0f;
}

void	Camera::update() {
	this->position.z -= 0.001f;
	this->calculateProjectionMatrix();
	this->calculateViewMatrix();
}

void	Camera::calculateProjectionMatrix() {
	fixed const	n = this->near;
	fixed const	f = this->far;
	fixed const	aspect = this->aspect;
	fixed const	a = fixed(1) / near; // TODO: 나눗셈
	// float(1.0f / float(near));
	// fixed(1.0f / float(near * tan(float(this->fov) / 2.0f)));
	// fixed(1) / (fixed(tan(float(this->fov) / 2.0f )) * near);
	fixed const	b = (n + f) / (f - n);
	fixed const	c = fixed(-2) * f * n / (f - n);

	this->projection = (mat4){
		a / aspect, 0, 0, 0,
		0, a, 0, 0,
		0, 0, b, c,
		0, 0, 1, 0
	};
}

void	Camera::calculateViewMatrix() {
	vec3 const	&position = this->position;
	vec3 const	forward = normalize(this->lookat - position);
	vec3 const	right = normalize(cross((vec3){0, 1, 0}, forward));
	vec3 const	up = cross(forward, right);
	mat4 const	inv_R = {
		right.x, right.y, right.z, 0,
		up.x, up.y, up.z, 0,
		forward.x, forward.y, forward.z, 0,
		0, 0, 0, 1 
	};
	mat4 const	inv_T = mat4::translate(-position.x, -position.y, -position.z);
	this->view = inv_R * inv_T;
}