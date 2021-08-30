#include "stack_tests.h"
#include "../stack.h"
#include <stdio.h>

static void printResult(int expected, char name[]) {
    printf("%s: %s\n", name, (expected > 0) ? "true" : "false");
}

static void pushElementOnEmptyStack() {
    //Arrange
    stack_top = 0;

    //Act
    int res = stack_push(1) > 0 && stack_top == 1;

    //Assert
    printResult(res, "pushElementOnEmptyStack");
}

static void cannotPushFullStack() {

    stack_top = 16;

    //Act
    int res = stack_push(1) == -1 && stack_top == 16;

    //Assert
    printResult(res, "cannotPushFullStack");
}

static void cannotPopEmptyStack() {
    //Arrange
    stack_top = 0;

    //Act
    int res = stack_pop() == -1 && stack_top == 0;

    //Assert
    printResult(res, "cannotPopEmptyStack");
}

static void canPopFromStack() {
    stack_top = 3;
    stack_push(1);
    stack_push(2);
    stack_push(3);

    int res = stack_pop() == 3;// && stack_top == 2;
    printf("res: %d", res);
    printResult(res, "canPopFromStack");
}
void run_stack_tests() {
    pushElementOnEmptyStack();
    cannotPushFullStack();
    cannotPopEmptyStack();
    canPopFromStack();
}

