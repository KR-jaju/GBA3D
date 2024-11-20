#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "object.hpp"
#include "player.hpp"
#include "vec3.hpp"
#include "gbamath/gbamath.h"
#include "GBAinput.hpp"
#include "clock.hpp"

class control
{
public:

    player mario;
    object obj[10];
    int objLen;
    Polygon ceil[1000];
    int ceilLen;
    Polygon wall[1000];
    int wallLen;
    Polygon floor[1000];
    int floorLen;

    vec3 force;
    vec3 moveTMP;
    f32 runSpeed ;
    f32 walkSpeed;
    f32 jumpForce;
    f32 gravity;
    f32 maxFallSpeed;

    f32 floorOP;
    f32 wallOP;
    f32 ceilOP;
    bool touchStatus[4]={ false, false, false, false };
    bool jumped;
    f32 distance;
    bool clickJump;

    control();
    void playerControll();
    void polygonInit();
    bool trianglePrismTest(Polygon tri, vec3 pos);
    bool normalTest(Polygon tri, vec3 pos, vec3 axis, f32 OP);
    void wallcheck(vec3& pos);
    bool floorcheck(vec3& pos);
    bool ceilcheck(vec3& pos);
    void checkCollision();
};



#endif