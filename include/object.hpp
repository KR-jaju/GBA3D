#ifndef OBJECT_HPP
#define OBJECT_HPP


#include "fixed.hpp"
#include "vec3.hpp"
#include "Triangle.hpp"


class object
{
    public:
    vec3 position;
    vec3 rotate;
    Triangle* tri = nullptr;
};



#endif