// Tested on Microsoft Visual Studio Community 2019: ALL PASSED

#include "pch.h"

extern "C"
{
#include "../Sources/Stack/ArrayStack.h"
#include "../Sources/Stack/LinkedStack.h"
}

TEST(Stack, ArrayStack)
{
    // ArrayStack_Create ArrayStack_Size ArrayStack_IsEmpty
    ArrayStack* stack = ArrayStack_Create();
    ASSERT_EQ(ArrayStack_Size(stack), 0);
    ASSERT_EQ(ArrayStack_IsEmpty(stack), true);

    // ArrayStack_Clear
    ArrayStack_Push(stack, 233);
    ASSERT_EQ(ArrayStack_Size(stack), 1);
    ArrayStack_Clear(stack);
    ASSERT_EQ(ArrayStack_Size(stack), 0);
    ArrayStack_Clear(stack); // double clear
    ASSERT_EQ(ArrayStack_Size(stack), 0);

    // ArrayStack_Push
    ArrayStackItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        ArrayStack_Push(stack, arr[i]);
    }
    ASSERT_EQ(ArrayStack_Size(stack), 5);

    // ArrayStack_Top
    ASSERT_EQ(ArrayStack_Top(stack), 5);

    // ArrayStack_Pop
    for (int i = 0; i < arr_size; i++)
    {
        ASSERT_EQ(ArrayStack_Pop(stack), 5 - i);
    }
    ASSERT_EQ(ArrayStack_Size(stack), 0);

    // ArrayStack_Destroy
    ArrayStack_Destroy(stack);
}

TEST(Stack, LinkedStack)
{
    // LinkedStack_Create LinkedStack_Size LinkedStack_IsEmpty
    LinkedStack* stack = LinkedStack_Create();
    ASSERT_EQ(LinkedStack_Size(stack), 0);
    ASSERT_EQ(LinkedStack_IsEmpty(stack), true);

    // LinkedStack_Clear
    LinkedStack_Push(stack, 233);
    ASSERT_EQ(LinkedStack_Size(stack), 1);
    LinkedStack_Clear(stack);
    ASSERT_EQ(LinkedStack_Size(stack), 0);
    LinkedStack_Clear(stack); // double clear
    ASSERT_EQ(LinkedStack_Size(stack), 0);

    // LinkedStack_Push
    LinkedStackItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        LinkedStack_Push(stack, arr[i]);
    }
    ASSERT_EQ(LinkedStack_Size(stack), 5);

    // LinkedStack_Top
    ASSERT_EQ(LinkedStack_Top(stack), 5);

    // LinkedStack_Pop
    for (int i = 0; i < arr_size; i++)
    {
        ASSERT_EQ(LinkedStack_Pop(stack), 5 - i);
    }
    ASSERT_EQ(LinkedStack_Size(stack), 0);

    // LinkedStack_Destroy
    LinkedStack_Destroy(stack);
}
