#ifndef OBJECT_HPP
#define OBJECT_HPP


#include "fixed.hpp"
#include "vec3.hpp"
#include "MeshTMP.hpp"
typedef struct Polygon Polygon;

struct Polygon
{
    vec3 A;
    vec3 B;
    vec3 C;
    vec3 edge0;
    vec3 edge1;
    vec3 edge2;
    vec3 N;
    fixed L;
    fixed dot;
};

class object
{
    public:
    vec3 position;
    MeshTMP mesh;
    void move(vec3 pos){position = pos;}
};



#endif