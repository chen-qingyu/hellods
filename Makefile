# Test all

Test: Outputs/MainTest.exe
	./Outputs/MainTest.exe

# Tests

MainTest = Tests/MainTest.c
TestGraph = Tests/TestGraph.c Outputs/MatrixGraph.o
TestHeap = Tests/TestHeap.c Outputs/MaxHeap.o
TestList = Tests/TestList.c Outputs/ArrayList.o Outputs/LinkedList.o Outputs/DoublyLinkedList.o
TestQueue = Tests/TestQueue.c Outputs/ArrayQueue.o Outputs/LinkedQueue.o Outputs/LinkedDeque.o
TestStack = Tests/TestStack.c Outputs/ArrayStack.o Outputs/LinkedStack.o
TestString = Tests/TestString.c Outputs/String.o
TestTable = Tests/TestTable.c Outputs/HashTable.o
TestTree = Tests/TestTree.c Outputs/BinarySearchTree.o

Outputs/MainTest.exe: $(MainTest) $(TestGraph) $(TestHeap) $(TestList) $(TestQueue) $(TestStack) $(TestString) $(TestTable) $(TestTree)
	gcc -Wall $(MainTest) $(TestGraph) $(TestHeap) $(TestList) $(TestQueue) $(TestStack) $(TestString) $(TestTable) $(TestTree) -o Outputs/MainTest.exe

# Graph

Outputs/MatrixGraph.o: Sources/Graph/MatrixGraph.c Sources/Graph/MatrixGraph.h
	gcc -Wall -c Sources/Graph/MatrixGraph.c -o Outputs/MatrixGraph.o

# Heap

Outputs/MaxHeap.o: Sources/Heap/MaxHeap.c Sources/Heap/MaxHeap.h
	gcc -Wall -c Sources/Heap/MaxHeap.c -o Outputs/MaxHeap.o

# List

Outputs/ArrayList.o: Sources/List/ArrayList.c Sources/List/ArrayList.h
	gcc -Wall -c Sources/List/ArrayList.c -o Outputs/ArrayList.o

Outputs/LinkedList.o: Sources/List/LinkedList.c Sources/List/LinkedList.h
	gcc -Wall -c Sources/List/LinkedList.c -o Outputs/LinkedList.o

Outputs/DoublyLinkedList.o: Sources/List/DoublyLinkedList.c Sources/List/DoublyLinkedList.h
	gcc -Wall -c Sources/List/DoublyLinkedList.c -o Outputs/DoublyLinkedList.o

# Queue

Outputs/ArrayQueue.o: Sources/Queue/ArrayQueue.c Sources/Queue/ArrayQueue.h
	gcc -Wall -c Sources/Queue/ArrayQueue.c -o Outputs/ArrayQueue.o

Outputs/LinkedQueue.o: Sources/Queue/LinkedQueue.c Sources/Queue/LinkedQueue.h
	gcc -Wall -c Sources/Queue/LinkedQueue.c -o Outputs/LinkedQueue.o

Outputs/LinkedDeque.o: Sources/Queue/LinkedDeque.c Sources/Queue/LinkedDeque.h
	gcc -Wall -c Sources/Queue/LinkedDeque.c -o Outputs/LinkedDeque.o

# Stack

Outputs/ArrayStack.o: Sources/Stack/ArrayStack.c Sources/Stack/ArrayStack.h
	gcc -Wall -c Sources/Stack/ArrayStack.c -o Outputs/ArrayStack.o

Outputs/LinkedStack.o: Sources/Stack/LinkedStack.c Sources/Stack/LinkedStack.h
	gcc -Wall -c Sources/Stack/LinkedStack.c -o Outputs/LinkedStack.o

# String

Outputs/String.o: Sources/String/String.c Sources/String/String.h
	gcc -Wall -c Sources/String/String.c -o Outputs/String.o

# Table

Outputs/HashTable.o: Sources/Table/HashTable.c Sources/Table/HashTable.h
	gcc -Wall -c Sources/Table/HashTable.c -o Outputs/HashTable.o

# Tree

Outputs/BinarySearchTree.o: Sources/Tree/BinarySearchTree.c Sources/Tree/BinarySearchTree.h
	gcc -Wall -c Sources/Tree/BinarySearchTree.c -o Outputs/BinarySearchTree.o

# Clean files

clean:
	rm -f Outputs/*
