#ifndef __STACK_H__

#define __STACK_H__

#include <stdbool.h>
#include <stdlib.h>

typedef struct StackNode {
    void *data;
    StackNode *next;
} StackNode;

typedef struct Stack {
    StackNode *top;
    size_t size;

    size_t data_size;
    bool should_pop_free_data;
} Stack;

void stack_push(Stack *stack, void *data);
void *stack_pop(Stack *stack);

#endif  // !__STACK_H__