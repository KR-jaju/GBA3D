// #include <iostream>
// #include "gbavfx/gbavfx.h"
// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "stb_image_write.h"
// #include "Vertex.h"
// #include "gbavfx/TestVertex.h"
// #include "palette.h"

// // #include "toad.h"
// #include "mario_model.h"
// #include "mario_idle0.h"

// extern u8 result[240 * 160];
// /*
// 0. black
// 1. red
// */

// TestVertex box_vertices[] = {
// 	{ 1.0, 1.0, 1.0, 0.875, 0.5 },
// 	{ 1.0, -1.0, 1.0, 0.625, 0.75 },
// 	{ 1.0, 1.0, -1.0, 0.625, 0.5 },
// 	{ 1.0, -1.0, -1.0, 0.375, 1.0 },
// 	{ -1.0, 1.0, 1.0, 0.375, 0.75 },
// 	{ -1.0, -1.0, 1.0, 0.625, 0.0 },
// 	{ -1.0, 1.0, -1.0, 0.375, 0.25 },
// 	{ -1.0, -1.0, -1.0, 0.375, 0.0 }};

// i32 box_indices[] = {4, 2, 0, 2, 7, 3, 6, 5, 7, 1, 7, 5, 0, 3, 1, 4, 1, 5, 4, 6, 2, 2, 6, 7, 6, 4, 5, 1, 3, 7, 0, 2, 3, 4, 0, 1};

// void	view(fixed *matrix, fixed pos[3], fixed dir[3]) {
// 	matrix[0] = dir[2];
// 	matrix[1] = 0;
// 	matrix[2] = -dir[0];
// 	matrix[3] = -(pos[0] * matrix[0] + pos[2] * matrix[2]);

// 	matrix[4] = dir[0] * dir[1];
// 	matrix[5] = -(dir[0] * dir[0] + dir[2] * dir[2]);
// 	matrix[6] = dir[1] * dir[2];
// 	matrix[7] = -(pos[0] * matrix[4] + pos[1] * matrix[5] + pos[2] * matrix[6]);

// 	matrix[8] = dir[0];
// 	matrix[9] = dir[1];
// 	matrix[10] = dir[2];
// 	matrix[11] = -(pos[0] * matrix[8] + pos[1] * matrix[9] + pos[2] * matrix[10]);
// }
// /*
// z : 
// cos -sin
// sin cos
// 0 0 1

// y : 
// cos 0 sin
// 0 1 0
// -sin 0 cos 

// x:
// 1 0 0
// 0 c -s
// 0 s c

// y * x * z

// c	s^
// 0
// -s

// */

// void	multiply_matrix(fixed *dst, fixed *a, fixed *b)
// {
// 	dst[0] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8];
// 	dst[1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9];
// 	dst[2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10];
// 	dst[3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3];

// 	dst[4] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8];
// 	dst[5] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9];
// 	dst[6] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10];
// 	dst[7] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7];

// 	dst[8] = a[8] * b[0] + a[9] * b[4] + a[10] * b[8];
// 	dst[9] = a[8] * b[1] + a[9] * b[5] + a[10] * b[9];
// 	dst[10] = a[8] * b[2] + a[9] * b[6] + a[10] * b[10];
// 	dst[11] = a[8] * b[3] + a[9] * b[7] + a[10] * b[11] + a[11];
// }

// void	qtor(fixed* dst, fixed x, fixed y, fixed z, fixed w)
// {
// 	fixed xx = x * x;
// 	fixed yy = y * y;
// 	fixed zz = z * z;
// 	fixed wx = w * x;
// 	fixed wy = w * y;
// 	fixed wz = w * z;
// 	fixed xy = x * y;
// 	fixed xz = x * z;
// 	fixed yz = y * z;
// 	dst[0] = 1 - 2 * (yy + zz);
// 	dst[1] = 2 * (xy - wz);
// 	dst[2] = 2 * (xz + wy);
// 	dst[3] = 0;
// 	dst[4] = 2 * (xy + wz);
// 	dst[5] = 1 - 2 * (xx + zz);
// 	dst[6] = 2 * (yz - wx);
// 	dst[3] = 0;
// 	dst[8] = 2 * (xz - wy);
// 	dst[9] = 2 * (yz + wx);
// 	dst[10] = 1 - 2 * (xx + yy);
// 	dst[11] = 0;
// }

