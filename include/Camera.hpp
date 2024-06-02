
#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "math.hpp"
# include "vec3.hpp"
# include "mat4.hpp"
# include "Triangle.hpp"
# include "Mesh.hpp"
# include "RasterSubject.hpp"
# include "Rasterizer.hpp"

class Camera {
public:
	Camera();
	void	update();
	template <u32 V, u32 F>
	void	push(Mesh<V, F> const &mesh) {
		this->rs.push(mesh, this->projection * this->view);
	}
	void	render(u8 *out) {
		Rasterizer::render(rs, out);
		this->rs.clear();
	}
private:
	vec3	position;
	// int		yaw;
	// int		pitch;
	// int		roll;
	vec3	lookat;
	mat4	projection;
	mat4	view;
	RasterSubject	rs;

	fixed aspect; //화면 비율
	fixed fov, near, far; //시야각, 절두체 앞 뒤
	void	calculateProjectionMatrix();
	void	calculateViewMatrix();
};


#endif
