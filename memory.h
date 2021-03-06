#include <stdio.h>
// MACROS
#define MEM_SIZE 4096
#define MEM_START 512
#define FONT_SET_START 0x50
#define FONT_SET_LENGTH 80
#define FONT_SET_END FONT_SET_START + FONT_SET_LENGTH
#define NUM_REGISTERS 16
#define VF NUM_REGISTERS - 1
#define GAME_ADDR_START 0x200

extern unsigned char registers[NUM_REGISTERS];
extern unsigned short I;
unsigned char *setup_memory(FILE *game);
