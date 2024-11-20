#ifndef MESHTMP_HPP
# define MESHTMP_HPP

# include "type.hpp"
# include "gbamath/gbamath.h"
# include "vec3.hpp"

struct MeshTMP {
    
	vec3	vertex[1000];
	int		index[1000];
    int vertexLen;
    int indexLen;
};

#endif