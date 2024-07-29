#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "player.hpp"
#include "vec3.hpp"
#include "math.hpp"
#include "GBAinput.hpp"

fixed speed = fixed(0);
fixed jumpForce = fixed(0);

void playerCtrl(player &mario)
{
    vec3 force = {0,0,0};

    key_poll();
    if(key_held(KEY_UP)) force = {0,speed,0};
    if(key_held(KEY_DOWN)) force = {0,-speed,0};
    if(key_held(KEY_RIGHT)) force = {speed,0,0};
    if(key_held(KEY_LEFT)) force = {-speed,0,0};
    if(mario.onGround)
    {
        if(key_held(KEY_B)) force.y = force.y * fixed(1.5f);
        if(key_hit(KEY_A)) force = {0,0,jumpForce};
    }
    

    mario.applyForce(force);

}




//땅에 있을때
void Run(player &obj)
{
    obj.rigid.velocity.x;
    obj.rigid.velocity.y;
}






#endif