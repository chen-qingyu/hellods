#include "ArrayQueue.h"

#include <stdlib.h> // malloc free

#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

// 为保证入队是严格的 O(1) 时间复杂度，故这里采用固定的容量，而不是动态增长。
#define QUEUE_CAPACITY 256

struct queue
{
    QueueItem data[QUEUE_CAPACITY + 1]; // 循环队列，数组容量为队列有效容量加一
    int front;
    int rear;
};

/*******************************
Helper functions implementation.
*******************************/

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
    check_full(ArrayQueue_Size(self), QUEUE_CAPACITY);

    self->rear = (self->rear + 1) % QUEUE_CAPACITY;
    self->data[self->rear] = data;
}

QueueItem ArrayQueue_Dequeue(Queue* self)
{
    check_empty(ArrayQueue_Size(self));

    self->front = (self->front + 1) % QUEUE_CAPACITY;

    return self->data[self->front];
}
