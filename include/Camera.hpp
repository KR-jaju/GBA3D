
#ifndef CAMERA_HPP
# define CAMERA_HPP

# include "math.hpp"
# include "vec3.hpp"
# include "mat4.hpp"
# include "Triangle.hpp"
# include "Mesh.hpp"
# include "Rasterizer.hpp"
# include "DepthTable.hpp"
# include "VertexShader.hpp"

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
	Vertex		processed[V];
	
	VertexShader::matrix[0] = this->projection * this->view;
	for (u32 i = 0; i < V; ++i) {
		typename Mesh<V, F>::Vertex const	&in = mesh.vertex[i];
		Vertex	&out = processed[i];
		VertexShader::main<V, F>(in, out.attr);
		vec4	position = VertexShader::out_position;
		
		out.flag = 0;
		if (position.w < 0.3f) {
			position.w = 0.3f;
			out.flag |= Vertex::CLIP_NEAR;
		} else if (position.w > 100.0f) {
			position.w = 100.0f;
			out.flag |= Vertex::CLIP_FAR;
		}
		if (position.x < -position.w) out.flag |= Vertex::CLIP_LEFT;
		if (position.x > position.w) out.flag |= Vertex::CLIP_RIGHT;
		if (position.y < -position.w) out.flag |= Vertex::CLIP_BOTTOM;
		if (position.y > position.w) out.flag |= Vertex::CLIP_TOP;
		position.x /= position.w;
		position.y /= position.w;

		out.x = (i32)(position.x * 960) + 960;
		out.y = (i32)(-position.y * 640) + 640;
		out.z = (i32)(position.w * 5);
	}
	for (u32 i = 0; i < F * 3; i += 3) {
		Vertex const	&a = processed[mesh.index[i]];
		Vertex const	&b = processed[mesh.index[i + 1]];
		Vertex const	&c = processed[mesh.index[i + 2]];
		u32 const		discard_flag = a.flag & b.flag & c.flag;
		u32	const		clip_flag = a.flag | b.flag | c.flag;
		i32 const		depth = (a.z + b.z + c.z);
		// + c.z);
		//  >> 2;
		Vertex			clipped[7]; // 최대 4번 잘리므로 3(각형) + 4 -> 7각형
		u32				n = 3;

		if (discard_flag & Vertex::DISCARDED) // 모든 정점이 화면 밖
			continue;
		if (!Clipper::isClockwise(a, b, c)) // 정점들이 시계방향이면 버림
			continue;
		clipped[0] = a;
		clipped[1] = b;
		clipped[2] = c;
		// if (clip_flag & Vertex::CLIP_Y)
		// 	Clipper::clipY(clipped, n);
		// if (clip_flag & Vertex::CLIP_X) // 어떤 정점이 x 범위를 벗어남
		// 	Clipper::clipX(clipped, n);
		for (u32 i = 2; i < n; ++i) {
			Triangle	&triangle = this->table.aquire(depth);

			triangle.init(clipped[0], clipped[i - 1], clipped[i]);
		}
	}
}

#endif
