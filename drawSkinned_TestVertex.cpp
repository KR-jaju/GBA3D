#include "common.h"
#include "gbavfx.h"
#include "TestVertex.h"
#include <algorithm>

namespace gbavfx {
	static void	transformVertex(TestVertex const* vertices, i32 offset, i32 count, fixed* matrix)
	{
		u8 *depth = vertex_depth_buffer + vertex_count + offset;
		u32 *v = vertex_buffer + (vertex_count << 1) + offset * 2;

		while (count--)
		{
			TestVertex const vertex = vertices[0];

			fixed post_x = vertex.x * matrix[0] + vertex.y * matrix[1] + vertex.z * matrix[2] + matrix[3];
			fixed post_y = vertex.x * matrix[4] + vertex.y * matrix[5] + vertex.z * matrix[6] + matrix[7];
			fixed post_z = vertex.x * matrix[8] + vertex.y * matrix[9] + vertex.z * matrix[10] + matrix[11];
			fixed z_reciprocal = reciprocal(post_z);

			u16 proj_x = ((post_x * z_reciprocal * 160 + 120).num >> 16);
			u16 proj_y = ((post_y * z_reciprocal * 160 + 80).num >> 16);

			depth[0] = u8(post_z.num >> (FIX_SHIFT - 2));
			depth += 1;
			v[0] = (u16(proj_y + 32768) << 16) | (u16(proj_x + 32768));
			v[1] = (u32(vertex.u) << 16) | (u32(vertex.v << 16) >> 16);
			v += 2;
			vertices += 1;
		}
	}
	static void	addFace(i32 const *indices, i32 face_count, u32 texture_id)
	{
		u8 *depth = vertex_depth_buffer + vertex_count;
		u32 *v = vertex_buffer + (vertex_count << 1);
		u32 *f = face_buffer;
		u32 idx = face_buffer_size;
		while (face_count--)
		{
			i32 i0 = indices[0];
			i32 i1 = indices[1];
			i32 i2 = indices[2];

			i32 z = depth[i0] + depth[i1] + depth[i2];
			// i32 z = 1;
			i32 next = ordering_table[z];

			u32 s0 = (v[i0 * 2]);
			u32 s1 = (v[i1 * 2]);
			u32 s2 = (v[i2 * 2]);

			if (s0 > s1) {
				std::swap(s0, s1);
				std::swap(i0, i1);
			}
			if (s1 > s2) {
				std::swap(s1, s2);
				std::swap(i1, i2);
			}
			if (s0 > s1) {
				std::swap(s0, s1);
				std::swap(i0, i1);
			}

			f[idx] = ((i1 << 16) | i0);
			idx += 1;
			f[idx] = ((next << 21) | (texture_id << 16)) | i2;
			ordering_table[z] = idx >> 1;
			idx += 1;
			indices += 3;
		}
	}
	template <>
	void	drawSkinned(TestVertex const *vertices, i32* vertex_count, i32 const *indices, u32 face_count, u32 texture_id, i32 bone_count)
	{
		i32 processed = 0;

		for (int bone = 0; bone < bone_count; ++bone)
		{
			i32 count = vertex_count[bone];

			transformVertex(vertices + processed, processed, count, gbavfx::matrix_slot[bone]);
			processed += count;
		}
		addFace(indices, face_count, texture_id);
		vertex_count += processed;
		face_buffer_size += face_count * 2;
	}
}