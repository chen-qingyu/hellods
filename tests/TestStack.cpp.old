#include <catch2/catch_test_macros.hpp>

extern "C"
{
#include "../sources/Stack/ArrayStack.h"
#include "../sources/Stack/LinkedStack.h"
}

TEST_CASE("Stack: ArrayStack")
{
    // ArrayStack_Create ArrayStack_Size ArrayStack_IsEmpty
    ArrayStack* stack = ArrayStack_Create();
    REQUIRE(ArrayStack_Size(stack) == 0);
    REQUIRE(ArrayStack_IsEmpty(stack) == true);

    // ArrayStack_Clear
    ArrayStack_Push(stack, 233);
    REQUIRE(ArrayStack_Size(stack) == 1);
    ArrayStack_Clear(stack);
    REQUIRE(ArrayStack_Size(stack) == 0);
    ArrayStack_Clear(stack); // double clear
    REQUIRE(ArrayStack_Size(stack) == 0);

    // ArrayStack_Push
    ArrayStackItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        ArrayStack_Push(stack, arr[i]);
    }
    REQUIRE(ArrayStack_Size(stack) == 5);

    // ArrayStack_Top
    REQUIRE(ArrayStack_Top(stack) == 5);

    // ArrayStack_Pop
    for (int i = 0; i < arr_size; i++)
    {
        REQUIRE(ArrayStack_Pop(stack) == 5 - i);
    }
    REQUIRE(ArrayStack_Size(stack) == 0);

    // ArrayStack_Destroy
    ArrayStack_Destroy(stack);
}

TEST_CASE("Stack: LinkedStack")
{
    // LinkedStack_Create LinkedStack_Size LinkedStack_IsEmpty
    LinkedStack* stack = LinkedStack_Create();
    REQUIRE(LinkedStack_Size(stack) == 0);
    REQUIRE(LinkedStack_IsEmpty(stack) == true);

    // LinkedStack_Clear
    LinkedStack_Push(stack, 233);
    REQUIRE(LinkedStack_Size(stack) == 1);
    LinkedStack_Clear(stack);
    REQUIRE(LinkedStack_Size(stack) == 0);
    LinkedStack_Clear(stack); // double clear
    REQUIRE(LinkedStack_Size(stack) == 0);

    // LinkedStack_Push
    LinkedStackItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        LinkedStack_Push(stack, arr[i]);
    }
    REQUIRE(LinkedStack_Size(stack) == 5);

    // LinkedStack_Top
    REQUIRE(LinkedStack_Top(stack) == 5);

    // LinkedStack_Pop
    for (int i = 0; i < arr_size; i++)
    {
        REQUIRE(LinkedStack_Pop(stack) == 5 - i);
    }
    REQUIRE(LinkedStack_Size(stack) == 0);

    // LinkedStack_Destroy
    LinkedStack_Destroy(stack);
}
