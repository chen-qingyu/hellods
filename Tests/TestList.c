#include "../Sources/List/ArrayList.h"
#include "../Sources/List/DoublyLinkedList.h"
#include "../Sources/List/LinkedList.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

// for test traverse
static char str[64] = {0};

static void Visit(int n)
{
    char tmp[8] = {0};
    sprintf(tmp, "%d ", n);
    strcat(str, tmp);
}

void TestArrayList(void)
{
    // ArrayList_Create ArrayList_Size ArrayList_IsEmpty
    ArrayList* list = ArrayList_Create();
    assert(ArrayList_Size(list) == 0);
    assert(ArrayList_IsEmpty(list) == true);

    // ArrayList_Insert
    ArrayListItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        ArrayList_Insert(list, i, arr[i]);
    }
    assert(ArrayList_Size(list) == arr_size);

    // ArrayList_At
    for (int i = 0; i < arr_size; ++i) // forward
    {
        assert(ArrayList_At(list, i) == i + 1);
    }
    for (int i = -1; i >= -arr_size; --i) // backward
    {
        assert(ArrayList_At(list, i) == i + 6);
    }

    // ArrayList_Find
    assert(ArrayList_Find(list, 1) == 0);
    assert(ArrayList_Find(list, 5) == 4);
    assert(ArrayList_Find(list, 0) == -1);

    // ArrayList_Traverse
    ArrayList_Traverse(list, Visit);
    assert(strcmp(str, "1 2 3 4 5 ") == 0);
    memset(str, 0, sizeof(str));

    // ArrayList_Reverse
    ArrayList_Reverse(list);
    ArrayList_Traverse(list, Visit);
    assert(strcmp(str, "5 4 3 2 1 ") == 0);
    memset(str, 0, sizeof(str));

    // ArrayList_Remove
    for (int i = 0; i < arr_size; i++)
    {
        assert(ArrayList_Remove(list, 0) == arr_size - i);
    }
    assert(ArrayList_Size(list) == 0);

    // ArrayList_Clear
    ArrayList_Insert(list, 0, 233);
    assert(ArrayList_Size(list) == 1);
    ArrayList_Clear(list);
    assert(ArrayList_Size(list) == 0);
    ArrayList_Clear(list); // double clear
    assert(ArrayList_Size(list) == 0);

    // ArrayList_Destroy
    ArrayList_Destroy(list);

    printf("Array List Test OK.\n");
}

void TestLinkedList(void)
{
    // LinkedList_Create LinkedList_Size LinkedList_IsEmpty
    LinkedList* list = LinkedList_Create();
    assert(LinkedList_Size(list) == 0);
    assert(LinkedList_IsEmpty(list) == true);

    // LinkedList_Insert
    LinkedListItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        LinkedList_Insert(list, i, arr[i]);
    }
    assert(LinkedList_Size(list) == arr_size);

    // LinkedList_At
    for (int i = 0; i < arr_size; ++i) // forward
    {
        assert(LinkedList_At(list, i) == i + 1);
    }
    for (int i = -1; i >= -arr_size; --i) // backward
    {
        assert(LinkedList_At(list, i) == i + 6);
    }

    // LinkedList_Find
    assert(LinkedList_Find(list, 1) == 0);
    assert(LinkedList_Find(list, 5) == 4);
    assert(LinkedList_Find(list, 0) == -1);

    // LinkedList_Traverse
    LinkedList_Traverse(list, Visit);
    assert(strcmp(str, "1 2 3 4 5 ") == 0);
    memset(str, 0, sizeof(str));

    // LinkedList_Reverse
    LinkedList_Reverse(list);
    LinkedList_Traverse(list, Visit);
    assert(strcmp(str, "5 4 3 2 1 ") == 0);
    memset(str, 0, sizeof(str));

    // LinkedList_Remove
    for (int i = 0; i < arr_size; i++)
    {
        assert(LinkedList_Remove(list, 0) == arr_size - i);
    }
    assert(LinkedList_Size(list) == 0);

    // LinkedList_Clear
    LinkedList_Insert(list, 0, 233);
    assert(LinkedList_Size(list) == 1);
    LinkedList_Clear(list);
    assert(LinkedList_Size(list) == 0);
    LinkedList_Clear(list); // double clear
    assert(LinkedList_Size(list) == 0);

    // LinkedList_Destroy
    LinkedList_Destroy(list);

    printf("Linked List Test OK.\n");
}

void TestDoublyLinkedList(void)
{
    // DoublyLinkedList_Create DoublyLinkedList_Size DoublyLinkedList_IsEmpty
    DoublyLinkedList* list = DoublyLinkedList_Create();
    assert(DoublyLinkedList_Size(list) == 0);
    assert(DoublyLinkedList_IsEmpty(list) == true);

    // DoublyLinkedList_Insert
    DoublyLinkedListItem arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        DoublyLinkedList_Insert(list, i, arr[i]);
    }
    assert(DoublyLinkedList_Size(list) == arr_size);

    // DoublyLinkedList_At
    for (int i = 0; i < arr_size; ++i) // forward
    {
        assert(DoublyLinkedList_At(list, i) == i + 1);
    }
    for (int i = -1; i >= -arr_size; --i) // backward
    {
        assert(DoublyLinkedList_At(list, i) == i + 6);
    }

    // DoublyLinkedList_Find
    assert(DoublyLinkedList_Find(list, 1) == 0);
    assert(DoublyLinkedList_Find(list, 5) == 4);
    assert(DoublyLinkedList_Find(list, 0) == -1);

    // DoublyLinkedList_Traverse
    DoublyLinkedList_Traverse(list, Visit);
    assert(strcmp(str, "1 2 3 4 5 ") == 0);
    memset(str, 0, sizeof(str));

    // DoublyLinkedList_Reverse
    DoublyLinkedList_Reverse(list);
    DoublyLinkedList_Traverse(list, Visit);
    assert(strcmp(str, "5 4 3 2 1 ") == 0);
    memset(str, 0, sizeof(str));

    // DoublyLinkedList_Remove
    for (int i = 0; i < arr_size; i++)
    {
        assert(DoublyLinkedList_Remove(list, 0) == arr_size - i);
    }
    assert(DoublyLinkedList_Size(list) == 0);

    // DoublyLinkedList_Clear
    DoublyLinkedList_Insert(list, 0, 233);
    assert(DoublyLinkedList_Size(list) == 1);
    DoublyLinkedList_Clear(list);
    assert(DoublyLinkedList_Size(list) == 0);
    DoublyLinkedList_Clear(list); // double clear
    assert(DoublyLinkedList_Size(list) == 0);

    // DoublyLinkedList_Destroy
    DoublyLinkedList_Destroy(list);

    printf("Doubly Linked List Test OK.\n");
}
