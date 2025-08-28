
#include <SDL.h>

void pacman_uut_get_adc_trace(int *buffer)
{
    for (int i=0; i<1024; i++)
        buffer[i] = SDL_GetTicks();
}