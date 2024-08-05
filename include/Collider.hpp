#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "vec3.hpp"
#include "fixed.hpp"
#include "object.hpp"
#include "player.hpp"
#include "math.hpp"
// type
// 0 -> Non
// 1 -> wall
// 2 -> ground
// 3 -> ceil

struct Collider
{
    u16 type;
    fixed push[4] = {0, fixed(20), 0, fixed(20)};
    fixed pixel[4] = {0, fixed(10), 0, fixed(10)};
};

struct Rigid
{
    vec3 weight;
    vec3 velocity;
    vec3 accel;
};

void colliderTypeManager(object objList[], int len)
{
    for (int i = 0; i < len; i++)
    {
        Triangle *tri = objList[i].tri;
        while (tri != nullptr)
        {
            if (fixed(0) <= tri->nv.y && tri->nv.y <= fixed(0)) // wall
            {
                tri->collider.type = 1;
            }
            else if (fixed(0) <= tri->nv.y && tri->nv.y <= fixed(0)) // ground
            {
                tri->collider.type = 2;
            }
            else if (fixed(0) <= tri->nv.y && tri->nv.y <= fixed(0)) // ceil
            {
                tri->collider.type = 3;
            }
        }
    }
}



bool trianglePrismTest(vec3 point, Triangle *tri, fixed pixel)
{
    vec3 p0 = {tri->vertex[0].x, tri->vertex[0].y, tri->vertex[0].z}; // 기준
    vec3 p1 = {tri->vertex[1].x, tri->vertex[1].y, tri->vertex[1].z};
    vec3 p2 = {tri->vertex[2].x, tri->vertex[2].y, tri->vertex[2].z};

    vec3 V = point - p0; // 기준점과 마리오 점 사이의 벡터

    vec3 d0 = normalize(cross(tri->nv, (p1 - p0))); // 모서리의 법선벡터들
    vec3 d1 = normalize(cross(tri->nv, (p2 - p0)));
    vec3 d2 = normalize(cross(tri->nv, (p2 - p1)));

    fixed L = length(cross((p0 - p1), (p2 - p1))) / length(p2 - p1); // 기준점과 맞은편 모서리와의 거리

    if (dot(V, d0) <= pixel || dot(V, d1) <= pixel || (dot(V, d2) - L) <= pixel)
        return true;
    else
        return false;
}

bool normalTest(vec3 point, Triangle *tri, fixed pixel)
{
    vec3 p0 = {tri->vertex[0].x, tri->vertex[0].y, tri->vertex[0].z};
    vec3 V = point - p0;
    if (dot(V, tri->nv) <= pixel)
        return true;
    else
        return false;
}

// 1 -> wall
// 2 -> ground
// 3 -> ceil
void crashProcess(player &mario, Triangle &tri)
{
    int type = tri.collider.type;
    vec3 V = tri.nv;
    switch(type)
    {
        case 1: //wall
            mario.wall = true;
            mario.applyForce(V * tri.collider.push[type]);
        break;
        case 2: //ground
            mario.onGround = true;
            mario.jumped = false;
            mario.applyForce(V * tri.collider.push[type]);
            break;
        case 3: //ceil
            mario.applyForce(V * tri.collider.push[type]);
            break;
    }

}
// 충돌확인
bool checkCollision(player &mario, object objList[], int len)
{
    Triangle *tri;
    Collider col;
    vec3 pos = mario.position; // 현재 마리오 좌표
    for (int i = 0; i < len; i++)
    {
        tri = objList[i].tri;
        while(tri->next != nullptr)
        {
            col = tri->collider;
            if(trianglePrismTest(pos,tri,col.pixel[col.type]) && normalTest(pos,tri,col.pixel[col.type]))
            return true; //처리함수 필요
            tri = tri->next;
        }
        
    }
    return false;
}
#endif