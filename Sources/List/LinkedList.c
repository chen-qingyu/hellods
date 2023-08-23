#include "LinkedList.h"

#include <limits.h> // INT_MAX
#include <stdlib.h> // malloc free NULL

#include "../common/utility.h"

/// Linked List Node.
struct LinkedListNode
{
    /// Data stored in the node.
    LinkedListItem data;

    /// Successor.
    struct LinkedListNode* next;
};

/// Linked List.
struct LinkedList
{
    /// Number of elements.
    int size;

    /// Pointer to the header (rank = -1).
    struct LinkedListNode* header;
};

/*
 * Helpers
 */

// Remove all of the elements.
static inline void clear(LinkedList* self)
{
    while (self->header->next != NULL)
    {
        struct LinkedListNode* node = self->header->next->next;
        free(self->header->next);
        self->header->next = node;
    }

    self->size = 0;
    self->header->next = NULL;
}

/*
 * Functions
 */

LinkedList* LinkedList_Create(void)
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    check_pointer(list);

    list->size = 0;
    list->header = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode));
    check_pointer(list->header);
    list->header->next = NULL;

    return list;
}

void LinkedList_Destroy(LinkedList* self)
{
    // let it crush if self is invalid

    clear(self);

    free(self->header);
    free(self);
}

int LinkedList_Size(const LinkedList* self)
{
    return self->size;
}

bool LinkedList_IsEmpty(const LinkedList* self)
{
    return self->size == 0;
}

LinkedListItem LinkedList_At(const LinkedList* self, int index) // list[index]
{
    check_bounds(index, -self->size, self->size);

    index = index >= 0 ? index : index + self->size;

    struct LinkedListNode* current = self->header->next;

    for (int i = 0; i < index; ++i)
    {
        current = current->next;
    }

    return current->data;
}

int LinkedList_Find(const LinkedList* self, LinkedListItem data)
{
    int index = 0;
    struct LinkedListNode* current = self->header->next;

    while (current != NULL && current->data != data)
    {
        current = current->next;
        index++;
    }

    return current != NULL ? index : -1;
}

void LinkedList_Insert(LinkedList* self, int index, LinkedListItem data)
{
    // check
    check_full(self->size, INT_MAX);

    check_bounds(index, -self->size, self->size + 1);

    // index
    index = index >= 0 ? index : index + self->size;

    struct LinkedListNode* current = self->header;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    // insert
    struct LinkedListNode* node = (struct LinkedListNode*)malloc(sizeof(struct LinkedListNode));
    check_pointer(node);
    node->data = data;
    node->next = current->next;

    current->next = node;

    // resize
    ++self->size;
}

LinkedListItem LinkedList_Remove(LinkedList* self, int index)
{
    // check
    check_empty(self->size);

    check_bounds(index, -self->size, self->size);

    // index
    index = index >= 0 ? index : index + self->size;

    struct LinkedListNode* current = self->header;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    // get data
    LinkedListItem data = current->next->data;

    // remove
    struct LinkedListNode* node = current->next;
    current->next = node->next;
    free(node);

    // resize
    --self->size;

    // return data
    return data;
}

void LinkedList_Traverse(LinkedList* self, void (*p_trav)(LinkedListItem data))
{
    for (struct LinkedListNode* cur = self->header->next; cur != NULL; cur = cur->next)
    {
        p_trav(cur->data);
    }
}

void LinkedList_Reverse(LinkedList* self)
{
    struct LinkedListNode* pre = self->header->next;
    self->header->next = NULL;

    while (pre)
    {
        struct LinkedListNode* tmp = pre;
        pre = pre->next;
        tmp->next = self->header->next;
        self->header->next = tmp;
    }
}

void LinkedList_Clear(LinkedList* self)
{
    if (self->size != 0)
    {
        clear(self);
    }
}
