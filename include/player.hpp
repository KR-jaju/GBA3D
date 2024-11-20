#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "MeshTMP.hpp"
#include "vec3.hpp"

class player
{
    public:
    MeshTMP mesh;
    vec3 position;
    vec3 velocity;
    f32 friction;
    void move(vec3 pos) {position = pos;}
};



#endif