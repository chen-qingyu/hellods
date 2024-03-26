#include <catch2/catch_test_macros.hpp>

#include "../sources/List/ArrayList.hpp"
// #include "../sources/List/DoublyLinkedList.h"
// #include "../sources/List/LinkedList.h"

TEST_CASE("List: ArrayList")
{
    // // ArrayList_Create ArrayList_Size ArrayList_IsEmpty
    // ArrayList* list = ArrayList_Create();
    // REQUIRE(ArrayList_Size(list) == 0);
    // REQUIRE(ArrayList_IsEmpty(list) == true);

    // // ArrayList_Clear
    // ArrayList_Insert(list, 0, 233);
    // REQUIRE(ArrayList_Size(list) == 1);
    // ArrayList_Clear(list);
    // REQUIRE(ArrayList_Size(list) == 0);
    // ArrayList_Clear(list); // double clear
    // REQUIRE(ArrayList_Size(list) == 0);

    // // ArrayList_Insert
    // ArrayListItem arr[] = {1, 2, 3, 4, 5};
    // int arr_size = sizeof(arr) / sizeof(arr[0]);
    // for (int i = 0; i < arr_size; i++)
    // {
    //     ArrayList_Insert(list, i, arr[i]);
    // }
    // REQUIRE(ArrayList_Size(list) == arr_size);

    // // ArrayList_At
    // for (int i = 0; i < arr_size; ++i) // forward
    // {
    //     REQUIRE(ArrayList_At(list, i) == i + 1);
    // }
    // for (int i = -1; i >= -arr_size; --i) // backward
    // {
    //     REQUIRE(ArrayList_At(list, i) == i + 6);
    // }

    // // ArrayList_Find
    // REQUIRE(ArrayList_Find(list, 1) == 0);
    // REQUIRE(ArrayList_Find(list, 5) == 4);
    // REQUIRE(ArrayList_Find(list, 0) == -1);

    // // ArrayList_Traverse
    // ArrayList_Traverse(list, Visit);
    // REQUIRE(strcmp(str, "1 2 3 4 5 ") == 0);
    // memset(str, 0, sizeof(str));

    // // ArrayList_Reverse
    // ArrayList_Reverse(list);
    // ArrayList_Traverse(list, Visit);
    // REQUIRE(strcmp(str, "5 4 3 2 1 ") == 0);
    // memset(str, 0, sizeof(str));

    // // ArrayList_Remove
    // for (int i = 0; i < arr_size; i++)
    // {
    //     REQUIRE(ArrayList_Remove(list, 0) == arr_size - i);
    // }
    // REQUIRE(ArrayList_Size(list) == 0);

    // // ArrayList_Destroy
    // ArrayList_Destroy(list);
    // }

    // TEST_CASE("List: LinkedList")
    // {
    //     // LinkedList_Create LinkedList_Size LinkedList_IsEmpty
    //     LinkedList* list = LinkedList_Create();
    //     REQUIRE(LinkedList_Size(list) == 0);
    //     REQUIRE(LinkedList_IsEmpty(list) == true);

    // // LinkedList_Clear
    // LinkedList_Insert(list, 0, 233);
    // REQUIRE(LinkedList_Size(list) == 1);
    // LinkedList_Clear(list);
    // REQUIRE(LinkedList_Size(list) == 0);
    // LinkedList_Clear(list); // double clear
    // REQUIRE(LinkedList_Size(list) == 0);

    // // LinkedList_Insert
    // LinkedListItem arr[] = {1, 2, 3, 4, 5};
    // int arr_size = sizeof(arr) / sizeof(arr[0]);
    // for (int i = 0; i < arr_size; i++)
    // {
    //     LinkedList_Insert(list, i, arr[i]);
    // }
    // REQUIRE(LinkedList_Size(list) == arr_size);

    // // LinkedList_At
    // for (int i = 0; i < arr_size; ++i) // forward
    // {
    //     REQUIRE(LinkedList_At(list, i) == i + 1);
    // }
    // for (int i = -1; i >= -arr_size; --i) // backward
    // {
    //     REQUIRE(LinkedList_At(list, i) == i + 6);
    // }

    // // LinkedList_Find
    // REQUIRE(LinkedList_Find(list, 1) == 0);
    // REQUIRE(LinkedList_Find(list, 5) == 4);
    // REQUIRE(LinkedList_Find(list, 0) == -1);

    // // LinkedList_Traverse
    // LinkedList_Traverse(list, Visit);
    // REQUIRE(strcmp(str, "1 2 3 4 5 ") == 0);
    // memset(str, 0, sizeof(str));

    // // LinkedList_Reverse
    // LinkedList_Reverse(list);
    // LinkedList_Traverse(list, Visit);
    // REQUIRE(strcmp(str, "5 4 3 2 1 ") == 0);
    // memset(str, 0, sizeof(str));

    // // LinkedList_Remove
    // for (int i = 0; i < arr_size; i++)
    // {
    //     REQUIRE(LinkedList_Remove(list, 0) == arr_size - i);
    // }
    // REQUIRE(LinkedList_Size(list) == 0);

    // // LinkedList_Destroy
    // LinkedList_Destroy(list);
    // }

    // TEST_CASE("List: DoublyLinkedList")
    // {
    //     // DoublyLinkedList_Create DoublyLinkedList_Size DoublyLinkedList_IsEmpty
    //     DoublyLinkedList* list = DoublyLinkedList_Create();
    //     REQUIRE(DoublyLinkedList_Size(list) == 0);
    //     REQUIRE(DoublyLinkedList_IsEmpty(list) == true);

    // // DoublyLinkedList_Clear
    // DoublyLinkedList_Insert(list, 0, 233);
    // REQUIRE(DoublyLinkedList_Size(list) == 1);
    // DoublyLinkedList_Clear(list);
    // REQUIRE(DoublyLinkedList_Size(list) == 0);
    // DoublyLinkedList_Clear(list); // double clear
    // REQUIRE(DoublyLinkedList_Size(list) == 0);

    // // DoublyLinkedList_Insert
    // DoublyLinkedListItem arr[] = {1, 2, 3, 4, 5};
    // int arr_size = sizeof(arr) / sizeof(arr[0]);
    // for (int i = 0; i < arr_size; i++)
    // {
    //     DoublyLinkedList_Insert(list, i, arr[i]);
    // }
    // REQUIRE(DoublyLinkedList_Size(list) == arr_size);

    // // DoublyLinkedList_At
    // for (int i = 0; i < arr_size; ++i) // forward
    // {
    //     REQUIRE(DoublyLinkedList_At(list, i) == i + 1);
    // }
    // for (int i = -1; i >= -arr_size; --i) // backward
    // {
    //     REQUIRE(DoublyLinkedList_At(list, i) == i + 6);
    // }

    // // DoublyLinkedList_Find
    // REQUIRE(DoublyLinkedList_Find(list, 1) == 0);
    // REQUIRE(DoublyLinkedList_Find(list, 5) == 4);
    // REQUIRE(DoublyLinkedList_Find(list, 0) == -1);

    // // DoublyLinkedList_Traverse
    // DoublyLinkedList_Traverse(list, Visit);
    // REQUIRE(strcmp(str, "1 2 3 4 5 ") == 0);
    // memset(str, 0, sizeof(str));

    // // DoublyLinkedList_Reverse
    // DoublyLinkedList_Reverse(list);
    // DoublyLinkedList_Traverse(list, Visit);
    // REQUIRE(strcmp(str, "5 4 3 2 1 ") == 0);
    // memset(str, 0, sizeof(str));

    // // DoublyLinkedList_Remove
    // for (int i = 0; i < arr_size; i++)
    // {
    //     REQUIRE(DoublyLinkedList_Remove(list, 0) == arr_size - i);
    // }
    // REQUIRE(DoublyLinkedList_Size(list) == 0);

    // // DoublyLinkedList_Destroy
    // DoublyLinkedList_Destroy(list);
}
