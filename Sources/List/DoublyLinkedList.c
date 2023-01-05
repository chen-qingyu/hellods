#include "DoublyLinkedList.h"

#include <limits.h> // INT_MAX
#include <stdlib.h> // malloc free NULL abs

#include "../common/check_bounds.h"
#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

struct node
{
    // Data stored in the node.
    ListItem data;

    // Predecessor.
    struct node* prev;

    // Successor.
    struct node* next;
};

struct list
{
    // Number of elements.
    int count;

    // Pointer to the header (rank = -1).
    struct node* header;

    // Pointer to the trailer (rank = count).
    struct node* trailer;

    // Index of the latest accessed element. For DoublyLinkedList_At().
    int latest;

    // Pointer to the latest accessed element. For DoublyLinkedList_At().
    struct node* p_latest;
};

/*******************************
Helper functions implementation.
*******************************/

// Remove all of the elements from the list.
static inline void clear(List* self)
{
    while (self->header)
    {
        struct node* next = self->header->next;
        free(self->header);
        self->header = next;
    }
    self->count = 0;
    self->latest = -1;
    self->p_latest = self->header;
}

/*******************************
Interface functions implementation.
*******************************/

List* DoublyLinkedList_Create(void)
{
    List* list = (List*)malloc(sizeof(List));
    check_pointer(list);

    list->count = 0;
    list->header = (struct node*)malloc(sizeof(struct node));
    check_pointer(list->header);
    list->trailer = (struct node*)malloc(sizeof(struct node));
    check_pointer(list->trailer);
    list->latest = -1;
    list->p_latest = list->header;

    list->header->prev = NULL;
    list->header->next = list->trailer;

    list->trailer->prev = list->header;
    list->trailer->next = NULL;

    return list;
}

void DoublyLinkedList_Destroy(List* self)
{
    clear(self);
    free(self);
}

int DoublyLinkedList_Size(const List* self)
{
    return self->count;
}

bool DoublyLinkedList_IsEmpty(const List* self)
{
    return self->count == 0;
}

ListItem DoublyLinkedList_At(const List* self, int index) // list[index] for index in range 0 to count will be O(1) on each access
{
    check_bounds(index, -self->count, self->count);

    index = index >= 0 ? index : index + self->count;

    List* list = (List*)self; // drop out const

    // too far from the last accessed element
    if (abs(index - self->latest) > self->count / 2)
    {
        // closer to the header or trailer
        list->p_latest = (index < self->latest) ? self->header->next : self->trailer->prev;
        list->latest = (index < self->latest) ? 0 : self->count - 1;
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

int DoublyLinkedList_Find(const List* self, ListItem data)
{
    int index = 0;
    struct node* current = self->header->next;

    while (current != self->trailer && current->data != data)
    {
        current = current->next;
        index++;
    }

    return current != self->trailer ? index : LIST_NOT_FOUND;
}

void DoublyLinkedList_Insert(List* self, int index, ListItem data)
{
    // check
    check_full(self->count, INT_MAX);

    check_bounds(index, 0, self->count + 1);

    // index
    struct node* current = NULL;
    if (index < self->count / 2)
    {
        current = self->header->next;
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
    }
    else
    {
        current = self->trailer; // be careful, index may be same as count
        for (int i = self->count; i > index; i--)
        {
            current = current->prev;
        }
    }

    // insert
    struct node* node = (struct node*)malloc(sizeof(struct node));
    check_pointer(node);
    node->data = data;
    node->prev = current->prev;
    node->next = current;

    current->prev->next = node;
    current->prev = node;

    // resize
    ++self->count;
}

ListItem DoublyLinkedList_Remove(List* self, int index)
{
    // check
    check_empty(self->count);

    check_bounds(index, 0, self->count);

    // index
    struct node* current = NULL;
    if (index < self->count / 2)
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
        for (int i = self->count - 1; i > index; i--)
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
    ListItem data = current->data;

    // remove
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);

    // resize
    --self->count;

    // return data
    return data;
}

void DoublyLinkedList_Traverse(List* self, void (*p_trav)(ListItem data))
{
    for (struct node* cur = self->header->next; cur != self->trailer; cur = cur->next)
    {
        p_trav(cur->data);
    }
}

void DoublyLinkedList_Reverse(List* self)
{
    for (struct node* cur = self->header; cur != NULL; cur = cur->prev)
    {
        struct node* tmp = cur->prev;
        cur->prev = cur->next;
        cur->next = tmp;
    }

    struct node* tmp = self->header;
    self->header = self->trailer;
    self->trailer = tmp;
}

void DoublyLinkedList_Clear(List* self)
{
    clear(self);
}
