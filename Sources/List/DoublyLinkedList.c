#include "DoublyLinkedList.h"

#include <limits.h> // INT_MAX
#include <stdlib.h> // malloc free NULL abs

#include "../common/check_bounds.h"
#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

struct DoublyLinkedListNode
{
    /// Data stored in the node.
    DoublyLinkedListItem data;

    /// Predecessor.
    struct DoublyLinkedListNode* prev;

    /// Successor.
    struct DoublyLinkedListNode* next;
};

struct DoublyLinkedList
{
    /// Number of elements.
    int size;

    /// Pointer to the header (rank = -1).
    struct DoublyLinkedListNode* header;

    /// Pointer to the trailer (rank = size).
    struct DoublyLinkedListNode* trailer;

    /// Index of the latest accessed element. For DoublyLinkedList_At().
    int latest;

    /// Pointer to the latest accessed element. For DoublyLinkedList_At().
    struct DoublyLinkedListNode* p_latest;
};

/*******************************
Helper functions implementation.
*******************************/

// Remove all of the elements from the list.
static inline void clear(DoublyLinkedList* self)
{
    while (self->header->next != self->trailer)
    {
        struct DoublyLinkedListNode* node = self->header->next->next;
        free(self->header->next);
        self->header->next = node;
    }
    self->size = 0;
    self->latest = -1;
    self->p_latest = self->header;
}

/*******************************
Interface functions implementation.
*******************************/

DoublyLinkedList* DoublyLinkedList_Create(void)
{
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    check_pointer(list);

    list->size = 0;
    list->header = (struct DoublyLinkedListNode*)malloc(sizeof(struct DoublyLinkedListNode));
    check_pointer(list->header);
    list->trailer = (struct DoublyLinkedListNode*)malloc(sizeof(struct DoublyLinkedListNode));
    check_pointer(list->trailer);
    list->latest = -1;
    list->p_latest = list->header;

    list->header->prev = NULL;
    list->header->next = list->trailer;

    list->trailer->prev = list->header;
    list->trailer->next = NULL;

    return list;
}

void DoublyLinkedList_Destroy(DoublyLinkedList* self)
{
    // let it crush if self is invalid

    clear(self);

    free(self->header);
    free(self->trailer);
    free(self);
}

int DoublyLinkedList_Size(const DoublyLinkedList* self)
{
    return self->size;
}

bool DoublyLinkedList_IsEmpty(const DoublyLinkedList* self)
{
    return self->size == 0;
}

DoublyLinkedListItem DoublyLinkedList_At(const DoublyLinkedList* self, int index) // list[index] for index in range 0 to size will be O(1) on each access
{
    check_bounds(index, -self->size, self->size);

    index = index >= 0 ? index : index + self->size;

    DoublyLinkedList* list = (DoublyLinkedList*)self; // drop out const

    // too far from the last accessed element
    if (abs(index - self->latest) > self->size / 2)
    {
        // closer to the header or trailer
        list->p_latest = (index < self->latest) ? self->header->next : self->trailer->prev;
        list->latest = (index < self->latest) ? 0 : self->size - 1;
    }

    if (index < self->latest)
    {
        while (index < self->latest)
        {
            list->latest--;
            list->p_latest = list->p_latest->prev;
        }
    }
    else if (index > self->latest)
    {
        while (index > self->latest)
        {
            list->latest++;
            list->p_latest = list->p_latest->next;
        }
    }
    // else the element accessed this time is the same as the last time

    return self->p_latest->data;
}

int DoublyLinkedList_Find(const DoublyLinkedList* self, DoublyLinkedListItem data)
{
    int index = 0;
    struct DoublyLinkedListNode* current = self->header->next;

    while (current != self->trailer && current->data != data)
    {
        current = current->next;
        index++;
    }

    return current != self->trailer ? index : -1;
}

void DoublyLinkedList_Insert(DoublyLinkedList* self, int index, DoublyLinkedListItem data)
{
    // check
    check_full(self->size, INT_MAX);

    check_bounds(index, -self->size, self->size + 1);

    // index
    index = index >= 0 ? index : index + self->size;

    struct DoublyLinkedListNode* current = NULL;
    if (index < self->size / 2)
    {
        current = self->header->next;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
    }
    else
    {
        current = self->trailer; // be careful, index may be same as size
        for (int i = self->size; i > index; i--)
        {
            current = current->prev;
        }
    }

    // insert
    struct DoublyLinkedListNode* node = (struct DoublyLinkedListNode*)malloc(sizeof(struct DoublyLinkedListNode));
    check_pointer(node);
    node->data = data;
    node->prev = current->prev;
    node->next = current;

    current->prev->next = node;
    current->prev = node;

    // resize
    ++self->size;
}

DoublyLinkedListItem DoublyLinkedList_Remove(DoublyLinkedList* self, int index)
{
    // check
    check_empty(self->size);

    check_bounds(index, -self->size, self->size);

    // index
    index = index >= 0 ? index : index + self->size;

    struct DoublyLinkedListNode* current = NULL;
    if (index < self->size / 2)
    {
        current = self->header->next;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
    }
    else
    {
        current = self->trailer->prev;
        for (int i = self->size - 1; i > index; i--)
        {
            current = current->prev;
        }
    }

    // reset state of the latest accessed element if it was removed
    if (current == self->p_latest)
    {
        self->latest = -1;
        self->p_latest = self->header;
    }

    // get data
    DoublyLinkedListItem data = current->data;

    // remove
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);

    // resize
    --self->size;

    // return data
    return data;
}

void DoublyLinkedList_Traverse(DoublyLinkedList* self, void (*p_trav)(DoublyLinkedListItem data))
{
    for (struct DoublyLinkedListNode* cur = self->header->next; cur != self->trailer; cur = cur->next)
    {
        p_trav(cur->data);
    }
}

void DoublyLinkedList_Reverse(DoublyLinkedList* self)
{
    for (struct DoublyLinkedListNode* cur = self->header; cur != NULL; cur = cur->prev)
    {
        struct DoublyLinkedListNode* tmp = cur->prev;
        cur->prev = cur->next;
        cur->next = tmp;
    }

    struct DoublyLinkedListNode* tmp = self->header;
    self->header = self->trailer;
    self->trailer = tmp;
}

void DoublyLinkedList_Clear(DoublyLinkedList* self)
{
    if (self->size != 0)
    {
        clear(self);
    }
}
