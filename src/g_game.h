void G_InitTiles(void);
void G_LoadLevels(void);

void G_InitPlayerAnim(void);
void G_UpdatePlayer(player_t *player);
void G_DrawPlayer(player_t *player);

#define ACCEL      2
#define MAX_SPEED  16
#define FRICTION   1
#define GRAVITY    2

extern bitmap_t* idleAnim[6];
extern bitmap_t* walkAnim[4];
extern bitmap_t* jumpAnim[4];