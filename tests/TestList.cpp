#include <gtest/gtest.h>

extern "C"
{
#include "../sources/List/ArrayList.h"
#include "../sources/List/DoublyLinkedList.h"
#include "../sources/List/LinkedList.h"
}

// for test traverse
static char str[64] = {0};

static void Visit(int n)
{
    char tmp[8] = {0};
    sprintf(tmp, "%d ", n);
    strcat(str, tmp);
}

TEST(List, ArrayList)
{
    // ArrayList_Create ArrayList_Size ArrayList_IsEmpty
    ArrayList* list = ArrayList_Create();
    ASSERT_EQ(ArrayList_Size(list), 0);
    ASSERT_EQ(ArrayList_IsEmpty(list), true);

    // ArrayList_Clear
    ArrayList_Insert(list, 0, 233);
    ASSERT_EQ(ArrayList_Size(list), 1);
    ArrayList_Clear(list);
    ASSERT_EQ(ArrayList_Size(list), 0);
    ArrayList_Clear(list); // double clear
    ASSERT_EQ(ArrayList_Size(list), 0);

    // ArrayList_Insert
    ArrayListItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        ArrayList_Insert(list, i, arr[i]);
    }
    ASSERT_EQ(ArrayList_Size(list), arr_size);

    // ArrayList_At
    for (int i = 0; i < arr_size; ++i) // forward
    {
        ASSERT_EQ(ArrayList_At(list, i), i + 1);
    }
    for (int i = -1; i >= -arr_size; --i) // backward
    {
        ASSERT_EQ(ArrayList_At(list, i), i + 6);
    }

    // ArrayList_Find
    ASSERT_EQ(ArrayList_Find(list, 1), 0);
    ASSERT_EQ(ArrayList_Find(list, 5), 4);
    ASSERT_EQ(ArrayList_Find(list, 0), -1);

    // ArrayList_Traverse
    ArrayList_Traverse(list, Visit);
    ASSERT_EQ(strcmp(str, "1 2 3 4 5 "), 0);
    memset(str, 0, sizeof(str));

    // ArrayList_Reverse
    ArrayList_Reverse(list);
    ArrayList_Traverse(list, Visit);
    ASSERT_EQ(strcmp(str, "5 4 3 2 1 "), 0);
    memset(str, 0, sizeof(str));

    // ArrayList_Remove
    for (int i = 0; i < arr_size; i++)
    {
        ASSERT_EQ(ArrayList_Remove(list, 0), arr_size - i);
    }
    ASSERT_EQ(ArrayList_Size(list), 0);

    // ArrayList_Destroy
    ArrayList_Destroy(list);
}

TEST(List, LinkedList)
{
    // LinkedList_Create LinkedList_Size LinkedList_IsEmpty
    LinkedList* list = LinkedList_Create();
    ASSERT_EQ(LinkedList_Size(list), 0);
    ASSERT_EQ(LinkedList_IsEmpty(list), true);

    // LinkedList_Clear
    LinkedList_Insert(list, 0, 233);
    ASSERT_EQ(LinkedList_Size(list), 1);
    LinkedList_Clear(list);
    ASSERT_EQ(LinkedList_Size(list), 0);
    LinkedList_Clear(list); // double clear
    ASSERT_EQ(LinkedList_Size(list), 0);

    // LinkedList_Insert
    LinkedListItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        LinkedList_Insert(list, i, arr[i]);
    }
    ASSERT_EQ(LinkedList_Size(list), arr_size);

    // LinkedList_At
    for (int i = 0; i < arr_size; ++i) // forward
    {
        ASSERT_EQ(LinkedList_At(list, i), i + 1);
    }
    for (int i = -1; i >= -arr_size; --i) // backward
    {
        ASSERT_EQ(LinkedList_At(list, i), i + 6);
    }

    // LinkedList_Find
    ASSERT_EQ(LinkedList_Find(list, 1), 0);
    ASSERT_EQ(LinkedList_Find(list, 5), 4);
    ASSERT_EQ(LinkedList_Find(list, 0), -1);

    // LinkedList_Traverse
    LinkedList_Traverse(list, Visit);
    ASSERT_EQ(strcmp(str, "1 2 3 4 5 "), 0);
    memset(str, 0, sizeof(str));

    // LinkedList_Reverse
    LinkedList_Reverse(list);
    LinkedList_Traverse(list, Visit);
    ASSERT_EQ(strcmp(str, "5 4 3 2 1 "), 0);
    memset(str, 0, sizeof(str));

    // LinkedList_Remove
    for (int i = 0; i < arr_size; i++)
    {
        ASSERT_EQ(LinkedList_Remove(list, 0), arr_size - i);
    }
    ASSERT_EQ(LinkedList_Size(list), 0);

    // LinkedList_Destroy
    LinkedList_Destroy(list);
}

TEST(List, DoublyLinkedList)
{
    // DoublyLinkedList_Create DoublyLinkedList_Size DoublyLinkedList_IsEmpty
    DoublyLinkedList* list = DoublyLinkedList_Create();
    ASSERT_EQ(DoublyLinkedList_Size(list), 0);
    ASSERT_EQ(DoublyLinkedList_IsEmpty(list), true);

    // DoublyLinkedList_Clear
    DoublyLinkedList_Insert(list, 0, 233);
    ASSERT_EQ(DoublyLinkedList_Size(list), 1);
    DoublyLinkedList_Clear(list);
    ASSERT_EQ(DoublyLinkedList_Size(list), 0);
    DoublyLinkedList_Clear(list); // double clear
    ASSERT_EQ(DoublyLinkedList_Size(list), 0);

    // DoublyLinkedList_Insert
    DoublyLinkedListItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        DoublyLinkedList_Insert(list, i, arr[i]);
    }
    ASSERT_EQ(DoublyLinkedList_Size(list), arr_size);

    // DoublyLinkedList_At
    for (int i = 0; i < arr_size; ++i) // forward
    {
        ASSERT_EQ(DoublyLinkedList_At(list, i), i + 1);
    }
    for (int i = -1; i >= -arr_size; --i) // backward
    {
        ASSERT_EQ(DoublyLinkedList_At(list, i), i + 6);
    }

    // DoublyLinkedList_Find
    ASSERT_EQ(DoublyLinkedList_Find(list, 1), 0);
    ASSERT_EQ(DoublyLinkedList_Find(list, 5), 4);
    ASSERT_EQ(DoublyLinkedList_Find(list, 0), -1);

    // DoublyLinkedList_Traverse
    DoublyLinkedList_Traverse(list, Visit);
    ASSERT_EQ(strcmp(str, "1 2 3 4 5 "), 0);
    memset(str, 0, sizeof(str));

    // DoublyLinkedList_Reverse
    DoublyLinkedList_Reverse(list);
    DoublyLinkedList_Traverse(list, Visit);
    ASSERT_EQ(strcmp(str, "5 4 3 2 1 "), 0);
    memset(str, 0, sizeof(str));

    // DoublyLinkedList_Remove
    for (int i = 0; i < arr_size; i++)
    {
        ASSERT_EQ(DoublyLinkedList_Remove(list, 0), arr_size - i);
    }
    ASSERT_EQ(DoublyLinkedList_Size(list), 0);

    // DoublyLinkedList_Destroy
    DoublyLinkedList_Destroy(list);
}
