/**
 * @file MatrixGraph.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 图 邻接矩阵实现 (Matrix Graph)
 * @version 1.0
 * @date 2022.01.29
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * 图 G(V, E) 由一个非空的有限顶点集合 V 和一个有限边集合 E 组成。
 * 图 G 属于 Graph ，顶点的编号 V 属于 GraphVertex ，边的权重 E 属于 GraphEdge 。
 */

#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include <stdbool.h> // bool

#define VERTEX_NUMBER 7

/* 注释掉此行变成无向图 */
// #define UNDIRECTED

typedef int GraphVertex; // 顶点的编号

typedef int GraphEdge; // 边的权重

typedef struct graph Graph; // 图

/**
 * @brief 创建一个空图
 *
 * @return Graph* 一个指向空图的指针
 */
Graph* MatrixGraph_Create(void);

/**
 * @brief 销毁一个图
 *
 * @param self 一个指向待销毁图的指针
 */
void MatrixGraph_Destroy(Graph* self);

/**
 * @brief 以权重 E 链接图的两个顶点 V1 和 V2
 *
 * @param self 一个指向图的指针
 * @param V1 顶点1
 * @param V2 顶点2
 * @param E 两个顶点之间连线的权重
 */
void MatrixGraph_Link(Graph* self, GraphVertex V1, GraphVertex V2, GraphEdge E);

/**
 * @brief 断开图的两个顶点 V1 和 V2
 *
 * @param self 一个指向图的指针
 * @param V1 顶点1
 * @param V2 顶点2
 */
void MatrixGraph_Unlink(Graph* self, GraphVertex V1, GraphVertex V2);

/**
 * @brief 判断图的两个顶点 V1 和 V2 之间是否链接
 *
 * @param self 一个指向图的指针
 * @param V1 顶点1
 * @param V2 顶点2
 * @return 如果两个顶点已链接则返回 true ，否则返回 false
 */
bool MatrixGraph_IsAdjacent(const Graph* self, GraphVertex V1, GraphVertex V2);

/**
 * @brief 深度优先遍历图
 *
 * @param self 一个指向图的指针
 * @param startV 遍历起始点
 * @param p_visit 一个对遍历到的每个顶点进行操作的函数的指针
 */
void MatrixGraph_DFS(Graph* self, GraphVertex startV, void (*p_visit)(GraphVertex V));

/**
 * @brief 广度优先遍历图
 *
 * @param self 一个指向图的指针
 * @param startV 遍历起始点
 * @param p_visit 一个对遍历到的每个顶点进行操作的函数的指针
 */
void MatrixGraph_BFS(Graph* self, GraphVertex startV, void (*p_visit)(GraphVertex V));

/**
 * @brief Dijkstra 算法遍历图
 *
 * @param self 一个指向图的指针
 * @param dist 距离数组
 * @param path 路径数组
 * @param startV 遍历起始点
 * @return 如果执行成功返回 true ，否则返回 false
 */
bool MatrixGraph_Dijkstra(const Graph* self, GraphEdge dist[], GraphVertex path[], GraphVertex startV);

/**
 * @brief Floyd 算法遍历图
 *
 * @param self 一个指向图的指针
 * @param dist 距离数组
 * @param path 路径数组
 * @return 如果执行成功返回 true ，否则返回 false
 */
bool MatrixGraph_Floyd(const Graph* self, GraphEdge dist[][VERTEX_NUMBER], GraphVertex path[][VERTEX_NUMBER]);

#endif // MATRIXGRAPH_H
