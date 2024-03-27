/**
 * @file LinkedDeque.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Deque implemented by double linked list.
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

#ifndef LINKEDDEQUE_HPP
#define LINKEDDEQUE_HPP

#include "../common/utility.hpp"

#include "../List/DoublyLinkedList.hpp"

namespace hellods
{

/// Deque implemented by double linked list.
template <typename T>
class LinkedDeque
{
private:
    // A doubly linked list.
    DoublyLinkedList<T> dlist_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty deque.
    LinkedDeque()
        : dlist_()
    {
    }

    /// Create a deque based on the given initializer list.
    LinkedDeque(const std::initializer_list<T>& il)
        : dlist_(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const LinkedDeque& that) const
    {
        return dlist_ == that.dlist_;
    }

    /// Check whether two queues are not equal.
    bool operator!=(const LinkedDeque& that) const
    {
        return dlist_ != that.dlist_;
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the deque.
    T& front()
    {
        common::check_empty(dlist_.size());
        return dlist_[0];
    }

    /// Return the const reference to the element at the front in the deque.
    const T& front() const
    {
        common::check_empty(dlist_.size());
        return dlist_[0];
    }

    /// Return the reference to the element at the back in the deque.
    T& back()
    {
        common::check_empty(dlist_.size());
        return dlist_[dlist_.size() - 1];
    }

    /// Return the const reference to the element at the back in the deque.
    const T& back() const
    {
        common::check_empty(dlist_.size());
        return dlist_[dlist_.size() - 1];
    }

    /*
     * Examination
     */

    /// Get the number of elements of the deque.
    int size() const
    {
        return dlist_.size();
    }

    /// Check if the deque is empty.
    bool is_empty() const
    {
        return dlist_.is_empty();
    }

    /*
     * Manipulation
     */

    /// Push front, insert an element at the front of the deque.
    void push_front(const T& element)
    {
        dlist_.insert(0, element);
    }

    /// Push back, insert an element at the back of the deque.
    void push_back(const T& element)
    {
        dlist_.insert(dlist_.size(), element);
    }

    /// Pop front, pop the front element of the deque.
    T pop_front()
    {
        return dlist_.remove(0);
    }

    /// Pop back, pop the back element of the deque.
    T pop_back()
    {
        return dlist_.remove(dlist_.size() - 1);
    }

    /// Remove all of the elements from the deque.
    LinkedDeque& clear()
    {
        dlist_.clear();

        return *this;
    }
};

} // namespace hellods

#endif // LINKEDDEQUE_HPP
