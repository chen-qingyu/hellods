/**
 * @file LinkedQueue.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Queue implemented by doubly linked list.
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

#ifndef LINKEDQUEUE_HPP
#define LINKEDQUEUE_HPP

#include "../List/DoublyLinkedList.hpp"

namespace hellods
{

/// Queue implemented by doubly linked list.
template <typename T>
class LinkedQueue
{
private:
    // A doubly linked list.
    DoublyLinkedList<T> dlist_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty queue.
    LinkedQueue()
        : dlist_()
    {
    }

    /// Create a queue based on the given initializer list.
    LinkedQueue(const std::initializer_list<T>& il)
        : dlist_(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const LinkedQueue& that) const
    {
        return dlist_ == that.dlist_;
    }

    /// Check whether two queues are not equal.
    bool operator!=(const LinkedQueue& that) const
    {
        return dlist_ != that.dlist_;
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the queue.
    T& front()
    {
        common::check_empty(size());
        return dlist_.header_->succ_->data_;
    }

    /// Return the const reference to the element at the front in the queue.
    const T& front() const
    {
        common::check_empty(size());
        return dlist_.header_->succ_->data_;
    }

    /*
     * Examination
     */

    /// Get the number of elements of the queue.
    int size() const
    {
        return dlist_.size();
    }

    /// Check if the queue is empty.
    bool is_empty() const
    {
        return dlist_.is_empty();
    }

    /*
     * Manipulation
     */

    /// Enqueue, insert an element at the end of the queue.
    void enqueue(const T& element)
    {
        dlist_.insert(size(), element);
    }

    /// Dequeue, pop the head element of the queue.
    T dequeue()
    {
        return dlist_.remove(0);
    }

    /// Remove all of the elements from the queue.
    LinkedQueue& clear()
    {
        dlist_.clear();

        return *this;
    }
};

} // namespace hellods

#endif // LINKEDQUEUE_HPP
