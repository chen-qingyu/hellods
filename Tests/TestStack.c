#include "../Sources/Stack/ArrayStack.h"
#include "../Sources/Stack/LinkedStack.h"

#include <assert.h>
#include <stdio.h>

void TestArrayStack(void)
{
    // ArrayStack_Create ArrayStack_Size ArrayStack_IsEmpty
    ArrayStack* stack = ArrayStack_Create();
    assert(ArrayStack_Size(stack) == 0);
    assert(ArrayStack_IsEmpty(stack) == true);

    // ArrayStack_Push
    ArrayStackItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        ArrayStack_Push(stack, arr[i]);
    }
    assert(ArrayStack_Size(stack) == 5);

    // ArrayStack_Top
    assert(ArrayStack_Top(stack) == 5);

    // ArrayStack_Pop
    for (int i = 0; i < arr_size; i++)
    {
        assert(ArrayStack_Pop(stack) == 5 - i);
    }
    assert(ArrayStack_Size(stack) == 0);

    // ArrayStack_Destroy
    ArrayStack_Destroy(stack);

    printf("Array Stack Test OK.\n");
}

void TestLinkedStack(void)
{
    // LinkedStack_Create LinkedStack_Size LinkedStack_IsEmpty
    LinkedStack* stack = LinkedStack_Create();
    assert(LinkedStack_Size(stack) == 0);
    assert(LinkedStack_IsEmpty(stack) == true);

    // LinkedStack_Push
    LinkedStackItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        LinkedStack_Push(stack, arr[i]);
    }
    assert(LinkedStack_Size(stack) == 5);

    // LinkedStack_Top
    assert(LinkedStack_Top(stack) == 5);

    // LinkedStack_Pop
    for (int i = 0; i < arr_size; i++)
    {
        assert(LinkedStack_Pop(stack) == 5 - i);
    }
    assert(LinkedStack_Size(stack) == 0);

    // LinkedStack_Destroy
    LinkedStack_Destroy(stack);

    printf("Linked Stack Test OK.\n");
}
