/**
 * @file LinkedQueue.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Queue implemented by single linked list.
 * @date 2022.01.28
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

#ifndef LINKEDQUEUE_HPP
#define LINKEDQUEUE_HPP

#include <stdbool.h> // bool

/// Linked Queue Item.
typedef int LinkedQueueItem;

/// Linked Queue.
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

/**
 * @brief 清空队列的内容
 *
 * @param self 一个指向队列的指针
 */
void LinkedQueue_Clear(LinkedQueue* self);

#endif // LINKEDQUEUE_HPP
