#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "vec3.hpp"
#include "fixed.hpp"
#include "fixed.hpp"

//type
//0 -> Non
//1 -> wall
//2 -> floor
//3 -> ceil

class Collider
{
    u16 type;
    fixed push;
    int pixel;

    Collider(int type);
};

Collider::Collider(int type)
{
    this->type = type;
    switch(type)
    {
        case 0:
            push = 0;
            pixel = 0;
        break;
        case 1:
            push = 0;
            pixel = 0;
        break;
        case 2:
            push = 0;
            pixel = 0;
        break;
        case 3:
            push = 0;
            pixel = 0;
        break;
    }
}



#endif