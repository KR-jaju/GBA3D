#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "vec3.hpp"
#include "fixed.hpp"

// type
// 0 -> Non
// 1 -> wall
// 2 -> ground
// 3 -> ceil

struct Collider
{
    u16 type;
    fixed pixel[4] = {0, fixed(10), 0, fixed(10)};
};

struct Rigid
{
    vec3 weight;
    vec3 velocity;
    vec3 accel;
};


#endif