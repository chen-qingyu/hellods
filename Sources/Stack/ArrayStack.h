/**
 * @file ArrayStack.h
 * @author 青羽 (chen_qingyu@qq.com)
 * @brief 栈 数组实现 (Array Stack)
 * @version 1.0
 * @date 2022.01.28
 *
 * @copyright Copyright (c) 2022
 *
 * 学习数据结构用。
 * 栈 stack 是一个有 n(n>=0) 个元素的有穷线性表。
 * 栈 stack 属于 Stack ，元素 data 属于 StackItem 。
 */

#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <stdbool.h> // bool

typedef int StackItem;

typedef struct stack Stack;

/**
 * @brief 创建一个空栈
 *
 * @return 一个指向空栈的指针
 */
Stack* ArrayStack_Create(void);

/**
 * @brief 销毁一个栈
 *
 * @param self 一个指向待销毁栈的指针
 */
void ArrayStack_Destroy(Stack* self);

/**
 * @brief 求栈的长度
 *
 * @param self 一个指向栈的指针
 * @return 栈长度
 */
int ArrayStack_Size(const Stack* self);

/**
 * @brief 判断栈是否已空
 *
 * @param self 一个指向栈的指针
 * @return 如果栈已空则返回 true ，否则返回 false
 */
bool ArrayStack_IsEmpty(const Stack* self);

/**
 * @brief 入栈，将元素 data 压入到栈的顶部
 *
 * @param self 一个指向栈的指针
 * @param data 一个待入栈的元素
 */
void ArrayStack_Push(Stack* self, StackItem data);

/**
 * @brief 出栈，将栈的顶部的元素弹出来
 *
 * @param self 一个指向栈的指针
 * @return 栈顶元素
 */
StackItem ArrayStack_Pop(Stack* self);

/**
 * @brief 检查栈的顶部元素，不改变栈
 *
 * @param self 一个指向栈的指针
 * @return 栈顶元素
 */
StackItem ArrayStack_Top(const Stack* self);

#endif // ARRAYSTACK_H
