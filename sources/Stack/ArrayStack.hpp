/**
 * @file ArrayStack.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Stack implemented by array.
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

#ifndef ARRAYSTACK_HPP
#define ARRAYSTACK_HPP

#include <stdbool.h> // bool

/// Array Stack Item.
typedef int ArrayStackItem;

/// Array Stack.
typedef struct ArrayStack ArrayStack;

/**
 * @brief 创建一个空栈
 *
 * @return 一个指向空栈的指针
 */
ArrayStack* ArrayStack_Create(void);

/**
 * @brief 销毁一个栈
 *
 * @param self 一个指向待销毁栈的指针
 */
void ArrayStack_Destroy(ArrayStack* self);

/**
 * @brief 求栈的长度
 *
 * @param self 一个指向栈的指针
 * @return 栈长度
 */
int ArrayStack_Size(const ArrayStack* self);

/**
 * @brief 判断栈是否已空
 *
 * @param self 一个指向栈的指针
 * @return 如果栈已空则返回 true ，否则返回 false
 */
bool ArrayStack_IsEmpty(const ArrayStack* self);

/**
 * @brief 入栈，将元素 data 压入到栈的顶部
 *
 * @param self 一个指向栈的指针
 * @param data 一个待入栈的元素
 */
void ArrayStack_Push(ArrayStack* self, ArrayStackItem data);

/**
 * @brief 出栈，将栈的顶部的元素弹出来
 *
 * @param self 一个指向栈的指针
 * @return 栈顶元素
 */
ArrayStackItem ArrayStack_Pop(ArrayStack* self);

/**
 * @brief 检查栈的顶部元素，不改变栈
 *
 * @param self 一个指向栈的指针
 * @return 栈顶元素
 */
ArrayStackItem ArrayStack_Top(const ArrayStack* self);

/**
 * @brief 清空栈的内容
 *
 * @param self 一个指向栈的指针
 */
void ArrayStack_Clear(ArrayStack* self);

#endif // ARRAYSTACK_HPP
