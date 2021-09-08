#include <stdlib.h>
#include <stdio.h>
#include "chip8.h"
#include "memory.h"
#include "timers.h"
#include <unistd.h>
#include <stdbool.h>
#include "stack.h"
#include "display.h"
#include "events.h"

//#include "/usr/local/Cellar/sdl2/2.0.16/include/SDL2/SDL.h"

//Global variables
static unsigned char *memory;
static unsigned short PC = GAME_ADDR_START;
static SDL_Event event;

int main() {
    FILE *game = fopen("../games/IBM_logo1.ch8", "r");
    if (game == NULL) {
        fprintf(stdout, "Error loading game\n");
        return EXIT_FAILURE;
    } else if (setup_display() != 1) {
        return EXIT_FAILURE;
    }
    memory = setup_memory(game); //also sets up registers
    setup_events();

    unsigned char first_byte;
    unsigned char second_byte;
    int test = 0;
    while(test < 50) {
        //Handle events
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                test = 50;
            }
            else {
                handle_event(&event);
            }
        }
        //Fetch
        first_byte = memory[PC];
        second_byte = memory[PC + 1];

        //Decode and execute
        decode(first_byte, second_byte);

        //Increase program counter
        PC += 2;
        test++;
    }
    SDL_Delay(3000);
    tear_down_display();
    return EXIT_SUCCESS;
}

int decode(unsigned char first_byte, unsigned char second_byte) {
    unsigned char first_nible = FIRST_HALF_BYTE(first_byte); //0xF0 = 1111 0000
    unsigned char second_nible = SECOND_HALF_BYTE(first_byte); //0x0F = 0000 1111
    unsigned char third_nible = FIRST_HALF_BYTE(second_byte);
    unsigned char fourth_nible = SECOND_HALF_BYTE(second_byte);

    //printf("nibles: %02x, %02x, %02x, %02x\n", first_nible, second_nible, third_nible, fourth_nible);
    switch(first_nible) {
        case 0 :
            decode_first_nible_zero(second_nible, third_nible, fourth_nible);
            break;
        case 1 :
            decode_first_nible_one(second_nible, third_nible, fourth_nible);
            break;
        case 6 :
            registers[second_nible] = ((third_nible << 4) | fourth_nible);
            break;
        case 7 :
            registers[second_nible] += ((third_nible << 4) | fourth_nible);
            break;
        case 0xA :
            I = ((second_nible << 8) | (third_nible << 4) | fourth_nible);
            break;
        case 0xD :
            update_display(second_nible, third_nible, fourth_nible);
            break;
        case 0xF :
            printf("F HAPPENED\n");
            decode_first_nible_f(second_nible, third_nible, fourth_nible);
            break;
        default:
            printf("SHOULD NEVER HAPPEN2: %01x\n", first_nible);
            break;
    }
    return 1;
}

static int decode_first_nible_f(unsigned char second_nible, unsigned char third_nible,
        unsigned char fourth_nible)
{
    printf("f, %01x, %01x, %01x\n", second_nible, third_nible, fourth_nible);
    return 0;
}

static int decode_first_nible_zero(unsigned char second_nible,
        unsigned char third_nible, unsigned char fourth_nible)
{
    switch(second_nible) {
        case 0:
            if (second_nible == 0x0 && third_nible == 0xE) {
                if (fourth_nible == 0x0) {
                    //Clear screen
                    clear_display();
                    return 1;
                } else if (fourth_nible == 0xE) {
                    //Return insn
                    printf("SHOULD NEVER HAPPEN 1\n");
                    PC = stack_pop();
                    return 1;
                }
            }
            printf("SHOULD NEVER HAPPEN 5\n");
            break;//call insn so we do nothing
        default :
            //If the opcode is not 0 the it is a call insn
            //Skip insn since this is used to execute asm at addr NNN
            printf("SHOULD NEVER HAPPEN 3\n");
            break;
    }
    return 1;
}

//Jump insn
static int decode_first_nible_one(unsigned char second_nible,
        unsigned char third_nible, unsigned char fourth_nible)
{
    PC = (second_nible << 8) | (third_nible << 4) | fourth_nible;
    return 1;
}

static int update_display(unsigned char Vx,
        unsigned char Vy, unsigned char N)
{

    unsigned char x = registers[Vx];
    unsigned char y = registers[Vy];

    struct draw_insn_data drawing_data;
    drawing_data.x = x;
    drawing_data.y = y;
    drawing_data.N = N;
    int drawing_data_size = sizeof(struct draw_insn_data);

    struct draw_insn_data *drawing_data_ref = malloc(drawing_data_size);
    memcpy(drawing_data_ref, &drawing_data, drawing_data_size);

    SDL_Event event;
    event.type = chip8_event_types.update_display;
    event.user.type = chip8_event_types.update_display;
    event.user.data1 = drawing_data_ref;
    event.user.data2 = memory;

    SDL_PushEvent(&event);//Data gets copied

    return 1;
}






















