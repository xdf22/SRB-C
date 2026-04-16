#ifndef M_MENU_H
#define M_MENU_H

#include <stddef.h>

typedef void (*menuaction_t)(void);

typedef struct menuitem_s
{
    const char *text;
    void (*submenu)(void);
    void (*action)(void);
} menuitem_t;

extern menuitem_t mainmenu[];
extern int mainmenu_count;

#endif