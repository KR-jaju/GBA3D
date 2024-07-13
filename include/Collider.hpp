#ifndef COLLIDER_HPP
# define COLLIDER_HPP

#include "vec3.hpp"
#include "fixed.hpp"



struct SphereCollider
{
    vec3 point;
    fixed radient;
};

struct BoxCollider
{
    vec3 point1;
    vec3 point2;
};

#endif