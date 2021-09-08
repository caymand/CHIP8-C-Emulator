#define STACK_SIZE 16


typedef unsigned short stack_element_t;

extern stack_element_t stack[STACK_SIZE];
extern int stack_top;

int stack_pop();
//Returns -1 upon error
int stack_push(stack_element_t element);
