#include "LinkedQueue.h"

#include <limits.h> // INT_MAX
#include <stdlib.h> // malloc free NULL

#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

struct node
{
    QueueItem data;
    struct node* next;
};

struct queue
{
    struct node* front;
    struct node* rear;
    int size;
};

/*******************************
Helper functions implementation.
*******************************/

/*******************************
Interface functions implementation.
*******************************/

Queue* LinkedQueue_Create(void)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    check_pointer(queue);

    queue->front = (struct node*)malloc(sizeof(struct node));
    check_pointer(queue->front);

    queue->rear = queue->front;
    queue->front->next = NULL;
    queue->size = 0;

    return queue;
}

void LinkedQueue_Destroy(Queue* self)
{
    while (self->front)
    {
        struct node* current = self->front->next;
        free(self->front);
        self->front = current;
    }
    free(self);
}

int LinkedQueue_Size(const Queue* self)
{
    return self->size;
}

bool LinkedQueue_IsEmpty(const Queue* self)
{
    return self->size == 0;
}

void LinkedQueue_Enqueue(Queue* self, QueueItem data)
{
    check_full(self->size, INT_MAX);

    struct node* add = (struct node*)malloc(sizeof(struct node));
    check_pointer(add);

    add->data = data;
    add->next = NULL;

    self->rear->next = add;
    self->rear = add;

    ++self->size;
}

QueueItem LinkedQueue_Dequeue(Queue* self)
{
    check_empty(self->size);

    if (self->rear == self->front->next)
    {
        self->rear = self->front;
    }

    struct node* del = self->front->next;
    QueueItem data = del->data;

    self->front->next = del->next;
    free(del);

    --self->size;

    return data;
}

QueueItem LinkedQueue_Front(Queue* self)
{
    check_empty(self->size);

    return self->front->next->data;
}
