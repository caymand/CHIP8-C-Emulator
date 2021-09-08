#include "/usr/local/Cellar/sdl2/2.0.16/include/SDL2/SDL.h"
typedef struct chip8_events {
    unsigned int first_event_num;
    unsigned int update_display;
    unsigned int clear_display;
} chip8_events;

int setup_events();
int handle_event(SDL_Event *event);

static void handle_update_display(SDL_Event *event);

extern chip8_events chip8_event_types;


