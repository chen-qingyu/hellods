#include "MatrixGraph.h"

#include <stdlib.h> // malloc free

#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

#define NOT_FOUND (-1)

#define NO_PATH INT_MAX

struct MatrixGraph
{
    int vertex_num;
    int edge_num;
    MatrixGraphEdge matrix[VERTEX_NUMBER][VERTEX_NUMBER]; // 邻接矩阵
};

static bool visited[VERTEX_NUMBER] = {false};

/*******************************
Helper functions implementation.
*******************************/

typedef MatrixGraphVertex ArrayQueueItem;

typedef struct ArrayQueue ArrayQueue;

#define ARRAYQUEUE_CAPACITY 256

struct ArrayQueue
{
    ArrayQueueItem data[ARRAYQUEUE_CAPACITY + 1];
    int front;
    int rear;
};

static ArrayQueue* ArrayQueue_Create(void)
{
    ArrayQueue* queue = (ArrayQueue*)malloc(sizeof(ArrayQueue));
    check_pointer(queue);

    queue->front = -1;
    queue->rear = -1;

    return queue;
}

static void ArrayQueue_Destroy(ArrayQueue* self)
{
    free(self);
}

static int ArrayQueue_Size(const ArrayQueue* self)
{
    return (self->rear - self->front + (ARRAYQUEUE_CAPACITY + 1)) % (ARRAYQUEUE_CAPACITY + 1);
}

static bool ArrayQueue_IsEmpty(const ArrayQueue* self)
{
    return ArrayQueue_Size(self) == 0;
}

static void ArrayQueue_Enqueue(ArrayQueue* self, ArrayQueueItem data)
{
    check_full(ArrayQueue_Size(self), ARRAYQUEUE_CAPACITY);

    self->rear = (self->rear + 1) % ARRAYQUEUE_CAPACITY;
    self->data[self->rear] = data;
}

static ArrayQueueItem ArrayQueue_Dequeue(ArrayQueue* self)
{
    check_empty(ArrayQueue_Size(self));

    self->front = (self->front + 1) % ARRAYQUEUE_CAPACITY;

    return self->data[self->front];
}

static void clean_visited_flag(void)
{
    for (MatrixGraphVertex i = 0; i < VERTEX_NUMBER; i++)
    {
        visited[i] = false;
    }
}

static void dfs(MatrixGraph* G, MatrixGraphVertex startV, void (*p_visit)(MatrixGraphVertex V))
{
    p_visit(startV);
    visited[startV] = true;

    for (MatrixGraphVertex V1 = 0; V1 < G->vertex_num; V1++)
    {
        if (MatrixGraph_IsAdjacent(G, startV, V1) && !visited[V1])
        {
            dfs(G, V1, p_visit);
        }
    }
}

static MatrixGraphVertex find_min_dist(const MatrixGraph* G, MatrixGraphEdge dist[])
{
    MatrixGraphVertex min_v;
    int min_dist = NO_PATH;

    for (MatrixGraphVertex V = 0; V < G->vertex_num; V++)
    {
        if (!visited[V] && dist[V] < min_dist)
        {
            min_dist = dist[V];
            min_v = V;
        }
    }

    return min_dist < NO_PATH ? min_v : NOT_FOUND;
}

/*******************************
Interface functions implementation.
*******************************/

MatrixGraph* MatrixGraph_Create(void)
{
    MatrixGraph* G = (MatrixGraph*)malloc(sizeof(MatrixGraph));
    check_pointer(G);

    G->vertex_num = VERTEX_NUMBER;
    G->edge_num = 0;

    for (MatrixGraphVertex V1 = 0; V1 < G->vertex_num; V1++)
    {
        for (MatrixGraphVertex V2 = 0; V2 < G->vertex_num; V2++)
        {
            G->matrix[V1][V2] = NO_PATH;
        }
    }

    return G;
}

void MatrixGraph_Destroy(MatrixGraph* self)
{
    free(self);
}