// void	rotation(fixed* mat, fixed x, fixed y, fixed z)
// {
// 	fixed xr[9] = {
// 		1, 0, 0,
// 		0, cos(x), -sin(x),
// 		0, sin(x), cos(x)
// 	};
// 	fixed yr[9] = {
// 		cos(y), 0, sin(y),
// 		0, 1, 0,
// 		-sin(y), 0, cos(y)
// 	};
// 	fixed zr[9] = {
// 		cos(z), -sin(z), 0,
// 		sin(z), cos(x), 0,
// 		0, 0, 1
// 	};
// 	fixed xzr[9] = {
// 		xr[0] * zr[0] + xr[1] * zr[3] + xr[2] * zr[6], xr[0] * zr[1] + xr[1] * zr[4] + xr[2] * zr[7], xr[0] * zr[2] + xr[1] * zr[5] + xr[2] * zr[8],
// 		xr[3] * zr[0] + xr[4] * zr[3] + xr[5] * zr[6], xr[3] * zr[1] + xr[4] * zr[4] + xr[5] * zr[7], xr[3] * zr[2] + xr[4] * zr[5] + xr[5] * zr[8],
// 		xr[6] * zr[0] + xr[7] * zr[3] + xr[8] * zr[6], xr[6] * zr[1] + xr[7] * zr[4] + xr[8] * zr[7], xr[6] * zr[2] + xr[7] * zr[5] + xr[8] * zr[8],
// 	};
// 	mat[0] = yr[0] * xzr[0] + yr[1] * xzr[3] + yr[2] * xzr[6];
// 	mat[1] = yr[0] * xzr[1] + yr[1] * xzr[4] + yr[2] * xzr[7];
// 	mat[2] = yr[0] * xzr[2] + yr[1] * xzr[5] + yr[2] * xzr[8];
	
// 	mat[4] = yr[3] * xzr[0] + yr[4] * xzr[3] + yr[5] * xzr[6];
// 	mat[5] = yr[3] * xzr[1] + yr[4] * xzr[4] + yr[5] * xzr[7];
// 	mat[6] = yr[3] * xzr[2] + yr[4] * xzr[5] + yr[5] * xzr[8];

// 	mat[8] = yr[6] * xzr[0] + yr[7] * xzr[3] + yr[8] * xzr[6];
// 	mat[9] = yr[6] * xzr[1] + yr[7] * xzr[4] + yr[8] * xzr[7];
// 	mat[10] = yr[6] * xzr[2] + yr[7] * xzr[5] + yr[8] * xzr[8];
// }
// //120, 33
// //150, 16
// //153, 29
// int	main(void)
// {
// 	Vertex t_vertices[] = {
// 		{141, -45, 5, 0, 0},
// 		{159, -30, 5, 0, 0},
// 		{136, -34, 5, 0, 0},
// 	};
// 	i32 t_indices[] = {0, 1, 2};
// 	float T = ((0.0f / 100.0f + 179.5f) / 180.f) * 3.141592f;
// 	float a = cos(T) - sin(T);
// 	float b = sin(T) + cos(T);
// 	TestVertex plane_vertices[] = {
// 		{-a, b, 0, 0, 0},
// 		// {-a, 0.3f, 0, 0, 0},
// 		{b, a, 0, 1.0f, 0},
// 		{-b, -a, 0, 0, 1.0f},
// 		{a, -b, 0, 1.0f, 1.0f},
// 	};
// 	i32 plane_indices[] = {0, 1, 2, 1, 2, 3};
// 	// i32 indices[] = {0, 1, 2};
// 	fixed matrix[] = {
// 		1, 0, 0, 0,
// 		0, 1, 0, 0,
// 		0, 0, 1, 10
// 	};
// 	// fixed pos[] = { 0, 1.0, -4 };
// 	// float t = 0.0f;
// 	// fixed dir[] = { sin(t), 0, cos(t) }; 

// 	fixed model_matrix[32][12];
// 	fixed pos[] = { 0, 1.0, 4 };
// 	float t = 3.14f;
// 	fixed dir[] = { sin(t), 0, cos(t) }; 
// 	view(matrix, pos, dir);
	
