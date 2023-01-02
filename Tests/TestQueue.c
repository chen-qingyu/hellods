#include "../Sources/Queue/ArrayQueue.h"
#include "../Sources/Queue/LinkedDeque.h"
#include "../Sources/Queue/LinkedQueue.h"

#include <assert.h>
#include <stdio.h>

void TestArrayQueue(void)
{
    Queue* queue = ArrayQueue_Create();
    assert(ArrayQueue_Size(queue) == 0);
    assert(ArrayQueue_IsEmpty(queue) == true);

    QueueItem arr[] = {1, 2, 3, 4};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        ArrayQueue_Enqueue(queue, arr[i]);
    }
    assert(ArrayQueue_Size(queue) == 4);
    assert(ArrayQueue_IsEmpty(queue) == false);

    for (int i = 0; i < arr_size; i++)
    {
        assert(ArrayQueue_Dequeue(queue) == i + 1);
    }
    assert(ArrayQueue_Size(queue) == 0);
    assert(ArrayQueue_IsEmpty(queue) == true);

    ArrayQueue_Destroy(queue);

    printf("Array Queue Test OK.\n");
}

void TestLinkedQueue(void)
{
    Queue* queue = LinkedQueue_Create();
    assert(LinkedQueue_Size(queue) == 0);
    assert(LinkedQueue_IsEmpty(queue) == true);

    QueueItem arr[] = {1, 2, 3, 4};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        LinkedQueue_Enqueue(queue, arr[i]);
    }
    assert(LinkedQueue_Size(queue) == 4);
    assert(LinkedQueue_IsEmpty(queue) == false);

    for (int i = 0; i < arr_size; i++)
    {
        assert(LinkedQueue_Dequeue(queue) == i + 1);
    }
    assert(LinkedQueue_Size(queue) == 0);
    assert(LinkedQueue_IsEmpty(queue) == true);

    LinkedQueue_Destroy(queue);

    printf("Linked Queue Test OK.\n");
}

void TestLinkedDeque(void)
{
    Deque* queue = LinkedDeque_Create();
    assert(LinkedDeque_Size(queue) == 0);
    assert(LinkedDeque_IsEmpty(queue) == true);

    DequeItem arr[] = {1, 2, 3, 4};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        LinkedDeque_PushBack(queue, arr[i]);
    }
    assert(LinkedDeque_Size(queue) == 4);
    assert(LinkedDeque_IsEmpty(queue) == false);

    for (int i = 0; i < arr_size; i++)
    {
        assert(LinkedDeque_PopFront(queue) == i + 1);
    }
    assert(LinkedDeque_Size(queue) == 0);
    assert(LinkedDeque_IsEmpty(queue) == true);

    for (int i = 0; i < arr_size; i++)
    {
        LinkedDeque_PushFront(queue, arr[i]);
    }
    assert(LinkedDeque_Size(queue) == 4);
    assert(LinkedDeque_IsEmpty(queue) == false);

    for (int i = 0; i < arr_size; i++)
    {
        assert(LinkedDeque_PopBack(queue) == i + 1);
    }
    assert(LinkedDeque_Size(queue) == 0);
    assert(LinkedDeque_IsEmpty(queue) == true);

    LinkedDeque_Destroy(queue);

    printf("Linked Deque Test OK.\n");
}
