#include "MeshTMP.hpp"

static MeshTMP wallOBJ = {
    {
        vec3({fixed(11.0000f), fixed(-5.0000f), fixed(10.0000f)}),
        vec3({fixed(9.0000f), fixed(-5.0000f), fixed(10.0000f)}),
        vec3({fixed(11.0000f), fixed(15.0000f), fixed(10.0000f)}),
        vec3({fixed(9.0000f), fixed(15.0000f), fixed(10.0000f)}),
        vec3({fixed(11.0000f), fixed(15.0000f), fixed(-10.0000f)}),
        vec3({fixed(9.0000f), fixed(15.0000f), fixed(-10.0000f)}),
        vec3({fixed(11.0000f), fixed(-5.0000f), fixed(-10.0000f)}),
        vec3({fixed(9.0000f), fixed(-5.0000f), fixed(-10.0000f)}),
        vec3({fixed(11.0000f), fixed(15.0000f), fixed(10.0000f)}),
        vec3({fixed(9.0000f), fixed(15.0000f), fixed(10.0000f)}),
        vec3({fixed(11.0000f), fixed(15.0000f), fixed(-10.0000f)}),
        vec3({fixed(9.0000f), fixed(15.0000f), fixed(-10.0000f)}),
        vec3({fixed(11.0000f), fixed(-5.0000f), fixed(-10.0000f)}),
        vec3({fixed(11.0000f), fixed(-5.0000f), fixed(10.0000f)}),
        vec3({fixed(9.0000f), fixed(-5.0000f), fixed(10.0000f)}),
        vec3({fixed(9.0000f), fixed(-5.0000f), fixed(-10.0000f)}),
        vec3({fixed(9.0000f), fixed(-5.0000f), fixed(10.0000f)}),
        vec3({fixed(9.0000f), fixed(15.0000f), fixed(10.0000f)}),
        vec3({fixed(9.0000f), fixed(15.0000f), fixed(-10.0000f)}),
        vec3({fixed(9.0000f), fixed(-5.0000f), fixed(-10.0000f)}),
        vec3({fixed(11.0000f), fixed(-5.0000f), fixed(-10.0000f)}),
        vec3({fixed(11.0000f), fixed(15.0000f), fixed(-10.0000f)}),
        vec3({fixed(11.0000f), fixed(15.0000f), fixed(10.0000f)}),
        vec3({fixed(11.0000f), fixed(-5.0000f), fixed(10.0000f)}),
    },
    {
        0, 2, 3, 0, 3, 1, 8, 4, 5, 
        8, 5, 9, 10, 6, 7, 10, 7, 11, 
        12, 13, 14, 12, 14, 15, 16, 17, 18, 
        16, 18, 19, 20, 21, 22, 20, 22, 23
    },
    24,
    36
};

