#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "fixed.hpp"
#include "vec3.hpp"
#include "Collider.hpp"
#include "Triangle.hpp"


class object
{
    public:
    Collider collider;
    Triangle* tri;
};



#endif