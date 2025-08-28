#include <stdio.h>
#include <stdlib.h>

#include "gui.h"


// Format of .srf files (addressed by bytes):
// [Number of Characters]                     [0] 
// [Font Height]                              [1]
// Total Width of all characters in the font  [2-3]
// Character Pixels                           [4 - ...]


FONT* load_font(char *filename)
{
    int c, ch, h, total_width, a;
    int i, x, y, ct;
    short *p;
    char *w;
    FONT *font;
    SDL_Texture *bitmap;
    FILE *fp;

    if ((font = malloc(sizeof(FONT))) == NULL)
    {
        printf("Malloc Failed in function: %s()\n", __func__);
        return NULL;
    }

    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("Failed to load font in function: %s()\n", __func__);
        return NULL;
    }

    ch = getc(fp);
    h = getc(fp);
    total_width = getc(fp) << 8;
    total_width |= getc(fp);

    if (ch != 96)
    {
        fclose(fp);
        printf("load font - bad character count\n");
        return NULL;
    }

    font->h = h;
    p = font->p;
    w = font->w;
    a = 0;

    for (i=0; i<96; i++)
    {
        c = getc(fp);
        w[i] = c;
        p[i] = a;
        a += c;
    }

    bitmap = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, total_width, h);
    font->bm = bitmap;

    // Set transparent backround
    SDL_SetRenderTarget(renderer, bitmap);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetTextureBlendMode(bitmap, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    x = 0; 
    y = 0; 
    ct = 0;
    c = getc(fp);

    while(x < total_width)
    {
        if (c & 1)
            SDL_RenderDrawPoint(renderer, x, y);

        if (++y >= h)
        {
            x++;
            y = 0;
        }

        if (++ct > 7)
        {
            c = getc(fp);
            ct = 0;
        }

        else
            c >>= 1;
    }

    SDL_SetRenderTarget(renderer, NULL);

    fclose(fp);
    
    return font;

}



// void write_text(FONT *font, char *s, int x, int y, int fgc)
void write_text(char *s, int x, int y, int fgc)
{
  char *wd;
  short *pd;
  int i, c, w;
  SDL_Color tclr;
  SDL_Rect r, sr, dr;
  
  FONT *font = font_srf;

  
  SDL_SetRenderTarget(renderer, NULL);
  SDL_SetTextureColorMod(font->bm, red_mask(fgc), blue_mask(fgc), green_mask(fgc));
  pd = font->p;
  wd = font->w;
  
  sr.y = 0;
  sr.h = font->h;
  dr.x = x;
  dr.y = y;
  dr.h = font->h;
  i = 0;

  while( (c=(s[i] - 32)) >= 0)
  {
    w = wd[c];
    sr.x = pd[c];
    sr.w = w;
    dr.w = w;
    SDL_RenderCopy(renderer, font->bm, &sr, &dr);
    dr.x += w;
    i++;
  }
}