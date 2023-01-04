#include <stdio.h>
#include <stdlib.h>

// TestGraph
void TestMatrixGraph(void);

// TestHeap
void TestMaxHeap(void);

// TestList
void TestArrayList(void);
void TestLinkedList(void);
void TestDoublyLinkedList(void);

// TestQueue
void TestArrayQueue(void);
void TestLinkedQueue(void);
void TestLinkedDeque(void);

// TestStack
void TestArrayStack(void);
void TestLinkedStack(void);

// TestString
void TestString(void);

// TestTable
void TestHashTable(void);

// TestTree
void TestBinarySearchTree(void);

int main(void)
{
    printf("\n=== Test Start ===\n");

    printf("\nTest Graph...\n");
    TestMatrixGraph();

    printf("\nTest Heap...\n");
    TestMaxHeap();

    printf("\nTest List...\n");
    TestArrayList();
    TestLinkedList();
    TestDoublyLinkedList();

    printf("\nTest Queue...\n");
    TestArrayQueue();
    TestLinkedQueue();
    TestLinkedDeque();

    printf("\nTest Stack...\n");
    TestArrayStack();
    TestLinkedStack();

    printf("\nTest String...\n");
    TestString();

    printf("\nTest Table...\n");
    TestHashTable();

    printf("\nTest Tree...\n");
    TestBinarySearchTree();

    printf("\n=== Test Finish ===\n");

    return EXIT_SUCCESS;
}
