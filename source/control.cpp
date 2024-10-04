#include "control.hpp"
#include "collideModel.hpp"

control::control()
{

    force = vec3::zero();
    moveTMP = vec3::zero();
    runSpeed = fixed(30);
    walkSpeed = fixed(15);
    jumpForce = fixed(25);
    gravity = fixed(-15);
    maxFallSpeed = fixed(-30);
    distance = fixed(0);

    jumped = false;

    floorOP =fixed(0.5f);
    wallOP = fixed(0.5f);
    ceilOP = fixed(0.5f);

    clickJump = false;
}

void control::polygonInit()
{
    mario.mesh = playerOBJ;
    obj[0].mesh = wallOBJ;
    obj[1].mesh = floorOBJ;

    for(int i = 0;i<objLen;i++)
    {
        object& tobj = obj[i];
        for(int j = 0;j<tobj.mesh.indexLen;j++)
        {
            Polygon poly;
            vec3 A = tobj.mesh.vertex[tobj.mesh.index[i]];
            vec3 B = tobj.mesh.vertex[tobj.mesh.index[i+1]];
            vec3 C = tobj.mesh.vertex[tobj.mesh.index[i+2]];
            poly.A = A;
            poly.B = B;
            poly.C = C;
            poly.N = normalize(cross(A - B, B - C));
            poly.edge0 = normalize(cross(B - A, poly.N));
            poly.edge1 = normalize(cross(C - B, poly.N));
            poly.edge2 = normalize(cross(A - C, poly.N));
            poly.L = length(normalize(cross(A - B, C - B)));
            fixed d = dot(poly.N, vec3::UP());
            poly.dot = d;
            if (d > 0.3f)
            {
                floor[floorLen] = poly;
                floorLen++;
            }
            else if (d < -0.3f)
            {
                ceil[ceilLen] = poly;
                ceilLen++;
            }
            else
            {
                wall[wallLen] = poly;
                wallLen++;
            }
        }
    }
        
}

void control::playerControll()
{
    updateDeltaTime(targetFPS);
    moveTMP = vec3::zero();
    fixed currentMoveSpeed = key_held(KEY_B) ? runSpeed : walkSpeed;
    key_poll();
    if(key_held(KEY_UP)) moveTMP = moveTMP + vec3::FRONT();
    if(key_held(KEY_DOWN)) moveTMP = moveTMP + vec3::BACK();
    if(key_held(KEY_RIGHT)) moveTMP = moveTMP + vec3::RIGHT();
    if(key_held(KEY_LEFT)) moveTMP = moveTMP + vec3::LEFT();
    moveTMP = moveTMP * currentMoveSpeed * deltaTime;

    if (!touchStatus[2])
    {
        force.y += gravity * deltaTime;
        force.y = max(force.y, maxFallSpeed);
    }
    else
    {
        force.y = 0;
        if (clickJump && !jumped)
        {
            clickJump = false;
            touchStatus[2] = false;
            jumped = true;
            force.y = jumpForce;
        }
    }
}



bool control::trianglePrismTest(Polygon tri, vec3 pos)
{
    vec3 V = pos - tri.A;
    float OP = 0.1f;
    if (dot(V, tri.edge0) < OP && dot(V, tri.edge2) < OP && (dot(V, tri.edge1) - tri.L) < OP)
    {
        return true;
    }
    else
        return false;
}

bool control::normalTest(Polygon tri, vec3 pos, vec3 axis, fixed OP)
{
    vec3 V = pos - tri.A;
    fixed height = dot(tri.N, V);
    fixed hypot = dot(tri.N, axis);
    distance = height / hypot;
    if (height <= OP && height >= 0.0f)
    {
        return true;
    }
    else
        return false;
}

void control::wallcheck(vec3& pos)
{
    for(int i = 0;i<wallLen;i++)
    {
        vec3 axis = ceil[i].N;
        axis.y = 0;
        axis = normalize(axis);
        if(normalTest(ceil[i],pos,axis,wallOP) && trianglePrismTest(ceil[i],pos))
        {
            if(distance <wallOP)
            {
                pos = pos + axis * (wallOP - distance);
            }
        }
    }
}

bool control::floorcheck(vec3& pos)
{
    vec3 axis = vec3::UP();
    bool flag = false;
    for(int i = 0;i<floorLen;i++)
    {
        if (normalTest(ceil[i], pos, axis, floorOP) && trianglePrismTest(ceil[i], pos))
        {
            if (distance < floorOP)
            {
                pos = pos + axis * (floorOP - distance);
                flag = true;
            }
        }
    }
    return flag;
}

bool control::ceilcheck(vec3& pos)
{
    vec3 axis = vec3::DOWN();
    for(int i = 0;i<ceilLen;i++)
    {
        if (normalTest(ceil[i], pos, axis, ceilOP) && trianglePrismTest(ceil[i], pos))
        {
            if (distance < ceilOP)
            {
                return true;
            }
        }
    }
    return false;
}

void control::checkCollision()
{
    vec3 npos = mario.position + moveTMP + force * deltaTime;

    wallcheck(npos);
    if (floorcheck(npos))
    {
        jumped = false;
        touchStatus[2] = true;
    }
    else touchStatus[2] = false;

    if(ceilcheck(npos))
    {
        force.y = 0;
        return;
    }
    mario.position = npos;
}