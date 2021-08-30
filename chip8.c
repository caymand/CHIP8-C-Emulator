#include <stdlib.h>
#include <stdio.h>
#include "chip8.h"
#include "memory.h"
#include "timers.h"
#include <unistd.h>
//Global variables
unsigned char *memory;

int main() {

    FILE *game = fopen("../games/pong.ch8", "r");
    if (game == NULL) {
        fprintf(stdout, "Error loading game\n");
        return EXIT_FAILURE;
    }

    //memory = setup_memory();
    printf("Starting to print stuff\n");
    printf("Succes: %d\n", create_delay_timer(120));
    unsigned short timer;
    sleep(1);
    get_delay_timer(&timer);
    printf("Timer: %d\n", timer);
    sleep(2);
    return EXIT_SUCCESS;
}
