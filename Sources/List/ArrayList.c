#include "ArrayList.h"

#include <limits.h> // INT_MAX
#include <stdlib.h> // malloc free realloc

#include "../common/check_bounds.h"
#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

struct list
{
    // Number of elements.
    int count;

    // Available capacity.
    int capacity;

    // Pointer to the data.
    ListItem* data;
};

/*******************************
Helper functions implementation.
*******************************/

// Expand capacity safely.
static inline void expand_capacity(List* self)
{
    self->capacity = (self->capacity < INT_MAX / 2) ? self->capacity * 2 : INT_MAX; // double the capacity until INT_MAX
    self->data = (ListItem*)realloc(self->data, sizeof(ListItem) * self->capacity);
    check_pointer(self->data);
}

/*******************************
Interface functions implementation.
*******************************/

List* ArrayList_Create(void)
{
    List* list = (List*)malloc(sizeof(List));
    check_pointer(list);

    list->count = 0;
    list->capacity = 8;
    list->data = (ListItem*)malloc(sizeof(ListItem) * list->capacity);
    check_pointer(list->data);

    return list;
}

void ArrayList_Destroy(List* self)
{
    free(self->data);
    free(self);
}

int ArrayList_Size(const List* self)
{
    return self->count;
}

bool ArrayList_IsEmpty(const List* self)
{
    return self->count == 0;
}

ListItem ArrayList_At(const List* self, int index) // list[index]
{
    check_bounds(index, -self->count, self->count);

    return index >= 0 ? self->data[index] : self->data[index + self->count];
}

int ArrayList_Find(const List* self, ListItem data)
{
    int index = 0;

    while (index < self->count && self->data[index] != data)
    {
        index++;
    }

    return index < self->count ? index : LIST_NOT_FOUND;
}

void ArrayList_Insert(List* self, int index, ListItem data)
{
    // check
    check_full(self->count, INT_MAX);

    check_bounds(index, 0, self->count + 1);

    // expand capacity
    if (self->count == self->capacity)
    {
        expand_capacity(self);
    }

    // index
    for (int i = self->count; i > index; i--)
    {
        self->data[i] = self->data[i - 1];
    }

    // insert
    self->data[index] = data;

    // resize
    ++self->count;
}

ListItem ArrayList_Remove(List* self, int index)
{
    // check
    check_empty(self->count);

    check_bounds(index, 0, self->count);

    // get data
    ListItem data = self->data[index];

    // index and remove
    for (int i = index + 1; i < self->count; i++)
    {
        self->data[i - 1] = self->data[i];
    }

    // resize
    --self->count;

    // return data
    return data;
}

void ArrayList_Traverse(List* self, void (*p_trav)(ListItem data))
{
    for (int i = 0; i < self->count; i++)
    {
        p_trav(self->data[i]);
    }
}

void ArrayList_Reverse(List* self)
{
    for (int i = 0, j = self->count - 1; i < j; ++i, --j)
    {
        ListItem tmp = self->data[i];
        self->data[i] = self->data[j];
        self->data[j] = tmp;
    }
}
