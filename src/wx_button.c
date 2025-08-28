#include "gui.h"
#include "SDL.h"



void wx_button_draw(widget_info *wx_info);
void wx_button_update(widget_info *wx_info);


widget wx_button_create(int x, int y, char *text)
{

    widget button;

    button.data.rect.x = x;
    button.data.rect.y = y;
    button.data.rect.w = 15;
    button.data.rect.h = 15;

    button.fx.fx_update = wx_button_update;
    button.fx.fx_draw = wx_button_draw;
    button.fx.fx_keypressed = wx_fx_none;
    button.fx.fx_mouse_motion = wx_fx_none_int;
    button.fx.fx_mouse_button_down = wx_fx_none;

    wx_button_draw(&button.data);
    
    return button;

}



void wx_button_draw(widget_info *wx_info)
{

    SDL_Rect fg_rect;

    fg_rect.x = wx_info->rect.x + 1;
    fg_rect.y = wx_info->rect.y + 1;
    fg_rect.w = wx_info->rect.w - 1;
    fg_rect.h = wx_info->rect.h - 1;

    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &wx_info->rect);
    SDL_SetRenderDrawColor(renderer, (COLOR_FOREGROUND>>16) & 0xff, (COLOR_FOREGROUND>>8) & 0xff, COLOR_FOREGROUND & 0xff, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &fg_rect);
    
}


void wx_button_update(widget_info *wx_info)
{

}
