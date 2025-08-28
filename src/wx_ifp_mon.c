
#include "gui.h"
#include "SDL.h"
#include "pacman_uut.h"
#include <stdlib.h>
#include <stdio.h>
#include "pacman.h"

int adc_trace[800];

#define IFP_MON_W 100
#define IFP_MON_H 100

#define MEM_F0 0   // Memory Field 0: Bit Mask for Channels Enabled (Uint8)

void wx_draw_ifp_mon(widget_info *wx_info);


widget wx_create_ifp_mon(int x, int y)
{
    widget ifp_mon;

    ifp_mon.data.rect.x = x;
    ifp_mon.data.rect.y = y;

    ifp_mon.data.selected = 0;
    
    ifp_mon.fx.fx_update = wx_fx_none;
    ifp_mon.fx.fx_draw = wx_draw_ifp_mon;
    ifp_mon.fx.fx_mouse_motion = wx_check_bounds;
    ifp_mon.fx.fx_keypressed = wx_fx_none;
    ifp_mon.fx.fx_mouse_button_down = wx_fx_none;
    
    
    return ifp_mon; 

}


void wx_draw_ifp_mon(widget_info *wx_info)
{

    SDL_Rect ifp_mon_bg_rect, ifp_mon_fg_rect;

    widget_info temp_wx_info;

    int opt_x, opt_y, opt_w, opt_h;
    
    int border_color = COLOR_PRIMARY;
    
    // Power Monitor Rectangle
    ifp_mon_fg_rect.x = wx_info->rect.x;
    ifp_mon_fg_rect.y = wx_info->rect.y;
    ifp_mon_fg_rect.w = IFP_MON_W;
    ifp_mon_fg_rect.h = IFP_MON_H;

    ifp_mon_bg_rect.x = ifp_mon_fg_rect.x - 1;
    ifp_mon_bg_rect.y = ifp_mon_fg_rect.y - 1;
    ifp_mon_bg_rect.w = ifp_mon_fg_rect.w + 2;
    ifp_mon_bg_rect.h = ifp_mon_fg_rect.h + 2;
    
    temp_wx_info.rect = ifp_mon_fg_rect;
    if (wx_check_bounds(&temp_wx_info) )
        border_color = COLOR_SECONDARY;

    SDL_SetRenderDrawColor(renderer, red_mask(border_color), green_mask(border_color), blue_mask(border_color), SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &ifp_mon_bg_rect);

    SDL_SetRenderDrawColor(renderer, red_mask(0), green_mask(0), blue_mask(0), SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &ifp_mon_fg_rect);

    gui_write_text(temp_wx_info.rect.x, temp_wx_info.rect.y, &temp_wx_info.rect.w, &temp_wx_info.rect.h, "a", COLOR_WHITE);

}



void wx_fx_mouse_button_down_ifp_mon(widget_info *wx_info)
{
    wx_fx_mouse_button_down_select(wx_info);
}

