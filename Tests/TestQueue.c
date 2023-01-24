#include "../Sources/Queue/ArrayQueue.h"
#include "../Sources/Queue/LinkedDeque.h"
#include "../Sources/Queue/LinkedQueue.h"

#include <assert.h>
#include <stdio.h>

void TestArrayQueue(void)
{
    // ArrayQueue_Create ArrayQueue_Size ArrayQueue_IsEmpty
    ArrayQueue* queue = ArrayQueue_Create();
    assert(ArrayQueue_Size(queue) == 0);
    assert(ArrayQueue_IsEmpty(queue) == true);

    // ArrayQueue_Enqueue ArrayQueue_Dequeue ArrayQueue_Front
    ArrayQueue_Enqueue(queue, -1);
    assert(ArrayQueue_Front(queue) == -1);
    assert(ArrayQueue_Dequeue(queue) == -1);
    assert(ArrayQueue_Size(queue) == 0);

    // ArrayQueue_Enqueue
    ArrayQueueItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        ArrayQueue_Enqueue(queue, arr[i]);
    }
    assert(ArrayQueue_Size(queue) == arr_size);

    // ArrayQueue_Front
    assert(ArrayQueue_Front(queue) == 1);

    // ArrayQueue_Dequeue
    for (int i = 0; i < arr_size; i++)
    {
        assert(ArrayQueue_Dequeue(queue) == i + 1);
    }
    assert(ArrayQueue_Size(queue) == 0);

    // ArrayQueue_Clear
    ArrayQueue_Enqueue(queue, 233);
    assert(ArrayQueue_Size(queue) == 1);
    ArrayQueue_Clear(queue);
    assert(ArrayQueue_Size(queue) == 0);
    ArrayQueue_Clear(queue); // double clear
    assert(ArrayQueue_Size(queue) == 0);

    // ArrayQueue_Destroy
    ArrayQueue_Destroy(queue);

    printf("Array Queue Test OK.\n");
}

void TestLinkedQueue(void)
{
    // LinkedQueue_Create LinkedQueue_Size LinkedQueue_IsEmpty
    LinkedQueue* queue = LinkedQueue_Create();
    assert(LinkedQueue_Size(queue) == 0);
    assert(LinkedQueue_IsEmpty(queue) == true);

    // LinkedQueue_Enqueue LinkedQueue_Dequeue LinkedQueue_Front
    LinkedQueue_Enqueue(queue, -1);
    assert(LinkedQueue_Front(queue) == -1);
    assert(LinkedQueue_Dequeue(queue) == -1);
    assert(LinkedQueue_Size(queue) == 0);

    // LinkedQueue_Enqueue
    LinkedQueueItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        LinkedQueue_Enqueue(queue, arr[i]);
    }
    assert(LinkedQueue_Size(queue) == arr_size);

    // LinkedQueue_Front
    assert(LinkedQueue_Front(queue) == 1);

    // LinkedQueue_Dequeue
    for (int i = 0; i < arr_size; i++)
    {
        assert(LinkedQueue_Dequeue(queue) == i + 1);
    }
    assert(LinkedQueue_Size(queue) == 0);

    // LinkedQueue_Clear
    LinkedQueue_Enqueue(queue, 233);
    assert(LinkedQueue_Size(queue) == 1);
    LinkedQueue_Clear(queue);
    assert(LinkedQueue_Size(queue) == 0);
    LinkedQueue_Clear(queue); // double clear
    assert(LinkedQueue_Size(queue) == 0);

    // LinkedQueue_Destroy
    LinkedQueue_Destroy(queue);

    printf("Linked Queue Test OK.\n");
}

void TestLinkedDeque(void)
{
    // LinkedDeque_Create LinkedDeque_Size LinkedDeque_IsEmpty
    LinkedDeque* queue = LinkedDeque_Create();
    assert(LinkedDeque_Size(queue) == 0);
    assert(LinkedDeque_IsEmpty(queue) == true);

    // LinkedDeque_PushBack LinkedDeque_PushFront
    // LinkedDeque_PopBack LinkedDeque_PopFront
    // LinkedDeque_Back LinkedDeque_Front
    LinkedDeque_PushBack(queue, 233);
    assert(LinkedDeque_Front(queue) == 233);
    assert(LinkedDeque_Back(queue) == 233);
    assert(LinkedDeque_PopFront(queue) == 233);
    LinkedDeque_PushFront(queue, 233);
    assert(LinkedDeque_Front(queue) == 233);
    assert(LinkedDeque_Back(queue) == 233);
    assert(LinkedDeque_PopBack(queue) == 233);

    // LinkedDeque_PushBack
    LinkedDequeItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        LinkedDeque_PushBack(queue, arr[i]);
    }
    assert(LinkedDeque_Size(queue) == arr_size);

    // LinkedDeque_Back LinkedDeque_Front
    assert(LinkedDeque_Front(queue) == 1);
    assert(LinkedDeque_Back(queue) == 5);

    // LinkedDeque_PopFront
    for (int i = 0; i < arr_size; i++)
    {
        assert(LinkedDeque_PopFront(queue) == i + 1);
    }
    assert(LinkedDeque_Size(queue) == 0);

    // LinkedDeque_PushFront
    for (int i = 0; i < arr_size; i++)
    {
        LinkedDeque_PushFront(queue, arr[i]);
    }
    assert(LinkedDeque_Size(queue) == arr_size);

    // LinkedDeque_Back LinkedDeque_Front
    assert(LinkedDeque_Front(queue) == 5);
    assert(LinkedDeque_Back(queue) == 1);

    // LinkedDeque_PopBack
    for (int i = 0; i < arr_size; i++)
    {
        assert(LinkedDeque_PopBack(queue) == i + 1);
    }
    assert(LinkedDeque_Size(queue) == 0);

    // LinkedDeque_Clear
    LinkedDeque_PushBack(queue, 233);
    assert(LinkedDeque_Size(queue) == 1);
    LinkedDeque_Clear(queue);
    assert(LinkedDeque_Size(queue) == 0);
    LinkedDeque_Clear(queue); // double clear
    assert(LinkedDeque_Size(queue) == 0);

    // LinkedDeque_Destroy
    LinkedDeque_Destroy(queue);

    printf("Linked Deque Test OK.\n");
}
