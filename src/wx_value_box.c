
#include "gui.h"
#include "SDL.h"
#include "SDL_ttf.h"



widget wx_value_box_create(int x, int y, void (*func)(void), int num_digits)
{
    
    widget value_box;
    
    // value_box.data.rect.x = x;
    // value_box.data.rect.y = y;
    // value_box.data.rect.w = 9 * num_digits;  // Change later 
    // value_box.data.rect.h = 14;              // Change later 

    // wx_draw_frame(value_box.data, COLOR_PRIMARY, COLOR_BACKGROUND);

    // value_box.fx.fx_update = *func;
    

    return value_box;
}

