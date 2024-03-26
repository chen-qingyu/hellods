#include <catch2/catch_test_macros.hpp>

extern "C"
{
#include "../sources/Queue/ArrayQueue.h"
#include "../sources/Queue/LinkedDeque.h"
#include "../sources/Queue/LinkedQueue.h"
}

TEST_CASE("Queue: ArrayQueue")
{
    // ArrayQueue_Create ArrayQueue_Size ArrayQueue_IsEmpty
    ArrayQueue* queue = ArrayQueue_Create();
    REQUIRE(ArrayQueue_Size(queue) == 0);
    REQUIRE(ArrayQueue_IsEmpty(queue) == true);

    // ArrayQueue_Clear
    ArrayQueue_Enqueue(queue, 233);
    REQUIRE(ArrayQueue_Size(queue) == 1);
    ArrayQueue_Clear(queue);
    REQUIRE(ArrayQueue_Size(queue) == 0);
    ArrayQueue_Clear(queue); // double clear
    REQUIRE(ArrayQueue_Size(queue) == 0);

    // ArrayQueue_Enqueue ArrayQueue_Dequeue ArrayQueue_Front
    ArrayQueue_Enqueue(queue, -1);
    REQUIRE(ArrayQueue_Front(queue) == -1);
    REQUIRE(ArrayQueue_Dequeue(queue) == -1);
    REQUIRE(ArrayQueue_Size(queue) == 0);

    // ArrayQueue_Enqueue
    ArrayQueueItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        ArrayQueue_Enqueue(queue, arr[i]);
    }
    REQUIRE(ArrayQueue_Size(queue) == arr_size);

    // ArrayQueue_Front
    REQUIRE(ArrayQueue_Front(queue) == 1);

    // ArrayQueue_Dequeue
    for (int i = 0; i < arr_size; i++)
    {
        REQUIRE(ArrayQueue_Dequeue(queue) == i + 1);
    }
    REQUIRE(ArrayQueue_Size(queue) == 0);

    // ArrayQueue_Destroy
    ArrayQueue_Destroy(queue);
}

TEST_CASE("Queue: LinkedQueue")
{
    // LinkedQueue_Create LinkedQueue_Size LinkedQueue_IsEmpty
    LinkedQueue* queue = LinkedQueue_Create();
    REQUIRE(LinkedQueue_Size(queue) == 0);
    REQUIRE(LinkedQueue_IsEmpty(queue) == true);

    // LinkedQueue_Clear
    LinkedQueue_Enqueue(queue, 233);
    REQUIRE(LinkedQueue_Size(queue) == 1);
    LinkedQueue_Clear(queue);
    REQUIRE(LinkedQueue_Size(queue) == 0);
    LinkedQueue_Clear(queue); // double clear
    REQUIRE(LinkedQueue_Size(queue) == 0);

    // LinkedQueue_Enqueue LinkedQueue_Dequeue LinkedQueue_Front
    LinkedQueue_Enqueue(queue, -1);
    REQUIRE(LinkedQueue_Front(queue) == -1);
    REQUIRE(LinkedQueue_Dequeue(queue) == -1);
    REQUIRE(LinkedQueue_Size(queue) == 0);

    // LinkedQueue_Enqueue
    LinkedQueueItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        LinkedQueue_Enqueue(queue, arr[i]);
    }
    REQUIRE(LinkedQueue_Size(queue) == arr_size);

    // LinkedQueue_Front
    REQUIRE(LinkedQueue_Front(queue) == 1);

    // LinkedQueue_Dequeue
    for (int i = 0; i < arr_size; i++)
    {
        REQUIRE(LinkedQueue_Dequeue(queue) == i + 1);
    }
    REQUIRE(LinkedQueue_Size(queue) == 0);

    // LinkedQueue_Destroy
    LinkedQueue_Destroy(queue);
}

TEST_CASE("Queue: LinkedDeque")
{
    // LinkedDeque_Create LinkedDeque_Size LinkedDeque_IsEmpty
    LinkedDeque* queue = LinkedDeque_Create();
    REQUIRE(LinkedDeque_Size(queue) == 0);
    REQUIRE(LinkedDeque_IsEmpty(queue) == true);

    // LinkedDeque_Clear
    LinkedDeque_PushBack(queue, 233);
    REQUIRE(LinkedDeque_Size(queue) == 1);
    LinkedDeque_Clear(queue);
    REQUIRE(LinkedDeque_Size(queue) == 0);
    LinkedDeque_Clear(queue); // double clear
    REQUIRE(LinkedDeque_Size(queue) == 0);

    // LinkedDeque_PushBack LinkedDeque_PushFront
    // LinkedDeque_PopBack LinkedDeque_PopFront
    // LinkedDeque_Back LinkedDeque_Front
    LinkedDeque_PushBack(queue, 233);
    REQUIRE(LinkedDeque_Front(queue) == 233);
    REQUIRE(LinkedDeque_Back(queue) == 233);
    REQUIRE(LinkedDeque_PopFront(queue) == 233);
    LinkedDeque_PushFront(queue, 233);
    REQUIRE(LinkedDeque_Front(queue) == 233);
    REQUIRE(LinkedDeque_Back(queue) == 233);
    REQUIRE(LinkedDeque_PopBack(queue) == 233);

    // LinkedDeque_PushBack
    LinkedDequeItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        LinkedDeque_PushBack(queue, arr[i]);
    }
    REQUIRE(LinkedDeque_Size(queue) == arr_size);

    // LinkedDeque_Back LinkedDeque_Front
    REQUIRE(LinkedDeque_Front(queue) == 1);
    REQUIRE(LinkedDeque_Back(queue) == 5);

    // LinkedDeque_PopFront
    for (int i = 0; i < arr_size; i++)
    {
        REQUIRE(LinkedDeque_PopFront(queue) == i + 1);
    }
    REQUIRE(LinkedDeque_Size(queue) == 0);

    // LinkedDeque_PushFront
    for (int i = 0; i < arr_size; i++)
    {
        LinkedDeque_PushFront(queue, arr[i]);
    }
    REQUIRE(LinkedDeque_Size(queue) == arr_size);

    // LinkedDeque_Back LinkedDeque_Front
    REQUIRE(LinkedDeque_Front(queue) == 5);
    REQUIRE(LinkedDeque_Back(queue) == 1);

    // LinkedDeque_PopBack
    for (int i = 0; i < arr_size; i++)
    {
        REQUIRE(LinkedDeque_PopBack(queue) == i + 1);
    }
    REQUIRE(LinkedDeque_Size(queue) == 0);

    // LinkedDeque_Destroy
    LinkedDeque_Destroy(queue);
}
