# Test all

test: TestTree TestTable TestList TestHeap TestQueue TestStack TestGraph TestString

# Tree

TestTree: Tree/TestTree.exe
	./Tree/TestTree.exe

Tree/TestTree.exe: Tree/TestTree.c Tree/BinarySearchTree.o Tree/QueueForTree.o # need QueueForTree
	gcc -Wall Tree/TestTree.c Tree/BinarySearchTree.o Tree/QueueForTree.o -o Tree/TestTree.exe

Tree/BinarySearchTree.o: Tree/BinarySearchTree.c Tree/BinarySearchTree.h
	gcc -Wall -c Tree/BinarySearchTree.c -o Tree/BinarySearchTree.o

Tree/QueueForTree.o: Tree/QueueForTree.h Tree/QueueForTree.c
	gcc -Wall -c Tree/QueueForTree.c -o Tree/QueueForTree.o

# Table

TestTable: Table/TestTable.exe
	./Table/TestTable.exe

Table/TestTable.exe: Table/TestTable.c Table/HashTable.o
	gcc -Wall Table/TestTable.c Table/HashTable.o -o Table/TestTable.exe

Table/HashTable.o: Table/HashTable.c Table/HashTable.h
	gcc -Wall -c Table/HashTable.c -o Table/HashTable.o

# List

TestList: List/TestList.exe
	./List/TestList.exe

List/TestList.exe: List/TestList.c List/ArrayList.o List/LinkedList.o
	gcc -Wall List/TestList.c List/ArrayList.o List/LinkedList.o -o List/TestList.exe

List/ArrayList.o: List/ArrayList.c List/ArrayList.h
	gcc -Wall -c List/ArrayList.c -o List/ArrayList.o

List/LinkedList.o: List/LinkedList.c List/LinkedList.h
	gcc -Wall -c List/LinkedList.c -o List/LinkedList.o

# Heap

TestHeap: Heap/TestHeap.exe
	./Heap/TestHeap.exe

Heap/TestHeap.exe: Heap/TestHeap.c Heap/MaxHeap.o
	gcc -Wall Heap/TestHeap.c Heap/MaxHeap.o -o Heap/TestHeap.exe

Heap/MaxHeap.o: Heap/MaxHeap.c Heap/MaxHeap.h
	gcc -Wall -c Heap/MaxHeap.c -o Heap/MaxHeap.o

# Queue

TestQueue: Queue/TestQueue.exe
	./Queue/TestQueue.exe

Queue/TestQueue.exe: Queue/TestQueue.c Queue/ArrayQueue.o Queue/LinkedQueue.o
	gcc -Wall Queue/TestQueue.c Queue/ArrayQueue.o Queue/LinkedQueue.o -o Queue/TestQueue.exe

Queue/ArrayQueue.o: Queue/ArrayQueue.c Queue/ArrayQueue.h
	gcc -Wall -c Queue/ArrayQueue.c -o Queue/ArrayQueue.o

Queue/LinkedQueue.o: Queue/LinkedQueue.c Queue/LinkedQueue.h
	gcc -Wall -c Queue/LinkedQueue.c -o Queue/LinkedQueue.o

# Stack

TestStack: Stack/TestStack.exe
	./Stack/TestStack.exe

Stack/TestStack.exe: Stack/TestStack.c Stack/ArrayStack.o Stack/LinkedStack.o
	gcc -Wall Stack/TestStack.c Stack/ArrayStack.o Stack/LinkedStack.o -o Stack/TestStack.exe

Stack/ArrayStack.o: Stack/ArrayStack.c Stack/ArrayStack.h
	gcc -Wall -c Stack/ArrayStack.c -o Stack/ArrayStack.o

Stack/LinkedStack.o: Stack/LinkedStack.c Stack/LinkedStack.h
	gcc -Wall -c Stack/LinkedStack.c -o Stack/LinkedStack.o

# Graph

TestGraph: Graph/TestGraph.exe
	./Graph/TestGraph.exe

Graph/TestGraph.exe: Graph/TestGraph.c Graph/MatrixGraph.o Queue/ArrayQueue.o # need Queue
	gcc -Wall Graph/TestGraph.c Graph/MatrixGraph.o Queue/ArrayQueue.o -o Graph/TestGraph.exe

Graph/MatrixGraph.o: Graph/MatrixGraph.c Graph/MatrixGraph.h
	gcc -Wall -c Graph/MatrixGraph.c -o Graph/MatrixGraph.o

# String

TestString: String/TestString.exe
	./String/TestString.exe

String/TestString.exe: String/TestString.c String/String.o
	gcc -Wall String/TestString.c String/String.o -o String/TestString.exe

String/String.o: String/String.c String/String.h
	gcc -Wall -c String/String.c -o String/String.o

# Clean files

clean:
	rm -f */*.o */*.exe
