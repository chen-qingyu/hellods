#include "ArrayList.h"

#include <limits.h> // INT_MAX
#include <stdlib.h> // malloc free realloc

#include "../common/check_bounds.h"
#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

// Initial capacity.
#define INIT_CAPACITY 8

// Maximum capacity.
#define MAX_CAPACITY (INT_MAX - 1) // - 1 to prevent boundary subscript overflow

struct ArrayList
{
    /// Number of elements.
    int size;

    /// Available capacity.
    int capacity;

    /// Pointer to the data.
    ArrayListItem* data;
};

/*******************************
Helper functions implementation.
*******************************/

// Expand capacity safely.
static inline void expand_capacity(ArrayList* self)
{
    self->capacity = (self->capacity < MAX_CAPACITY / 2) ? self->capacity * 2 : MAX_CAPACITY; // double the capacity until MAX_CAPACITY
    self->data = (ArrayListItem*)realloc(self->data, sizeof(ArrayListItem) * self->capacity);
    check_pointer(self->data);
}

/*******************************
Interface functions implementation.
*******************************/

ArrayList* ArrayList_Create(void)
{
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    check_pointer(list);

    list->size = 0;
    list->capacity = INIT_CAPACITY;
    list->data = (ArrayListItem*)malloc(sizeof(ArrayListItem) * list->capacity);
    check_pointer(list->data);

    return list;
}

void ArrayList_Destroy(ArrayList* self)
{
    if (self)
    {
        free(self->data);
        free(self);
    }
}

int ArrayList_Size(const ArrayList* self)
{
    return self->size;
}

bool ArrayList_IsEmpty(const ArrayList* self)
{
    return self->size == 0;
}

ArrayListItem ArrayList_At(const ArrayList* self, int index) // list[index]
{
    check_bounds(index, -self->size, self->size);

    return index >= 0 ? self->data[index] : self->data[index + self->size];
}

int ArrayList_Find(const ArrayList* self, ArrayListItem data)
{
    int index = 0;

    while (index < self->size && self->data[index] != data)
    {
        index++;
    }

    return index < self->size ? index : -1;
}

void ArrayList_Insert(ArrayList* self, int index, ArrayListItem data)
{
    // check
    check_full(self->size, MAX_CAPACITY);

    check_bounds(index, -self->size, self->size + 1);

    // expand capacity
    if (self->size == self->capacity)
    {
        expand_capacity(self);
    }

    // index
    index = index >= 0 ? index : index + self->size;
    for (int i = self->size; i > index; i--)
    {
        self->data[i] = self->data[i - 1];
    }

    // insert
    self->data[index] = data;

    // resize
    ++self->size;
}

ArrayListItem ArrayList_Remove(ArrayList* self, int index)
{
    // check
    check_empty(self->size);

    check_bounds(index, -self->size, self->size);

    // get data
    index = index >= 0 ? index : index + self->size;
    ArrayListItem data = self->data[index];

    // index and remove
    for (int i = index + 1; i < self->size; i++)
    {
        self->data[i - 1] = self->data[i];
    }

    // resize
    --self->size;

    // return data
    return data;
}

void ArrayList_Traverse(ArrayList* self, void (*p_trav)(ArrayListItem data))
{
    for (int i = 0; i < self->size; i++)
    {
        p_trav(self->data[i]);
    }
}

void ArrayList_Reverse(ArrayList* self)
{
    for (int i = 0, j = self->size - 1; i < j; ++i, --j)
    {
        ArrayListItem tmp = self->data[i];
        self->data[i] = self->data[j];
        self->data[j] = tmp;
    }
}

void ArrayList_Clear(ArrayList* self)
{
    if (self->size != 0)
    {
        self->size = 0;
        self->capacity = INIT_CAPACITY;
        free(self->data);
        self->data = (ArrayListItem*)malloc(sizeof(ArrayListItem) * self->capacity);
        check_pointer(self->data);
    }
}
