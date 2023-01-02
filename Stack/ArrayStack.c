#include "ArrayStack.h"

#include <stdlib.h> // malloc free

#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

// 为保证入栈是严格的 O(1) 时间复杂度，故这里采用固定的容量，而不是动态增长。
#define STACK_CAPACITY 256

struct stack
{
    StackItem data[STACK_CAPACITY];
    int top;
};

/*******************************
Helper functions implementation.
*******************************/

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
    check_full(ArrayStack_Size(self), STACK_CAPACITY);

    self->data[++(self->top)] = data;
}

StackItem ArrayStack_Pop(Stack* self)
{
    check_empty(ArrayStack_Size(self));

    return self->data[(self->top)--];
}

StackItem ArrayStack_Top(const Stack* self)
{
    check_empty(ArrayStack_Size(self));

    return self->data[self->top];
}
