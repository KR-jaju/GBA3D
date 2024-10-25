// #include "common.h"
// #include "gbavfx/gbavfx.h"
// #include "Vertex.h"
// #include <algorithm>

// #include <iostream>

// namespace gbavfx {
// 	static void	transformVertex(Vertex const* vertices, u32 count)
// 	{
// 		u32 *v = vertex_buffer + vertex_buffer_size;

// 		while (count--)
// 		{
// 			Vertex const vertex = vertices[0];

// 			v[0] = (u16(vertex.y + 32768) << 16) | (u16(vertex.x + 32768));
// 			// v[0] = (vertex.y << 16) | (u32(vertex.x << 16) >> 16);
// 			// v[1] = (vertex.u << 16) | (vertex.v << 8) | (vertex.z);
// 			v[1] = (vertex.u << 16) | (vertex.v);
			
// 			v += 2;
// 			vertices += 1;
// 		}
// 	}
// 	static void	addFace(i32 const *indices, i32 face_count, u32 texture_id)
// 	{
// 		u32 *v = vertex_buffer + vertex_buffer_size;
// 		u32 *f = face_buffer;
// 		u32 idx = face_buffer_size;
// 		while (face_count--)
// 		{
// 			i32 i0 = indices[0];
// 			i32 i1 = indices[1];
// 			i32 i2 = indices[2];

// 			// i32 z = *(u8 *)&v[i0 * 2 + 1] + *(u8 *)&v[i1 * 2 + 1] + *(u8 *)&v[i2 * 2 + 1];
// 			i32 z = 1;
// 			i32 next = ordering_table[z];

// 			u32 s0 = (v[i0 * 2]);
// 			u32 s1 = (v[i1 * 2]);
// 			u32 s2 = (v[i2 * 2]);
			
// 			if (s0 > s1) {
// 				std::swap(s0, s1);
// 				std::swap(i0, i1);
// 			}
// 			if (s1 > s2) {
// 				std::swap(s1, s2);
// 				std::swap(i1, i2);
// 			}
// 			if (s0 > s1) {
// 				std::swap(s0, s1);
// 				std::swap(i0, i1);
// 			}

// 			f[idx] = ((i1 << 16) | i0);
// 			idx += 1;
// 			f[idx] = ((next << 21) | (texture_id << 16)) | i2;
// 			ordering_table[z] = idx >> 1;
// 			idx += 1;
// 			indices += 3;
// 		}
// 	}
// 	template <>
// 	void	drawIndexed(Vertex const *vertices, u32 vertex_count, i32 const *indices, u32 face_count,  u32 texture_id)
// 	{
// 		transformVertex(vertices, vertex_count);
// 		addFace(indices, face_count, texture_id);
// 		vertex_buffer_size += vertex_count * 2;
// 		face_buffer_size += face_count * 2;
// 	}
// }