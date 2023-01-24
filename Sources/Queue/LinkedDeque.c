#include "LinkedDeque.h"
#include "../List/DoublyLinkedList.h"

#include <stdlib.h> // malloc free

#include "../common/check_pointer.h"

struct LinkedDeque
{
    /// A doubly linked list.
    DoublyLinkedList* dlist;
};

/*******************************
Helper functions implementation.
*******************************/

/*******************************
Interface functions implementation.
*******************************/

LinkedDeque* LinkedDeque_Create(void)
{
    LinkedDeque* deque = (LinkedDeque*)malloc(sizeof(LinkedDeque));
    check_pointer(deque);

    deque->dlist = DoublyLinkedList_Create();

    return deque;
}

void LinkedDeque_Destroy(LinkedDeque* self)
{
    // let it crush if self is invalid

    DoublyLinkedList_Destroy(self->dlist);
    free(self);
}

int LinkedDeque_Size(const LinkedDeque* self)
{
    return DoublyLinkedList_Size(self->dlist);
}

bool LinkedDeque_IsEmpty(const LinkedDeque* self)
{
    return DoublyLinkedList_IsEmpty(self->dlist);
}

void LinkedDeque_PushFront(LinkedDeque* self, LinkedDequeItem data)
{
    DoublyLinkedList_Insert(self->dlist, 0, data);
}

void LinkedDeque_PushBack(LinkedDeque* self, LinkedDequeItem data)
{
    DoublyLinkedList_Insert(self->dlist, DoublyLinkedList_Size(self->dlist), data);
}

LinkedDequeItem LinkedDeque_PopFront(LinkedDeque* self)
{
    return DoublyLinkedList_Remove(self->dlist, 0);
}

LinkedDequeItem LinkedDeque_PopBack(LinkedDeque* self)
{
    return DoublyLinkedList_Remove(self->dlist, DoublyLinkedList_Size(self->dlist) - 1);
}

LinkedDequeItem LinkedDeque_Front(LinkedDeque* self)
{
    return DoublyLinkedList_At(self->dlist, 0);
}

LinkedDequeItem LinkedDeque_Back(LinkedDeque* self)
{
    return DoublyLinkedList_At(self->dlist, DoublyLinkedList_Size(self->dlist) - 1);
}

void LinkedDeque_Clear(LinkedDeque* self)
{
    DoublyLinkedList_Clear(self->dlist);
}
