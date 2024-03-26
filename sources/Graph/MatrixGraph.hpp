/**
 * @file MatrixGraph.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Graph implemented by adjacency matrix. This is weighted directed graph.
 * @date 2022.01.29
 *
 * @copyright Copyright (C) 2022
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MATRIXGRAPH_HPP
#define MATRIXGRAPH_HPP

#include <stdbool.h> // bool

/// 顶点的编号
typedef int MatrixGraphVertex;

/// 边的权重
typedef int MatrixGraphEdge;

/// 加权有向图
typedef struct MatrixGraph MatrixGraph;

/**
 * @brief 创建一个空图（零个节点的加权有向图）
 *
 * @return 一个指向空图的指针
 */
MatrixGraph* MatrixGraph_Create(void);

/**
 * @brief 销毁一个图
 *
 * @param self 一个指向待销毁图的指针
 */
void MatrixGraph_Destroy(MatrixGraph* self);

/**
 * @brief 设置图的顶点数量
 *
 * @param self 一个指向图的指针
 * @param vertex_number 顶点数量
 */
void MatrixGraph_SetVertexNumber(MatrixGraph* self, int vertex_number);

/**
 * @brief 以权重 E 单向链接 V1 和 V2
 *
 * @param self 一个指向图的指针
 * @param V1 顶点1
 * @param V2 顶点2
 * @param E V1 到 V2 的权重
 */
void MatrixGraph_Link(MatrixGraph* self, MatrixGraphVertex V1, MatrixGraphVertex V2, MatrixGraphEdge E);

/**
 * @brief 断开 V1 到 V2 的单向链接
 *
 * @param self 一个指向图的指针
 * @param V1 顶点1
 * @param V2 顶点2
 */
void MatrixGraph_Unlink(MatrixGraph* self, MatrixGraphVertex V1, MatrixGraphVertex V2);

/**
 * @brief 判断 V1 到 V2 是否有单向链接
 *
 * @param self 一个指向图的指针
 * @param V1 顶点1
 * @param V2 顶点2
 * @return 如果已链接则返回 true ，否则返回 false
 */
bool MatrixGraph_IsAdjacent(const MatrixGraph* self, MatrixGraphVertex V1, MatrixGraphVertex V2);

/**
 * @brief 深度优先遍历图
 *
 * @param self 一个指向图的指针
 * @param startV 遍历起始点
 * @param p_visit 一个对遍历到的每个顶点进行操作的函数的指针
 */
void MatrixGraph_DFS(MatrixGraph* self, MatrixGraphVertex startV, void (*p_visit)(MatrixGraphVertex V));

/**
 * @brief 广度优先遍历图
 *
 * @param self 一个指向图的指针
 * @param startV 遍历起始点
 * @param p_visit 一个对遍历到的每个顶点进行操作的函数的指针
 */
void MatrixGraph_BFS(MatrixGraph* self, MatrixGraphVertex startV, void (*p_visit)(MatrixGraphVertex V));

/**
 * @brief Dijkstra 算法遍历图
 *
 * @param self 一个指向图的指针
 * @param dist 距离数组
 * @param path 路径数组
 * @param startV 遍历起始点
 * @return 如果执行成功返回 true ，否则返回 false
 */
bool MatrixGraph_Dijkstra(const MatrixGraph* self, MatrixGraphEdge dist[], MatrixGraphVertex path[], MatrixGraphVertex startV);

/**
 * @brief Floyd 算法遍历图
 *
 * @param self 一个指向图的指针
 * @param dist 距离数组
 * @param path 路径数组
 * @return 如果执行成功返回 true ，否则返回 false
 */
bool MatrixGraph_Floyd(const MatrixGraph* self, MatrixGraphEdge** dist, MatrixGraphVertex** path);

#endif // MATRIXGRAPH_HPP
