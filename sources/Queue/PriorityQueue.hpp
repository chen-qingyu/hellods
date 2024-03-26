/**
 * @file PriorityQueue.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Priority queue implemented by binary heap. This is max-heap.
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

#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <stdbool.h> // bool

/// Max Heap Item.
typedef int MaxHeapItem;

/// Max Heap.
typedef struct MaxHeap MaxHeap;

/**
 * @brief 创建一个空堆
 *
 * @return MaxHeap* 一个指向空堆的指针
 */
MaxHeap* MaxHeap_Create(void);

/**
 * @brief 销毁一个堆
 *
 * @param self 一个指向待销毁堆的指针
 */
void MaxHeap_Destroy(MaxHeap* self);

/**
 * @brief 求堆的元素个数
 *
 * @param self 一个指向堆的指针
 * @return 堆的元素个数
 */
int MaxHeap_Size(const MaxHeap* self);

/**
 * @brief 判断堆是否已空
 *
 * @param self 一个指向堆的指针
 * @return 如果堆已空则返回 true ，否则返回 false
 */
bool MaxHeap_IsEmpty(const MaxHeap* self);

/**
 * @brief 在堆中插入一个元素 data
 *
 * @param self 一个指向堆的指针
 * @param data 一个待插入元素
 */
void MaxHeap_Push(MaxHeap* self, MaxHeapItem data);

/**
 * @brief  在堆中删除堆顶元素
 *
 * @param self 一个指向堆的指针
 * @return 堆顶元素
 */
MaxHeapItem MaxHeap_Pop(MaxHeap* self);

/**
 * @brief 查看堆的堆顶元素
 *
 * @param self 一个指向堆的指针
 * @return 堆顶元素
 */
MaxHeapItem MaxHeap_Top(MaxHeap* self);

/**
 * @brief 清空堆的内容
 *
 * @param self 一个指向堆的指针
 */
void MaxHeap_Clear(MaxHeap* self);

#endif // PRIORITYQUEUE_HPP
