/**
 * @file DoublyLinkedList.h
 * @author 青羽 (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief 列表 双链表实现 (Doubly Linked List)
 * @version 1.0
 * @date 2023.01.02
 *
 * @copyright Copyright (c) 2023
 */

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <stdbool.h> // bool

typedef int DoublyLinkedListItem;

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

#endif // DOUBLYLINKEDLIST_H
