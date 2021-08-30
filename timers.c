#include <stdlib.h>
#include <stdio.h>
#include "timers.h"
#include <pthread.h>
#include <CoreFoundation/CFRunLoop.h>

static pthread_t timer_thread;
static unsigned char delay_timer;
static pthread_mutex_t delay_timer_mutex = PTHREAD_MUTEX_INITIALIZER;

//TODO: Using a runloop might be overkill. Consider creating dispatch timer


int create_delay_timer(unsigned short ticks) {
    unsigned short *ticks_ref = malloc(sizeof(unsigned short));
    *ticks_ref = ticks;
    return pthread_create(&timer_thread, NULL, setup_delay_timer, ticks_ref);
}

int set_delay_timer(unsigned short ticks) {
    if (pthread_mutex_lock(&delay_timer_mutex) != 0 ) {
        printf("Error setting up the delay timer\n");
    }
    //In this case the runlop was invalidated, so we have to start it again
    if (delay_timer == 0) {
        unsigned short *ticks_ref = malloc(sizeof(unsigned short));
        *ticks_ref = ticks;
        if (pthread_mutex_unlock(&delay_timer_mutex) != 0) {
            printf("Error unlocking the mutex\n");
        }
        setup_delay_timer(ticks_ref);
        return 1;
    }
    delay_timer = ticks;
    if (pthread_mutex_unlock(&delay_timer_mutex) != 0) {
        printf("Error unlocking the mutex\n");
    }
    return 1;
}

int get_delay_timer(unsigned short *Vx) {
    if (pthread_mutex_lock(&delay_timer_mutex) != 0 ) {
        printf("Error setting up the delay timer\n");
    }
    *Vx = delay_timer;
    if (pthread_mutex_unlock(&delay_timer_mutex) != 0) {
        printf("Error unlocking the mutex\n");
    }
    return 1;
}
//Method run in other thread
static void *setup_delay_timer(void *ticks) {
    unsigned short *ticks_ref = (unsigned short *) ticks;
    unsigned short delay_timer_ticks = *ticks_ref;
    free(ticks_ref);

    double timer_frequency = (double) 1/60; //60 Hz

    if (pthread_mutex_lock(&delay_timer_mutex) != 0 ) {
        printf("Error setting up the delay timer\n");
    }
    delay_timer = delay_timer_ticks;
    if (pthread_mutex_unlock(&delay_timer_mutex) != 0) {
        printf("Error unlocking the mutex\n");
    }
    CFRunLoopRef run_loop = CFRunLoopGetCurrent();
    CFRunLoopTimerContext timer_context = {0, NULL, NULL, NULL, NULL};
    CFRunLoopTimerRef timer_ref = CFRunLoopTimerCreate(NULL, CFAbsoluteTimeGetCurrent(),
            timer_frequency, 0, 0, decrement_delay_timer, &timer_context);
    CFRunLoopAddTimer(run_loop, timer_ref, kCFRunLoopDefaultMode);
    CFRunLoopRun();
    return NULL;
}

static void decrement_delay_timer(CFRunLoopTimerRef timer, void *info) {
    (void) info;
    if (pthread_mutex_lock(&delay_timer_mutex) != 0 ) {
        printf("Error setting up the delay timer\n");
    }
    delay_timer--;
    if (delay_timer == 0) {
        if (pthread_mutex_unlock(&delay_timer_mutex) != 0) {
            printf("Error unlocking the mutex\n");
        }
        CFRunLoopTimerInvalidate(timer); //Invalidates runloop since this is the only source
        return;
    }
    if (pthread_mutex_unlock(&delay_timer_mutex) != 0) {
        printf("Error unlocking the mutex\n");
    }
}

