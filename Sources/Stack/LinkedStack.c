#include "LinkedStack.h"

#include <limits.h> // INT_MAX
#include <stdlib.h> // malloc free NULL

#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

struct node
{
    StackItem data;
    struct node* next;
};

struct stack
{
    int size;
    struct node* top;
};

/*******************************
Helper functions implementation.
*******************************/

/*******************************
Interface functions implementation.
*******************************/

Stack* LinkedStack_Create(void)
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    check_pointer(stack);

    stack->top = NULL;
    stack->size = 0;

    return stack;
}

void LinkedStack_Destroy(Stack* self)
{
    while (self->top)
    {
        struct node* current = self->top->next;
        free(self->top);
        self->top = current;
    }
    free(self);
}

int LinkedStack_Size(const Stack* self)
{
    return self->size;
}

bool LinkedStack_IsEmpty(const Stack* self)
{
    return self->size == 0;
}

void LinkedStack_Push(Stack* self, StackItem data)
{
    check_full(self->size, INT_MAX);

    struct node* node = (struct node*)malloc(sizeof(struct node));
    check_pointer(node);

    node->data = data;
    node->next = self->top;
    self->top = node;

    self->size++;
}

StackItem LinkedStack_Pop(Stack* self)
{
    check_empty(self->size);

    struct node* node = self->top;
    self->top = node->next;
    StackItem data = node->data;
    free(node);

    self->size--;

    return data;
}

StackItem LinkedStack_Top(const Stack* self)
{
    check_empty(self->size);

    return self->top->data;
}
