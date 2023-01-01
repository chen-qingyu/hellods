#include "ArrayQueue.h"

#include <stdio.h>
#include <stdlib.h>

#define QUEUE_CAPACITY 100

struct queue
{
    QueueItem data[QUEUE_CAPACITY + 1]; // 循环队列，数组容量为队列有效容量加一
    int front;
    int rear;
};

/*******************************
Helper functions implementation.
*******************************/

// Check whether the pointer is a non-null pointer.
static inline void check_pointer(const void* pointer)
{
    if (pointer == NULL)
    {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
}

/*******************************
Interface functions implementation.
*******************************/

Queue* ArrayQueue_Create(void)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    check_pointer(queue);

    queue->front = -1;
    queue->rear = -1;

    return queue;
}

void ArrayQueue_Destroy(Queue* self)
{
    free(self);
}

int ArrayQueue_Size(const Queue* self)
{
    return (self->rear - self->front + (QUEUE_CAPACITY + 1)) % (QUEUE_CAPACITY + 1);
}

bool ArrayQueue_IsEmpty(const Queue* self)
{
    return ArrayQueue_Size(self) == 0;
}

void ArrayQueue_Enqueue(Queue* self, QueueItem data)
{
    if (ArrayQueue_Size(self) == QUEUE_CAPACITY)
    {
        fprintf(stderr, "ERROR: The queue is full.\n");
        return;
    }

    self->rear = (self->rear + 1) % QUEUE_CAPACITY;
    self->data[self->rear] = data;
}

QueueItem ArrayQueue_Dequeue(Queue* self)
{
    if (ArrayQueue_IsEmpty(self))
    {
        fprintf(stderr, "ERROR: The queue is empty.\n");
        exit(EXIT_FAILURE);
    }

    self->front = (self->front + 1) % QUEUE_CAPACITY;

    return self->data[self->front];
}
