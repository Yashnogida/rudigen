
#include "gui.h"
#include "SDL.h"
#include "pacman_uut.h"
#include <stdlib.h>
#include <stdio.h>
#include "pacman.h"

int adc_trace[800];

#define SCOPE_W 800
#define SCOPE_H 400

#define SCOPE_CONTROL_W 200
#define SCOPE_CONTROL_H 250

#define SPACE_BETWEEN 10


enum MEM_FIELD_ENUM
{
    MEM_F0,         // Memory Field 0: Bit Mask for Channels Enabled (Uint8) 
    MEM_F1,         // Memory Field 1: Pointer to array of channel colors (Uint32)
    MEM_FIELD_MAX
};


void wx_scope_draw(widget_info *data);
void wx_fx_mouse_button_down_scope(widget_info *wx_info);
void wx_scope_initialize_channel_setings(widget_info *wx_info);

#define channel_selected(wx_info, channel) ((widget_info*)wx_info->heap + channel)->selected
#define channel_color(wx_info, channel) *(((uint32_t*)(wx_info->heap[MEM_F1])) + channel)


widget wx_scope_create(int x, int y)
{
    widget scope;

    scope.data.rect.x = x;
    scope.data.rect.y = y;

    scope.data.selected = 0;
    
    scope.fx.fx_update = wx_fx_none;
    scope.fx.fx_draw = wx_scope_draw;
    scope.fx.fx_mouse_motion = wx_check_bounds;
    scope.fx.fx_keypressed = wx_fx_none;
    scope.fx.fx_mouse_button_down = wx_fx_mouse_button_down_scope;
    
    
    scope.data.heap[MEM_F0] = malloc(sizeof(uint8_t*) * PM_NUMBER_CHANNELS);
    scope.data.heap[MEM_F1] = malloc(sizeof(uint32_t*) * PM_NUMBER_CHANNELS);


    wx_scope_initialize_channel_setings(&scope);

    return scope; 

}



void wx_scope_initialize_channel_setings(widget_info *wx_info)
{
    
    // UNCOMMENTING THIS breaks shit. 
    // for (int channel=0; channel<8; channel+=1)
        // channel_selected(wx_info, channel) = 1;

    // *((uint32_t*)wx_info->heap[MEM_F1]) = 1;
    // channel_color(wx_info, 0) = COLOR_RED;
    // channel_color(wx_info, 1) = COLOR_ORANGE;
    // channel_color(wx_info, 2) = COLOR_YELLOW;
    // channel_color(wx_info, 3) = COLOR_GREEN;
    // channel_color(wx_info, 4) = COLOR_BLUE;
    // channel_color(wx_info, 5) = COLOR_PURPLE;
    // channel_color(wx_info, 6) = COLOR_CYAN;
    // channel_color(wx_info, 7) = COLOR_INDIGO;

    // printf("%x\n", channel_color(wx_info, 0));
}

void wx_scope_draw(widget_info *wx_info)
{

    SDL_Rect scope_bg_rect, scope_fg_rect;
    SDL_Rect scope_control_bg_rect, scope_control_fg_rect;
    SDL_Rect option_rect;

    widget_info temp_wx_info;

    int opt_x, opt_y, opt_w, opt_h;
    
    int border_color = COLOR_PRIMARY;
    
    // Scope Rectangle
    scope_fg_rect.x = wx_info->rect.x;
    scope_fg_rect.y = wx_info->rect.y;
    scope_fg_rect.w = SCOPE_W;
    scope_fg_rect.h = SCOPE_H;

    scope_bg_rect.x = scope_fg_rect.x - 1;
    scope_bg_rect.y = scope_fg_rect.y - 1;
    scope_bg_rect.w = scope_fg_rect.w + 2;
    scope_bg_rect.h = scope_fg_rect.h + 2;
    
    // Scope Control Rectangle
    scope_control_fg_rect.x = wx_info->rect.x + SCOPE_W + SPACE_BETWEEN;
    scope_control_fg_rect.y = wx_info->rect.y;
    scope_control_fg_rect.w = SCOPE_CONTROL_W;
    scope_control_fg_rect.h = SCOPE_CONTROL_H;

    scope_control_bg_rect.x = scope_control_fg_rect.x - 1;
    scope_control_bg_rect.y = scope_control_fg_rect.y - 1;
    scope_control_bg_rect.w = scope_control_fg_rect.w + 2;
    scope_control_bg_rect.h = scope_control_fg_rect.h + 2;
    

    // Draw Scope and Scope Control

    temp_wx_info.rect = scope_fg_rect;
    if (wx_check_bounds(&temp_wx_info) )
        border_color = COLOR_SECONDARY;

    temp_wx_info.rect = scope_control_fg_rect;
    if (wx_check_bounds(&temp_wx_info) )
        border_color = COLOR_SECONDARY;
    
    SDL_SetRenderDrawColor(renderer, red_mask(border_color), green_mask(border_color), blue_mask(border_color), SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &scope_bg_rect);

    SDL_SetRenderDrawColor(renderer, red_mask(0), green_mask(0), blue_mask(0), SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &scope_fg_rect);

    SDL_SetRenderDrawColor(renderer, red_mask(border_color), green_mask(border_color), blue_mask(border_color), SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &scope_control_bg_rect);

    SDL_SetRenderDrawColor(renderer, red_mask(0), green_mask(0), blue_mask(0), SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &scope_control_fg_rect);


    // Draw "Channel" Buttons

    temp_wx_info.rect.x = scope_control_bg_rect.x + 15;
    temp_wx_info.rect.y = scope_control_bg_rect.y + 40;
    temp_wx_info.rect.h = 13;

    char option_str[80];

    for (int channel=0; channel<PM_NUMBER_CHANNELS; channel++)
    {
        sprintf(option_str, "Channel %d", channel);
        
        write_text(option_str, temp_wx_info.rect.x, temp_wx_info.rect.y, COLOR_GRAY);
        
        if ( wx_check_bounds(&temp_wx_info) )
            write_text(option_str, temp_wx_info.rect.x, temp_wx_info.rect.y, COLOR_WHITE);

        temp_wx_info.rect.y += 20;
        //
    }


}


void wx_scope_frame(widget_info *wx_info)
{

}


void wx_fx_mouse_button_down_scope(widget_info *wx_info)
{
    wx_fx_mouse_button_down_select(wx_info);
}

