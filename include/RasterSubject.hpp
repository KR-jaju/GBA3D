
#ifndef RASTER_SUBJECT_HPP
# define RASTER_SUBJECT_HPP

# include "type.hpp"
# include "Vertex.hpp"
# include "Triangle.hpp"
# include "Mesh.hpp"

class RasterSubject {
public:
	Triangle	polygon[MAX_FACE_COUNT];
	u32			polygon_count;

	RasterSubject(): polygon_count(0) {}
	template <u32 V, u32 F>
	IWRAM_CODE
	void	push(Mesh<V, F> const &mesh) {
		for (u32 i = 0; i < V; ++i) {
			Vertex const	&in = mesh.vertex[i];
			//run vertex shader
		}
		for (u32 i = 0; i < F * 3; i += 3) {
			Triangle	tri = {
				mesh.vertex[mesh.index[i]],
				mesh.vertex[mesh.index[i + 1]],
				mesh.vertex[mesh.index[i + 2]]
			};
			this->push(tri);
		}
	}
	IWRAM_CODE
	void	push(Triangle const &tri) {
		// TODO: Backface culling
		//Possible polygon clipping
		Triangle &triangle = this->polygon[this->polygon_count];
		triangle = tri;
		triangle.sort();
		this->polygon_count += 1;
	}
private:
};
#endif
