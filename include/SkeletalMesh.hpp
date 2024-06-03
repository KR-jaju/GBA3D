
#ifndef SKELETAL_MESH_HPP
# define SKELETAL_MESH_HPP

# include "type.hpp"
# include "fixed.hpp"

template <u32 V, u32 F>
struct SkeletalMesh {
	struct Vertex {
		fixed	x;
		fixed	y;
		fixed	z;
		i32		u;
		i32		v;
		i32		joint_id[3];
		fixed	joint_weight[3];
	};
	Vertex	vertex[V];
	u32		index[F * 3];
};

#endif
