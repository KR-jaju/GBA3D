
#include "Clipper.hpp"

vec4	&Clipper::clampDepth(vec4 const &in, i32 near, i32 far) {
	vec4	out = in;

	if (out.z < near) {
		out.z = near;
	} else if (out.z > far) {
		out.z = far;
	}
	return (out);
}