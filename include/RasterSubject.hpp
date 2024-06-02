
#ifndef RASTER_SUBJECT_HPP
# define RASTER_SUBJECT_HPP

# include "type.hpp"
# include "Vertex.hpp"
# include "Triangle.hpp"
# include "Mesh.hpp"
# include "Shader.hpp"

class RasterSubject {
public:
	Triangle	polygon[MAX_FACE_COUNT];
	Triangle	*depth[DEPTH_LAYER_SIZE];
	u32			polygon_count;

	RasterSubject(): polygon_count(0) {}
	template <u32 V, u32 F>
	IWRAM_CODE
	void	push(Mesh<V, F> const &mesh) {
		Vertex	processed[V];
		for (u32 i = 0; i < V; ++i) {
			Vertex const	&in = mesh.vertex[i];

			processed[i] = Shader::vertexShader(in);
			//run vertex shader
		}
		for (u32 i = 0; i < F * 3; i += 3) {
			Triangle	&tri = this->allocatePolygon();
			tri.init(
				processed[mesh.index[i]],
				processed[mesh.index[i + 1]],
				processed[mesh.index[i + 2]]
			);
			tri.next = this->depth[0];
			this->depth[0] = &tri;
		}
	}
	IWRAM_CODE
	void	push(Triangle const &tri) {
		// TODO: Backface culling
		//Possible polygon clipping
		Triangle	&allocated = this->allocatePolygon();
			
		allocated = tri;
		allocated.next = this->depth[0];
		this->depth[0] = &allocated;
	}
private:
	Triangle	&allocatePolygon() {
		Triangle &tri = this->polygon[this->polygon_count];

		this->polygon_count += 1;
		return (tri);
	}
};
#endif
