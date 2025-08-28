
#include "SDL.h"
#include "gui.h"
#include "cmd.h"

void wx_draw_soft_command(widget_info *data);
void wx_fx_mouse_button_down_soft_command(widget_info *wx_info);


#define SOFT_COMMAND_W 200
#define SOFT_COMMAND_H 800

widget wx_soft_command_create(int x, int y)
{
    widget soft_command_window;

    soft_command_window.data.rect.x = x;
    soft_command_window.data.rect.y = y;

    soft_command_window.fx.fx_draw = wx_draw_soft_command;
    soft_command_window.fx.fx_mouse_button_down = wx_fx_mouse_button_down_soft_command;
    soft_command_window.fx.fx_update = wx_fx_none;
    soft_command_window.fx.fx_mouse_motion = wx_check_bounds;
    soft_command_window.fx.fx_keypressed = wx_fx_none;

    return soft_command_window; 

}

void wx_draw_soft_command(widget_info *wx_info)
{
    SDL_Rect bg_rect;

    int border_color = COLOR_PRIMARY;

    // Scope Rectangle
    wx_w(wx_info) = SOFT_COMMAND_W;
    wx_h(wx_info) = SOFT_COMMAND_H;

    bg_rect.x = wx_x(wx_info) - 1;
    bg_rect.y = wx_y(wx_info) - 1;
    bg_rect.w = wx_w(wx_info) + 2;
    bg_rect.h = wx_h(wx_info) + 2;

    if (wx_check_bounds(wx_info) )
    
        border_color = COLOR_SECONDARY;
        

    SDL_SetRenderDrawColor(renderer, red_mask(border_color), green_mask(border_color), blue_mask(border_color), SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &bg_rect);

    SDL_SetRenderDrawColor(renderer, red_mask(COLOR_BLACK), green_mask(COLOR_BLACK), blue_mask(COLOR_BLACK), SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &wx_info->rect);
}


void wx_fx_mouse_button_down_soft_command(widget_info *wx_info)
{

}
