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

#include "../common/Container.hpp"
#include "../common/utility.hpp"

namespace hellods
{

/// Queue implemented by array.
template <typename T>
class ArrayQueue : public common::Container
{
private:
    // Index of front in ring buffer. data[front] is the first element, except size == 0.
    int front_;

    // Available capacity.
    int capacity_;

    // Pointer to ring buffer.
    T* data_;

    // Convert logic index to ring buffer physical index.
    int access(int logic_index) const
    {
        return (front_ + logic_index) % capacity_;
    }

    // Expand capacity safely for ring buffer. Require size == capacity.
    void expand_capacity()
    {
        capacity_ = (capacity_ < MAX_CAPACITY / 2) ? capacity_ * 2 : MAX_CAPACITY; // double the capacity until MAX_CAPACITY
        T* new_data = new T[capacity_];
        int j = 0;
        for (int i = front_; i < size_; ++i)
        {
            new_data[j++] = data_[i];
        }
        for (int i = 0; i < front_; ++i)
        {
            new_data[j++] = data_[i];
        }

        delete[] data_;
        data_ = new_data;
        front_ = 0;
    }

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty queue.
    ArrayQueue()
        : common::Container(0)
        , front_(0)
        , capacity_(INIT_CAPACITY)
        , data_(new T[capacity_])
    {
    }

    /// Create a queue based on the given initializer list.
    ArrayQueue(const std::initializer_list<T>& il)
        : common::Container(int(il.size()))
        , front_(0)
        , capacity_(size_ > INIT_CAPACITY ? size_ : INIT_CAPACITY)
        , data_(new T[capacity_])
    {
        std::copy(il.begin(), il.end(), data_);
    }

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const ArrayQueue& that) const
    {
        if (size_ != that.size_)
        {
            return false;
        }

        for (int i = access(0), j = that.access(0), cnt = 0; cnt < size_; i = access(i + 1), j = that.access(j + 1), ++cnt)
        {
            if (data_[i] != that.data_[j])
            {
                return false;
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
        common::check_empty(size_);
        return data_[front_];
    }

    /// Return the const reference to the element at the front in the queue.
    const T& front() const
    {
        common::check_empty(size_);
        return data_[front_];
    }

    /*
     * Manipulation
     */

    /// Enqueue, insert an element at the rear of the queue.
    void enqueue(const T& element)
    {
        common::check_full(size_, MAX_CAPACITY);

        if (size_ == capacity_)
        {
            expand_capacity();
        }

        data_[(front_ + size_) % capacity_] = element;
        size_++;
    }

    /// Dequeue, pop the front element of the queue.
    T dequeue()
    {
        common::check_empty(size_);

        T data = std::move(data_[front_]);
        front_ = (front_ + 1) % capacity_;
        size_--;

        return data;
    }

    /// Remove all of the elements from the queue.
    ArrayQueue& clear()
    {
        size_ = 0;
        front_ = 0;

        return *this;
    }
};

} // namespace hellods

#endif // ARRAYQUEUE_HPP
