#include "/usr/local/Cellar/sdl2/2.0.16/include/SDL2/SDL.h"
typedef struct chip8_events {
    int first_event_num;
    int update_display;
} chip8_events;
int setup_events();
extern chip8_events chip8_event_types;
static void handle_update_display(SDL_Event *event);
