#include "gui.h"
#include "SDL.h"



void wx_score_window_draw(widget_info *wx_info);
void wx_score_window_update(widget_info *wx_info);


widget wx_score_window_create(int x, int y)
{

    widget score_window;

    score_window.data.rect.x = x;
    score_window.data.rect.y = y;
    score_window.data.rect.w = 560;
    score_window.data.rect.h = 800;
    score_window.data.selected = 0;

    score_window.fx.fx_update = wx_score_window_update;
    score_window.fx.fx_draw = wx_score_window_draw;
    score_window.fx.fx_keypressed = wx_fx_none;
    score_window.fx.fx_mouse_motion = wx_fx_none_int;
    score_window.fx.fx_mouse_button_down = wx_fx_mouse_button_down_select;


    wx_score_window_draw(&score_window.data);
    
    return score_window;

}



void wx_score_window_draw(widget_info *wx_info)
{

    wx_draw_frame(wx_info, COLOR_TERTIARY, COLOR_GRAY);
}


void wx_score_window_update(widget_info *wx_info)
{

}
