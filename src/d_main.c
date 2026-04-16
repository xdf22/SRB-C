#include "interface/i_video.h"
#include "interface/mixer_sound.h"
#include "interface/i_system.h"
#include "d_main.h"
#include "m_menu.h"
#include "g_game.h"
#include "states.h"
#include "v_video.h"

void D_SRBMain(void)
{
    printf("I_StartupGraphics()...\n");
    I_StartupGraphics();
    printf("V_InitFonts()...\n");
    V_InitFonts();
    printf("I_StartupMusic()...\n");
    I_StartupMusic();
    printf("I_InitSounds()...\n");
    I_InitSounds();
    printf("G_InitTiles()...\n");
    G_InitTiles();
}

gamestate_t gamestate;
gamestate_t prev_gamestate;

player_t player_instance;
player_t *player = &player_instance;

bitmap_t* title_background;
bitmap_t* menu_selection;

bitmap_t* sonicthe;
bitmap_t* hedgehog;
bitmap_t* roboblast;

void D_SRBLoop(void)
{
    player->mo = malloc(sizeof(mobj_t));

    memset(player->mo, 0, sizeof(mobj_t)); // VERY IMPORTANT

    player->mo->width  = 48;
    player->mo->height = 48;
    player->mo->x = 10;
    player->mo->y = 10;
    player->mo->facing = 1;

    G_InitPlayerAnim();
    gamestate = GS_TITLESCREEN;
    prev_gamestate = -1;
    title_background = I_LoadBitmap("assets/title/bg.bmp");
    menu_selection = I_LoadBitmap("assets/menu/selection.bmp");
    sonicthe = I_LoadBitmap("assets/menu/sonicthe.bmp");
    hedgehog = I_LoadBitmap("assets/menu/hedgehog.bmp");
    roboblast = I_LoadBitmap("assets/menu/roboblast.bmp");

    boolean ticking = true;

    while (ticking)
    {
        I_InputUpdate();


        if (gamestate != prev_gamestate)
        {
            switch (gamestate)
            {
                case GS_TITLESCREEN:
                    I_StopSound();
                    I_PlaySFX(title_mus);
                    break;

                case GS_MENU:
                    I_StopSound();
                    I_PlaySong("assets/music/quartzja.mid");
                    break;

                case GS_LEVEL:
                    I_StopSound();
                    I_PlaySong("assets/music/electric.mid");
                    break;
            }

            prev_gamestate = gamestate;
        }

        switch (gamestate)
        {
            case GS_TITLESCREEN:
            {
                Title_Tick();
                break;
            }

            case GS_MENU:
            {
                Menu_Tick();
                break;
            }

            case GS_LEVEL:
            {
                G_Tick();
                break;
            }
        }

        I_FinishUpdate();
        SDL_Delay(16);
    }
}

void Title_Tick(void)
{
    // draw it
    for (int x=0; x < (640/32); x++)
    {
        for (int y=0; y < (480/32); y++)
            V_DrawBitmap(title_background, x*32, y*32, 0);
    }

    // oh god.
    V_DrawString(font_italic, 140, 0, "SONIC", 4, 0x0000FF);
    V_DrawString(font_italic, 170, 75, "T", 2, 0xBDB76B);
    V_DrawString(font_italic, 200, 68, "H", 1, 0xBDB76B);
    V_DrawString(font_italic, 227, 65, "E", 1, 0xBDB76B);
    V_DrawString(font_italic, 160, 105, "H", 1, 0x0000FF);
    V_DrawString(font_italic, 176, 105, "E", 3/2, 0x0000FF);
    V_DrawString(font_italic, 192, 95, "D", 2, 0x0000FF);
    V_DrawString(font_italic, 208, 95, "G", 5/2, 0x0000FF);
    V_DrawString(font_italic, 230, 95, "EHOG", 3, 0x0000FF);
    V_DrawString(font_italic, 160, 137, "Robo-Blast!", 2, 0xFF4500);

    V_DrawString(font_italic, 140, 464, "Press enter to begin!", 1, 0x000000);

    if (I_KeyPressed(KEY_JUMP))
    {
        gamestate = GS_MENU;
        V_FreeBitmap(title_background);
    }
}

int selected;

void Menu_Tick(void)
{
    if (!selected)
        selected=0;
    V_FillFramebuffer(0x000000); // clear screen

    V_DrawBitmap(sonicthe, 120, 16, 0);
    V_DrawBitmap(hedgehog, 245, 2, 0);
    V_DrawBitmap(roboblast, 375, 13, 0);

    V_DrawStringCentered(font, 80, "OPTIONS", 3/2, 0x008000);
    V_DrawStringCentered(font_italic, 400, "Press enter to pick an option", 3/2, 0x4169E1);

    // now draw menus
    for (int i = 0; i < mainmenu_count; i++)
        V_DrawStringCentered(font, 150+i*48, mainmenu[i].text, 3/2, 0xFFFF00);

    V_DrawBitmap(menu_selection, 100, 150+selected*48, 0);

    if (I_KeyDown(KEY_DOWN))
    {
        selected++;
        I_PlaySFX(sfx_sighted);
    }
    if (selected >= mainmenu_count)
    {
        selected=0;
        I_PlaySFX(sfx_sighted);
    }
    if (I_KeyDown(KEY_UP))
    {
        selected--;
        I_PlaySFX(sfx_sighted);
    }
    if (selected < 0)
    {
        selected=mainmenu_count;
        I_PlaySFX(sfx_sighted);
    }

    if (I_KeyDown(KEY_JUMP))
    {
        mainmenu[selected].action();
    }
}

void G_Tick(void)
{
    S_InitStates();
    G_UpdatePlayer(player);
    G_LoadLevels();
    G_DrawPlayer(player);
}
