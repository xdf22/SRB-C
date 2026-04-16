#ifndef V_VIDEO_H
#define V_VIDEO_H

#include <stdint.h>

#define UINT32 uint32_t

typedef struct
{
    int w;
    int h;
    UINT32* pixels;
} bitmap_t;

void V_DrawPixel(int x, int y, UINT32 color);
void V_DrawBitmap(bitmap_t* tex, int x, int y, int flipX);
void V_FreeBitmap(bitmap_t* bmp);

void V_FillFramebuffer(UINT32 color);

extern bitmap_t *font, *font_italic;
void V_InitFonts(void);
void V_DrawString(bitmap_t *font, int x, int y, const char *text, int scale, UINT32 color);
void V_DrawStringCentered(bitmap_t *font, int y, const char *text, int scale, UINT32 color);

#endif
