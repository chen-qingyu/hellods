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

#include "../List/LinkedList.hpp"

namespace hellods
{

/// Deque implemented by double linked list.
template <typename T>
class LinkedDeque : private LinkedList<T>
{
public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty deque.
    LinkedDeque()
        : LinkedList()
    {
    }

    /// Create a deque based on the given initializer list.
    LinkedDeque(const std::initializer_list<T>& il)
        : LinkedList(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const LinkedDeque& that) const
    {
        return static_cast<const LinkedList&>(*this) == static_cast<const LinkedList&>(that);
    }

    /// Check whether two queues are not equal.
    bool operator!=(const LinkedDeque& that) const
    {
        return !(*this == that);
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the list.
    Iterator begin() const
    {
        return LinkedList::begin();
    }

    /// Return an iterator to the element following the last element of the list.
    Iterator end() const
    {
        return LinkedList::end();
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the deque.
    T& front()
    {
        common::check_empty(size());
        return header_->succ_->data_;
    }

    /// Return the const reference to the element at the front in the deque.
    const T& front() const
    {
        return const_cast<LinkedDeque&>(*this).front();
    }

    /// Return the reference to the element at the back in the deque.
    T& back()
    {
        common::check_empty(size());
        return trailer_->pred_->data_;
    }

    /// Return the const reference to the element at the back in the deque.
    const T& back() const
    {
        return const_cast<LinkedDeque&>(*this).back();
    }

    /*
     * Examination
     */

    /// Get the number of elements of the deque.
    int size() const
    {
        return LinkedList::size();
    }

    /// Check if the deque is empty.
    bool is_empty() const
    {
        return LinkedList::is_empty();
    }

    /*
     * Manipulation
     */

    /// Push front, insert an element at the front of the deque.
    void push_front(const T& element)
    {
        common::check_full(size_, MAX_CAPACITY);
        LinkedList::insert_node(header_->succ_, element);
    }

    /// Push back, insert an element at the back of the deque.
    void push_back(const T& element)
    {
        common::check_full(size_, MAX_CAPACITY);
        LinkedList::insert_node(trailer_, element);
    }

    /// Pop front, pop the front element of the deque.
    T pop_front()
    {
        common::check_empty(size_);
        return LinkedList::remove_node(header_->succ_);
    }

    /// Pop back, pop the back element of the deque.
    T pop_back()
    {
        common::check_empty(size_);
        return LinkedList::remove_node(trailer_->pred_);
    }

    /// Remove all of the elements from the deque.
    void clear()
    {
        LinkedList::clear();
    }

    /*
     * Print
     */

    /// Print the deque.
    friend std::ostream& operator<<(std::ostream& os, const LinkedDeque& deque)
    {
        return common::print(os, deque, "Deque");
    }
};

} // namespace hellods

#endif // LINKEDDEQUE_HPP
