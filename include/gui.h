
#include "SDL.h"
#include "SDL_ttf.h"


// Colors
#define COLOR_BACKGROUND   0x02040F
#define COLOR_FOREGROUND   0x002642
#define COLOR_PRIMARY      0xE5DADA
#define COLOR_SECONDARY    0xE59500
#define COLOR_TERTIARY     0x840032

#define COLOR_WHITE        0xFFFFFF
#define COLOR_BLACK        0x000000
#define COLOR_GRAY         0x888888

#define COLOR_RED          0xFF0000
#define COLOR_ORANGE       0XFFA500
#define COLOR_YELLOW       0xFFFF00
#define COLOR_GREEN        0x00FF00
#define COLOR_BLUE         0x0000FF
#define COLOR_PURPLE       0xFF00FF
#define COLOR_CYAN         0x00FFFF
#define COLOR_INDIGO       0X4B0082

#define red_mask(color)   (color >> 16) & 0xff
#define green_mask(color) (color >> 8)  & 0xff
#define blue_mask(color)  (color >> 0)  & 0xff

#define wx_x(wx_info) wx_info->rect.x
#define wx_y(wx_info) wx_info->rect.y
#define wx_w(wx_info) wx_info->rect.w
#define wx_h(wx_info) wx_info->rect.h

//
int key_char, key_mod;

int mouse_x, mouse_y;
int wx_mouse_x, wx_mouse_y;

SDL_Renderer *renderer;
SDL_Window *window;
SDL_Event event;    
SDL_Texture *screen;

int gui_init();
int gui_close();
int gui_update();

/// Font Stuff

TTF_Font *font;
int font_w, font_h;
TTF_Font *font_big;
SDL_Color font_color_normal;
SDL_Color font_color_red;
SDL_Color font_color_yellow;
SDL_Color font_color_green;



// Widget Stuff 
typedef struct widget_info
{
    SDL_Rect rect;
    int selected;
    void **heap; 
} widget_info;


typedef struct widget_functions

{
    void (*fx_update)(widget_info *data);
    void (*fx_draw)(widget_info *data);
    int (*fx_mouse_motion)(widget_info *data);
    void (*fx_keypressed)(widget_info *data);
    void (*fx_mouse_button_down)(widget_info *data);
    void (*fx_mouse_scroll_up)(widget_info *data);
    void (*fx_mouse_scroll_down)(widget_info *data);
    void (*fx_mouse_left_button_press)(widget_info *data);
    void (*fx_mouse_left_button_release)(widget_info *data);
    
    // void (*fx_create)(void);
    // void (*fx_destroy)(void);
    // struct widget **sub_widgets_queue;
    // int sub_widgets_queue_size;

} widget_functions;



typedef struct widget
{
    widget_functions fx;
    widget_info data;
} widget;


void gui_add_widget_queue(widget wx);
void gui_write_text(int x, int y, int *w, int *h, char *text, int color);
widget widget_queue[100];
int widget_queue_size;


// Instantiations of widgets (for global access)
widget main_terminal;

// Scope Widget
widget wx_scope_create(int x, int y);

// Value Box 
widget wx_value_box_create(int x, int y, void (*func)(void), int num_digits);

// Scroll Box
widget wx_scroll_box_create(int x, int y, int *val, int num_digits);

// Soft Commands Window
widget wx_soft_command_create(int x, int y);

//Terminal
widget wx_terminal_create(int x, int y);
void wx_terminal_printf(widget_info *wx_info);

// Button
widget wx_button_create(int x, int y, char *text);

// Helper Functions
void wx_draw_frame(widget_info *wx, int border_color, int fill_color);
int wx_check_bounds(widget_info *wx_info);
void wx_fx_mouse_button_down_select(widget_info *data);
void wx_write_text(widget_info *wx_info, int x, int y, char* text);

// Power Monitor
widget wx_create_power_mon(int x, int y);


// IFP Monitor
widget wx_create_ifp_mon(int x, int y);

void wx_fx_test(void);
void wx_fx_none(widget_info *wx_info);
int wx_fx_none_int(widget_info *wx_info);

// Font


typedef struct
{
  SDL_Texture *bm;
  int h;
  
  /* A character's x-position in the font bitmap array. 
     For example, If the font has a width of 7, the 10th 
     character would have a position of 70. This allows for
     characters in a font having different widths. */
  short p[128];  

  // Width of the individual character in a font.
  char w[128];   
  
} FONT;

FONT* font_srf;
FONT* load_font(char *filename);

void write_text(char *s, int x, int y, int fgc);


