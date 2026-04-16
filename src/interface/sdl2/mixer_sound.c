#include <SDL2/SDL_mixer.h>

#include "../i_system.h"
#include "../mixer_sound.h"

void I_StartupMusic(void)
{
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void I_PlaySong(const char *midi)
{
    Mix_Music* music = Mix_LoadMUS(midi);
    if (!music)
        I_Error("Failed to load MIDI: %s\n", Mix_GetError());
    Mix_PlayMusic(music, -1);
}

Mix_Chunk *sfx_jump;
Mix_Chunk *sfx_sighted;
Mix_Chunk *title_mus;

void I_InitSounds(void)
{
    sfx_jump = Mix_LoadWAV("assets/sfx/jump.wav");
    sfx_sighted = Mix_LoadWAV("assets/sfx/sighted.wav");
    title_mus = Mix_LoadWAV("assets/sfx/sontitle.wav");
}

void I_PlaySFX(Mix_Chunk *sfx)
{
    Mix_PlayChannel(-1, sfx, 0);
}

void I_StopSound(void)
{
    Mix_HaltChannel(-1);
}
