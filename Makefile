# Test all

test: Tests/MainTest.exe
	./Tests/MainTest.exe

# Tests

MainTest = Tests/MainTest.c
TestGraph = Tests/TestGraph.c Sources/Graph/MatrixGraph.o
TestHeap = Tests/TestHeap.c Sources/Heap/MaxHeap.o
TestList = Tests/TestList.c Sources/List/ArrayList.o Sources/List/LinkedList.o
TestQueue = Tests/TestQueue.c Sources/Queue/ArrayQueue.o Sources/Queue/LinkedQueue.o
TestStack = Tests/TestStack.c Sources/Stack/ArrayStack.o Sources/Stack/LinkedStack.o
TestString = Tests/TestString.c Sources/String/String.o
TestTable = Tests/TestTable.c Sources/Table/HashTable.o
TestTree = Tests/TestTree.c Sources/Tree/BinarySearchTree.o Sources/Tree/QueueForTree.o

Tests/MainTest.exe: $(MainTest) $(TestGraph) $(TestHeap) $(TestList) $(TestQueue) $(TestStack) $(TestString) $(TestTable) $(TestTree)
	gcc -Wall $(MainTest) $(TestGraph) $(TestHeap) $(TestList) $(TestQueue) $(TestStack) $(TestString) $(TestTable) $(TestTree) -o Tests/MainTest.exe

# Graph

Sources/Graph/MatrixGraph.o: Sources/Graph/MatrixGraph.c Sources/Graph/MatrixGraph.h
	gcc -Wall -c Sources/Graph/MatrixGraph.c -o Sources/Graph/MatrixGraph.o

# Heap

Sources/Heap/MaxHeap.o: Sources/Heap/MaxHeap.c Sources/Heap/MaxHeap.h
	gcc -Wall -c Sources/Heap/MaxHeap.c -o Sources/Heap/MaxHeap.o

# List

Sources/List/ArrayList.o: Sources/List/ArrayList.c Sources/List/ArrayList.h
	gcc -Wall -c Sources/List/ArrayList.c -o Sources/List/ArrayList.o

Sources/List/LinkedList.o: Sources/List/LinkedList.c Sources/List/LinkedList.h
	gcc -Wall -c Sources/List/LinkedList.c -o Sources/List/LinkedList.o

# Queue

Sources/Queue/ArrayQueue.o: Sources/Queue/ArrayQueue.c Sources/Queue/ArrayQueue.h
	gcc -Wall -c Sources/Queue/ArrayQueue.c -o Sources/Queue/ArrayQueue.o

Sources/Queue/LinkedQueue.o: Sources/Queue/LinkedQueue.c Sources/Queue/LinkedQueue.h
	gcc -Wall -c Sources/Queue/LinkedQueue.c -o Sources/Queue/LinkedQueue.o

# Stack

Sources/Stack/ArrayStack.o: Sources/Stack/ArrayStack.c Sources/Stack/ArrayStack.h
	gcc -Wall -c Sources/Stack/ArrayStack.c -o Sources/Stack/ArrayStack.o

Sources/Stack/LinkedStack.o: Sources/Stack/LinkedStack.c Sources/Stack/LinkedStack.h
	gcc -Wall -c Sources/Stack/LinkedStack.c -o Sources/Stack/LinkedStack.o

# String

Sources/String/String.o: Sources/String/String.c Sources/String/String.h
	gcc -Wall -c Sources/String/String.c -o Sources/String/String.o

# Table

Sources/Table/HashTable.o: Sources/Table/HashTable.c Sources/Table/HashTable.h
	gcc -Wall -c Sources/Table/HashTable.c -o Sources/Table/HashTable.o

# Tree

Sources/Tree/BinarySearchTree.o: Sources/Tree/BinarySearchTree.c Sources/Tree/BinarySearchTree.h
	gcc -Wall -c Sources/Tree/BinarySearchTree.c -o Sources/Tree/BinarySearchTree.o

Sources/Tree/QueueForTree.o: Sources/Tree/QueueForTree.h Sources/Tree/QueueForTree.c
	gcc -Wall -c Sources/Tree/QueueForTree.c -o Sources/Tree/QueueForTree.o

# Clean files

clean:
	rm -f Sources/*/*.o Tests/*.exe
