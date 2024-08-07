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
    if(key_held(KEY_UP)) force = force + vec3::FRONT() * speed;
    if(key_held(KEY_DOWN)) force = force + vec3::BACK() * speed;
    if(key_held(KEY_RIGHT)) force = force + vec3::RIGHT() * speed;
    if(key_held(KEY_LEFT)) force = force + vec3::LEFT() * speed;
    if(mario.onGround)
    {
        if(key_held(KEY_B)) //run
        {
            force.x = force.x * fixed(1.5f);
            force.z = force.z * fixed(1.5f);
        }
        if(key_hit(KEY_A)) //jump
        {
            mario.jumped = true;
            force = force + vec3::UP() * jumpForce;
        }
    }
    

    mario.applyForce(force);
}



#endif