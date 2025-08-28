
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "gui.h"
#include "SDL.h"
#include "string.h"
#include "ctype.h"
#include "cmd.h"


enum MEM_FIELD_ENUM
{
    MEM_F0,         // Memory Field 0: Terminal buffer buffer Count 
    MEM_F1,         // Memory Field 1: Terminal Parser Cursor Position 
    MEM_F2,         // Memory Field 2: Terminal Parser Select Size
    MEM_F3,         // Memory Field 3: Pointer to terminal buffer (char array)
    MEM_F4,         // Memory Field 4: Log heap pointer 
    MEM_F5,         // Memory Field 5: Log heap allocated size
    MEM_F6,         // Memory Field 6: Log heap current size
    MEM_FIELD_MAX
};

#define buffer_size(wx_info)                  (*(int*)(wx_info->heap[MEM_F0]))
#define cursor_position(wx_info)              (*(int*)(wx_info->heap[MEM_F1]))
#define cursor_size(wx_info)                  (*(int*)(wx_info->heap[MEM_F2]))
#define terminal_buffer(wx_info, char_index)  ((char*)(wx_info->heap + MEM_F3) + char_index)
// #define log_buffer(wx_info, char_index)       ((char*)(wx_info->heap + MEM_F4) + char_index)
// #define log_alloc_size(wx_info, char_index)   ((char*)(wx_info->heap + MEM_F5) + char_index)
// #define log_current_size(wx_info, char_index) ((char*)(wx_info->heap + MEM_F6) + char_index)

#define MAX_TERMINAL_BUFFER_SIZE 80
#define LOG_ALLOC_BLOCK_SIZE 1000

#define X_PAD 4
#define Y_PAD 16

/*  Terminal Widget Functions  */
void wx_terminal_draw(widget_info *wx_info);
void wx_terminal_keypressed(widget_info *wx_info);
void wx_terminal_set_commands(widget_info *wx_info);
void wx_terminal_parser_clear(widget_info *wx_info);
void wx_terminal_process_command(widget_info *wx_info);
void wx_terminal_draw_cursor(widget_info *wx_info);

/*  Terminal Typing Functions  */
void wx_terminal_insert_character(widget_info *wx_info, char character);
void wx_terminal_backspace(widget_info *wx_info);
void wx_terminal_move_cursor_left(widget_info *wx_info);
void wx_terminal_jump_word_left(widget_info *wx_info);
void wx_terminal_delete_word_left(widget_info *wx_info);
void wx_terminal_select_character_left(widget_info *wx_info);
void wx_terminal_select_word_left(widget_info *wx_info);
void wx_terminal_move_cursor_right(widget_info *wx_info);
void wx_terminal_jump_word_right(widget_info *wx_info);
void wx_terminal_delete_character_right(widget_info *wx_info);
void wx_terminal_delete_word_right(widget_info *wx_info);
void wx_terminal_select_character_right(widget_info *wx_info);
void wx_terminal_select_word_right(widget_info *wx_info);


#define TERMINAL_WIDTH 550
#define TERMINAL_HEIGHT 370

widget wx_terminal_create(int x, int y)
{
    widget terminal;

    terminal.data.rect.x = x;
    terminal.data.rect.y = y;
    terminal.data.rect.w = TERMINAL_WIDTH; // 80 characters at 9 pixel width
    terminal.data.rect.h = TERMINAL_HEIGHT;

    terminal.data.selected = 0;

    terminal.fx.fx_update = wx_terminal_printf;
    terminal.fx.fx_draw = wx_terminal_draw;
    terminal.fx.fx_keypressed = wx_terminal_keypressed;
    terminal.fx.fx_mouse_motion = wx_check_bounds;
    terminal.fx.fx_mouse_button_down = wx_fx_mouse_button_down_select;

    terminal.data.heap = malloc(sizeof(void*) * MEM_FIELD_MAX);

    terminal.data.heap[MEM_F0] = malloc(sizeof(int));                              // buffer_size
    terminal.data.heap[MEM_F1] = malloc(sizeof(int));                              // cursor_position
    terminal.data.heap[MEM_F2] = malloc(sizeof(int));                              // cursor_size
    terminal.data.heap[MEM_F3] = malloc(sizeof(char) * MAX_TERMINAL_BUFFER_SIZE);  // log_buffer

    if (terminal.data.heap[MEM_F3] == NULL) 
    { 
        printf("Malloc Failed: %s()\n", __func__); 
        exit(0); 
    }

    wx_terminal_parser_clear(&terminal.data);
        
    // terminal.data.heap[MEM_F5] = malloc(sizeof(int));                              // log_alloc_size
    // terminal.data.heap[MEM_F6] = malloc(sizeof(char) * MAX_TERMINAL_BUFFER_SIZE);  // log_current_size

    return terminal; 

}








