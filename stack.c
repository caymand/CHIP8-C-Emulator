#include "stack.h"

int stack_top = 0;
stack_element_t stack[STACK_SIZE];

int stack_push(stack_element_t element) {
    if (stack_top == STACK_SIZE) {
        //TODO: Error msg
        return -1;
    }
    stack[stack_top] = element;
    stack_top++;

    return element;
}

int stack_pop() {
    if (stack_top == 0) {
        //TODO: Error msg
        return -1;
    }
    stack_element_t element = stack[stack_top - 1];
    stack_top -= 1;
    return element;
}