void MatrixGraph_Link(MatrixGraph* self, MatrixGraphVertex V1, MatrixGraphVertex V2, MatrixGraphEdge E)
{
    self->matrix[V1][V2] = E;
#ifdef UNDIRECTED
    self->matrix[V2][V1] = E;
#endif
}

void MatrixGraph_Unlink(MatrixGraph* self, MatrixGraphVertex V1, MatrixGraphVertex V2)
{
    self->matrix[V1][V2] = NO_PATH;
#ifdef UNDIRECTED
    self->matrix[V2][V1] = NO_PATH;
#endif
}

bool MatrixGraph_IsAdjacent(const MatrixGraph* self, MatrixGraphVertex V1, MatrixGraphVertex V2)
{
    return self->matrix[V1][V2] != NO_PATH ? true : false;
}

void MatrixGraph_DFS(MatrixGraph* self, MatrixGraphVertex startV, void (*p_visit)(MatrixGraphVertex V))
{
    clean_visited_flag();

    dfs(self, startV, p_visit);
}

void MatrixGraph_BFS(MatrixGraph* self, MatrixGraphVertex startV, void (*p_visit)(MatrixGraphVertex V))
{
    clean_visited_flag();

    p_visit(startV);
    visited[startV] = true;

    ArrayQueue* Q = ArrayQueue_Create();
    ArrayQueue_Enqueue(Q, startV);
    while (!ArrayQueue_IsEmpty(Q))
    {
        MatrixGraphVertex V1 = ArrayQueue_Dequeue(Q);
        for (MatrixGraphVertex V2 = 0; V2 < self->vertex_num; V2++)
        {
            if (!visited[V2] && MatrixGraph_IsAdjacent(self, V1, V2))
            {
                p_visit(V2);
                visited[V2] = true;
                ArrayQueue_Enqueue(Q, V2);
            }
        }
    }
    ArrayQueue_Destroy(Q);
}

bool MatrixGraph_Dijkstra(const MatrixGraph* self, MatrixGraphEdge dist[], MatrixGraphVertex path[], MatrixGraphVertex startV)
{
    clean_visited_flag();

    // init array state
    for (MatrixGraphVertex V1 = 0; V1 < self->vertex_num; V1++)
    {
        dist[V1] = self->matrix[startV][V1];
        path[V1] = dist[V1] < NO_PATH ? startV : NOT_FOUND;
    }

    dist[startV] = 0;
    visited[startV] = true;

    while (1)
    {
        MatrixGraphVertex V1 = find_min_dist(self, dist);
        if (V1 == NOT_FOUND)
        {
            break;
        }
        visited[V1] = true;
        for (MatrixGraphVertex V2 = 0; V2 < self->vertex_num; V2++)
        {
            if (visited[V2] == false && self->matrix[V1][V2] < NO_PATH)
            {
                if (self->matrix[V1][V2] < 0)
                {
                    return false;
                }
                if (dist[V1] + self->matrix[V1][V2] < dist[V2])
                {
                    dist[V2] = dist[V1] + self->matrix[V1][V2];
                    path[V2] = V1;
                }
            }
        }
    }

    return true;
}

bool MatrixGraph_Floyd(const MatrixGraph* self, MatrixGraphEdge dist[][VERTEX_NUMBER], MatrixGraphVertex path[][VERTEX_NUMBER])
{
    for (MatrixGraphVertex i = 0; i < self->vertex_num; i++)
    {
        for (MatrixGraphVertex j = 0; j < self->vertex_num; j++)
        {
            dist[i][j] = self->matrix[i][j];
            path[i][j] = NOT_FOUND;
        }
    }

    for (MatrixGraphVertex k = 0; k < self->vertex_num; k++)
    {
        for (MatrixGraphVertex i = 0; i < self->vertex_num; i++)
        {
            for (MatrixGraphVertex j = 0; j < self->vertex_num; j++)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    if (i == j && dist[i][j] < 0)
                    {
                        return false;
                    }
                    path[i][j] = k;
                }
            }
        }
    }

    return true;
}
