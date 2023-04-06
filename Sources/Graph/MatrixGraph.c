#include "MatrixGraph.h"

#include <stdlib.h> // malloc free

#include "../common/check_empty.h"
#include "../common/check_full.h"
#include "../common/check_pointer.h"

#define NOT_FOUND (-1)

#define NO_PATH INT_MAX

/// Matrix Graph (Weighted Directed).
struct MatrixGraph
{
    /// Number of vertices.
    int vertex_num;

    /// Adjacency matrix.
    MatrixGraphEdge** matrix;
};

/*
 * Helpers
 */

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

static void dfs(MatrixGraph* G, MatrixGraphVertex startV, void (*p_visit)(MatrixGraphVertex V), bool* visited)
{
    p_visit(startV);
    visited[startV] = true;

    for (MatrixGraphVertex V1 = 0; V1 < G->vertex_num; V1++)
    {
        if (MatrixGraph_IsAdjacent(G, startV, V1) && !visited[V1])
        {
            dfs(G, V1, p_visit, visited);
        }
    }
}

static MatrixGraphVertex find_min_dist(const MatrixGraph* G, MatrixGraphEdge dist[], bool* visited)
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

static void free_matrix(MatrixGraph* self)
{
    if (self->matrix != NULL)
    {
        for (int i = 0; i < self->vertex_num; i++)
        {
            free(self->matrix[i]);
        }
        free(self->matrix);
    }
}

/*
 * Functions
 */

MatrixGraph* MatrixGraph_Create(void)
{
    MatrixGraph* G = (MatrixGraph*)malloc(sizeof(MatrixGraph));
    check_pointer(G);

    G->vertex_num = 0;
    G->matrix = NULL;

    return G;
}

void MatrixGraph_Destroy(MatrixGraph* self)
{
    // let it crush if self is invalid

    free_matrix(self);

    free(self);
}

void MatrixGraph_SetVertexNumber(MatrixGraph* self, int vertex_number)
{
    free_matrix(self);

    self->vertex_num = vertex_number;

    self->matrix = (MatrixGraphEdge**)malloc(sizeof(MatrixGraphEdge*) * vertex_number);
    for (int i = 0; i < vertex_number; i++)
    {
        self->matrix[i] = (MatrixGraphEdge*)malloc(sizeof(MatrixGraphEdge) * vertex_number);
    }

    for (MatrixGraphVertex v1 = 0; v1 < vertex_number; v1++)
    {
        for (MatrixGraphVertex v2 = 0; v2 < vertex_number; v2++)
        {
            self->matrix[v1][v2] = NO_PATH;
        }
    }
}

void MatrixGraph_Link(MatrixGraph* self, MatrixGraphVertex V1, MatrixGraphVertex V2, MatrixGraphEdge E)
{
    self->matrix[V1][V2] = E;
}

void MatrixGraph_Unlink(MatrixGraph* self, MatrixGraphVertex V1, MatrixGraphVertex V2)
{
    self->matrix[V1][V2] = NO_PATH;
}

bool MatrixGraph_IsAdjacent(const MatrixGraph* self, MatrixGraphVertex V1, MatrixGraphVertex V2)
{
    return self->matrix[V1][V2] != NO_PATH ? true : false;
}

void MatrixGraph_DFS(MatrixGraph* self, MatrixGraphVertex startV, void (*p_visit)(MatrixGraphVertex V))
{
    bool* visited = (bool*)calloc(self->vertex_num, sizeof(bool));

    dfs(self, startV, p_visit, visited);

    free(visited);
}

void MatrixGraph_BFS(MatrixGraph* self, MatrixGraphVertex startV, void (*p_visit)(MatrixGraphVertex V))
{
    bool* visited = (bool*)calloc(self->vertex_num, sizeof(bool));

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
    free(visited);
}

bool MatrixGraph_Dijkstra(const MatrixGraph* self, MatrixGraphEdge dist[], MatrixGraphVertex path[], MatrixGraphVertex startV)
{
    bool* visited = (bool*)calloc(self->vertex_num, sizeof(bool));

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
        MatrixGraphVertex V1 = find_min_dist(self, dist, visited);
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

    free(visited);

    return true;
}

bool MatrixGraph_Floyd(const MatrixGraph* self, MatrixGraphEdge** dist, MatrixGraphVertex** path)
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
