
#include "gui.h"
#include "SDL.h"
#include "pacman_uut.h"
#include <stdlib.h>
#include <stdio.h>
#include "pacman.h"

int adc_trace[800];

#define POWER_MON_W 100
#define POWER_MON_H 100

#define SCOPE_CONTROL_W 200
#define SCOPE_CONTROL_H 250

#define MEM_F0 0   // Memory Field 0: Bit Mask for Channels Enabled (Uint8)

void wx_draw_power_mon(widget_info *wx_info);


widget wx_create_power_mon(int x, int y)
{
    widget power_mon;

    power_mon.data.rect.x = x;
    power_mon.data.rect.y = y;

    power_mon.data.selected = 0;
    
    power_mon.fx.fx_update = wx_fx_none;
    power_mon.fx.fx_draw = wx_draw_power_mon;
    power_mon.fx.fx_mouse_motion = wx_check_bounds;
    power_mon.fx.fx_keypressed = wx_fx_none;
    power_mon.fx.fx_mouse_button_down = wx_fx_none;
    
    
    return power_mon; 

}


void wx_draw_power_mon(widget_info *wx_info)
{

    SDL_Rect power_mon_bg_rect, power_mon_fg_rect;

    widget_info temp_wx_info;

    int opt_x, opt_y, opt_w, opt_h;
    
    int border_color = COLOR_PRIMARY;
    
    // Power Monitor Rectangle
    power_mon_fg_rect.x = wx_info->rect.x;
    power_mon_fg_rect.y = wx_info->rect.y;
    power_mon_fg_rect.w = POWER_MON_W;
    power_mon_fg_rect.h = POWER_MON_H;

    power_mon_bg_rect.x = power_mon_fg_rect.x - 1;
    power_mon_bg_rect.y = power_mon_fg_rect.y - 1;
    power_mon_bg_rect.w = power_mon_fg_rect.w + 2;
    power_mon_bg_rect.h = power_mon_fg_rect.h + 2;
    
    temp_wx_info.rect = power_mon_fg_rect;
    if (wx_check_bounds(&temp_wx_info) )
        border_color = COLOR_SECONDARY;

    SDL_SetRenderDrawColor(renderer, red_mask(border_color), green_mask(border_color), blue_mask(border_color), SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &power_mon_bg_rect);

    SDL_SetRenderDrawColor(renderer, red_mask(0), green_mask(0), blue_mask(0), SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &power_mon_fg_rect);

    gui_write_text(temp_wx_info.rect.x, temp_wx_info.rect.y, &temp_wx_info.rect.w, &temp_wx_info.rect.h, "a", COLOR_WHITE);

}



void wx_fx_mouse_button_down_power_mon(widget_info *wx_info)
{
    wx_fx_mouse_button_down_select(wx_info);
}

