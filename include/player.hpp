#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "object.hpp"
#include "vec3.hpp"

class player : public object
{
    public:
    Rigid rigid;
    bool onGround = false;
    bool wall = false;
    bool ceil = false;
    bool jumped = false;
};



#endif