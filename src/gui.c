
#include "SDL.h"
#include "gui.h"
#include "SDL_ttf.h"
#include <stdlib.h>
#include <stdio.h>


#define WINDOW_W 1640
#define WINDOW_H 920

int gui_init()
{

    SDL_Init(SDL_INIT_VIDEO);
  
    //Create Window and Renderer
    window = SDL_CreateWindow("PACMAN ET Diagnostic", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W , WINDOW_H, SDL_WINDOW_BORDERLESS);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, 0, 1, 1);

    SDL_SetRenderDrawColor(renderer, red_mask(COLOR_BACKGROUND), green_mask(COLOR_BACKGROUND), blue_mask(COLOR_BACKGROUND), SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    /* Initialize Font Stuff */
    TTF_Init();
    font_srf = load_font("fonts/cw7x13.srf");

    font = TTF_OpenFont("fonts/courier_prime/CourierPrime-Regular.ttf", 14);
    TTF_SizeText(font, "a", &font_w, &font_h);
    font_big = TTF_OpenFont("fonts/courier_prime/CourierPrime-Regular.ttf", 32);
    
    font_color_normal.r = 255;
    font_color_normal.g = 255;
    font_color_normal.b = 255;

    widget_queue_size = 0;

    return 0;
}


void gui_add_widget_queue(widget wx)
{
    widget_queue[widget_queue_size] = wx;
    widget_queue_size++;
}

void gui_destroy_widget_queue()
{
    widget *wx;
    
    for (int i=0; i<widget_queue_size; i++)
    {
        wx = &widget_queue[i];
        wx->fx.fx_mouse_motion(&wx->data);
    }
    
    widget_queue_size = 0;

}


int gui_update()
{
    widget *wx;
    
    SDL_PollEvent(&event);
    
    if (event.type == SDL_MOUSEMOTION)
    {
        mouse_x = event.button.x;
        mouse_y = event.button.y;
    }
    
    if (event.type == SDL_KEYDOWN)
    {
        key_char = event.key.keysym.sym;
        key_mod = event.key.keysym.mod;

        // Ctl-Q: quit 
        if (key_mod & KMOD_CTRL)
            if (key_char == 'q')
                exit(1);

        // Escape
        if (key_char == SDLK_ESCAPE)
            for (int i=0; i<widget_queue_size; i++)
                widget_queue[i].data.selected = 0;

    }

    // Clear the screen every time. Painful but safe.
    SDL_SetRenderDrawColor(renderer, red_mask(COLOR_BACKGROUND), green_mask(COLOR_BACKGROUND), blue_mask(COLOR_BACKGROUND), SDL_ALPHA_OPAQUE);

    SDL_RenderClear(renderer);

    // Print Mouse Coordinates
    char mouse_coord[80];
    int w, h;
    sprintf(mouse_coord, "%5d %5d %5d %5d", mouse_x, mouse_y, wx_mouse_x, wx_mouse_y);
    SDL_GetWindowSize(window, &w, &h);
    
    write_text(mouse_coord, 0, WINDOW_H - font_srf->h-5, COLOR_WHITE);

    for (int i=0; i<widget_queue_size; i++)
    {
        wx = &widget_queue[i];

        wx->fx.fx_update(&wx->data);
        wx->fx.fx_draw(&wx->data);
        wx->fx.fx_mouse_motion(&wx->data);
        wx->fx.fx_mouse_button_down(&wx->data);
        wx->fx.fx_keypressed(&wx->data);
    }
    
    SDL_RenderPresent(renderer);

}

void gui_write_text(int x, int y, int *w, int *h, char *text, int color)
{
    SDL_Rect rect;
    SDL_Color text_color;
    SDL_Surface *s;
    SDL_Texture *texture;
    int text_width, text_height;

    if (*text == '\0')  // empty text
        return;  
    
    text_color.r = red_mask(color);
    text_color.g = green_mask(color);
    text_color.b = blue_mask(color);


    /*  THIS LINE CAUSES SEGFAULT  */
    s = TTF_RenderText_Solid(font, text, text_color);  
    /*******************************/

    texture = SDL_CreateTextureFromSurface(renderer, s);
    
    
    text_width = s->w;
    text_height = s->h;
    
    SDL_FreeSurface(s);
    
    rect.x = x;
    rect.y = y;
    rect.w = text_width;
    rect.h = text_height;

    if (w != NULL) 
        *w = text_width;
    
    if (h != NULL) 
        *h = text_height;
    
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);

}


int gui_close()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

