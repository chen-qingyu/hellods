/**
 * @file DoublyLinkedList.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief List implemented by double linked list.
 * @date 2023.01.02
 *
 * @copyright Copyright (C) 2023
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

#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include <stdbool.h> // bool

/// Doubly Linked List Item.
typedef int DoublyLinkedListItem;

/// Doubly Linked List.
typedef struct DoublyLinkedList DoublyLinkedList;

/**
 * @brief 创建一个空列表
 *
 * @return 一个指向空列表的指针
 */
DoublyLinkedList* DoublyLinkedList_Create(void);

/**
 * @brief 销毁一个列表
 *
 * @param self 一个指向待销毁列表的指针
 */
void DoublyLinkedList_Destroy(DoublyLinkedList* self);

/**
 * @brief 求列表的长度
 *
 * @param self 一个指向列表的指针
 * @return 列表长度
 */
int DoublyLinkedList_Size(const DoublyLinkedList* self);

/**
 * @brief 判断列表是否为空
 *
 * @param self 一个指向列表的指针
 * @return 如果列表为空则返回 true ，否则返回 false
 */
bool DoublyLinkedList_IsEmpty(const DoublyLinkedList* self);

/**
 * @brief 取列表的第 index 个元素
 *
 * @param self 一个指向列表的指针
 * @param index 下标 (-Size(self) <= index < Size(self))
 * @return 第 index 个元素
 */
DoublyLinkedListItem DoublyLinkedList_At(const DoublyLinkedList* self, int index);

/**
 * @brief 求元素 data 在列表中的下标
 *
 * @param self 一个指向列表的指针
 * @param data 一个待寻找元素
 * @return 待寻找元素 data 的下标 index 或者 -1 代表没找到
 */
int DoublyLinkedList_Find(const DoublyLinkedList* self, DoublyLinkedListItem data);

/**
 * @brief 在列表的下标为 index 的位置上插入一个元素 data
 *
 * @param self 一个指向列表的指针
 * @param index 下标 (-Size(self) <= index <= Size(self))
 * @param data 待插入元素
 */
void DoublyLinkedList_Insert(DoublyLinkedList* self, int index, DoublyLinkedListItem data);

/**
 * @brief 从列表当中删除下标为 index 的元素
 *
 * @param self 一个指向列表的指针
 * @param index 下标 (-Size(self) <= index < Size(self))
 * @return 删除的元素
 */
DoublyLinkedListItem DoublyLinkedList_Remove(DoublyLinkedList* self, int index);

/**
 * @brief 遍历列表
 *
 * @param self 一个指向列表的指针
 * @param p_trav 一个指向用以操作列表元素的函数的指针
 */
void DoublyLinkedList_Traverse(DoublyLinkedList* self, void (*p_trav)(DoublyLinkedListItem data));

/**
 * @brief 就地逆置列表
 *
 * @param self 一个指向列表的指针
 */
void DoublyLinkedList_Reverse(DoublyLinkedList* self);

/**
 * @brief 清空列表的内容
 *
 * @param self 一个指向列表的指针
 */
void DoublyLinkedList_Clear(DoublyLinkedList* self);

#endif // DOUBLYLINKEDLIST_HPP
