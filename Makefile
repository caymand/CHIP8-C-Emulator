CC=clang
CFLAGS= -Wall -Wextra -pedantic -g
#-Werror
FILES=chip8.c memory.c timers.c stack.c
FRAMEWORK = -framework CoreFoundation

chip8: $(FILES)
	$(CC) $(CFLAGS) $(FRAMEWORK) -o chip8 $(FILES)

all: chip8

tests: tests/testc.c tests/stack_tests.c stack.c
	$(CC) $(CFLAGS) -o tests_res tests/testc.c tests/stack_tests.c stack.c

#all:
#	$(CC) $(CFLAGS) -o $@ chip8
#
#file:
#	$(CC) $(CFLAGS) -0 file file.c
