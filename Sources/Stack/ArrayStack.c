#include "ArrayStack.h"

#include <stdlib.h> // malloc free

#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

// 为保证入栈是严格的 O(1) 时间复杂度，故这里采用固定的容量，而不是动态增长。
#define MAX_CAPACITY 256

struct ArrayStack
{
    /// Pointer to the data.
    ArrayStackItem data[MAX_CAPACITY];

    /// Index of the top element.
    int top;
};

/*******************************
Helper functions implementation.
*******************************/

/*******************************
Interface functions implementation.
*******************************/

ArrayStack* ArrayStack_Create(void)
{
    ArrayStack* stack = (ArrayStack*)malloc(sizeof(ArrayStack));
    check_pointer(stack);

    stack->top = -1;

    return stack;
}

void ArrayStack_Destroy(ArrayStack* self)
{
    // let it crush if self is invalid

    free(self);
}

int ArrayStack_Size(const ArrayStack* self)
{
    return self->top + 1;
}

bool ArrayStack_IsEmpty(const ArrayStack* self)
{
    return self->top + 1 == 0;
}

void ArrayStack_Push(ArrayStack* self, ArrayStackItem data)
{
    check_full(ArrayStack_Size(self), MAX_CAPACITY);

    self->data[++(self->top)] = data;
}

ArrayStackItem ArrayStack_Pop(ArrayStack* self)
{
    check_empty(ArrayStack_Size(self));

    return self->data[(self->top)--];
}

ArrayStackItem ArrayStack_Top(const ArrayStack* self)
{
    check_empty(ArrayStack_Size(self));

    return self->data[self->top];
}
