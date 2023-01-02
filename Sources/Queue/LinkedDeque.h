/**
 * @file LinkedDeque.h
 * @author 青羽 (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief 双端队列 链表实现 (Linked Deque)
 * @version 1.0
 * @date 2023.01.02
 *
 * @copyright Copyright (c) 2023
 *
 * 学习数据结构用。
 * 双端队列 deque 是一个有 n(n>=0) 个元素的有穷线性表。
 * 双端队列 deque 属于 Deque ，元素 data 属于 DequeItem 。
 */

#ifndef LINKEDDEQUE_H
#define LINKEDDEQUE_H

#include <stdbool.h> // bool

typedef int DequeItem; // must be same as ListItem

typedef struct deque Deque;

/**
 * @brief 创建一个空队列
 *
 * @return 一个指向空队列的指针
 */
Deque* LinkedDeque_Create(void);

/**
 * @brief 销毁一个队列
 *
 * @param self 一个指向待销毁队列的指针
 */
void LinkedDeque_Destroy(Deque* self);

/**
 * @brief 求队列的长度
 *
 * @param self 一个指向队列的指针
 * @return 队列长度
 */
int LinkedDeque_Size(const Deque* self);

/**
 * @brief 判断队列是否已空
 *
 * @param self 一个指向队列的指针
 * @return 如果队列已空则返回 true ，否则返回 false
 */
bool LinkedDeque_IsEmpty(const Deque* self);

/**
 * @brief 入队，将元素 data 插入到队列的首部
 *
 * @param self 一个指向队列的指针
 * @param data 一个待入队的元素
 */
void LinkedDeque_PushFront(Deque* self, DequeItem data);

/**
 * @brief 入队，将元素 data 插入到队列的尾部
 *
 * @param self 一个指向队列的指针
 * @param data 一个待入队的元素
 */
void LinkedDeque_PushBack(Deque* self, DequeItem data);

/**
 * @brief 出队，将队列的队首元素出队
 *
 * @param self 一个指向队列的指针
 * @return 队首元素
 */
DequeItem LinkedDeque_PopFront(Deque* self);

/**
 * @brief 出队，将队列的队尾元素出队
 *
 * @param self 一个指向队列的指针
 * @return 队尾元素
 */
DequeItem LinkedDeque_PopBack(Deque* self);

#endif // LINKEDDEQUE_H
