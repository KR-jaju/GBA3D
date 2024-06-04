
#ifndef DEPTH_TABLE_HPP
# define DEPTH_TABLE_HPP

# include "Triangle.hpp"
# include "type.hpp"
# include "VertexShader.hpp"

class DepthTable {
public:
	DepthTable(): bucket(), allocated_count(0) {}
	Triangle	&push(Vertex const &a, Vertex const &b, Vertex const &c) {
		Triangle	&triangle = this->pool[this->allocated_count++];

		triangle.init(a, b, c);
		triangle.next = this->bucket[0];
		this->bucket[0] = &triangle;
		return (triangle);
	}
	void	reset() {
		for (int i = 0; i < 768; ++i)
			this->bucket[i] = NULL; // TODO: DMA
		this->allocated_count = 0;
	}
	Triangle const*const	*getBucket() const {
		return (this->bucket);
	}
private:
	Triangle	*bucket[768];
	Triangle	pool[1024];
	u32			allocated_count;
};

#endif
