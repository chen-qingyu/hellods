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

    // Rank of the latest accessed element. For DoublyLinkedList_At().
    int latest;

    // Pointer to the latest accessed element. For DoublyLinkedList_At().
    struct node* p_latest;
};

/*******************************
Helper functions implementation.
*******************************/

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
    while (self->header)
    {
        struct node* next = self->header->next;
        free(self->header);
        self->header = next;
    }
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

ListItem DoublyLinkedList_At(const List* self, int i) // list[i] for i in range 0 to count will be O(1) on each access
{
    check_bounds(i, -self->count, self->count);

    i = i >= 0 ? i : i + self->count;

    List* list = (List*)self; // drop out const

    // too far from the last accessed element
    if (abs(i - self->latest) > self->count / 2)
    {
        // closer to the header or trailer
        list->p_latest = (i < self->latest) ? self->header : self->trailer;
        list->latest = (i < self->latest) ? -1 : self->count;
    }

    if (i < self->latest)
    {
        while (i < self->latest)
        {
            list->latest--;
            list->p_latest = list->p_latest->prev;
        }
    }
    else if (i > self->latest)
    {
        while (i > self->latest)
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

void DoublyLinkedList_Insert(List* self, int i, ListItem data)
{
    check_full(self->count, INT_MAX);

    check_bounds(i, 0, self->count + 1);

    struct node* node = (struct node*)malloc(sizeof(struct node));
    check_pointer(node);
    node->data = data;

    struct node* current = self->header->next;
    for (int j = 0; j < i; j++)
    {
        current = current->next;
    }
    node->prev = current->prev;
    node->next = current;

    current->prev->next = node;
    current->prev = node;

    ++self->count;
}

void DoublyLinkedList_Delete(List* self, int i)
{
    check_empty(self->count);

    check_bounds(i, 0, self->count);

    struct node* current = self->header->next;
    for (int j = 0; j < i; j++)
    {
        current = current->next;
    }

    // keep p_latest pointing to the previous node.
    if (current == self->p_latest)
    {
        self->latest--;
        self->p_latest = self->p_latest->prev;
    }

    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);

    --self->count;
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
