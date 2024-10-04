#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "object.hpp"
#include "player.hpp"
#include "vec3.hpp"
#include "fixed.hpp"
#include "math.hpp"
#include "GBAinput.hpp"
#include "clock.hpp"

class control
{
public:
    int FPS;

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
    fixed runSpeed ;
    fixed walkSpeed;
    fixed jumpForce;
    fixed gravity;
    fixed maxFallSpeed;

    fixed floorOP;
    fixed wallOP;
    fixed ceilOP;
    bool touchStatus[4]={ false, false, false, false };
    bool jumped;
    fixed distance;
    bool clickJump;

    control();
    void playerControll();
    void polygonInit();
    bool trianglePrismTest(Polygon tri, vec3 pos);
    bool normalTest(Polygon tri, vec3 pos, vec3 axis, fixed OP);
    void wallcheck(vec3& pos);
    bool floorcheck(vec3& pos);
    bool ceilcheck(vec3& pos);
    void checkCollision();
};



#endif