void wx_terminal_draw(widget_info *wx_info)
{
    char str[80];

    wx_draw_frame(wx_info, COLOR_PRIMARY, COLOR_BLACK);
    sprintf(str, ">> %s", terminal_buffer(wx_info, 0));
    write_text(str, wx_x(wx_info) + X_PAD, wx_y(wx_info) + wx_h(wx_info) - Y_PAD, COLOR_WHITE);
    wx_terminal_draw_cursor(wx_info);
}



void wx_terminal_parser_clear(widget_info *wx_info)     
{
    memset(terminal_buffer(wx_info, 0), '\0', 80);

    // for (int c=0; c<MAX_TERMINAL_BUFFER_SIZE; c++)
        // printf("[%2d] %p\n", c, *terminal_buffer(wx_info, c));

    buffer_size(wx_info) = 0;
    cursor_position(wx_info) = 0;
    cursor_size(wx_info) = 0;

}


void wx_terminal_printf(widget_info *wx_info)
{

}


void wx_terminal_process_command(widget_info *wx_info)     
{
    if (buffer_size(wx_info) == 0) return;
    
    wx_terminal_parser_clear(wx_info);
}



void wx_terminal_draw_cursor(widget_info *wx_info)
{

    static int lt;
    static uint32_t cursor_color;
    const int cursor_blink_rate = 500; //ms
    
    if (wx_info->selected)
    {
        SDL_Rect rect;

        rect.x = wx_x(wx_info) + X_PAD + ((cursor_position(wx_info) + 3 )* font_srf->w[0]); // "3" for '>> '
        rect.y = wx_y(wx_info) + wx_h(wx_info) - Y_PAD - 1;
        rect.w = font_w * cursor_size(wx_info);

        rect.h = font_srf->h;
        
        if ((SDL_GetTicks() - lt) > cursor_blink_rate)
        {
            cursor_color = (cursor_color == COLOR_SECONDARY) ? COLOR_BLACK : COLOR_SECONDARY;
            lt = SDL_GetTicks();
        }

        SDL_SetRenderDrawColor(renderer, red_mask(cursor_color), green_mask(cursor_color), blue_mask(cursor_color), SDL_ALPHA_OPAQUE);
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);
    }

}


void wx_terminal_insert_character(widget_info *wx_info, char character)
{
    int c;

    buffer_size(wx_info)++;

    for (c=buffer_size(wx_info); c>cursor_position(wx_info); c--)
        *terminal_buffer(wx_info, c) = *terminal_buffer(wx_info, c-1);

    *terminal_buffer(wx_info, c) = key_char;
    cursor_position(wx_info)++;
    
}

void wx_terminal_move_cursor_left(widget_info *wx_info)
{

    if (cursor_position(wx_info) == 0)  return;

    if (cursor_size(wx_info) > 0)
    {
        cursor_size(wx_info) = 0;
        return;
    }

    if (cursor_size(wx_info) < 0)
    {
        cursor_position(wx_info) = cursor_position(wx_info) + cursor_size(wx_info);
        cursor_size(wx_info) = 0;
        return;
    }

    cursor_position(wx_info)--;
}

