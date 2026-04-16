#include <SDL2/SDL.h>
#include <SDL2/SDL_messagebox.h>

#include "../i_video.h"
#include "../i_system.h"

static int keyDown[NUM_KEYS];
static int keyPressed[NUM_KEYS];
static int keyReleased[NUM_KEYS];

void I_Error(const char *errorMsg, ...)
{
    char buffer[8192];

    va_list args;
	va_start(args, errorMsg);
	vsprintf(buffer, errorMsg, args);
	va_end(args);

    printf("I_Error: %s\n", buffer);

    SDL_Quit();
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SRB Error", buffer, window);

    exit(-1);
}

static int SDLKeyToGameKey(SDL_Scancode scancode)
{
    switch (scancode)
    {
        case SDL_SCANCODE_LEFT:  return KEY_LEFT;
        case SDL_SCANCODE_RIGHT: return KEY_RIGHT;
        case SDL_SCANCODE_UP:    return KEY_UP;
        case SDL_SCANCODE_DOWN:  return KEY_DOWN;
        case SDL_SCANCODE_SPACE: return KEY_JUMP;
    }

    return -1;
}

void I_InputUpdate(void)
{
    SDL_Event event;

    for (int i = 0; i < NUM_KEYS; i++)
    {
        keyPressed[i] = 0;
        keyReleased[i] = 0;
    }

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            exit(0);
        }

        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            int key = SDLKeyToGameKey(event.key.keysym.scancode);

            if (key != -1)
            {
                if (event.type == SDL_KEYDOWN)
                {
                    if (!keyDown[key])
                        keyPressed[key] = 1;

                    keyDown[key] = 1;
                }
                else
                {
                    keyDown[key] = 0;
                    keyReleased[key] = 1;
                }
            }
        }
    }
}

int I_KeyDown(keys_t key)
{
    return keyDown[key];
}

int I_KeyPressed(keys_t key)
{
    return keyPressed[key];
}

int I_KeyReleased(keys_t key)
{
    return keyReleased[key];
}
