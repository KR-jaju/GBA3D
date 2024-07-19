#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "vec3.hpp"
#include "fixed.hpp"
#include "object.hpp"

//type
//0 -> Non
//1 -> wall
//2 -> floor
//3 -> ceil

struct Collider
{
    u16 type;
    fixed push;
    int pixel;
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
            if(tri->nv.y == 0) //wall
            {

            }
            else if(tri->nv.y == 0) //ground
            {

            }
            else if(tri->nv.y == 0) //ceil
            {
                
            }

        }
    }
}

#endif