void wx_terminal_jump_word_left(widget_info *wx_info)
{
    cursor_size(wx_info) = 0;

    if (cursor_position(wx_info) == 0) return;

    while (*terminal_buffer(wx_info, (cursor_position(wx_info) - 1)) == SDLK_SPACE)
        if (--cursor_position(wx_info) == 0) return;

    while (*terminal_buffer(wx_info, (cursor_position(wx_info) - 1)) != SDLK_SPACE)
        if (--cursor_position(wx_info) == 0) return;
}


void wx_terminal_backspace(widget_info *wx_info)
{
    int start_char, end_char;
    int c;

    if (cursor_position(wx_info) == 0) return;
    
    start_char = cursor_position(wx_info);
    end_char = cursor_position(wx_info) + cursor_size(wx_info);   

    start_char = (end_char > start_char) ? cursor_position(wx_info) : end_char;
    end_char = (end_char > cursor_position(wx_info)) ? end_char : cursor_position(wx_info);
    
    printf("%d %d\n", start_char, end_char);

    if (start_char == end_char)
    {
        // memcpy( terminal_buffer(wx_info, c - 1), terminal_buffer(wx_info, c), MAX_TERMINAL_BUFFER_SIZE );
        for (c = start_char; c < buffer_size(wx_info); c++)
            *terminal_buffer(wx_info, c - 1) = *terminal_buffer(wx_info, c);
        // 
        *terminal_buffer(wx_info, c - 1) = '\0';
        cursor_position(wx_info)--;
        buffer_size(wx_info)--;
        // return;
    }


}

void wx_terminal_delete_word_left(widget_info *wx_info)
{
    int cursor_start, cursor_end, diff, c;

    if (cursor_position(wx_info) == 0) return;
    
    cursor_start = cursor_position(wx_info);
    wx_terminal_jump_word_left(wx_info);
    diff = cursor_start - cursor_position(wx_info);

    buffer_size(wx_info) -= diff;
    
    for (c = cursor_position(wx_info); c < buffer_size(wx_info); c++)
        *terminal_buffer(wx_info,  c) = *terminal_buffer(wx_info,  c + diff );

    *terminal_buffer(wx_info, c) = '\0';

}

void wx_terminal_select_character_left(widget_info *wx_info)
{
    if ((cursor_position(wx_info) + cursor_size(wx_info)) == 0) return;
    cursor_size(wx_info)--;
}

void wx_terminal_select_word_left(widget_info *wx_info)
{
    printf("TO DO: Selected word left");
}


void wx_terminal_move_cursor_right(widget_info *wx_info)
{

    if (cursor_position(wx_info) >= buffer_size(wx_info)) return;

    if (cursor_size(wx_info) > 0)
    {
        cursor_position(wx_info) = cursor_position(wx_info) + cursor_size(wx_info);
        cursor_size(wx_info) = 0;
        return;
    }

    if (cursor_size(wx_info) < 0)
    {
        cursor_size(wx_info) = 0;
        return;
    }
    
    cursor_position(wx_info)++;
}


void wx_terminal_jump_word_right(widget_info *wx_info)
{
    cursor_size(wx_info) = 0;

    if (cursor_position(wx_info) == buffer_size(wx_info)) return;

    while ((*terminal_buffer(wx_info, cursor_position(wx_info)) == SDLK_SPACE))
        if (++cursor_position(wx_info) == buffer_size(wx_info)) return;

    while ((*terminal_buffer(wx_info, cursor_position(wx_info))) != SDLK_SPACE)
        if (++cursor_position(wx_info) == buffer_size(wx_info)) return;
}

void wx_terminal_delete_character_right(widget_info *wx_info)
{

    if (buffer_size(wx_info) == 0) return;
    
    if (cursor_size(wx_info) != 0)
    {
        wx_terminal_backspace(wx_info);
        return;
    }

    for (int c=cursor_position(wx_info); c<buffer_size(wx_info); c++)
        *terminal_buffer(wx_info, c) = *terminal_buffer(wx_info, c + 1);

    buffer_size(wx_info)--;

}

