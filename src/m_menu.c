// basic as hell menu system, better than manually drawing everything tho lol
// definition: {"option-name", callbackmenutable, callbackfunction}
// if callbackmenu is NULL, callbackfunction will be used and vice verca

#include "srbdef.h"
#include "d_main.h"
#include "m_menu.h"
#include <stddef.h>

void temp(void) // as you can see, this is temporary
{
    gamestate = GS_LEVEL;
}

menuitem_t mainmenu[] =
{
    {"START GAME", NULL, temp},
    {"DIFFICULTY SELECT", NULL, NULL},
    {"TRAINING MODE", NULL, NULL},
    {"MULTIPLAYER", NULL, NULL},
};

int mainmenu_count = sizeof(mainmenu) / sizeof(mainmenu[0]);
