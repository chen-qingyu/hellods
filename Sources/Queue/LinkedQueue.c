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
    int count;
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
    queue->count = 0;

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
    return self->count;
}

bool LinkedQueue_IsEmpty(const Queue* self)
{
    return self->count == 0;
}

void LinkedQueue_Enqueue(Queue* self, QueueItem data)
{
    check_full(self->count, INT_MAX);

    struct node* add = (struct node*)malloc(sizeof(struct node));
    check_pointer(add);

    add->data = data;
    add->next = NULL;

    self->rear->next = add;
    self->rear = add;

    ++self->count;
}

QueueItem LinkedQueue_Dequeue(Queue* self)
{
    check_empty(self->count);

    struct node* del = self->front->next;
    QueueItem data = del->data;

    self->front->next = del->next;
    free(del);

    --self->count;

    return data;
}
