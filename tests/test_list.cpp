#include <catch2/catch_test_macros.hpp>

#include "../sources/List/ArrayList.hpp"
#include "../sources/List/DoublyLinkedList.hpp"
// #include "../sources/List/LinkedList.h"

using namespace hellods;

template <typename List>
void test()
{
    // Constructor / Destructor
    List empty;
    List list = {1, 2, 3, 4, 5};

    // Comparison
    REQUIRE(empty == List());
    REQUIRE(list == List({1, 2, 3, 4, 5}));
    REQUIRE(empty != list);

    // Access
    for (int i = 0; i < 5; ++i)
    {
        REQUIRE(list[i] == i + 1);
    }

    // Examination
    REQUIRE(empty.size() == 0);
    REQUIRE(empty.is_empty() == true);
    REQUIRE(empty.find(1) == -1);
    REQUIRE(list.size() == 5);
    REQUIRE(list.is_empty() == false);
    REQUIRE(list.find(1) == 0);

    // Manipulation
    empty.insert(0, 1);
    REQUIRE(empty == List({1}));
    empty.insert(0, 2);
    REQUIRE(empty == List({2, 1}));
    empty.insert(2, 3);
    REQUIRE(empty == List({2, 1, 3}));

    REQUIRE(empty.remove(1) == 1);
    REQUIRE(empty.remove(0) == 2);
    REQUIRE(empty.remove(0) == 3);

    REQUIRE(list.map([&](int& e)
                     { e *= 2; }) == List({2, 4, 6, 8, 10}));

    REQUIRE(list.reverse() == List({10, 8, 6, 4, 2}));

    REQUIRE(list.clear() == empty);
    REQUIRE(list.clear() == empty); // double clear
}

TEST_CASE("ArrayList")
{
    test<ArrayList<int>>();
}

TEST_CASE("DoublyLinkedList")
{
    test<DoublyLinkedList<int>>();
}

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
