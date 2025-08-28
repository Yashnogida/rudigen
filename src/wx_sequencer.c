#include <string.h>
#include <stdlib.h>
#include "SDL.h"
#include "gui.h"


void wx_sequencer_draw(widget_info *wx_info);
void wx_sequencer_update(widget_info *wx_info);

#define HEAP_ADDR_DRUM_NAME_STRING 0
#define HEAP_ADDR_SEQUENCE 80

widget wx_sequencer_create(int x, int y, char *drum_name)
{

    widget sequencer;

    
    sequencer.data.rect.x = x;
    sequencer.data.rect.y = y;
    sequencer.data.rect.w = 600;
    sequencer.data.rect.h = 20;
    sequencer.data.selected = 0;
    
    sequencer.fx.fx_update = wx_sequencer_update;
    sequencer.fx.fx_draw = wx_sequencer_draw;
    sequencer.fx.fx_keypressed = wx_fx_none;
    sequencer.fx.fx_mouse_motion = wx_fx_none_int;
    sequencer.fx.fx_mouse_button_down = wx_fx_none;
    
    sequencer.data.heap = malloc(120);
    strcpy(((char*)sequencer.data.heap + HEAP_ADDR_DRUM_NAME_STRING), drum_name);
    
    wx_sequencer_draw(&sequencer.data);
    
    return sequencer;

}



void wx_sequencer_draw(widget_info *wx_info)
{
    wx_draw_frame(wx_info, COLOR_FOREGROUND, COLOR_TERTIARY);
    wx_write_text(wx_info, 5, 4, (char*)wx_info->heap, COLOR_BLACK);
    // gui_write_text(wx_info->rect.x, wx_info->rect.y, NULL, NULL, (char*)wx_info->heap, 0x0A100D);

    // printf((char*)wx_info->heap);
}


void wx_sequencer_update(widget_info *wx_info)
{

}
