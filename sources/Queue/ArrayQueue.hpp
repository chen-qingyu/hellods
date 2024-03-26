/**
 * @file ArrayQueue.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Queue implemented by array.
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

#ifndef ARRAYQUEUE_HPP
#define ARRAYQUEUE_HPP

#include <stdbool.h> // bool

/// Array Queue Item.
typedef int ArrayQueueItem;

/// Array Queue.
typedef struct ArrayQueue ArrayQueue;

/**
 * @brief 创建一个空队列
 *
 * @return 一个指向空队列的指针
 */
ArrayQueue* ArrayQueue_Create(void);

/**
 * @brief 销毁一个队列
 *
 * @param self 一个指向待销毁队列的指针
 */
void ArrayQueue_Destroy(ArrayQueue* self);

/**
 * @brief 求队列的长度
 *
 * @param self 一个指向队列的指针
 * @return 队列长度
 */
int ArrayQueue_Size(const ArrayQueue* self);

/**
 * @brief 判断队列是否已空
 *
 * @param self 一个指向队列的指针
 * @return 如果队列已空则返回 true ，否则返回 false
 */
bool ArrayQueue_IsEmpty(const ArrayQueue* self);

/**
 * @brief 入队，将元素 data 插入到队列的尾部
 *
 * @param self 一个指向队列的指针
 * @param data 一个待入队的元素
 */
void ArrayQueue_Enqueue(ArrayQueue* self, ArrayQueueItem data);

/**
 * @brief 出队，将队列的队首元素出队
 *
 * @param self 一个指向队列的指针
 * @return 队首元素
 */
ArrayQueueItem ArrayQueue_Dequeue(ArrayQueue* self);

/**
 * @brief 查看队首元素
 *
 * @param self 一个指向队列的指针
 * @return 队首元素
 */
ArrayQueueItem ArrayQueue_Front(ArrayQueue* self);

/**
 * @brief 清空队列的内容
 *
 * @param self 一个指向队列的指针
 */
void ArrayQueue_Clear(ArrayQueue* self);

#endif // ARRAYQUEUE_HPP
