#include <catch2/catch_test_macros.hpp>

extern "C"
{
#include "../sources/Heap/MaxHeap.h"
}

TEST_CASE("Heap: MaxHeap")
{
    // MaxHeap_Create MaxHeap_Size MaxHeap_IsEmpty
    MaxHeap* heap = MaxHeap_Create();
    REQUIRE(MaxHeap_Size(heap) == 0);
    REQUIRE(MaxHeap_IsEmpty(heap) == true);

    // MaxHeap_Clear
    MaxHeap_Push(heap, 233);
    REQUIRE(MaxHeap_Size(heap) == 1);
    MaxHeap_Clear(heap);
    REQUIRE(MaxHeap_Size(heap) == 0);
    MaxHeap_Clear(heap); // double clear
    REQUIRE(MaxHeap_Size(heap) == 0);

    // MaxHeap_Push
    MaxHeap_Push(heap, 1);
    MaxHeap_Push(heap, 2);
    MaxHeap_Push(heap, 4);
    MaxHeap_Push(heap, 3);
    MaxHeap_Push(heap, 9);
    MaxHeap_Push(heap, 0);
    REQUIRE(MaxHeap_Size(heap) == 6);

    // MaxHeap_Top
    REQUIRE(MaxHeap_Top(heap) == 9);

    // MaxHeap_Pop
    REQUIRE(MaxHeap_Pop(heap) == 9);
    REQUIRE(MaxHeap_Pop(heap) == 4);
    REQUIRE(MaxHeap_Pop(heap) == 3);
    REQUIRE(MaxHeap_Pop(heap) == 2);
    REQUIRE(MaxHeap_Pop(heap) == 1);
    REQUIRE(MaxHeap_Pop(heap) == 0);
    REQUIRE(MaxHeap_Size(heap) == 0);

    // MaxHeap_Destroy
    MaxHeap_Destroy(heap);
}
