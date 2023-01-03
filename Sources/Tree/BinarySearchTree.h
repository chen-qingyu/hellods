/**
 * @file BinarySearchTree.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 二叉搜索树 (Binary Search Tree)
 * @version 1.0
 * @date 2022.01.29
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * 二叉树 tree 是一个有穷的结点集合。若不为空，则由根结点和其左、右二叉子树组成。
 * 二叉树 tree 属于 Tree ，结点数据 data 属于 TreeItem 。
 */

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <stdbool.h> // bool

#define TREE_NOT_FOUND (-1) // a value of TreeItem that indicates not found

typedef enum
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER,
    LEVEL_ORDER
} traverse_t;

typedef int TreeItem;

typedef struct tree Tree;

/**
 * @brief 创建一个空二叉搜索树
 *
 * @return 一个指向空二叉搜索树的指针
 */
Tree* BinarySearchTree_Create(void);

/**
 * @brief 销毁一个二叉搜索树
 *
 * @param self 一个指向待销毁二叉搜索树的指针
 */
void BinarySearchTree_Destroy(Tree* self);

/**
 * @brief 求二叉搜索树的元素个数
 *
 * @param self 一个指向二叉搜索树的指针
 * @return 二叉搜索树的元素个数
 */
int BinarySearchTree_Size(const Tree* self);

/**
 * @brief 判断二叉搜索树是否为空
 *
 * @param self 一个指向二叉搜索树的指针
 * @return 如果二叉搜索树为空则返回 true ，否则返回 false
 */
bool BinarySearchTree_IsEmpty(const Tree* self);

/**
 * @brief 遍历一个二叉搜索树
 *
 * @param self 一个指向二叉搜索树的指针
 * @param type 一个枚举遍历类型
 *              - PRE_ORDER   先序遍历
 *              - IN_ORDER    中序遍历
 *              - POST_ORDER  后序遍历
 *              - LEVEL_ORDER 层次遍历
 * @param p_trav 一个对遍历到的每个元素进行操作的函数的指针
 */
void BinarySearchTree_Traverse(Tree* self, traverse_t type, void (*p_trav)(TreeItem data));

/**
 * @brief 在一个二叉搜索树中寻找元素 data
 *
 * @param self 一个指向二叉搜索树的指针
 * @param data 一个待寻找元素
 * @return 元素 data 或者 TREE_NOT_FOUND
 */
TreeItem BinarySearchTree_Find(const Tree* self, TreeItem data);

/**
 * @brief 在一个二叉搜索树中寻找最小元素
 *
 * @param self 一个指向二叉搜索树的指针
 * @return 最小的元素或者 TREE_NOT_FOUND
 */
TreeItem BinarySearchTree_FindMin(const Tree* self);

/**
 * @brief 在一个二叉搜索树中寻找最大元素
 *
 * @param self 一个指向二叉搜索树的指针
 * @return 最大的元素或者 TREE_NOT_FOUND
 */
TreeItem BinarySearchTree_FindMax(const Tree* self);

/**
 * @brief 在一个二叉搜索树中插入元素 data
 *
 * @param self 一个指向二叉搜索树的指针
 * @param data 一个待插入元素
 */
void BinarySearchTree_Insert(Tree* self, TreeItem data);

/**
 * @brief 在一个二叉搜索树中删除元素 data
 *
 * @param self 一个指向二叉搜索树的指针
 * @param data 一个待删除元素
 */
void BinarySearchTree_Remove(Tree* self, TreeItem data);

#endif // BINARYSEARCHTREE_H
