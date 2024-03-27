/**
 * @file LinkedStack.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Stack implemented by doubly linked list.
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

#ifndef LINKEDSTACK_HPP
#define LINKEDSTACK_HPP

#include "../List/LinkedList.hpp"

namespace hellods
{

/// Stack implemented by doubly linked list.
template <typename T>
class LinkedStack
{
private:
    // A doubly linked list.
    LinkedList<T> dlist_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty stack.
    LinkedStack()
        : dlist_()
    {
    }

    /// Create a stack based on the given initializer list.
    LinkedStack(const std::initializer_list<T>& il)
        : dlist_(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two stacks are equal.
    bool operator==(const LinkedStack& that) const
    {
        return dlist_ == that.dlist_;
    }

    /// Check whether two stacks are not equal.
    bool operator!=(const LinkedStack& that) const
    {
        return dlist_ != that.dlist_;
    }

    /*
     * Access
     */

    /// Return the reference to the element at the top in the stack.
    T& top()
    {
        common::check_empty(size());
        return dlist_.trailer_->pred_->data_;
    }

    /// Return the const reference to the element at the top in the stack.
    const T& top() const
    {
        common::check_empty(size());
        return dlist_.trailer_->pred_->data_;
    }

    /*
     * Examination
     */

    /// Get the number of elements of the stack.
    int size() const
    {
        return dlist_.size();
    }

    /// Check if the stack is empty.
    bool is_empty() const
    {
        return dlist_.is_empty();
    }

    /*
     * Manipulation
     */

    /// Push, insert an element at the top of the stack.
    void push(const T& element)
    {
        dlist_.insert(dlist_.size(), element);
    }

    /// Pop the top element of the stack.
    T pop()
    {
        return dlist_.remove(dlist_.size() - 1);
    }

    /// Remove all of the elements from the stack.
    LinkedStack& clear()
    {
        dlist_.clear();

        return *this;
    }
};

} // namespace hellods

#endif // LINKEDSTACK_HPP
