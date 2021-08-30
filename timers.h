#include <CoreFoundation/CFRunLoop.h>

int create_delay_timer(unsigned short ticks);
int set_delay_timer(unsigned short ticks);
int get_delay_timer(unsigned short *Vx);

static void *setup_delay_timer(void *ticks);
static void decrement_delay_timer();

