#include "../Sources/Heap/MaxHeap.h"

#include <assert.h>
#include <stdio.h>

void TestMaxHeap(void)
{
    // MaxHeap_Create MaxHeap_Size MaxHeap_IsEmpty
    MaxHeap* heap = MaxHeap_Create();
    assert(MaxHeap_Size(heap) == 0);
    assert(MaxHeap_IsEmpty(heap) == true);

    // MaxHeap_Clear
    MaxHeap_Push(heap, 233);
    assert(MaxHeap_Size(heap) == 1);
    MaxHeap_Clear(heap);
    assert(MaxHeap_Size(heap) == 0);
    MaxHeap_Clear(heap); // double clear
    assert(MaxHeap_Size(heap) == 0);

    // MaxHeap_Push
    MaxHeap_Push(heap, 1);
    MaxHeap_Push(heap, 2);
    MaxHeap_Push(heap, 4);
    MaxHeap_Push(heap, 3);
    MaxHeap_Push(heap, 9);
    MaxHeap_Push(heap, 0);
    assert(MaxHeap_Size(heap) == 6);

    // MaxHeap_Top
    assert(MaxHeap_Top(heap) == 9);

    // MaxHeap_Pop
    assert(MaxHeap_Pop(heap) == 9);
    assert(MaxHeap_Pop(heap) == 4);
    assert(MaxHeap_Pop(heap) == 3);
    assert(MaxHeap_Pop(heap) == 2);
    assert(MaxHeap_Pop(heap) == 1);
    assert(MaxHeap_Pop(heap) == 0);
    assert(MaxHeap_Size(heap) == 0);

    // MaxHeap_Destroy
    MaxHeap_Destroy(heap);

    printf("Max Heap Test OK.\n");
}
