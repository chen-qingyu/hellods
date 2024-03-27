#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_exception.hpp>

#include "../sources/Queue/ArrayQueue.hpp"
// #include "../sources/Queue/LinkedDeque.hpp"
// #include "../sources/Queue/LinkedQueue.hpp"

using Catch::Matchers::Message;

using namespace hellods;

template <typename Queue>
void test()
{
    // Constructor / Destructor
    Queue empty;
    Queue some = {1, 2, 3, 4, 5};

    // Comparison
    REQUIRE(empty == Queue());
    REQUIRE(some == Queue({1, 2, 3, 4, 5}));
    REQUIRE(empty != some);
    REQUIRE(some != Queue({1, 2, 3, 4, 6}));

    // Access
    REQUIRE(some.front() == 1);
    some.front() = 0;
    REQUIRE(some.front() == 0);
    REQUIRE_THROWS_MATCHES(empty.front(), std::runtime_error, Message("Error: The container is empty."));

    // Examination
    REQUIRE(empty.size() == 0);
    REQUIRE(empty.is_empty() == true);

    REQUIRE(some.size() == 5);
    REQUIRE(some.is_empty() == false);

    // Manipulation
    empty.enqueue(1);
    REQUIRE(empty == Queue({1}));
    empty.enqueue(2);
    REQUIRE(empty == Queue({1, 2}));
    empty.enqueue(3);
    REQUIRE(empty == Queue({1, 2, 3}));

    REQUIRE(empty.dequeue() == 1);
    REQUIRE(empty.dequeue() == 2);
    REQUIRE(empty.dequeue() == 3);
    REQUIRE_THROWS_MATCHES(empty.dequeue(), std::runtime_error, Message("Error: The container is empty."));

    REQUIRE(some.clear() == empty);
    REQUIRE(some.clear() == empty); // double clear
}

TEST_CASE("ArrayQueue")
{
    test<ArrayQueue<int>>();
}

// TEST_CASE("Queue: LinkedQueue")
// {
//     // LinkedQueue_Create LinkedQueue_Size LinkedQueue_IsEmpty
//     LinkedQueue* queue = LinkedQueue_Create();
//     REQUIRE(LinkedQueue_Size(queue) == 0);
//     REQUIRE(LinkedQueue_IsEmpty(queue) == true);

// // LinkedQueue_Clear
// LinkedQueue_Enqueue(queue, 233);
// REQUIRE(LinkedQueue_Size(queue) == 1);
// LinkedQueue_Clear(queue);
// REQUIRE(LinkedQueue_Size(queue) == 0);
// LinkedQueue_Clear(queue); // double clear
// REQUIRE(LinkedQueue_Size(queue) == 0);

// // LinkedQueue_Enqueue LinkedQueue_Dequeue LinkedQueue_Front
// LinkedQueue_Enqueue(queue, -1);
// REQUIRE(LinkedQueue_Front(queue) == -1);
// REQUIRE(LinkedQueue_Dequeue(queue) == -1);
// REQUIRE(LinkedQueue_Size(queue) == 0);

// // LinkedQueue_Enqueue
// LinkedQueueItem arr[] = {1, 2, 3, 4, 5};
// int arr_size = sizeof(arr) / sizeof(arr[0]);
// for (int i = 0; i < arr_size; i++)
// {
//     LinkedQueue_Enqueue(queue, arr[i]);
// }
// REQUIRE(LinkedQueue_Size(queue) == arr_size);

// // LinkedQueue_Front
// REQUIRE(LinkedQueue_Front(queue) == 1);

// // LinkedQueue_Dequeue
// for (int i = 0; i < arr_size; i++)
// {
//     REQUIRE(LinkedQueue_Dequeue(queue) == i + 1);
// }
// REQUIRE(LinkedQueue_Size(queue) == 0);

// // LinkedQueue_Destroy
// LinkedQueue_Destroy(queue);
// }

// TEST_CASE("Queue: LinkedDeque")
// {
//     // LinkedDeque_Create LinkedDeque_Size LinkedDeque_IsEmpty
//     LinkedDeque* queue = LinkedDeque_Create();
//     REQUIRE(LinkedDeque_Size(queue) == 0);
//     REQUIRE(LinkedDeque_IsEmpty(queue) == true);

// // LinkedDeque_Clear
// LinkedDeque_PushBack(queue, 233);
// REQUIRE(LinkedDeque_Size(queue) == 1);
// LinkedDeque_Clear(queue);
// REQUIRE(LinkedDeque_Size(queue) == 0);
// LinkedDeque_Clear(queue); // double clear
// REQUIRE(LinkedDeque_Size(queue) == 0);

// // LinkedDeque_PushBack LinkedDeque_PushFront
// // LinkedDeque_PopBack LinkedDeque_PopFront
// // LinkedDeque_Back LinkedDeque_Front
// LinkedDeque_PushBack(queue, 233);
// REQUIRE(LinkedDeque_Front(queue) == 233);
// REQUIRE(LinkedDeque_Back(queue) == 233);
// REQUIRE(LinkedDeque_PopFront(queue) == 233);
// LinkedDeque_PushFront(queue, 233);
// REQUIRE(LinkedDeque_Front(queue) == 233);
// REQUIRE(LinkedDeque_Back(queue) == 233);
// REQUIRE(LinkedDeque_PopBack(queue) == 233);

// // LinkedDeque_PushBack
// LinkedDequeItem arr[] = {1, 2, 3, 4, 5};
// int arr_size = sizeof(arr) / sizeof(arr[0]);
// for (int i = 0; i < arr_size; i++)
// {
//     LinkedDeque_PushBack(queue, arr[i]);
// }
// REQUIRE(LinkedDeque_Size(queue) == arr_size);

// // LinkedDeque_Back LinkedDeque_Front
// REQUIRE(LinkedDeque_Front(queue) == 1);
// REQUIRE(LinkedDeque_Back(queue) == 5);

// // LinkedDeque_PopFront
// for (int i = 0; i < arr_size; i++)
// {
//     REQUIRE(LinkedDeque_PopFront(queue) == i + 1);
// }
// REQUIRE(LinkedDeque_Size(queue) == 0);

// // LinkedDeque_PushFront
// for (int i = 0; i < arr_size; i++)
// {
//     LinkedDeque_PushFront(queue, arr[i]);
// }
// REQUIRE(LinkedDeque_Size(queue) == arr_size);

// // LinkedDeque_Back LinkedDeque_Front
// REQUIRE(LinkedDeque_Front(queue) == 5);
// REQUIRE(LinkedDeque_Back(queue) == 1);

// // LinkedDeque_PopBack
// for (int i = 0; i < arr_size; i++)
// {
//     REQUIRE(LinkedDeque_PopBack(queue) == i + 1);
// }
// REQUIRE(LinkedDeque_Size(queue) == 0);

// // LinkedDeque_Destroy
// LinkedDeque_Destroy(queue);
// }
