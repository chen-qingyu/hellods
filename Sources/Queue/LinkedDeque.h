/**
 * @file LinkedDeque.h
 * @author 青羽 (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief 双端队列 双链表实现 (Linked Deque)
 * @version 1.0
 * @date 2023.01.02
 *
 * @copyright Copyright (c) 2023
 */

#ifndef LINKEDDEQUE_H
#define LINKEDDEQUE_H

#include <stdbool.h> // bool

typedef int LinkedDequeItem; // must be same as DoublyLinkedListItem

typedef struct LinkedDeque LinkedDeque;

/**
 * @brief 创建一个空队列
 *
 * @return 一个指向空队列的指针
 */
LinkedDeque* LinkedDeque_Create(void);

/**
 * @brief 销毁一个队列
 *
 * @param self 一个指向待销毁队列的指针
 */
void LinkedDeque_Destroy(LinkedDeque* self);

/**
 * @brief 求队列的长度
 *
 * @param self 一个指向队列的指针
 * @return 队列长度
 */
int LinkedDeque_Size(const LinkedDeque* self);

/**
 * @brief 判断队列是否已空
 *
 * @param self 一个指向队列的指针
 * @return 如果队列已空则返回 true ，否则返回 false
 */
bool LinkedDeque_IsEmpty(const LinkedDeque* self);

/**
 * @brief 入队，将元素 data 插入到队列的首部
 *
 * @param self 一个指向队列的指针
 * @param data 一个待入队的元素
 */
void LinkedDeque_PushFront(LinkedDeque* self, LinkedDequeItem data);

/**
 * @brief 入队，将元素 data 插入到队列的尾部
 *
 * @param self 一个指向队列的指针
 * @param data 一个待入队的元素
 */
void LinkedDeque_PushBack(LinkedDeque* self, LinkedDequeItem data);

/**
 * @brief 出队，将队列的队首元素出队
 *
 * @param self 一个指向队列的指针
 * @return 队首元素
 */
LinkedDequeItem LinkedDeque_PopFront(LinkedDeque* self);

/**
 * @brief 出队，将队列的队尾元素出队
 *
 * @param self 一个指向队列的指针
 * @return 队尾元素
 */
LinkedDequeItem LinkedDeque_PopBack(LinkedDeque* self);

/**
 * @brief 查看队首元素
 *
 * @param self 一个指向队列的指针
 * @return 队首元素
 */
LinkedDequeItem LinkedDeque_Front(LinkedDeque* self);

/**
 * @brief 查看队尾元素
 *
 * @param self 一个指向队列的指针
 * @return 队尾元素
 */
LinkedDequeItem LinkedDeque_Back(LinkedDeque* self);

/**
 * @brief 清空队列的内容
 *
 * @param self 一个指向队列的指针
 */
void LinkedDeque_Clear(LinkedDeque* self);

#endif // LINKEDDEQUE_H
