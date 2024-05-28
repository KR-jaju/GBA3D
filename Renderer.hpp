
#ifndef RENDERER_HPP
# define RENDERER_HPP

# include "Mesh.hpp"
# include "RasterSubject.hpp"
# include "Shader.hpp"
# include "Clipper.hpp"
# include "Rasterizer.hpp"

/*
Assumption
- void push()

- void render(u32 *out)
	out : int[RENDERER_WIDTH * RENDERER_HEIGHT]
*/
class Renderer {
	void	push(Mesh const &mesh) {
		
	}
	void	render(u32 *out) {
		this->clipper.clip(this->subject);
		this->rasterizer.render(this->subject);
	}
private:
	RasterSubject	subject;
	Shader	shader;
	Clipper	clipper;
	Rasterizer	rasterizer;
};

#endif
