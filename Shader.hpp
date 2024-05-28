
#ifndef SHADER_HPP
# define SHADER_HPP

# include "Fragment.hpp"

/*
1. MVP mul (Vertex shader)
2. clip
3. Rasterize (fragment shader)
*/

# include "Segment.hpp"

class Shader {
public:
	static u16	pixelShader(Segment const *segment, u32 x, u32 y);
private:
	static u16	pixelMain(Fragment const &fragment);
};

#endif
