/**
 * @file ArrayQueue.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Queue implemented by array.
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

#ifndef ARRAYQUEUE_HPP
#define ARRAYQUEUE_HPP

#include "../Deque/ArrayDeque.hpp"

namespace hellods
{

/// Queue implemented by array.
template <typename T>
class ArrayQueue : private ArrayDeque<T>
{
public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty queue.
    ArrayQueue()
        : ArrayDeque()
    {
    }

    /// Create a queue based on the given initializer list.
    ArrayQueue(const std::initializer_list<T>& il)
        : ArrayDeque(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const ArrayQueue& that) const
    {
        return static_cast<const ArrayDeque&>(*this) == static_cast<const ArrayDeque&>(that);
    }

    /// Check whether two queues are not equal.
    bool operator!=(const ArrayQueue& that) const
    {
        return !(*this == that);
    }

    /*
     * Examination
     */

    /// Get the number of elements of the queue.
    int size() const
    {
        return ArrayDeque::size();
    }

    /// Check if the queue is empty.
    bool is_empty() const
    {
        return ArrayDeque::is_empty();
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the queue.
    T& front()
    {
        return ArrayDeque::front();
    }

    /// Return the const reference to the element at the front in the queue.
    const T& front() const
    {
        return ArrayDeque::front();
    }

    /*
     * Manipulation
     */

    /// Enqueue, insert an element at the rear of the queue.
    void enqueue(const T& element)
    {
        ArrayDeque::push_back(element);
    }

    /// Dequeue, pop the front element of the queue.
    T dequeue()
    {
        return ArrayDeque::pop_front();
    }

    /// Remove all of the elements from the queue.
    ArrayQueue& clear()
    {
        ArrayDeque::clear();

        return *this;
    }

    /*
     * Print
     */

    /// Print the queue.
    friend std::ostream& operator<<(std::ostream& os, const ArrayQueue& queue)
    {
        std::ostringstream oss;
        oss << static_cast<const ArrayDeque&>(queue);
        return os << "Queue" << oss.str().erase(0, 5);
    }
};

} // namespace hellods

#endif // ARRAYQUEUE_HPP
