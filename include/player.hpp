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

void player::update(fixed deltaTime)
{
    this->rigid.accel.y = this->rigid.accel.y - this->rigid.weight;//중력
    
    this->rigid.velocity = this->rigid.velocity + this->rigid.accel * deltaTime;
    this->position = this->position + this->rigid.velocity * deltaTime;
    this->rigid.accel = {0,0,0};
}



#endif