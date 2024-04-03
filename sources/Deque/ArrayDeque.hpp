/**
 * @file ArrayDeque.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief Deque implemented by array.
 * @date 2024.03.29
 *
 * @copyright Copyright (C) 2024
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

#ifndef ARRAYDEQUE_HPP
#define ARRAYDEQUE_HPP

#include "../common/Container.hpp"
#include "../common/utility.hpp"

namespace hellods
{

/// Deque implemented by array.
template <typename T>
class ArrayDeque : public common::Container
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

    /// Create an empty deque.
    ArrayDeque()
        : common::Container(0)
        , front_(0)
        , capacity_(INIT_CAPACITY)
        , data_(new T[capacity_])
    {
    }

    /// Create a deque based on the given initializer list.
    ArrayDeque(const std::initializer_list<T>& il)
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

    /// Check whether two deques are equal.
    bool operator==(const ArrayDeque& that) const
    {
        if (size_ != that.size_)
        {
            return false;
        }

        for (int logic = 0; logic < size_; ++logic)
        {
            if (data_[access(logic)] != that.data_[that.access(logic)])
            {
                return false;
            }
        }

        return true;
    }

    /// Check whether two deques are not equal.
    bool operator!=(const ArrayDeque& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the deque.
    T& front()
    {
        common::check_empty(size_);
        return data_[front_];
    }

    /// Return the const reference to the element at the front in the deque.
    const T& front() const
    {
        common::check_empty(size_);
        return data_[front_];
    }

    /// Return the reference to the element at the back in the deque.
    T& back()
    {
        common::check_empty(size_);
        return data_[access(size_ - 1)];
    }

    /// Return the const reference to the element at the back in the deque.
    const T& back() const
    {
        common::check_empty(size_);
        return data_[access(size_ - 1)];
    }

    /*
     * Manipulation
     */

    /// Push front, insert an element at the front of the deque.
    void push_front(const T& element)
    {
        common::check_full(size_, MAX_CAPACITY);

        if (size_ == capacity_)
        {
            expand_capacity();
        }

        front_ = (front_ + capacity_ - 1) % capacity_;
        data_[front_] = element;
        size_++;
    }

    /// Push back, insert an element at the back of the deque.
    void push_back(const T& element)
    {
        common::check_full(size_, MAX_CAPACITY);

        if (size_ == capacity_)
        {
            expand_capacity();
        }

        data_[access(size_)] = element;
        size_++;
    }

    /// Pop front, pop the front element of the deque.
    T pop_front()
    {
        common::check_empty(size_);

        T data = std::move(data_[front_]);
        front_ = (front_ + 1) % capacity_;
        size_--;

        return data;
    }

    /// Pop back, pop the back element of the deque.
    T pop_back()
    {
        common::check_empty(size_);

        T data = std::move(data_[access(size_ - 1)]);
        size_--;

        return data;
    }

    /// Remove all of the elements from the deque.
    ArrayDeque& clear()
    {
        // If the elements themselves are pointers, the pointed-to memory is not touched in any way.
        // Managing the pointer is the user's responsibility.
        size_ = 0;
        front_ = 0;

        return *this;
    }

    /// Print the deque.
    friend std::ostream& operator<<(std::ostream& os, const ArrayDeque& deque)
    {
        os << "<";
        for (int i = 0; i < deque.size_; i++)
        {
            os << ((i == 0) ? "" : ", ") << deque.data_[deque.access(i)];
        }
        return os << ">";
    }
};

} // namespace hellods

#endif // ARRAYDEQUE_HPP
