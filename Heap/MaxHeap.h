/**
 * @file MaxHeap.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 最大堆 (Max Heap)
 * @version 1.0
 * @date 2022.01.29
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * 最大堆 heap 是一棵完全二叉树，每个结点的元素值不小于其子结点的元素值。
 * 最大堆 heap 属于 Heap ，元素 data 属于 HeapItem 。
 */

#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <stdbool.h> // bool

typedef int HeapItem;

typedef struct heap Heap;

/**
 * @brief 创建一个空堆
 *
 * @return Heap* 一个指向空堆的指针
 */
Heap* MaxHeap_Create(void);

/**
 * @brief 销毁一个堆
 *
 * @param self 一个指向待销毁堆的指针
 */
void MaxHeap_Destroy(Heap* self);

/**
 * @brief 求堆的元素个数
 *
 * @param self 一个指向堆的指针
 * @return 堆的元素个数
 */
int MaxHeap_Size(const Heap* self);

/**
 * @brief 判断堆是否已空
 *
 * @param self 一个指向堆的指针
 * @return 如果堆已空则返回 true ，否则返回 false
 */
bool MaxHeap_IsEmpty(const Heap* self);

/**
 * @brief 在堆中插入一个元素 data
 *
 * @param self 一个指向堆的指针
 * @param data 一个待插入元素
 */
void MaxHeap_Push(Heap* self, HeapItem data);

/**
 * @brief  在堆中删除堆顶元素
 *
 * @param self 一个指向堆的指针
 * @return 堆顶元素
 */
HeapItem MaxHeap_Pop(Heap* self);

/**
 * @brief 查看堆的堆顶元素
 *
 * @param self 一个指向堆的指针
 * @return 堆顶元素
 */
HeapItem MaxHeap_Top(Heap* self);

#endif // MAXHEAP_H
