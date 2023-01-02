/**
 * @file ArrayQueue.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 队列 数组实现 (Array Queue)
 * @version 1.0
 * @date 2022.01.28
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * 队列 queue 是一个有 n(n>=0) 个元素的有穷线性表。
 * 队列 queue 属于 Queue ，元素 data 属于 QueueItem 。
 */

#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

#include <stdbool.h> // bool

typedef int QueueItem;

typedef struct queue Queue;

/**
 * @brief 创建一个空队列
 *
 * @return 一个指向空队列的指针
 */
Queue* ArrayQueue_Create(void);

/**
 * @brief 销毁一个队列
 *
 * @param self 一个指向待销毁队列的指针
 */
void ArrayQueue_Destroy(Queue* self);

/**
 * @brief 求队列的长度
 *
 * @param self 一个指向队列的指针
 * @return 队列长度
 */
int ArrayQueue_Size(const Queue* self);

/**
 * @brief 判断队列是否已空
 *
 * @param self 一个指向队列的指针
 * @return 如果队列已空则返回 true ，否则返回 false
 */
bool ArrayQueue_IsEmpty(const Queue* self);

/**
 * @brief 入队，将元素 data 插入到队列的尾部
 *
 * @param self 一个指向队列的指针
 * @param data 一个待入队的元素
 */
void ArrayQueue_Enqueue(Queue* self, QueueItem data);

/**
 * @brief 出队，将队列的队首元素出队
 *
 * @param self 一个指向队列的指针
 * @return 队首元素
 */
QueueItem ArrayQueue_Dequeue(Queue* self);

#endif // ARRAYQUEUE_H
