#include "display.h"
#include "memory.h"
#include <stdlib.h>
#include <stdio.h>
#include </usr/local/Cellar/sdl2/2.0.16/include/SDL2/SDL.h>

//Private Data
static unsigned char display[DISPLAY_HEIGHT][DISPLAY_WIDTH] = { 0 };
static SDL_Window *window;
static SDL_Renderer *renderer;

int setup_display() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to initialize SDL and emulator will not start\n");
        printf("SDL error: %s\n", SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow(
            "CHIP 8",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            640,
            320,
            0);

    if (window == NULL) {
        printf("Error setting up window: %s\n", SDL_GetError());
        return -1;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        printf("Error setting up renderer: %s\n", SDL_GetError());
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    return 1;
}
int tear_down_display() {
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}

int calculate_display_pixels(unsigned char x, unsigned char y, unsigned char N, unsigned char *memory) {
    unsigned char Vf = 0;
    x = x % DISPLAY_WIDTH;
    y = y % DISPLAY_HEIGHT;
    for (unsigned char j = 0; j < N; j++) {
        unsigned char current_byte = memory[I + j];
        unsigned char i_reversed = 7;
        for (unsigned char i = 0; i < 8; i++) {
            if (x == DISPLAY_WIDTH)
                break;
            unsigned char bit_value = BIT_N(current_byte, i_reversed);
            //Case where the pixel was already on
            unsigned char *current_pixel = &display[y + j][x + i];
            unsigned char next_display_value = (bit_value ^ (*current_pixel));
            if (bit_value && current_pixel) {
                Vf = 1;
            }
            *current_pixel = next_display_value;
            i_reversed--;
        }
    }
    registers[VF] = Vf;
    return 1;
}

int draw_display() {
    SDL_RenderPresent(renderer);
    return 1;
}

int clear_display() {
    for (int j = 0; j < DISPLAY_HEIGHT; j++) {
        for (int i = 0; i <DISPLAY_WIDTH; i++) {
            display[j][i] = 0;
        }
    }
    return 1;
}
















