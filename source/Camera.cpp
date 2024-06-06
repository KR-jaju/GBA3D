
#include "Camera.hpp"
#include "Screen.hpp"

Camera::Camera(): position({0, 0, 0}), lookat({0, 0, 0}), table(), aspect(1) {
	this->near = 0.3f;
	this->far = 100.0f;
}

int	g = 0;

void	Camera::update() {
	// this->position.z -= fixed::from(1000);
	// this->position.z -= 0.1f;
	// this->position.x -= fixed::from(100);
	// this->position.y = (sincos(g).y) * 5.3f;
	// this->position.x = (sincos(g).x) * 5.1f;
	// this->position.z = -20;
	fixed	s;
	fixed	c;
	sincos(g, s, c);
	this->position.x = (c) * 7.0f;
	this->position.z = (s) * 7.0f;
	this->position.y = 5.0f;
	g += 100;
	// this->position.y += fixed::from(1);
	this->calculateProjectionMatrix();
	this->calculateViewMatrix();
}


void	Camera::render(u8 *out) {
	Rasterizer::render(this->table, out);
	this->table.reset();
}

void	Camera::calculateProjectionMatrix() {
	fixed const	n = this->near;
	fixed const	f = this->far;
	fixed const	a = fixed(1) / near; // TODO: 나눗셈
	fixed const	b = (n + f) / (f - n);
	fixed const	c = fixed(-2) * f * n / (f - n);

	this->projection = (mat4){
		a * i32(Screen::height * Screen::subpixel / 2), 0, 0, 0,
		0, a * i32(Screen::height * Screen::subpixel / 2), 0, 0,
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
