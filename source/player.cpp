#include "player.hpp"

void player::update(fixed deltaTime)
{
    this->rigid.accel.y = this->rigid.accel.y - this->rigid.weight.y;//중력
    
    this->rigid.velocity = this->rigid.velocity + this->rigid.accel * deltaTime;
    this->position = this->position + this->rigid.velocity * deltaTime;
    this->rigid.accel = {0,0,0};
}