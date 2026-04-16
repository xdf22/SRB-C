#include "srbdef.h"
#include "g_game.h"
#include "v_video.h"
#include "states.h"

state_t states[STATE_COUNT];

void S_InitStates(void)
{
    states[STATE_IDLE] = (state_t){
        idleAnim, // bitmap_t
        6,        // frames
        8,        // speed
        48, 50,   // hitbox
        2,        // gravity
        0,        // acceleration
        0         // maxspeed
    };

    states[STATE_WALK] = (state_t){
        walkAnim, // bitmap_t
        4,        // frames
        4,        // speed
        48, 50,   // hitbox
        2,        // gravity
        ACCEL,    // acceleration
        MAX_SPEED // maxspeed
    };

    states[STATE_JUMP] = (state_t){
        jumpAnim,   // bitmap_t
        4,          // frames
        10,         // speed
        48, 50,     // hitbox
        2,          // gravity
        ACCEL,      // acceleration
        MAX_SPEED   // maxspeed
    };
}