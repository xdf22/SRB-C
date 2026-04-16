#include <SDL2/SDL.h>

#include "../../srbdef.h"
#include "../i_video.h"
#include "../i_system.h"

// variables and definitions
UINT32 framebuffer[WIDTH * HEIGHT];

// main variables
SDL_Window* window;
SDL_Texture* screenTexture;
SDL_Renderer* renderer;

void I_StartupGraphics(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SONIC THE HEDGEHOG ROBO-BLAST!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480,  SDL_WINDOW_SHOWN);
    SDL_Surface* icon = SDL_LoadBMP("assets/icon.bmp");
    if (icon)
    {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }
    else
        I_Error("Icon not found\n");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    screenTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
}

void I_FinishUpdate(void)
{
    SDL_UpdateTexture(screenTexture, NULL, framebuffer, WIDTH * sizeof(UINT32));

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

bitmap_t* I_LoadBitmap(const char* path) // prepares a bitmap for use with V_DrawBitmap
{
    printf("Loading Bitmap: %s\n", path);
    SDL_Surface* surface = SDL_LoadBMP(path);
    if (!surface)
        I_Error("Bitmap not found, expected at: %s\n", path);

    SDL_Surface* converted = SDL_ConvertSurfaceFormat(
        surface,
        SDL_PIXELFORMAT_ARGB8888,
        0
    );
    SDL_FreeSurface(surface);

    bitmap_t* bitmap = malloc(sizeof(bitmap_t));
    bitmap->w = converted->w;
    bitmap->h = converted->h;
    bitmap->pixels = malloc(bitmap->w * bitmap->h * sizeof(UINT32));

    UINT32* src = (UINT32*)converted->pixels;
    int pitchPixels = converted->pitch / 4;

    for (int y = 0; y < bitmap->h; y++)
    {
        for (int x = 0; x < bitmap->w; x++)
        {
            bitmap->pixels[y * bitmap->w + x] = src[y * pitchPixels + x];
        }
    }

    SDL_FreeSurface(converted);

    return bitmap;
}
