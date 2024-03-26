#include "MaxHeap.h"

#include <limits.h> // INT_MAX
#include <stdlib.h> // malloc free realloc

#include "../common/utility.h"

// Max value of MaxHeapItem.
#define MAX_ITEM INT_MAX

// Initial capacity.
#define INIT_CAPACITY 8

// Maximum capacity.
#define MAX_CAPACITY (INT_MAX - 1) // - 1 to prevent boundary subscript overflow

/// Max Heap.
struct MaxHeap
{
    /// Number of elements.
    int size;

    /// Available capacity.
    int capacity;

    /// Pointer to the data.
    MaxHeapItem* data;
};

/*
 * Helpers
 */

// Expand capacity safely.
static inline void expand_capacity(MaxHeap* self)
{
    self->capacity = (self->capacity < MAX_CAPACITY / 2) ? self->capacity * 2 : MAX_CAPACITY; // double the capacity until MAX_CAPACITY
    self->data = (MaxHeapItem*)realloc(self->data, sizeof(MaxHeapItem) * self->capacity);
    check_pointer(self->data);
}

/*
 * Functions
 */

MaxHeap* MaxHeap_Create(void)
{
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    check_pointer(heap);

    heap->size = 0;
    heap->capacity = INIT_CAPACITY;
    heap->data = (MaxHeapItem*)malloc(heap->capacity * sizeof(MaxHeapItem));
    check_pointer(heap->data);

    heap->data[0] = MAX_ITEM;

    return heap;
}

void MaxHeap_Destroy(MaxHeap* self)
{
    // let it crush if self is invalid

    free(self->data);
    free(self);
}

int MaxHeap_Size(const MaxHeap* self)
{
    return self->size;
}

bool MaxHeap_IsEmpty(const MaxHeap* self)
{
    return self->size == 0;
}

void MaxHeap_Push(MaxHeap* self, MaxHeapItem data)
{
    check_full(self->size, MAX_CAPACITY);

    if (self->size == self->capacity) // need to expand capacity
    {
        expand_capacity(self);
    }

    int pos;
    for (pos = ++self->size; self->data[pos / 2] < data; pos /= 2)
    {
        self->data[pos] = self->data[pos / 2];
    }
    self->data[pos] = data;
}

MaxHeapItem MaxHeap_Pop(MaxHeap* self)
{
    check_empty(self->size);

    MaxHeapItem max_item = self->data[1];
    MaxHeapItem tmp = self->data[self->size--];

    int parent, child;
    for (parent = 1; parent * 2 <= self->size; parent = child)
    {
        child = parent * 2;
        if ((child != self->size) && (self->data[child] < self->data[child + 1]))
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

MaxHeapItem MaxHeap_Top(MaxHeap* self)
{
    check_empty(self->size);

    return self->data[1];
}

void MaxHeap_Clear(MaxHeap* self)
{
    self->size = 0; // plain old data
}
