#pragma once
#include "common.h"

static inline i32 approach_i32(i32 current, i32 target, i32 inc, i32 dec) {
    //! If target is close to the max or min s32, then it's possible to overflow
    // past it without stopping.
    if (current < target) {
        current += inc;
        if (current > target) {
            current = target;
        }
    } else {
        current -= dec;
        if (current < target) {
            current = target;
        }
    }
    return current;
}