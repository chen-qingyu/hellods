#include "LinkedList.h"

#include <limits.h> // INT_MAX
#include <stdlib.h> // malloc free NULL

#include "../common/check_bounds.h"
#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

struct node
{
    // Data stored in the node.
    ListItem data;

    // Successor.
    struct node* next;
};

struct list
{
    // Number of elements.
    int count;

    // Pointer to the header (rank = -1).
    struct node* header;
};

/*******************************
Helper functions implementation.
*******************************/

/*******************************
Interface functions implementation.
*******************************/

List* LinkedList_Create(void)
{
    List* list = (List*)malloc(sizeof(List));
    check_pointer(list);

    list->count = 0;
    list->header = (struct node*)malloc(sizeof(struct node));
    check_pointer(list->header);
    list->header->next = NULL;

    return list;
}

void LinkedList_Destroy(List* self)
{
    while (self->header)
    {
        struct node* next = self->header->next;
        free(self->header);
        self->header = next;
    }
    free(self);
}

int LinkedList_Size(const List* self)
{
    return self->count;
}

bool LinkedList_IsEmpty(const List* self)
{
    return self->count == 0;
}

ListItem LinkedList_At(const List* self, int index) // list[index]
{
    check_bounds(index, -self->count, self->count);

    index = index >= 0 ? index : index + self->count;

    struct node* current = self->header->next;

    for (int i = 0; i < index; ++i)
    {
        current = current->next;
    }

    return current->data;
}

int LinkedList_Find(const List* self, ListItem data)
{
    int index = 0;
    struct node* current = self->header->next;

    while (current != NULL && current->data != data)
    {
        current = current->next;
        index++;
    }

    return current != NULL ? index : LIST_NOT_FOUND;
}

void LinkedList_Insert(List* self, int index, ListItem data)
{
    // check
    check_full(self->count, INT_MAX);

    check_bounds(index, 0, self->count + 1);

    // index
    struct node* current = self->header;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    // insert
    struct node* node = (struct node*)malloc(sizeof(struct node));
    check_pointer(node);
    node->data = data;
    node->next = current->next;

    current->next = node;

    // resize
    ++self->count;
}

ListItem LinkedList_Remove(List* self, int index)
{
    // check
    check_empty(self->count);

    check_bounds(index, 0, self->count);

    // index
    struct node* current = self->header;
    for (int i = 0; i < index; i++)
    {
        current = current->next;
    }

    // get data
    ListItem data = current->next->data;

    // remove
    struct node* node = current->next;
    current->next = node->next;
    free(node);

    // resize
    --self->count;

    // return data
    return data;
}

void LinkedList_Traverse(List* self, void (*p_trav)(ListItem data))
{
    for (struct node* cur = self->header->next; cur != NULL; cur = cur->next)
    {
        p_trav(cur->data);
    }
}

void LinkedList_Reverse(List* self)
{
    struct node* pre = self->header->next;
    self->header->next = NULL;

    while (pre)
    {
        struct node* tmp = pre;
        pre = pre->next;
        tmp->next = self->header->next;
        self->header->next = tmp;
    }
}
