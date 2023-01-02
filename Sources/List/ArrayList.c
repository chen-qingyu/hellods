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

ListItem ArrayList_At(const List* self, int i) // list[i]
{
    check_bounds(i, -self->count, self->count);

    return i >= 0 ? self->data[i] : self->data[i + self->count];
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

void ArrayList_Insert(List* self, int i, ListItem data)
{
    check_full(self->count, INT_MAX);

    check_bounds(i, 0, self->count + 1);

    if (self->count == self->capacity) // need to expand capacity
    {
        expand_capacity(self);
    }

    for (int j = self->count; j > i; j--)
    {
        self->data[j] = self->data[j - 1];
    }
    self->data[i] = data;
    ++self->count;
}

void ArrayList_Delete(List* self, int i)
{
    check_empty(self->count);

    check_bounds(i, 0, self->count);

    for (int j = i + 1; j < self->count; j++)
    {
        self->data[j - 1] = self->data[j];
    }
    --self->count;
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