static MeshTMP playerOBJ = {
    {
        vec3({fixed(0.5000f), fixed(10.8000f), fixed(0.5000f)}),
        vec3({fixed(-0.5000f), fixed(10.8000f), fixed(0.5000f)}),
        vec3({fixed(0.5000f), fixed(11.8000f), fixed(0.5000f)}),
        vec3({fixed(-0.5000f), fixed(11.8000f), fixed(0.5000f)}),
        vec3({fixed(0.5000f), fixed(11.8000f), fixed(-0.5000f)}),
        vec3({fixed(-0.5000f), fixed(11.8000f), fixed(-0.5000f)}),
        vec3({fixed(0.5000f), fixed(10.8000f), fixed(-0.5000f)}),
        vec3({fixed(-0.5000f), fixed(10.8000f), fixed(-0.5000f)}),
        vec3({fixed(0.5000f), fixed(11.8000f), fixed(0.5000f)}),
        vec3({fixed(-0.5000f), fixed(11.8000f), fixed(0.5000f)}),
        vec3({fixed(0.5000f), fixed(11.8000f), fixed(-0.5000f)}),
        vec3({fixed(-0.5000f), fixed(11.8000f), fixed(-0.5000f)}),
        vec3({fixed(0.5000f), fixed(10.8000f), fixed(-0.5000f)}),
        vec3({fixed(0.5000f), fixed(10.8000f), fixed(0.5000f)}),
        vec3({fixed(-0.5000f), fixed(10.8000f), fixed(0.5000f)}),
        vec3({fixed(-0.5000f), fixed(10.8000f), fixed(-0.5000f)}),
        vec3({fixed(-0.5000f), fixed(10.8000f), fixed(0.5000f)}),
        vec3({fixed(-0.5000f), fixed(11.8000f), fixed(0.5000f)}),
        vec3({fixed(-0.5000f), fixed(11.8000f), fixed(-0.5000f)}),
        vec3({fixed(-0.5000f), fixed(10.8000f), fixed(-0.5000f)}),
        vec3({fixed(0.5000f), fixed(10.8000f), fixed(-0.5000f)}),
        vec3({fixed(0.5000f), fixed(11.8000f), fixed(-0.5000f)}),
        vec3({fixed(0.5000f), fixed(11.8000f), fixed(0.5000f)}),
        vec3({fixed(0.5000f), fixed(10.8000f), fixed(0.5000f)}),
    },
    {
        0, 2, 3, 0, 3, 1, 8, 4, 5, 
        8, 5, 9, 10, 6, 7, 10, 7, 11, 
        12, 13, 14, 12, 14, 15, 16, 17, 18, 
        16, 18, 19, 20, 21, 22, 20, 22, 23
    },
    24,
    36
};

static MeshTMP floorOBJ = {
    {
        vec3({fixed(10.0000f), fixed(-1.0000f), fixed(10.0000f)}),
        vec3({fixed(-10.0000f), fixed(-1.0000f), fixed(10.0000f)}),
        vec3({fixed(10.0000f), fixed(1.0000f), fixed(10.0000f)}),
        vec3({fixed(-10.0000f), fixed(1.0000f), fixed(10.0000f)}),
        vec3({fixed(10.0000f), fixed(1.0000f), fixed(-10.0000f)}),
        vec3({fixed(-10.0000f), fixed(1.0000f), fixed(-10.0000f)}),
        vec3({fixed(10.0000f), fixed(-1.0000f), fixed(-10.0000f)}),
        vec3({fixed(-10.0000f), fixed(-1.0000f), fixed(-10.0000f)}),
        vec3({fixed(10.0000f), fixed(1.0000f), fixed(10.0000f)}),
        vec3({fixed(-10.0000f), fixed(1.0000f), fixed(10.0000f)}),
        vec3({fixed(10.0000f), fixed(1.0000f), fixed(-10.0000f)}),
        vec3({fixed(-10.0000f), fixed(1.0000f), fixed(-10.0000f)}),
        vec3({fixed(10.0000f), fixed(-1.0000f), fixed(-10.0000f)}),
        vec3({fixed(10.0000f), fixed(-1.0000f), fixed(10.0000f)}),
        vec3({fixed(-10.0000f), fixed(-1.0000f), fixed(10.0000f)}),
        vec3({fixed(-10.0000f), fixed(-1.0000f), fixed(-10.0000f)}),
        vec3({fixed(-10.0000f), fixed(-1.0000f), fixed(10.0000f)}),
        vec3({fixed(-10.0000f), fixed(1.0000f), fixed(10.0000f)}),
        vec3({fixed(-10.0000f), fixed(1.0000f), fixed(-10.0000f)}),
        vec3({fixed(-10.0000f), fixed(-1.0000f), fixed(-10.0000f)}),
        vec3({fixed(10.0000f), fixed(-1.0000f), fixed(-10.0000f)}),
        vec3({fixed(10.0000f), fixed(1.0000f), fixed(-10.0000f)}),
        vec3({fixed(10.0000f), fixed(1.0000f), fixed(10.0000f)}),
        vec3({fixed(10.0000f), fixed(-1.0000f), fixed(10.0000f)}),
    },
    {
        0, 2, 3, 0, 3, 1, 8, 4, 5, 
        8, 5, 9, 10, 6, 7, 10, 7, 11, 
        12, 13, 14, 12, 14, 15, 16, 17, 18, 
        16, 18, 19, 20, 21, 22, 20, 22, 23
    },
    24,
    36
};