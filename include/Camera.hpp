
#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "math.hpp"
# include "vec3.hpp"
# include "mat4.hpp"
# include "Triangle.hpp"
# include "Mesh.hpp"
# include "Rasterizer.hpp"
# include "DepthTable.hpp"

class Camera {
public:
	Camera();
	void	update();
	void	render(u8 *out);
	template <u32 V, u32 F>
	void	push(Mesh<V, F> const &mesh);
private:
	vec3	position;
	// int		yaw;
	// int		pitch;
	// int		roll;
	vec3	lookat;
	mat4	projection;
	mat4	view;
	DepthTable	table;

	fixed aspect; //화면 비율
	fixed fov, near, far; //시야각, 절두체 앞 뒤
	void	calculateProjectionMatrix();
	void	calculateViewMatrix();
};

template <u32 V, u32 F>
void	Camera::push(Mesh<V, F> const &mesh) {
	Fragment	processed[V];
	
	Shader::matrix[0] = this->projection * this->view;
	for (u32 i = 0; i < V; ++i) {
		Fragment			&dst = processed[i];
		typename Mesh<V, F>::Vertex const	&in = mesh.vertex[i];
	
		dst = Shader::vertexShader<V, F>(in);
	}
	for (u32 i = 0; i < F * 3; i += 3) {
		this->table.push(
			processed[mesh.index[i]],
			processed[mesh.index[i + 1]],
			processed[mesh.index[i + 2]]
		);
	}
}

#endif
