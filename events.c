#include "display.h"
#include "events.h"

#define NUM_CUSTOM_EVENTS 3

chip8_events chip8_event_types;

int setup_events() {
    chip8_event_types.first_event_num = SDL_RegisterEvents(NUM_CUSTOM_EVENTS);
    chip8_event_types.update_display = chip8_event_types.first_event_num;
    chip8_event_types.clear_display = chip8_event_types.first_event_num + 2;
    return 1;
}

int handle_event(SDL_Event *event) {
    if (event->type == chip8_event_types.update_display) {
        handle_update_display(event);
        return 1;
    }
    return -1;
}

static void handle_update_display(SDL_Event *event) {
    struct draw_insn_data *draw_data = (draw_insn_data *)event->user.data1;
    unsigned char *memory = (unsigned char *) event->user.data2;
    calculate_display_pixels(draw_data->x, draw_data->y, draw_data->N, memory);
    draw_display();
    free(draw_data);
}



