#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "vec3.hpp"
#include "fixed.hpp"
#include "object.hpp"
#include "player.hpp"
//type
//0 -> Non
//1 -> wall
//2 -> ground
//3 -> ceil

struct Collider
{
    u16 type;
    fixed push[4] = {0,20,0,20};
    int pixel[4] = {0,10,0,10};
};

struct Rigid
{
    vec3 weight;
    vec3 velocity;
};

void colliderTypeManager(object objList[], int len)
{
    for(int i = 0;i<len;i++)
    {
        Triangle* tri = objList[i].tri;
        while(tri!=nullptr)
        {
            if(fixed(0) <= tri->nv.y &&  tri->nv.y <= fixed(0)) //wall
            {
                objList[i].collider.type = 1;
            }
            else if(fixed(0) <= tri->nv.y &&  tri->nv.y <= fixed(0)) //ground
            {
                objList[i].collider.type = 2;
            }
            else if(fixed(0) <= tri->nv.y &&  tri->nv.y <= fixed(0)) //ceil
            {
                objList[i].collider.type = 3;
            }

        }
    }
}

//충돌확인
bool checkCollision(player &mario, object objList[], int len)
{
    for(int i = 0;i<len;i++)
    {
        
    }
}
#endif