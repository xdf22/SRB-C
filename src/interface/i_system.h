#ifndef I_SYSTEM_H
#define I_SYSTEM_H

void I_Error(const char *errorMsg, ...);

typedef enum
{
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_JUMP,
    KEY_SHIFT,

    NUM_KEYS
} keys_t;

void I_InputInit(void);
void I_InputUpdate(void);

int I_KeyDown(keys_t key);
int I_KeyPressed(keys_t key);
int I_KeyReleased(keys_t key);

#endif
