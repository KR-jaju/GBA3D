#include "GBAinput.hpp"
#include "Mesh.hpp"
#include "player.hpp"

object ObjPool[20];
player mario;
int objlen= 0;
int moveObjlen = 0;

fixed calculateDeltaTime(int fps) {
    return fixed(1) / fixed(fps);
}

