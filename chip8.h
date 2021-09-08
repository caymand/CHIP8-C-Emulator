#include "/usr/local/Cellar/sdl2/2.0.16/include/SDL2/SDL.h"

#define FIRST_HALF_BYTE(byte) ((byte & 0xF0) >> 4) //0xF0 = 1111 0000
#define SECOND_HALF_BYTE(byte) (byte & 0x0F)//0x0F = 0000 1111


static int decode_first_nible_zero(unsigned char second_nible,
        unsigned char third_nible, unsigned char fourth_nible);

//static int decode_second_nible_zero(unsigned char third_nible, unsigned char fourth_nible);
//static int decode_third_nible_zero(unsigned char fourth_nible);


static int decode_first_nible_one(unsigned char second_nible,
        unsigned char third_nible, unsigned char fourth_nible);

int decode(unsigned char first_byte, unsigned char second_byte);

static int decode_first_nible_f(unsigned char second_nible, unsigned char third_nible,
        unsigned char fourth_nible);

static int update_display(unsigned char x, unsigned char y, unsigned char N);

static int handle_event(SDL_Event *event);

