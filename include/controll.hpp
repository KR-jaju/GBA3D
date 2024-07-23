#ifndef CONTROLL_HPP
#define CONTROLL_HPP

#include "player.hpp"
#include "vec3.hpp"
#include "math.hpp"

fixed speed = fixed(0);

void moveFront(player &obj)
{
    obj.rigid.velocity.y = speed;
}

void moveBack(player &obj)
{
    obj.rigid.velocity.y;
}

void moveRight(player &obj)
{
    obj.rigid.velocity.x;
}

void moveLeft(player &obj)
{
    obj.rigid.velocity.x;
}

void moveStop(player &obj)
{
    obj.rigid.velocity = {0,0,obj.rigid.velocity.z};
}

//땅에 있을때, 점프키 hold
void JumpOn(player &obj)
{
    obj.jumped = true;
    obj.rigid.velocity.y;
    
}

void JumpOff(player &obj)
{
    obj.rigid.velocity.y = obj.rigid.weight.y;
    
}

//땅에 있을때
void Run(player &obj)
{
    obj.rigid.velocity.x;
    obj.rigid.velocity.y;
}






#endif