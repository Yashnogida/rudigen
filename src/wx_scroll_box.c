
#include "gui.h"
#include "SDL.h"
#include "SDL_ttf.h"


SDL_Rect scroll_box_rect;

void wx_scroll_box_draw(widget_info *data);




widget wx_scroll_box_create(int x, int y, int *val, int num_digits)
{
    widget scroll_box;

    scroll_box.data.rect.x = x;
    scroll_box.data.rect.y = y;
    scroll_box.data.rect.w = num_digits * 14;
    scroll_box.data.rect.h = 100;
    
    scroll_box.data.selected = 0;
    
    scroll_box.fx.fx_update = wx_fx_none;
    scroll_box.fx.fx_draw = wx_scroll_box_draw;
    scroll_box.fx.fx_mouse_motion = wx_check_bounds;
    scroll_box.fx.fx_keypressed = wx_fx_none;
    scroll_box.fx.fx_mouse_button_down = wx_fx_mouse_button_down_select;

    return scroll_box; 

}


void wx_scroll_box_draw(widget_info *data)
{
    wx_draw_frame(data, COLOR_PRIMARY, COLOR_FOREGROUND);
    char str_val[20];
    // sprintf(str_val, "%10d\n", )
    // sprintf()
    // gui_write_text(0, h-16, mouse_coord);

}