void wx_terminal_delete_word_right(widget_info *wx_info)
{
    int cursor_start, cursor_end, diff, c;

    if (cursor_position(wx_info) == buffer_size(wx_info)) return;
    
    cursor_start = cursor_position(wx_info);
    wx_terminal_jump_word_right(wx_info);
    diff = cursor_position(wx_info) - cursor_start;
    cursor_position(wx_info) = cursor_start;
    buffer_size(wx_info) -= diff;

    for (c = cursor_position(wx_info); c < buffer_size(wx_info) + 1; c++)
        *terminal_buffer(wx_info,  c) = *terminal_buffer(wx_info,  c + diff);

}


void wx_terminal_select_character_right(widget_info *wx_info)
{
    if (cursor_position(wx_info) + cursor_size(wx_info) == buffer_size(wx_info)) return;
    cursor_size(wx_info)++;
}

void wx_terminal_select_word_right(widget_info *wx_info)
{
    printf("TO DO: Selected word right");
}



void wx_terminal_keypressed(widget_info *wx_info)
{
    static bool key_pressed = false;  // Stupid hack to prevent backspace from getting spammed
    
    bool shift_key, control_key;

    control_key = key_mod & KMOD_CTRL;
    shift_key = key_mod & KMOD_SHIFT;

    if (wx_info->selected)
    {
        if ((event.type == SDL_KEYUP))
            key_pressed = false;

        if (event.type == SDL_KEYDOWN)
        {
            
            if ((key_char == SDLK_RETURN) && (buffer_size(wx_info) > 0))  { wx_terminal_process_command(wx_info); }
            
            // No Modifier Keys
            if ((key_char == SDLK_LEFT)      && !control_key && !shift_key && !key_pressed) { key_pressed = true; wx_terminal_move_cursor_left(wx_info); }
            if ((key_char == SDLK_RIGHT)     && !control_key && !shift_key && !key_pressed) { key_pressed = true; wx_terminal_move_cursor_right(wx_info); }
            if ((key_char == SDLK_DELETE)    && !control_key && !shift_key && !key_pressed) { key_pressed = true; wx_terminal_delete_character_right(wx_info); }
            if ((key_char == SDLK_BACKSPACE) && !control_key && !shift_key && !key_pressed) { key_pressed = true; wx_terminal_backspace(wx_info); }

            // Control Modifiers
            if ((key_char == SDLK_LEFT)      && control_key && !shift_key && !key_pressed) { key_pressed = true; wx_terminal_jump_word_left(wx_info); } 
            if ((key_char == SDLK_RIGHT)     && control_key && !shift_key && !key_pressed) { key_pressed = true; wx_terminal_jump_word_right(wx_info); } 
            if ((key_char == SDLK_DELETE)    && control_key && !shift_key && !key_pressed) { key_pressed = true; wx_terminal_delete_word_right(wx_info); }
            if ((key_char == SDLK_BACKSPACE) && control_key && !shift_key && !key_pressed) { key_pressed = true; wx_terminal_delete_word_left(wx_info); }

            // Shift Modifiers
            if ((key_char == SDLK_LEFT)  && !control_key && shift_key && !key_pressed) { key_pressed = true; wx_terminal_select_character_left(wx_info); } 
            if ((key_char == SDLK_RIGHT) && !control_key && shift_key && !key_pressed) { key_pressed = true; wx_terminal_select_character_right(wx_info); } 

            // Control + Shift Modifiers
            if ((key_char == SDLK_LEFT)  && control_key && shift_key && !key_pressed) { key_pressed = true; wx_terminal_select_word_left(wx_info); } 
            if ((key_char == SDLK_RIGHT) && control_key && shift_key && !key_pressed) { key_pressed = true; wx_terminal_select_word_right(wx_info); } 


            if (buffer_size(wx_info) < MAX_TERMINAL_BUFFER_SIZE) 
                if ((key_char >= 32) && (key_char < 127) && (key_mod == KMOD_NONE)) 
                    wx_terminal_insert_character(wx_info, key_char);
            
            printf("Key pressed: %d | Key Mod: 0x%04x | Cursor Position: %2d | Select Size: %2d | Buffer Size: %2d\n", key_char, key_mod, cursor_position(wx_info), cursor_size(wx_info), buffer_size(wx_info));

        }   
    }
}
