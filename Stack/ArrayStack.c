#include "ArrayStack.h"

#include <stdio.h>
#include <stdlib.h>

#define STACK_CAPACITY 100

struct stack
{
    StackItem data[STACK_CAPACITY];
    int top;
};

/*******************************
Helper functions implementation.
*******************************/

// Check whether the pointer is a non-null pointer.
static inline void check_pointer(const void* pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

/*******************************
Interface functions implementation.
*******************************/

Stack* ArrayStack_Create(void)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    check_pointer(stack);

    stack->top = -1;

    return stack;
}

void ArrayStack_Destroy(Stack* self)
{
    free(self);
}

int ArrayStack_Size(const Stack* self)
{
    return self->top + 1;
}

bool ArrayStack_IsEmpty(const Stack* self)
{
    return self->top + 1 == 0;
}

void ArrayStack_Push(Stack* self, StackItem data)
{
    if (ArrayStack_Size(self) == STACK_CAPACITY)
    {
        fprintf(stderr, "ERROR: The stack is full.\n");
        return;
    }

    self->data[++(self->top)] = data;
}

StackItem ArrayStack_Pop(Stack* self)
{
    if (ArrayStack_IsEmpty(self))
    {
        fprintf(stderr, "ERROR: The stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    return self->data[(self->top)--];
}

StackItem ArrayStack_Top(const Stack* self)
{
    if (ArrayStack_IsEmpty(self))
    {
        fprintf(stderr, "ERROR: The stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    return self->data[self->top];
}
