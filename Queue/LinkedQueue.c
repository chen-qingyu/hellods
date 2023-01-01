#include "LinkedQueue.h"

#include <stdio.h>
#include <stdlib.h>

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
    if (self->count == 0)
    {
        fprintf(stderr, "ERROR: The queue is empty.\n");
        exit(EXIT_FAILURE);
    }

    struct node* del = self->front->next;
    QueueItem data = del->data;

    self->front->next = del->next;
    free(del);

    --self->count;

    return data;
}
