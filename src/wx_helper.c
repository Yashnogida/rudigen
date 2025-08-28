#include "gui.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "stdio.h"

void wx_draw_frame(widget_info *wx, int border_color, int fill_color)
{
    SDL_Rect bg_rect;

    bg_rect.x = wx->rect.x - 1;
    bg_rect.y = wx->rect.y - 1;
    bg_rect.w = wx->rect.w + 2;
    bg_rect.h = wx->rect.h + 2;
    
    if (wx->selected | wx_check_bounds(wx)) border_color = COLOR_SECONDARY;
    SDL_SetRenderDrawColor(renderer, (border_color>>16) & 0xff, (border_color>>8) & 0xff, border_color & 0xff, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &bg_rect);
    SDL_SetRenderDrawColor(renderer, (fill_color>>16) & 0xff, (fill_color>>8) & 0xff, fill_color & 0xff, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &wx->rect);

}


int wx_check_bounds(widget_info *wx_info)
{
    if ((mouse_x > wx_info->rect.x) && ( mouse_x < (wx_info->rect.x + wx_info->rect.w)))
    {
        if ((mouse_y > wx_info->rect.y) && ( mouse_y < (wx_info->rect.y + wx_info->rect.h)))
        {
            wx_mouse_x = mouse_x - wx_info->rect.x;
            wx_mouse_y = mouse_y - wx_info->rect.y;
            return 1;
        }
    }
    
    return 0;

}


void wx_fx_mouse_button_down_select(widget_info *wx_info)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
        if (event.button.type == SDL_MOUSEBUTTONDOWN)
            wx_info->selected = wx_check_bounds(wx_info);
}

void wx_fx_test(void)
{
//   printf("%d\n", SDL_GetTicks());

}

void wx_write_text(widget_info *wx_info, int x, int y, char* text)
{
    gui_write_text(wx_info->rect.x + x, wx_info->rect.y + y, NULL, NULL,  text, 0xffffff);
}




void wx_fx_none(widget_info *wx_info)
{
    
}


int wx_fx_none_int(widget_info *wx_info)
{
    
}