// 	// view matrix인데 z를 노말라이즈 하지 않는
// 	// memcpy(gbavfx::texture_slot[0], super_mario, 64 * 64);
// 	// memcpy(gbavfx::texture_slot[0], kinopio, 64 * 64);
// 	memcpy(gbavfx::texture_slot[0], mario_test, 64 * 64);
// 	// memcpy(gbavfx::texture_slot[0], stupid_ai, 64 * 64);
// 	gbavfx::stride_slot[0] = gbavfx::STRIDE_64;
// 	gbavfx::clear();
// 	constexpr i32 frame = 30;
// 	float (*data)[7] = animation[frame];
// 	for (int bone = 0; bone < 17; bone++)
// 	{
// 		fixed model[12] = {1, 0, 0, 0,
// 		0, 1, 0, 0,
// 		0, 0, 1, 0,};
// 		fixed* dst = gbavfx::matrix_slot[0];
// 		fixed x = data[bone][0];
// 		fixed y = data[bone][1];
// 		fixed z = data[bone][2];

// 		fixed rx = data[bone][3];
// 		fixed ry = data[bone][4];
// 		fixed rz = data[bone][5];
// 		fixed rw = data[bone][6];

// 		qtor(model, rx, ry, rz, rw);
// 		model[3] = x;
// 		model[7] = y;
// 		model[11] = z;

// 		multiply_matrix(model_matrix[bone], matrix, model);
// 		gbavfx::matrix_slot[bone] = model_matrix[bone];
// 		// gbavfx::matrix_slot[bone] = matrix;
// 	}
// 	// gbavfx::drawIndexed(plane_vertices, 4, plane_indices, 2, 0);
// 	// gbavfx::drawIndexed(box_vertices, 8, box_indices, 12, 0);
// 	// gbavfx::drawIndexed(vertices, 300, indices, 301, 0);
// 	// gbavfx::drawIndexed(vertices, 312, indices, 368, 0);

// 	gbavfx::drawSkinned(vertices, vertex_count, indices, 368, 0, 17);
// 	// gbavfx::drawIndexed(t_vertices, 3, t_indices, 1, 0);
// 	// std::cout << indices[202 * 3]
// 	gbavfx::flip();

// 	u8 png_out[240 * 160 * 3]; // rgb 240 * 160
// //2149679224
// //2148565142
// //2149417113
// 	for (u32 y = 0; y < 160; ++y)
// 	{
// 		for (u32 x = 0; x < 240; ++x)
// 		{
// 			u32 idx = (x + y * 240);
// 			u32 pidx = result[idx];
// 			u32 color = palette[pidx];
// 			png_out[idx * 3] = u8(float(color & 0b11111) / 31 * 255);
// 			png_out[idx * 3 + 1] = u8(float((color >> 5) & 0b11111) / 31 * 255);
// 			png_out[idx * 3 + 2] = u8(float((color >> 10) & 0b11111) / 31 * 255);
// 		}
// 	}
// 	// char id[3] = {'a' + (i / 26 / 26 % 26), 'a' + (i / 26 % 26), 'a' + (i % 26)};
// 	// char name[8] = "AAA.png";
// 	// name[0] = id[0];
// 	// name[1] = id[1];
// 	// name[2] = id[2];
// 	stbi_write_png("output.png", 240, 160, 3, png_out, 240 * 3);
// 	// texture test
// 	// u8 out_test[64 * 64 * 3];
// 	// for (u32 y = 0; y < 64; ++y)
// 	// {
// 	// 	for (u32 x = 0; x < 64; ++x)
// 	// 	{
// 	// 		u32 idx = (x + y * 64);
// 	// 		u32 pidx = gbavfx::texture_slot[0][idx];
// 	// 		u32 color = palette[pidx];
// 	// 		out_test[idx * 3] = u8(float(color & 0b11111) / 31 * 255);
// 	// 		out_test[idx * 3 + 1] = u8(float((color >> 5) & 0b11111) / 31 * 255);
// 	// 		out_test[idx * 3 + 2] = u8(float((color >> 10) & 0b11111) / 31 * 255);
// 	// 	}
// 	// }
// 	// stbi_write_png("test.png", 64, 64, 3, out_test, 64 * 3);
// }