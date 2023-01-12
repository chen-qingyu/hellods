#include "ArrayQueue.h"

#include <stdlib.h> // malloc free

#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

// 为保证入队是严格的 O(1) 时间复杂度，故这里采用固定的容量，而不是动态增长。
#define MAX_CAPACITY 256

struct ArrayQueue
{
    ArrayQueueItem data[MAX_CAPACITY + 1]; // 循环队列，数组容量为队列有效容量加一
    int front;
    int rear;
};

/*******************************
Helper functions implementation.
*******************************/

/*******************************
Interface functions implementation.
*******************************/

ArrayQueue* ArrayQueue_Create(void)
{
    ArrayQueue* queue = (ArrayQueue*)malloc(sizeof(ArrayQueue));
    check_pointer(queue);

    queue->front = -1;
    queue->rear = -1;

    return queue;
}

void ArrayQueue_Destroy(ArrayQueue* self)
{
    free(self);
}

int ArrayQueue_Size(const ArrayQueue* self)
{
    return (self->rear - self->front + (MAX_CAPACITY + 1)) % (MAX_CAPACITY + 1);
}

bool ArrayQueue_IsEmpty(const ArrayQueue* self)
{
    return ArrayQueue_Size(self) == 0;
}

void ArrayQueue_Enqueue(ArrayQueue* self, ArrayQueueItem data)
{
    check_full(ArrayQueue_Size(self), MAX_CAPACITY);

    self->rear = (self->rear + 1) % MAX_CAPACITY;
    self->data[self->rear] = data;
}

ArrayQueueItem ArrayQueue_Dequeue(ArrayQueue* self)
{
    check_empty(ArrayQueue_Size(self));

    self->front = (self->front + 1) % MAX_CAPACITY;

    return self->data[self->front];
}

ArrayQueueItem ArrayQueue_Front(ArrayQueue* self)
{
    check_empty(ArrayQueue_Size(self));

    return self->data[(self->front + 1) % MAX_CAPACITY];
}
