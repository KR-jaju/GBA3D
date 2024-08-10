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
    void update(fixed deltaTime);
    void applyForce(const vec3& force) { this->rigid.accel = this->rigid.accel + force; }
};



#endif