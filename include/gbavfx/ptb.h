#pragma once

#include "common.h"

typedef struct s_ptb t_ptb;

struct s_ptb
{
    u16  vertex_top_offset;        // 0x0000 ~ 0x0001 (2 bytes)
    u16  face_top_offset;          // 0x0002 ~ 0x0003 (2 bytes)
    u32  vertex[2048];        // 0x0004 ~ 0x2003 (8192 bytes)
    u32  face[2048];          // 0x2004 ~ 0x4003 (8192 bytes)
    u16  ordering_table[768]; // 0x4004 ~ 0x4603 (1536 bytes)
}; // sizeof(s_ptb) = 17924 bytes
