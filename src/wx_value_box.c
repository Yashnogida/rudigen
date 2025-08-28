
#include <stdlib.h>

#include "gui.h"
#include "SDL.h"
#include "SDL_ttf.h"


void wx_value_box_draw(widget_info *wx_info);
void wx_value_box_update(widget_info *wx_info);

#define VALUE_BOX_MIN_VALUE 0
#define VALUE_BOX_MAX_VALUE 1
#define VALUE_BOX_CURRENT_VALUE 2

widget wx_value_box_create(int x, int y, int min_val, int max_val, int init_val)
{

    widget value_box;
    
    value_box.data.rect.x = x;
    value_box.data.rect.y = y;
    value_box.data.rect.w = 560;
    value_box.data.rect.h = 800;
    value_box.data.selected = 0;

    value_box.fx.fx_update = wx_value_box_update;
    value_box.fx.fx_draw = wx_value_box_draw;
    value_box.fx.fx_keypressed = wx_fx_none;
    value_box.fx.fx_mouse_motion = wx_fx_none_int;
    value_box.fx.fx_mouse_button_down = wx_fx_mouse_button_down_select;

    value_box.data.heap = malloc(sizeof(int) * 3);
    
    *((int*)value_box.data.heap + VALUE_BOX_MIN_VALUE) = min_val;
    *((int*)value_box.data.heap + VALUE_BOX_MAX_VALUE) = max_val;
    *((int*)value_box.data.heap + VALUE_BOX_CURRENT_VALUE) = init_val;

    wx_value_box_draw(&value_box.data);
    
    return value_box;

}



void wx_value_box_draw(widget_info *wx_info)
{

    wx_draw_frame(wx_info, COLOR_TERTIARY, COLOR_GRAY);
}


void wx_value_box_update(widget_info *wx_info)
{

}
