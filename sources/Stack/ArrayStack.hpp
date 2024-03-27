/**
 * @file ArrayStack.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Stack implemented by array list.
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

#include "../List/ArrayList.hpp"

namespace hellods
{

/// Stack implemented by array list.
template <typename T>
class ArrayStack
{
private:
    // An array list.
    ArrayList<T> alist_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty stack.
    ArrayStack()
        : alist_()
    {
    }

    /// Create a stack based on the given initializer list.
    ArrayStack(const std::initializer_list<T>& il)
        : alist_(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two stacks are equal.
    bool operator==(const ArrayStack& that) const
    {
        return alist_ == that.alist_;
    }

    /// Check whether two stacks are not equal.
    bool operator!=(const ArrayStack& that) const
    {
        return alist_ != that.alist_;
    }

    /*
     * Access
     */

    /// Return the reference to the element at the top in the stack.
    T& top()
    {
        common::check_empty(size());
        return alist_[size() - 1];
    }

    /// Return the const reference to the element at the top in the stack.
    const T& top() const
    {
        common::check_empty(size());
        return alist_[size() - 1];
    }

    /*
     * Examination
     */

    /// Get the number of elements of the stack.
    int size() const
    {
        return alist_.size();
    }

    /// Check if the stack is empty.
    bool is_empty() const
    {
        return alist_.is_empty();
    }

    /*
     * Manipulation
     */

    /// Push, insert an element at the top of the stack.
    void push(const T& element)
    {
        alist_.insert(size(), element);
    }

    /// Pop the top element of the stack.
    T pop()
    {
        return alist_.remove(size() - 1);
    }

    /// Remove all of the elements from the stack.
    ArrayStack& clear()
    {
        alist_.clear();

        return *this;
    }
};

} // namespace hellods

#endif // ARRAYSTACK_HPP
