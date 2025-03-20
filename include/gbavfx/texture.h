#pragma once

#include "common.h"

typedef struct s_texture t_texture;

struct s_texture
{
    u8  pixel[64 * 64];       // offset: 0 ~ 4095 (4096 bytes)
}; // sizeof(t_texture) = 4096 bytes
