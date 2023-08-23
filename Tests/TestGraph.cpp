// Tested on Microsoft Visual Studio Community 2019: ALL PASSED

#include "../pch.h"

extern "C"
{
#include "../Sources/Graph/MatrixGraph.h"
}

// for test traverse
static char str[64] = {0};

static void Visit(MatrixGraphVertex V)
{
    char tmp[8] = {0};
    sprintf(tmp, "%d ", V);
    strcat(str, tmp);
}

TEST(Graph, MatrixGraph)
{
    // MatrixGraph_Create
    MatrixGraph* G = MatrixGraph_Create();

    // MatrixGraph_SetVertexNumber
    MatrixGraph_SetVertexNumber(G, 7);

    // MatrixGraph_Link
    MatrixGraph_Link(G, 0, 1, 2);
    MatrixGraph_Link(G, 0, 3, 1);
    MatrixGraph_Link(G, 1, 4, 10);
    MatrixGraph_Link(G, 1, 3, 3);
    MatrixGraph_Link(G, 2, 0, 4);
    MatrixGraph_Link(G, 2, 5, 5);
    MatrixGraph_Link(G, 3, 2, 2);
    MatrixGraph_Link(G, 3, 4, 2);
    MatrixGraph_Link(G, 3, 5, 8);
    MatrixGraph_Link(G, 3, 6, 4);
    MatrixGraph_Link(G, 6, 5, 1);

    /*
          +--+   2    +--+
          |V0|------->|V1|
          +--+        +--+
       +--^  | 1    3 |  |  10
      4|     +--v  v--+  +--v
    +--+    2   +--+   2    +--+
    |V2|<-------|V3|------->|V4|
    +--+        +--+        +--+
      5|      8 |  | 4      |6
       +--v  v--+  +--v  v--+
          +--+   1    +--+
          |V5|<-------|V6|
          +--+        +--+
    */

    // MatrixGraph_IsAdjacent
    ASSERT_EQ(MatrixGraph_IsAdjacent(G, 0, 1), true);
    ASSERT_EQ(MatrixGraph_IsAdjacent(G, 0, 6), false);
    ASSERT_EQ(MatrixGraph_IsAdjacent(G, 6, 0), false);

    MatrixGraph_Link(G, 0, 6, 99);
    ASSERT_EQ(MatrixGraph_IsAdjacent(G, 0, 6), true);
    ASSERT_EQ(MatrixGraph_IsAdjacent(G, 6, 0), false);

    // MatrixGraph_Unlink
    MatrixGraph_Unlink(G, 0, 6);
    ASSERT_EQ(MatrixGraph_IsAdjacent(G, 0, 6), false);

    // MatrixGraph_DFS
    MatrixGraph_DFS(G, 0, Visit);
    ASSERT_EQ(strcmp(str, "0 1 3 2 5 4 6 "), 0);
    memset(str, 0, sizeof(str));

    // MatrixGraph_BFS
    MatrixGraph_BFS(G, 0, Visit);
    ASSERT_EQ(strcmp(str, "0 1 3 4 2 5 6 "), 0);
    memset(str, 0, sizeof(str));

    // MatrixGraph_Dijkstra
    int dist[7];
    int path[7];
    MatrixGraph_Dijkstra(G, dist, path, 0);

    ASSERT_EQ(dist[0], 0);
    ASSERT_EQ(dist[1], 2);
    ASSERT_EQ(dist[2], 3);
    ASSERT_EQ(dist[3], 1);
    ASSERT_EQ(dist[4], 3);
    ASSERT_EQ(dist[5], 6);
    ASSERT_EQ(dist[6], 5);

    ASSERT_EQ(path[0], -1);
    ASSERT_EQ(path[1], 0);
    ASSERT_EQ(path[2], 3);
    ASSERT_EQ(path[3], 0);
    ASSERT_EQ(path[4], 3);
    ASSERT_EQ(path[5], 6);
    ASSERT_EQ(path[6], 3);

    // MatrixGraph_Destroy
    MatrixGraph_Destroy(G);
}
