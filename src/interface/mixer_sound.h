#include <SDL2/SDL_mixer.h>

void I_StartupMusic(void);
void I_PlaySong(const char *midi);

extern Mix_Chunk *sfx_jump;
extern Mix_Chunk *sfx_sighted;
extern Mix_Chunk *title_mus;

void I_InitSounds(void);
void I_PlaySFX(Mix_Chunk *sfx);
void I_StopSound(void);