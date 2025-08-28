
#include <stdio.h>
#include <stdbool.h>
#include "SDL.h"
#include "SDL.h"
#include "gui.h"
#include "cmd.h"

bool quit;


void setup_state_0();

int main(int argc, char* argv[])
{

  gui_init();

  setup_state_0();
  
  while (!quit)
  {
    gui_update();
  }

  gui_close();

  return 0; 
  
}


void setup_state_0()
{
  
  gui_add_widget_queue( wx_score_window_create(800, 60) );
  gui_add_widget_queue( wx_sequencer_create(100, 120, "Hihatt") );
  gui_add_widget_queue( wx_sequencer_create(100, 142, "Hihatt") );
  gui_add_widget_queue( wx_sequencer_create(100, 164, "Hihatt") );
  gui_add_widget_queue( wx_sequencer_create(100, 186, "Hihatt") );
  gui_add_widget_queue( wx_sequencer_create(100, 208, "Hihatt") );
  gui_add_widget_queue( wx_sequencer_create(100, 230, "Hihatt") );
  gui_add_widget_queue( wx_sequencer_create(100, 254, "Hihatt") );
}