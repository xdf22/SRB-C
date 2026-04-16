// main drawing functions

#include "interface/i_video.h"
#include "srbdef.h"
#include "v_video.h"

void V_DrawPixel(int x, int y, UINT32 color)
{
    if ((unsigned)x >= WIDTH || (unsigned)y >= HEIGHT)
        return;

    framebuffer[y * WIDTH + x] = color;
}

void V_DrawBitmap(bitmap_t* tex, int x, int y, int flipX)
{
    for (int textureY = 0; textureY < tex->h; textureY++)
    {
        for (int textureX = 0; textureX < tex->w; textureX++)
        {
            int srcX = flipX ? (tex->w - 1 - textureX) : textureX;
            UINT32 color = tex->pixels[textureY * tex->w + srcX];

            if (color == 0xFF00FF00) // pure GREEN
                continue;

            V_DrawPixel(x + textureX, y + textureY, color);
        }
    }
}

void V_FreeBitmap(bitmap_t* bmp) // KILLS the bitmap from memory
{
    if (!bmp) return;

    free(bmp->pixels);
    free(bmp);
}

void V_FillFramebuffer(UINT32 color)
{
    for (int i = 0; i < WIDTH * HEIGHT; i++)
        framebuffer[i] = color;
}

bitmap_t *font, *font_italic;

void V_InitFonts(void)
{
    font = I_LoadBitmap("assets/fonts/arial.bmp");
    font_italic = I_LoadBitmap("assets/fonts/arial_italic.bmp");
}

#define FONT_COLS (font->w / 16)

void V_DrawChar(bitmap_t *font, int x, int y, char c, int scale, UINT32 color)
{
    if (c < 32 || c > 126) return;

    int index = c - 32;

    int sx = (index % 19) * 16;
    int sy = (index / 19) * 16;

    for (int ty = 0; ty < 16; ty++)
    {
        for (int tx = 0; tx < 16; tx++)
        {
            UINT32 col = font->pixels[(sy + ty) * font->w + (sx + tx)];

            if (col == 0xFF00FF00) // pure GREEN
                continue;

            for (int syy = 0; syy < scale; syy++)
            {
                for (int sxx = 0; sxx < scale; sxx++)
                    V_DrawPixel(x + tx * scale + sxx, y + ty * scale + syy, color);
            }
        }
    }
}

void V_DrawString(bitmap_t *font, int x, int y, const char *text, int scale, UINT32 color)
{
    int cx = x;

    while (*text)
    {
        if (*text == '\n')
        {
            y += 16 * scale;
            cx = x;
            text++;
            continue;
        }

        V_DrawChar(font, cx, y, *text, scale, color);

        cx += (16 * scale)-4;

        text++;
    }
}

int getStringWidth(const char *text, int scale)
{
    return strlen(text) * (16 * scale)-4;
}

void V_DrawStringCentered(bitmap_t *font, int y, const char *text, int scale, UINT32 color)
{
    int w = getStringWidth(text, scale);
    int x = (640 - w) / 2;

    V_DrawString(font, x, y, text, scale, color);
}

