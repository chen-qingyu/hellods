#include "LinkedStack.h"

#include <limits.h> // INT_MAX
#include <stdlib.h> // malloc free NULL

#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

struct LinkedStackNode
{
    /// Data stored in the node.
    LinkedStackItem data;

    /// Successor.
    struct LinkedStackNode* next;
};

struct LinkedStack
{
    /// Number of elements.
    int size;

    /// Pointer to the top element.
    struct LinkedStackNode* top;
};

/*******************************
Helper functions implementation.
*******************************/

// Remove all of the elements from the queue.
static inline void clear(LinkedStack* self)
{
    while (self->top)
    {
        struct LinkedStackNode* current = self->top->next;
        free(self->top);
        self->top = current;
    }
    self->size = 0;
}

/*******************************
Interface functions implementation.
*******************************/

LinkedStack* LinkedStack_Create(void)
{
    LinkedStack* stack = (LinkedStack*)malloc(sizeof(LinkedStack));
    check_pointer(stack);

    stack->top = NULL;
    stack->size = 0;

    return stack;
}

void LinkedStack_Destroy(LinkedStack* self)
{
    // let it crush if self is invalid

    clear(self);

    free(self);
}

int LinkedStack_Size(const LinkedStack* self)
{
    return self->size;
}

bool LinkedStack_IsEmpty(const LinkedStack* self)
{
    return self->size == 0;
}

void LinkedStack_Push(LinkedStack* self, LinkedStackItem data)
{
    check_full(self->size, INT_MAX);

    struct LinkedStackNode* node = (struct LinkedStackNode*)malloc(sizeof(struct LinkedStackNode));
    check_pointer(node);

    node->data = data;
    node->next = self->top;
    self->top = node;

    self->size++;
}

LinkedStackItem LinkedStack_Pop(LinkedStack* self)
{
    check_empty(self->size);

    struct LinkedStackNode* node = self->top;
    self->top = node->next;
    LinkedStackItem data = node->data;
    free(node);

    self->size--;

    return data;
}

LinkedStackItem LinkedStack_Top(const LinkedStack* self)
{
    check_empty(self->size);

    return self->top->data;
}

void LinkedStack_Clear(LinkedStack* self)
{
    if (self->size != 0)
    {
        clear(self);
    }
}
