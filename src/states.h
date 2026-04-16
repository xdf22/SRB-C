#ifndef STATES_H
#define STATES_H

#include "v_video.h"

typedef enum
{
    STATE_IDLE,
    STATE_WALK,
    STATE_JUMP,
    STATE_COUNT
} state_e;

typedef struct
{
    bitmap_t **frames;
    int frameCount;
    int animSpeed;
    int width;
    int height;
    int gravity;
    int accel;
    int maxSpeed;
} state_t;

extern state_t states[STATE_COUNT];

void S_InitStates(void);

#endif
