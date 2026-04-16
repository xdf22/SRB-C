#ifndef SRBDEF_H
#define SRBDEF_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stddef.h>

#include "states.h"

#ifdef LINUX
#define boolean bool
#endif

// doomtype.h moment
#define UINT32 uint32_t
#define UINT16 uint16_t
#define UINT8 uint8_t
#define UINT uint_t
#define INT8 int8_t
#define INT16 int16_t
#define INT32 int32_t

// structs
typedef struct
{
    int x, y;
    int momx, momy;
    int width, height;
    int animFrame;
    int animTimer;

    boolean onGround;
    int facing;
    state_e state;
    char *type;
} mobj_t;

typedef struct
{
    int lives;
    int state;
    mobj_t* mo;
} player_t;

typedef enum
{
    GS_TITLESCREEN,
    GS_MENU,
    GS_LEVEL
} gamestate_t;

#endif
