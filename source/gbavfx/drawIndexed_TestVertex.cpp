// #include "common.h"
// #include "gbavfx/gbavfx.h"
// #include "gbavfx/TestVertex.h"
// #include <algorithm>
// #include "clock.hpp"
// // #include "transformVertex.h"

// #include "division.h"
// #include <iostream>

// static void IWRAM_CODE	transformVertex(TestVertex const* vertices, u32 count, fixed* matrix)
// {
// 	u32 *v = gbavfx_vbo.vertex + (gbavfx_vbo.size << 1);//r3
// 	u8 *depth = gbavfx_vbo.depth + gbavfx_vbo.size;//r4

// 	while (count--)
// 	{
// 		TestVertex const vertex = vertices[0];

// 		fixed post_x = vertex.x * matrix[0] + vertex.y * matrix[1] + vertex.z * matrix[2] + matrix[3];
// 		fixed post_y = vertex.x * matrix[4] + vertex.y * matrix[5] + vertex.z * matrix[6] + matrix[7];
// 		fixed post_z = vertex.x * matrix[8] + vertex.y * matrix[9] + vertex.z * matrix[10] + matrix[11];
// 		fixed z_reciprocal = fixed::from(reciprocal(u32(post_z.num)) << 1);

// 		u16 proj_x = ((post_x * z_reciprocal * 160 + 120).num >> 16);
// 		u16 proj_y = ((post_y * z_reciprocal * 160 + 80).num >> 16);

// 		depth[0] = u8(post_z.num >> (FIX_SHIFT - 2));
// 		depth += 1;
// 		v[0] = (u16(proj_y + 32768) << 16) | (u16(proj_x + 32768));
// 		v[1] = vertex.uv;
// 		v += 2;
// 		vertices += 1;
// 	}
// }

// static void IWRAM_CODE	addFace(i32 const *indices, i32 face_count, u32 texture_id)
// {
// 	u32 *v = gbavfx_vbo.vertex + (gbavfx_vbo.size << 1);
// 	u8 *depth = gbavfx_vbo.depth + gbavfx_vbo.size;
// 	u32 *f = gbavfx_fbo.face;
// 	u32 idx = gbavfx_fbo.size;
// 	while (face_count--)
// 	{
// 		i32 i0 = indices[0];
// 		i32 i1 = indices[1];
// 		i32 i2 = indices[2];
// 		indices += 3;

// 		i32 z = depth[i0] + depth[i1] + depth[i2];
// 		i32 next = ordering_table[z];

// 		u32 s0 = (v[i0 * 2]);
// 		u32 s1 = (v[i1 * 2]);
// 		u32 s2 = (v[i2 * 2]);
// 		{
// 			i32 x0 = u16(s0);
// 			i32 dx01 = (s1 & 0xFFFF) - x0;
// 			i32 dx02 = (s2 & 0xFFFF) - x0;
			
// 			i32 y0 = (s0 >> 16);
// 			i32 dy01 = i32(s1 >> 16) - y0;
// 			i32 dy02 = i32(s2 >> 16) - y0;

// 			if (dx01 * dy02 <= dx02 * dy01)
// 			// if (dx01 * dy02 > dx02 * dy01)
// 				continue;
// 		}
// 		// 0 1 2 -> (rotate)
// 		// 1 2 0
// 		// 2와 0 비교 -> 합칠 것 정함
// 		if (s0 > s1) {
// 			std::swap(s0, s1);
// 			std::swap(i0, i1);
// 		}
// 		if (s1 > s2) {
// 			std::swap(s1, s2);
// 			std::swap(i1, i2);
// 		}
// 		if (s0 > s1) {
// 			std::swap(s0, s1);
// 			std::swap(i0, i1);
// 		}

// 		f[idx] = ((i1 << 16) | i0);
// 		idx += 1;
// 		f[idx] = ((next << 21) | (texture_id << 16)) | i2;
// 		ordering_table[z] = idx >> 1;
// 		idx += 1;
// 	}
// }
// // char buffer[2][20];
// // template <>
// // void IWRAM_CODE	gbavfx_drawIndexed(TestVertex const *vertices, u32 vertex_count, i32 const *indices, u32 face_count, u32 texture_id)
// void IWRAM_CODE	gbavfx_drawIndexed(TestVertex const *vertices, u32 vertex_count, i32 const *indices, u32 face_count, u32 texture_id)

// {
// 	transformVertex_A(vertices, vertex_count, gbavfx_matrix_slot[0]);
// 	// transformVertex(vertices, vertex_count, gbavfx_matrix_slot[0]);
// 	addFace(indices, face_count, texture_id);
// 	gbavfx_vbo.size += vertex_count;
// 	gbavfx_fbo.size += face_count * 2;
// }