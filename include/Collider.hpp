#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "vec3.hpp"
#include "fixed.hpp"
#include "object.hpp"
#include "player.hpp"
#include "math.hpp"
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
    vec3 accel;
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
    vec3 nv; //삼각형의 평면 벡터
    fixed d; //점(마리오)과 평면의 거리
    Triangle *tri;
    Collider col;
    vec3 pos = mario.position; //현재 마리오 좌표
    vec3 trimiddle,npos;
    for(int i = 0;i<len;i++)
    {
        tri =  objList[i].tri;
        col = objList[i].collider;
        trimiddle = {
            (tri->vertex[0].x + tri->vertex[1].x + tri->vertex[2].x) / 3, 
            (tri->vertex[0].y + tri->vertex[1].y + tri->vertex[2].y) / 3,
            (tri->vertex[0].z + tri->vertex[1].z + tri->vertex[2].z) / 3 }; //삼각형의 무게중심
        npos = pos - trimiddle;
        while(tri != nullptr)
        {
            nv = tri->nv;
            d = (nv.x * pos.x + nv.y * pos.y +nv.z * pos.z) ;
                /// sqrt(nv.x * nv.x + nv.y * nv.y + nv.z * nv.z); //점과 평면사이의 거리
            if(d<col.pixel) return true;
            tri = tri->next;
        }
    }
    return false;
}
#endif