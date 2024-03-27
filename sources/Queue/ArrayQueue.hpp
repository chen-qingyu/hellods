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

#include "../utility.hpp"

namespace hellods
{

template <typename T>
class ArrayQueue
{
private:
    static const int MAX_CAPACITY = 256;

    // Pointer to the data.
    T data_[MAX_CAPACITY + 1];

    // Index before the front element.
    int front_;

    // Index of the rear element.
    int rear_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty queue.
    ArrayQueue()
        : front_(-1)
        , rear_(-1)
    {
    }

    /// Create a queue based on the given initializer list.
    ArrayQueue(const std::initializer_list<T>& il)
        : ArrayQueue()
    {
        for (auto it = il.begin(); it != il.end(); it++)
        {
            enqueue(*it);
        }
    }

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const ArrayQueue& that) const
    {
        if (size() != that.size())
        {
            return false;
        }

        int i;
        for (i = front_ + 1; i < size() && i < MAX_CAPACITY; ++i)
        {
            if (data_[i] != that.data_[i])
            {
                return false;
            }
        }
        if (i == MAX_CAPACITY)
        {
            for (i = 0; i <= rear_; ++i)
            {
                if (data_[i] != that.data_[i])
                {
                    return false;
                }
            }
        }

        return true;
    }

    /// Check whether two queues are not equal.
    bool operator!=(const ArrayQueue& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the queue.
    T& front()
    {
        internal::check_empty(size());
        return data_[(front_ + 1) % MAX_CAPACITY];
    }

    /// Return the const reference to the element at the front in the queue.
    const T& front() const
    {
        internal::check_empty(size());
        return data_[(front_ + 1) % MAX_CAPACITY];
    }

    /*
     * Examination
     */

    /// Get the number of elements of the queue.
    int size() const
    {
        return (rear_ - front_ + (MAX_CAPACITY + 1)) % (MAX_CAPACITY + 1);
    }

    /// Check if the queue is empty.
    bool is_empty() const
    {
        return size() == 0;
    }

    /*
     * Manipulation
     */

    /// Enqueue, insert an element at the end of the queue.
    void enqueue(const T& element)
    {
        internal::check_full(size(), MAX_CAPACITY);

        rear_ = (rear_ + 1) % MAX_CAPACITY;
        data_[rear_] = element;
    }

    /// Dequeue, pop the head element of the queue.
    T dequeue()
    {
        internal::check_empty(size());

        front_ = (front_ + 1) % MAX_CAPACITY;
        return data_[front_];
    }

    /// Remove all of the elements from the queue.
    ArrayQueue& clear()
    {
        front_ = -1;
        rear_ = -1;

        return *this;
    }
};

} // namespace hellods

#endif // ARRAYQUEUE_HPP
