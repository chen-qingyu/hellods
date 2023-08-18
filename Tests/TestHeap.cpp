// Tested on Microsoft Visual Studio Community 2019: ALL PASSED

#include "../pch.h"

extern "C"
{
#include "../Sources/Heap/MaxHeap.h"
}

TEST(Heap, MaxHeap)
{
    // MaxHeap_Create MaxHeap_Size MaxHeap_IsEmpty
    MaxHeap* heap = MaxHeap_Create();
    ASSERT_EQ(MaxHeap_Size(heap), 0);
    ASSERT_EQ(MaxHeap_IsEmpty(heap), true);

    // MaxHeap_Clear
    MaxHeap_Push(heap, 233);
    ASSERT_EQ(MaxHeap_Size(heap), 1);
    MaxHeap_Clear(heap);
    ASSERT_EQ(MaxHeap_Size(heap), 0);
    MaxHeap_Clear(heap); // double clear
    ASSERT_EQ(MaxHeap_Size(heap), 0);

    // MaxHeap_Push
    MaxHeap_Push(heap, 1);
    MaxHeap_Push(heap, 2);
    MaxHeap_Push(heap, 4);
    MaxHeap_Push(heap, 3);
    MaxHeap_Push(heap, 9);
    MaxHeap_Push(heap, 0);
    ASSERT_EQ(MaxHeap_Size(heap), 6);

    // MaxHeap_Top
    ASSERT_EQ(MaxHeap_Top(heap), 9);

    // MaxHeap_Pop
    ASSERT_EQ(MaxHeap_Pop(heap), 9);
    ASSERT_EQ(MaxHeap_Pop(heap), 4);
    ASSERT_EQ(MaxHeap_Pop(heap), 3);
    ASSERT_EQ(MaxHeap_Pop(heap), 2);
    ASSERT_EQ(MaxHeap_Pop(heap), 1);
    ASSERT_EQ(MaxHeap_Pop(heap), 0);
    ASSERT_EQ(MaxHeap_Size(heap), 0);

    // MaxHeap_Destroy
    MaxHeap_Destroy(heap);
}
