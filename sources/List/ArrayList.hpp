/**
 * @file ArrayList.hpp
 * @author Qingyu Chen (chen_qingyu@qq.com, https://chen-qingyu.github.io/)
 * @brief List implemented by array.
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

#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include "../common/Container.hpp"
#include "../common/utility.hpp"

namespace hellods
{

/// List implemented by array.
template <typename T>
class ArrayList : public common::Container
{
    template <typename _>
    friend class ArrayStack;

private:
    // Available capacity.
    int capacity_;

    // Pointer to the data.
    T* data_;

    // Expand capacity safely.
    void expand_capacity()
    {
        capacity_ = (capacity_ < MAX_CAPACITY / 2) ? capacity_ * 2 : MAX_CAPACITY; // double the capacity until MAX_CAPACITY
        T* new_data = new T[capacity_];
        std::copy(data_, data_ + size_, new_data);
        delete[] data_;
        data_ = new_data;
    }

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty list.
    ArrayList()
        : common::Container(0)
        , capacity_(INIT_CAPACITY)
        , data_(new T[capacity_])
    {
    }

    /// Create a list based on the given initializer list.
    ArrayList(const std::initializer_list<T>& il)
        : common::Container(int(il.size()))
        , capacity_(size_ > INIT_CAPACITY ? size_ : INIT_CAPACITY)
        , data_(new T[capacity_])
    {
        std::copy(il.begin(), il.end(), data_);
    }

    /// Destroy the list object.
    ~ArrayList()
    {
        delete[] data_;
    }

    /*
     * Comparison
     */

    /// Check whether two lists are equal.
    bool operator==(const ArrayList& that) const
    {
        if (size_ != that.size_)
        {
            return false;
        }

        for (int i = 0; i < size_; ++i)
        {
            if (data_[i] != that.data_[i])
            {
                return false;
            }
        }

        return true;
    }

    /// Check whether two lists are not equal.
    bool operator!=(const ArrayList& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the specified position in the list.
    T& operator[](int index)
    {
        common::check_bounds(index, 0, size_);
        return data_[index];
    }

    /// Return the const reference to element at the specified position in the list.
    const T& operator[](int index) const
    {
        common::check_bounds(index, 0, size_);
        return data_[index];
    }

    /*
     * Examination
     */

    /// Return the index of the first occurrence of the specified element, or -1 if the list does not contains the element.
    int find(const T& element) const
    {
        auto it = std::find(data_, data_ + size_, element);
        return it == data_ + size_ ? -1 : it - data_;
    }

    /*
     * Manipulation
     */

    /// Insert the specified element at the specified position in the list.
    void insert(int index, const T& element)
    {
        // check
        common::check_full(size_, MAX_CAPACITY);
        common::check_bounds(index, 0, size_ + 1);

        // expand capacity if need
        if (size_ == capacity_)
        {
            expand_capacity();
        }

        // shift
        for (int i = size_; i > index; --i)
        {
            data_[i] = data_[i - 1];
        }

        // insert
        data_[index] = element; // copy assignment on T

        // resize
        ++size_;
    }

    /// Remove and return the element at the specified position in the list.
    T remove(int index)
    {
        // check
        common::check_empty(size_);
        common::check_bounds(index, 0, size_);

        // move element
        T element = std::move(data_[index]);

        // shift
        for (int i = index + 1; i < size_; ++i)
        {
            data_[i - 1] = data_[i];
        }

        // resize
        --size_;

        // return element
        return element;
    }

    /// Perform the given action for each element of the list.
    template <typename F>
    ArrayList& map(const F& action)
    {
        for (int i = 0; i < size_; ++i)
        {
            action(data_[i]);
        }

        return *this;
    }

    /// Reverse the list in place.
    ArrayList& reverse()
    {
        for (int i = 0, j = size_ - 1; i < j; ++i, --j)
        {
            common::swap(data_[i], data_[j]);
        }

        return *this;
    }

    /// Remove all of the elements from the list.
    ArrayList& clear()
    {
        // If the elements themselves are pointers, the pointed-to memory is not touched in any way.
        // Managing the pointer is the user's responsibility.
        size_ = 0;

        return *this;
    }
};

} // namespace hellods

#endif // ARRAYLIST_HPP
