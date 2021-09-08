#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define PIXEL_SCALE_FACTOR 10

#define BIT_N(num, n) ((num >> n) & 1)

typedef struct draw_insn_data {
    unsigned char x;
    unsigned char y;
    unsigned char N;
} draw_insn_data;

int calculate_display_pixels(unsigned char x, unsigned char y, unsigned char N, unsigned char* memory);
int clear_display();
int draw_display();

int setup_display();
int tear_down_display();
