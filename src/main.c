
#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "SDL.h"
#include "gui.h"
#include "pacman_uut.h"
#include "cmd.h"

#include "socket.h"

bool quit;


void setup_state_0();

int main(int argc, char* argv[])
{
  // socket_init("p700-k1.scs.is.keysight.com");
  // socket_close();
  // return 1;

  gui_init();

  setup_state_0();
  
  int ta, tb;

  // socket_init("p700-k1.scs.is.keysight.com");

  while (!quit)
  {
    // ta = SDL_GetTicks();
    gui_update();
    // tb = SDL_GetTicks();
    // printf("%d %d | Update rate: %dms\n", ta, tb, tb - ta);
  }
    

  gui_close();

  return 0;
  
}


void setup_state_0()
{
  
  // gui_add_widget_queue( wx_scope_create(220, 10) );
  //gui_add_widget_queue( wx_soft_command_create(10, 10) );
  // gui_add_widget_queue( wx_terminal_create(220, 420) );
  // gui_add_widget_queue( wx_create_power_mon(1000, 500) );
  // gui_add_widget_queue( wx_create_ifp_mon(1000, 500) );
  // gui_add_widget_queue( wx_scroll_box_create(860, 470, NULL, 10) );
}
