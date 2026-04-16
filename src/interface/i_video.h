#include <SDL2/SDL.h>

#include "../srbdef.h"

#define WIDTH  640
#define HEIGHT 480

extern UINT32 framebuffer[WIDTH * HEIGHT];

extern SDL_Window* window;
extern SDL_Renderer* renderer;

void I_StartupGraphics(void);
void I_GetEvents(boolean* running);
void I_FinishUpdate(void);

bitmap_t* I_LoadBitmap(const char* path);