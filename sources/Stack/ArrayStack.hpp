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

#include "../common/utility.hpp"

namespace hellods
{

template <typename T>
class ArrayStack
{
private:
    // Maximum capacity.
    static const int MAX_CAPACITY = 256; // TODO: dyn INT_MAX - 1: use ArrayList

    // Pointer to the data.
    T data_[MAX_CAPACITY];

    // Index of the top element.
    int top_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty stack.
    ArrayStack()
        : top_(-1)
    {
    }

    /// Create a stack based on the given initializer list.
    ArrayStack(const std::initializer_list<T>& il)
        : ArrayStack()
    {
        for (auto it = il.begin(); it != il.end(); it++)
        {
            push(*it);
        }
    }

    /*
     * Comparison
     */

    /// Check whether two stacks are equal.
    bool operator==(const ArrayStack& that) const
    {
        if (size() != that.size())
        {
            return false;
        }

        for (int i = 0; i < size(); ++i)
        {
            if (data_[i] != that.data_[i])
            {
                return false;
            }
        }

        return true;
    }

    /// Check whether two stacks are not equal.
    bool operator!=(const ArrayStack& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the top in the stack.
    T& top()
    {
        common::check_empty(size());
        return data_[top_];
    }

    /// Return the const reference to the element at the top in the stack.
    const T& top() const
    {
        common::check_empty(size());
        return data_[top_];
    }

    /*
     * Examination
     */

    /// Get the number of elements of the stack.
    int size() const
    {
        return top_ + 1;
    }

    /// Check if the stack is empty.
    bool is_empty() const
    {
        return size() == 0;
    }

    /*
     * Manipulation
     */

    /// Push, insert an element at the top of the stack.
    void push(const T& element)
    {
        common::check_full(size(), MAX_CAPACITY);

        data_[++top_] = element;
    }

    /// Pop the top element of the stack.
    T pop()
    {
        common::check_empty(size());

        return data_[top_--];
    }

    /// Remove all of the elements from the stack.
    ArrayStack& clear()
    {
        top_ = -1;

        return *this;
    }
};

} // namespace hellods

#endif // ARRAYSTACK_HPP
