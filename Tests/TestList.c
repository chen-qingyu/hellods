#include "../Sources/List/ArrayList.h"
#include "../Sources/List/DoublyLinkedList.h"
#include "../Sources/List/LinkedList.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

static char str[64] = {0};

static void Visit(ListItem n)
{
    char tmp[8] = {0};
    sprintf(tmp, "%d ", n);
    strcat(str, tmp);
}

void TestArrayList(void)
{
    List* list1 = ArrayList_Create();
    assert(ArrayList_Size(list1) == 0);
    assert(ArrayList_IsEmpty(list1) == true);

    ListItem arr[] = {1, 2, 3, 4};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        ArrayList_Insert(list1, i, arr[i]);
        assert(ArrayList_At(list1, i) == i + 1);
    }
    assert(ArrayList_Size(list1) == 4);
    assert(ArrayList_IsEmpty(list1) == false);
    assert(ArrayList_At(list1, -1) == 4);

    ArrayList_Traverse(list1, Visit);
    assert(strcmp(str, "1 2 3 4 ") == 0);
    memset(str, 0, sizeof(str));

    ArrayList_Reverse(list1);
    ArrayList_Traverse(list1, Visit);
    assert(strcmp(str, "4 3 2 1 ") == 0);
    memset(str, 0, sizeof(str));

    List* list2 = ArrayList_Create();
    ListItem arr2[] = {233, 666, 888, 999};
    int arr2Size = sizeof(arr2) / sizeof(arr2[0]);
    for (int i = 0; i < arr2Size; i++)
    {
        ArrayList_Insert(list2, i, arr2[i]);
    }

    for (int i = 0; i < arr2Size; ++i)
    {
        ArrayList_Insert(list1, i, ArrayList_At(list2, i));
    }
    ArrayList_Traverse(list1, Visit);
    assert(strcmp(str, "233 666 888 999 4 3 2 1 ") == 0);
    memset(str, 0, sizeof(str));

    assert(ArrayList_Size(list1) == 8);
    assert(ArrayList_IsEmpty(list1) == false);

    assert(ArrayList_Find(list1, 233) == 0);
    assert(ArrayList_Find(list1, 999) == 3);
    assert(ArrayList_Find(list1, 1) == 7);
    assert(ArrayList_Find(list1, 0) == LIST_NOT_FOUND);

    int length = ArrayList_Size(list1);
    for (int i = 0; i < length; i++)
    {
        ArrayList_Remove(list1, 0);
    }
    assert(ArrayList_Size(list1) == 0);
    assert(ArrayList_IsEmpty(list1) == true);

    ArrayList_Destroy(list1);
    ArrayList_Destroy(list2);

    printf("Array List Test OK.\n");
}

void TestLinkedList(void)
{
    List* list1 = LinkedList_Create();
    assert(LinkedList_Size(list1) == 0);
    assert(LinkedList_IsEmpty(list1) == true);

    ListItem arr[] = {1, 2, 3, 4};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        LinkedList_Insert(list1, i, arr[i]);
        assert(LinkedList_At(list1, i) == i + 1);
    }
    assert(LinkedList_Size(list1) == 4);
    assert(LinkedList_IsEmpty(list1) == false);
    assert(LinkedList_At(list1, -1) == 4);

    LinkedList_Traverse(list1, Visit);
    assert(strcmp(str, "1 2 3 4 ") == 0);
    memset(str, 0, sizeof(str));

    LinkedList_Reverse(list1);
    LinkedList_Traverse(list1, Visit);
    assert(strcmp(str, "4 3 2 1 ") == 0);
    memset(str, 0, sizeof(str));

    List* list2 = LinkedList_Create();
    ListItem arr2[] = {233, 666, 888, 999};
    int arr2Size = sizeof(arr2) / sizeof(arr2[0]);
    for (int i = 0; i < arr2Size; i++)
    {
        LinkedList_Insert(list2, i, arr2[i]);
    }

    for (int i = 0; i < arr2Size; ++i)
    {
        LinkedList_Insert(list1, i, LinkedList_At(list2, i));
    }
    LinkedList_Traverse(list1, Visit);
    assert(strcmp(str, "233 666 888 999 4 3 2 1 ") == 0);
    memset(str, 0, sizeof(str));

    assert(LinkedList_Size(list1) == 8);
    assert(LinkedList_IsEmpty(list1) == false);

    assert(LinkedList_Find(list1, 233) == 0);
    assert(LinkedList_Find(list1, 999) == 3);
    assert(LinkedList_Find(list1, 1) == 7);
    assert(LinkedList_Find(list1, 0) == LIST_NOT_FOUND);

    int length = LinkedList_Size(list1);
    for (int i = 0; i < length; i++)
    {
        LinkedList_Remove(list1, 0);
    }
    assert(LinkedList_Size(list1) == 0);
    assert(LinkedList_IsEmpty(list1) == true);

    LinkedList_Destroy(list1);
    LinkedList_Destroy(list2);

    printf("Linked List Test OK.\n");
}

void TestDoublyLinkedList(void)
{
    List* list1 = DoublyLinkedList_Create();
    assert(DoublyLinkedList_Size(list1) == 0);
    assert(DoublyLinkedList_IsEmpty(list1) == true);

    ListItem arr[] = {1, 2, 3, 4};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < arr_size; i++)
    {
        DoublyLinkedList_Insert(list1, i, arr[i]);
        assert(DoublyLinkedList_At(list1, i) == i + 1);
    }
    assert(DoublyLinkedList_Size(list1) == 4);
    assert(DoublyLinkedList_IsEmpty(list1) == false);
    assert(DoublyLinkedList_At(list1, -1) == 4);

    DoublyLinkedList_Traverse(list1, Visit);
    assert(strcmp(str, "1 2 3 4 ") == 0);
    memset(str, 0, sizeof(str));

    DoublyLinkedList_Reverse(list1);
    DoublyLinkedList_Traverse(list1, Visit);
    assert(strcmp(str, "4 3 2 1 ") == 0);
    memset(str, 0, sizeof(str));

    List* list2 = DoublyLinkedList_Create();
    ListItem arr2[] = {233, 666, 888, 999};
    int arr2Size = sizeof(arr2) / sizeof(arr2[0]);
    for (int i = 0; i < arr2Size; i++)
    {
        DoublyLinkedList_Insert(list2, i, arr2[i]);
    }

    for (int i = 0; i < arr2Size; ++i)
    {
        DoublyLinkedList_Insert(list1, i, DoublyLinkedList_At(list2, i));
    }
    DoublyLinkedList_Traverse(list1, Visit);
    assert(strcmp(str, "233 666 888 999 4 3 2 1 ") == 0);
    memset(str, 0, sizeof(str));

    assert(DoublyLinkedList_Size(list1) == 8);
    assert(DoublyLinkedList_IsEmpty(list1) == false);

    assert(DoublyLinkedList_Find(list1, 233) == 0);
    assert(DoublyLinkedList_Find(list1, 999) == 3);
    assert(DoublyLinkedList_Find(list1, 1) == 7);
    assert(DoublyLinkedList_Find(list1, 0) == LIST_NOT_FOUND);

    int length = DoublyLinkedList_Size(list1);
    for (int i = 0; i < length; i++)
    {
        DoublyLinkedList_Remove(list1, 0);
    }
    assert(DoublyLinkedList_Size(list1) == 0);
    assert(DoublyLinkedList_IsEmpty(list1) == true);

    DoublyLinkedList_Destroy(list1);
    DoublyLinkedList_Destroy(list2);

    printf("Doubly Linked List Test OK.\n");
}
