#include "LinkedDeque.h"
#include "../List/DoublyLinkedList.h"

#include <stdlib.h> // malloc free

#include "../common/check_pointer.h"

struct deque
{
    List* dlist;
};

/*******************************
Helper functions implementation.
*******************************/

/*******************************
Interface functions implementation.
*******************************/

Deque* LinkedDeque_Create(void)
{
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    check_pointer(deque);

    deque->dlist = DoublyLinkedList_Create();

    return deque;
}

void LinkedDeque_Destroy(Deque* self)
{
    DoublyLinkedList_Destroy(self->dlist);
    free(self);
}

int LinkedDeque_Size(const Deque* self)
{
    return DoublyLinkedList_Size(self->dlist);
}

bool LinkedDeque_IsEmpty(const Deque* self)
{
    return DoublyLinkedList_IsEmpty(self->dlist);
}

void LinkedDeque_PushFront(Deque* self, DequeItem data)
{
    DoublyLinkedList_Insert(self->dlist, 0, data);
}

void LinkedDeque_PushBack(Deque* self, DequeItem data)
{
    DoublyLinkedList_Insert(self->dlist, DoublyLinkedList_Size(self->dlist), data);
}

DequeItem LinkedDeque_PopFront(Deque* self)
{
    return DoublyLinkedList_Remove(self->dlist, 0);
}

DequeItem LinkedDeque_PopBack(Deque* self)
{
    return DoublyLinkedList_Remove(self->dlist, DoublyLinkedList_Size(self->dlist) - 1);
}

DequeItem LinkedDeque_Front(Deque* self)
{
    return DoublyLinkedList_At(self->dlist, 0);
}

DequeItem LinkedDeque_Back(Deque* self)
{
    return DoublyLinkedList_At(self->dlist, DoublyLinkedList_Size(self->dlist) - 1);
}
