#include "MatrixGraph.h"
#include "../Queue/ArrayQueue.h"

#include <stdlib.h> // malloc free

#include "../common/check_pointer.h"

#define NOT_FOUND (-1)

#define NO_PATH INT_MAX

struct graph
{
    int vertex_num;
    int edge_num;
    GraphEdge matrix[VERTEX_NUMBER][VERTEX_NUMBER]; // 邻接矩阵
};

static bool visited[VERTEX_NUMBER] = {false};

/*******************************
Helper functions implementation.
*******************************/

static void clean_visited_flag(void)
{
    for (GraphVertex i = 0; i < VERTEX_NUMBER; i++)
    {
        visited[i] = false;
    }
}

static void dfs(Graph* G, GraphVertex startV, void (*p_visit)(GraphVertex V))
{
    p_visit(startV);
    visited[startV] = true;

    for (GraphVertex V1 = 0; V1 < G->vertex_num; V1++)
    {
        if (MatrixGraph_IsAdjacent(G, startV, V1) && !visited[V1])
        {
            dfs(G, V1, p_visit);
        }
    }
}

static GraphVertex find_min_dist(const Graph* G, GraphEdge dist[])
{
    GraphVertex min_v;
    int min_dist = NO_PATH;

    for (GraphVertex V = 0; V < G->vertex_num; V++)
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

Graph* MatrixGraph_Create(void)
{
    Graph* G = (Graph*)malloc(sizeof(Graph));
    check_pointer(G);

    G->vertex_num = VERTEX_NUMBER;
    G->edge_num = 0;

    for (GraphVertex V1 = 0; V1 < G->vertex_num; V1++)
    {
        for (GraphVertex V2 = 0; V2 < G->vertex_num; V2++)
        {
            G->matrix[V1][V2] = NO_PATH;
        }
    }

    return G;
}

void MatrixGraph_Destroy(Graph* self)
{
    free(self);
}

void MatrixGraph_Link(Graph* self, GraphVertex V1, GraphVertex V2, GraphEdge E)
{
    self->matrix[V1][V2] = E;
#ifdef UNDIRECTED
    self->matrix[V2][V1] = E;
#endif
}

void MatrixGraph_Unlink(Graph* self, GraphVertex V1, GraphVertex V2)
{
    self->matrix[V1][V2] = NO_PATH;
#ifdef UNDIRECTED
    self->matrix[V2][V1] = NO_PATH;
#endif
}

bool MatrixGraph_IsAdjacent(const Graph* self, GraphVertex V1, GraphVertex V2)
{
    return self->matrix[V1][V2] != NO_PATH ? true : false;
}

void MatrixGraph_DFS(Graph* self, GraphVertex startV, void (*p_visit)(GraphVertex V))
{
    clean_visited_flag();

    dfs(self, startV, p_visit);
}

void MatrixGraph_BFS(Graph* self, GraphVertex startV, void (*p_visit)(GraphVertex V))
{
    clean_visited_flag();

    p_visit(startV);
    visited[startV] = true;

    Queue* Q = ArrayQueue_Create();
    ArrayQueue_Enqueue(Q, startV);
    while (!ArrayQueue_IsEmpty(Q))
    {
        GraphVertex V1 = ArrayQueue_Dequeue(Q);
        for (GraphVertex V2 = 0; V2 < self->vertex_num; V2++)
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

bool MatrixGraph_Dijkstra(const Graph* self, GraphEdge dist[], GraphVertex path[], GraphVertex startV)
{
    clean_visited_flag();

    // init array state
    for (GraphVertex V1 = 0; V1 < self->vertex_num; V1++)
    {
        dist[V1] = self->matrix[startV][V1];
        path[V1] = dist[V1] < NO_PATH ? startV : NOT_FOUND;
    }

    dist[startV] = 0;
    visited[startV] = true;

    while (1)
    {
        GraphVertex V1 = find_min_dist(self, dist);
        if (V1 == NOT_FOUND)
        {
            break;
        }
        visited[V1] = true;
        for (GraphVertex V2 = 0; V2 < self->vertex_num; V2++)
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

bool MatrixGraph_Floyd(const Graph* self, GraphEdge dist[][VERTEX_NUMBER], GraphVertex path[][VERTEX_NUMBER])
{
    for (GraphVertex i = 0; i < self->vertex_num; i++)
    {
        for (GraphVertex j = 0; j < self->vertex_num; j++)
        {
            dist[i][j] = self->matrix[i][j];
            path[i][j] = NOT_FOUND;
        }
    }

    for (GraphVertex k = 0; k < self->vertex_num; k++)
    {
        for (GraphVertex i = 0; i < self->vertex_num; i++)
        {
            for (GraphVertex j = 0; j < self->vertex_num; j++)
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
