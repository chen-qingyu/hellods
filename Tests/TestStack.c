#include "../Sources/Stack/ArrayStack.h"
#include "../Sources/Stack/LinkedStack.h"

#include <assert.h>
#include <stdio.h>

void TestArrayStack(void)
{
    ArrayStack* stack = ArrayStack_Create();
    assert(ArrayStack_Size(stack) == 0);
    assert(ArrayStack_IsEmpty(stack) == true);

    ArrayStackItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        ArrayStack_Push(stack, arr[i]);
    }
    assert(ArrayStack_Size(stack) == 5);
    assert(ArrayStack_IsEmpty(stack) == false);
    assert(ArrayStack_Top(stack) == 5);

    for (int i = 0; i < arr_size; i++)
    {
        assert(ArrayStack_Pop(stack) == arr[arr_size - i - 1]);
    }
    assert(ArrayStack_IsEmpty(stack) == true);

    ArrayStack_Push(stack, 233);
    assert(ArrayStack_Size(stack) == 1);
    assert(ArrayStack_IsEmpty(stack) == false);
    assert(ArrayStack_Top(stack) == 233);

    ArrayStack_Destroy(stack);

    printf("Array Stack Test OK.\n");
}

void TestLinkedStack(void)
{
    LinkedStack* stack = LinkedStack_Create();
    assert(LinkedStack_Size(stack) == 0);
    assert(LinkedStack_IsEmpty(stack) == true);

    LinkedStackItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        LinkedStack_Push(stack, arr[i]);
    }
    assert(LinkedStack_Size(stack) == 5);
    assert(LinkedStack_IsEmpty(stack) == false);
    assert(LinkedStack_Top(stack) == 5);

    for (int i = 0; i < arr_size; i++)
    {
        assert(LinkedStack_Pop(stack) == arr[arr_size - i - 1]);
    }
    assert(LinkedStack_IsEmpty(stack) == true);

    LinkedStack_Push(stack, 233);
    assert(LinkedStack_Size(stack) == 1);
    assert(LinkedStack_IsEmpty(stack) == false);
    assert(LinkedStack_Top(stack) == 233);

    LinkedStack_Destroy(stack);

    printf("Linked Stack Test OK.\n");
}
