CC=clang
CFLAGS= -Wall -Wextra -pedantic -g
#-Werror
FILES=chip8.c memory.c timers.c stack.c display.c events.c
FRAMEWORK = -framework CoreFoundation
SDL2 = -I /usr/local/Cellar/sdl2/2.0.16/include -L /usr/local/Cellar/sdl2/2.0.16/lib -l SDL2-2.0.0

chip8: $(FILES)
	$(CC) $(CFLAGS) $(FRAMEWORK) -o chip8 $(FILES) $(SDL2)

all: chip8

tests: tests/testc.c tests/stack_tests.c stack.c
	$(CC) $(CFLAGS) -o tests_res tests/testc.c tests/stack_tests.c stack.c

#all:
#	$(CC) $(CFLAGS) -o $@ chip8
#
#file:
#	$(CC) $(CFLAGS) -0 file file.c
