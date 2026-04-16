#include "interface/i_video.h"
#include "interface/mixer_sound.h"
#include "interface/i_system.h"
#include "states.h"
#include "g_game.h"
#include "v_video.h"

int kbz1[20*26] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,
    0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,2,2,2,
    0,0,0,0,0,0,0,0,3,3,3,2,2,2,2,0,0,2,2,2,
    0,0,0,0,0,0,0,0,3,3,3,2,2,2,2,0,0,2,2,2,
    1,1,1,1,1,0,0,0,0,0,0,2,2,2,2,0,0,2,2,2,
    3,3,3,3,3,0,0,0,0,0,0,2,2,2,2,0,0,2,2,2,
    3,3,3,3,3,0,0,0,0,0,0,2,2,2,2,0,0,2,2,2,
    0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,0,0,2,2,2,
    0,0,0,0,0,0,0,3,3,3,3,2,2,2,2,0,0,2,2,2,
    1,1,1,1,0,0,0,3,3,3,3,2,2,2,2,0,0,0,0,0,
    2,2,2,2,1,1,0,3,3,3,3,2,2,2,2,0,0,0,0,0,
    2,2,2,2,2,2,0,0,0,0,0,2,2,2,2,0,0,0,0,0,
    2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,1,1,1,1,1,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
    2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
};

