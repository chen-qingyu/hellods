/**
 * @file LinkedQueue.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 队列 链表实现 (Linked Queue)
 * @version 1.0
 * @date 2022.01.28
 *
 * @copyright Copyright (c) 2022
 */

#ifndef LINKEDQUEUE_H
#define LINKEDQUEUE_H

#include <stdbool.h> // bool

typedef int LinkedQueueItem;

typedef struct LinkedQueue LinkedQueue;

/**
 * @brief 创建一个空队列
 *
 * @return 一个指向空队列的指针
 */
LinkedQueue* LinkedQueue_Create(void);

/**
 * @brief 销毁一个队列
 *
 * @param self 一个指向待销毁队列的指针
 */
void LinkedQueue_Destroy(LinkedQueue* self);

/**
 * @brief 求队列的长度
 *
 * @param self 一个指向队列的指针
 * @return 队列长度
 */
int LinkedQueue_Size(const LinkedQueue* self);

/**
 * @brief 判断队列是否已空
 *
 * @param self 一个指向队列的指针
 * @return 如果队列已空则返回 true ，否则返回 false
 */
bool LinkedQueue_IsEmpty(const LinkedQueue* self);

/**
 * @brief 入队，将元素 data 插入到队列的尾部
 *
 * @param self 一个指向队列的指针
 * @param data 一个待入队的元素
 */
void LinkedQueue_Enqueue(LinkedQueue* self, LinkedQueueItem data);

/**
 * @brief 出队，将队列的队首元素出队
 *
 * @param self 一个指向队列的指针
 * @return 队首元素
 */
LinkedQueueItem LinkedQueue_Dequeue(LinkedQueue* self);

/**
 * @brief 查看队首元素
 *
 * @param self 一个指向队列的指针
 * @return 队首元素
 */
LinkedQueueItem LinkedQueue_Front(LinkedQueue* self);

#endif // LINKEDQUEUE_H
