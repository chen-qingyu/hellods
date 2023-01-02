#include "MaxHeap.h"

#include <limits.h> // INT_MAX
#include <stdlib.h> // malloc free realloc

#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

#define MAX_ITEM INT_MAX // max value of HeapItem

struct heap
{
    HeapItem* data;
    int count;
    int capacity;
};

/*******************************
Helper functions implementation.
*******************************/

// Expand capacity safely.
static inline void expand_capacity(Heap* self)
{
    self->capacity = (self->capacity < INT_MAX / 2) ? self->capacity * 2 : INT_MAX; // double the capacity until INT_MAX
    self->data = (HeapItem*)realloc(self->data, sizeof(HeapItem) * self->capacity);
    check_pointer(self->data);
}

/*******************************
Interface functions implementation.
*******************************/

Heap* MaxHeap_Create(void)
{
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    check_pointer(heap);

    heap->count = 0;
    heap->capacity = 8;
    heap->data = (HeapItem*)malloc(heap->capacity * sizeof(HeapItem));
    check_pointer(heap->data);

    heap->data[0] = MAX_ITEM;

    return heap;
}

void MaxHeap_Destroy(Heap* self)
{
    free(self->data);
    free(self);
}

int MaxHeap_Size(const Heap* self)
{
    return self->count;
}

bool MaxHeap_IsEmpty(const Heap* self)
{
    return self->count == 0;
}

void MaxHeap_Push(Heap* self, HeapItem data)
{
    check_full(self->count, INT_MAX);

    if (self->count == self->capacity) // need to expand capacity
    {
        expand_capacity(self);
    }

    int pos;
    for (pos = ++self->count; self->data[pos / 2] < data; pos /= 2)
    {
        self->data[pos] = self->data[pos / 2];
    }
    self->data[pos] = data;
}

HeapItem MaxHeap_Pop(Heap* self)
{
    check_empty(self->count);

    HeapItem max_item = self->data[1];
    HeapItem tmp = self->data[self->count--];

    int parent, child;
    for (parent = 1; parent * 2 <= self->count; parent = child)
    {
        child = parent * 2;
        if ((child != self->count) && (self->data[child] < self->data[child + 1]))
        {
            child++;
        }

        if (tmp >= self->data[child])
        {
            break;
        }
        else
        {
            self->data[parent] = self->data[child];
        }
    }
    self->data[parent] = tmp;

    return max_item;
}

HeapItem MaxHeap_Top(Heap* self)
{
    check_empty(self->count);

    return self->data[1];
}