int kbz1layer2[20*26] = { // todo: dont hardcode levels like this
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

#define TILE_SIZE 32
#define MAP_W 20
#define MAP_H 26

// tiles
static bitmap_t* tileGrass;
static bitmap_t* tileRock;
static bitmap_t* tileDirt;

void G_InitTiles(void)
{
    tileGrass   = I_LoadBitmap("assets/kbz/grass.bmp");
    tileRock    = I_LoadBitmap("assets/kbz/rock.bmp");
    tileDirt    = I_LoadBitmap("assets/kbz/dirt.bmp");
}

void G_LoadLevels(void) // temp! more like G_LoadKBZ1
{
    V_FillFramebuffer(0xFF00FFFF); // sky?

    for (int y = 0; y < MAP_H; y++)
    {
        for (int x = 0; x < MAP_W; x++)
        {
            int tile = kbz1[y * MAP_W + x];

            int screenX = x * TILE_SIZE;
            int screenY = y * TILE_SIZE;

            switch (tile)
            {
                case 0:
                    // air already exists
                    break;
                case 1:
                    V_DrawBitmap(tileGrass, screenX, screenY+(TILE_SIZE/2), 1);
                    break;
                case 2:
                    V_DrawBitmap(tileDirt, screenX, screenY, 1);
                    break;
                case 3:
                    V_DrawBitmap(tileDirt, screenX, screenY, 1);
                    break;
            }

            int tile2 = kbz1layer2[y * MAP_W + x];

            switch (tile2)
            {
                case 0:
                    // air already exists
                    break;
                case 1:
                    V_DrawBitmap(tileGrass, screenX, screenY+(TILE_SIZE/2), 1);
                    break;
                case 4:
                    V_DrawBitmap(tileRock, screenX, screenY+TILE_SIZE, 1);
                    break;
            }
        }
    }
}

int IsSolid(int tile)
{
    return tile != 0 && tile != 3;
}

int TileAt(int x, int y)
{
    int tx = x / TILE_SIZE;
    int ty = y / TILE_SIZE;

    if (tx < 0 || ty < 0 || tx >= MAP_W || ty >= MAP_H)
        return 1; // map boundaries

    return kbz1[ty * MAP_W + tx];
}

int mobjTouchesTile(mobj_t *mo)
{
    state_t *st = &states[mo->state];

    int left   = mo->x - st->width/2;
    int right  = mo->x + st->width/2;
    int top    = mo->y - st->height/2;
    int bottom = mo->y + st->height/2;

    return IsSolid(TileAt(left, top)) ||
           IsSolid(TileAt(right, top)) ||
           IsSolid(TileAt(left, bottom)) ||
           IsSolid(TileAt(right, bottom));
}

void G_MovePlayer(player_t *player)
{
    mobj_t *mo = player->mo;

    // x momentum (srb2 reference)
    mo->x += mo->momx;

    if (mobjTouchesTile(mo))
    {
        mo->x -= mo->momx;
        mo->momx = 0;
    }

    // y momentum
    mo->y += mo->momy;

    if (mobjTouchesTile(mo))
    {
        mo->y -= mo->momy;

        // if falling, we hit the ground
        if (mo->momy > 0)
            mo->onGround = true;

        mo->momy = 0;
    }
    else
    {
        mo->onGround = false;
    }
}

bitmap_t* idleAnim[6];
bitmap_t* walkAnim[4];
bitmap_t* jumpAnim[4];

void G_InitPlayerAnim(void)
{
    // idle
    idleAnim[0] = I_LoadBitmap("assets/sonic/stand_1.bmp");
    idleAnim[1] = I_LoadBitmap("assets/sonic/stand_2.bmp");
    idleAnim[2] = I_LoadBitmap("assets/sonic/stand_3.bmp");
    idleAnim[3] = I_LoadBitmap("assets/sonic/stand_4.bmp");
    idleAnim[4] = I_LoadBitmap("assets/sonic/stand_5.bmp");
    idleAnim[5] = I_LoadBitmap("assets/sonic/stand_6.bmp");

    // walk / run
    walkAnim[0] = I_LoadBitmap("assets/sonic/run_1.bmp");
    walkAnim[1] = I_LoadBitmap("assets/sonic/run_2.bmp");
    walkAnim[2] = I_LoadBitmap("assets/sonic/run_3.bmp");
    walkAnim[3] = I_LoadBitmap("assets/sonic/run_4.bmp");

    // jump / fall
    jumpAnim[0] = I_LoadBitmap("assets/sonic/jump_1.bmp");
    jumpAnim[1] = I_LoadBitmap("assets/sonic/jump_2.bmp");
    jumpAnim[2] = I_LoadBitmap("assets/sonic/jump_3.bmp");
    jumpAnim[3] = I_LoadBitmap("assets/sonic/jump_4.bmp");
}

void G_UpdateAnimation(player_t *player)
{
    mobj_t *mo = player->mo;
    state_t *st = &states[mo->state];

    mo->animTimer++;

    if (mo->animTimer >= st->animSpeed)
    {
        mo->animTimer = 0;
        mo->animFrame++;

        if (mo->animFrame >= st->frameCount)
            mo->animFrame = 0;
    }
}

void G_UpdatePlayer(player_t *player)
{
    mobj_t *mo = player->mo;

    if (I_KeyDown(KEY_LEFT))
        mo->momx -= ACCEL;

    if (I_KeyDown(KEY_RIGHT))
        mo->momx += ACCEL;

    if (mo->momx > MAX_SPEED) mo->momx = MAX_SPEED;
    if (mo->momx < -MAX_SPEED) mo->momx = -MAX_SPEED;

    if (I_KeyPressed(KEY_JUMP) && mo->onGround)
    {
        mo->momy = -20;
        I_PlaySFX(sfx_jump);
    }

    mo->momy += GRAVITY;

    // friction
    if (mo->momx > 0) mo->momx -= FRICTION;
    else if (mo->momx < 0) mo->momx += FRICTION;

    if (mo->momx > 0) mo->facing = 1;
    if (mo->momx < 0) mo->facing = -1;

    // update state
    int oldState = mo->state;

    if (mo->onGround && mo->momx == 0)
        mo->state = STATE_IDLE;
    else if (mo->onGround)
        mo->state = STATE_WALK;
    else if (!mo->onGround)
        mo->state = STATE_JUMP;

    if (mo->state != oldState)
    {
        mo->animFrame = 0;
        mo->animTimer = 0;
    }

    // movement and collision
    G_MovePlayer(player);
    G_UpdateAnimation(player);
}

void G_DrawPlayer(player_t *player)
{
    mobj_t *mo = player->mo;
    state_t *st = &states[mo->state];

    bitmap_t *frame = st->frames[mo->animFrame];

    int drawX = mo->x - st->width / 2;
    int drawY = mo->y - st->height / 2;

    V_DrawBitmap(frame, drawX, drawY, mo->facing == -1);
}
