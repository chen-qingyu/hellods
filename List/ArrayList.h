/**
 * @file ArrayList.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 列表 数组实现 (Array List)
 * @version 1.0
 * @date 2022.01.28
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * 列表 list 是由 n (n >= 0) 个元素构成的有序序列： a_1, a_2, a_3 ... a_n 。
 * 列表 list 属于 List ，整数 i 表示元素下标（从0开始），元素 data 属于 ListItem 。
 */

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdbool.h> // bool

#define LIST_NOT_FOUND (-1) // a value of ListItem that indicates not found

typedef int ListItem;

typedef struct list List;

/**
 * @brief 创建一个空列表
 *
 * @return 一个指向空列表的指针
 */
List* ArrayList_Create(void);

/**
 * @brief 销毁一个列表
 *
 * @param self 一个指向待销毁列表的指针
 */
void ArrayList_Destroy(List* self);

/**
 * @brief 求列表的长度
 *
 * @param self 一个指向列表的指针
 * @return 列表长度
 */
int ArrayList_Size(const List* self);

/**
 * @brief 判断列表是否为空
 *
 * @param self 一个指向列表的指针
 * @return 如果列表为空则返回 true ，否则返回 false
 */
bool ArrayList_IsEmpty(const List* self);

/**
 * @brief 取列表的第 i 个元素
 *
 * @param self 一个指向列表的指针
 * @param i 下标 (-Size(self) <= i < Size(self))
 * @return 第 i 个元素
 */
ListItem ArrayList_At(const List* self, int i);

/**
 * @brief 求元素 data 在列表中的下标
 *
 * @param self 一个指向列表的指针
 * @param data 一个待寻找元素
 * @return 待寻找元素 data 的下标 i 或者 LIST_NOT_FOUND 代表没找到
 */
int ArrayList_Find(const List* self, ListItem data);

/**
 * @brief 在列表的下标为 i 的位置上插入一个元素 data
 *
 * @param self 一个指向列表的指针
 * @param i 下标 (0 <= i <= Size(self))
 * @param data 待插入元素
 */
void ArrayList_Insert(List* self, int i, ListItem data);

/**
 * @brief 从列表当中删除下标为 i 的元素
 *
 * @param self 一个指向列表的指针
 * @param i 下标 (0 <= i < Size(self))
 */
void ArrayList_Delete(List* self, int i);

/**
 * @brief 遍历列表
 *
 * @param self 一个指向列表的指针
 * @param p_trav 一个指向用以操作列表元素的函数的指针
 */
void ArrayList_Traverse(List* self, void (*p_trav)(ListItem data));

/**
 * @brief 就地逆置列表
 *
 * @param self 一个指向列表的指针
 */
void ArrayList_Reverse(List* self);

#endif // ARRAYLIST_H
