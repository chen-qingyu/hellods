/**
 * @file ArrayDeque.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Deque implemented by array.
 * @date 2024.03.29
 */

#ifndef ARRAYDEQUE_HPP
#define ARRAYDEQUE_HPP

#include "../detail.hpp"

namespace hellods
{

/// Deque implemented by array.
template <typename T>
class ArrayDeque : public detail::Container
{
public:
    /// Deque iterator class.
    class Iterator
    {
        friend class ArrayDeque;

    protected:
        // Current data pointer.
        T* current_;

        // Begin of the ring buffer.
        T* buffer_begin_;

        // End of the ring buffer.
        T* buffer_end_;

        // Create an iterator that point to the current data of list.
        Iterator(T* current, T* begin, T* end)
            : current_(current)
            , buffer_begin_(begin)
            , buffer_end_(end)
        {
        }

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = int;
        using pointer = value_type*;
        using reference = value_type&;

        /// Dereference.
        T& operator*() const
        {
            return *current_;
        }

        /// Get current pointer.
        T* operator->() const
        {
            return current_;
        }

        /// Check if two iterators are same.
        bool operator==(const Iterator& that) const
        {
            return current_ == that.current_;
        }

        /// Check if two iterators are different.
        bool operator!=(const Iterator& that) const
        {
            return !(current_ == that.current_);
        }

        /// Increment the iterator: ++it.
        Iterator& operator++()
        {
            ++current_;
            if (current_ == buffer_end_)
            {
                current_ = buffer_begin_;
            }
            return *this;
        }

        /// Increment the iterator: it++.
        Iterator operator++(int)
        {
            auto it = *this;
            ++*this;
            return it;
        }

        /// Decrement the iterator: --it.
        Iterator& operator--()
        {
            if (current_ == buffer_begin_)
            {
                current_ = buffer_end_;
            }
            --current_;
            return *this;
        }

        /// Decrement the iterator: it--.
        Iterator operator--(int)
        {
            auto it = *this;
            --*this;
            return it;
        }
    };

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
        : detail::Container(0)
        , front_(0)
        , capacity_(INIT_CAPACITY)
        , data_(new T[capacity_])
    {
    }

    /// Create a deque based on the given initializer list.
    ArrayDeque(const std::initializer_list<T>& il)
        : detail::Container(int(il.size()))
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
     * Iterator
     */

    /// Return an iterator to the first element of the list.
    Iterator begin() const
    {
        return Iterator(data_ + front_, data_, data_ + capacity_);
    }

    /// Return an iterator to the element following the last element of the list.
    Iterator end() const
    {
        return Iterator(data_ + access(size_), data_, data_ + capacity_);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the deque.
    T& front()
    {
        detail::check_empty(size_);
        return data_[front_];
    }

    /// Return the const reference to the element at the front in the deque.
    const T& front() const
    {
        return const_cast<ArrayDeque&>(*this).front();
    }

    /// Return the reference to the element at the back in the deque.
    T& back()
    {
        detail::check_empty(size_);
        return data_[access(size_ - 1)];
    }

    /// Return the const reference to the element at the back in the deque.
    const T& back() const
    {
        return const_cast<ArrayDeque&>(*this).back();
    }

    /*
     * Manipulation
     */

    /// Push front, insert an element at the front of the deque.
    void push_front(const T& element)
    {
        detail::check_full(size_, MAX_CAPACITY);

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
        detail::check_full(size_, MAX_CAPACITY);

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
        detail::check_empty(size_);

        T data = std::move(data_[front_]);
        front_ = (front_ + 1) % capacity_;
        size_--;

        return data;
    }

    /// Pop back, pop the back element of the deque.
    T pop_back()
    {
        detail::check_empty(size_);

        T data = std::move(data_[access(size_ - 1)]);
        size_--;

        return data;
    }

    /// Remove all of the elements from the deque.
    void clear()
    {
        // If the elements themselves are pointers, the pointed-to memory is not touched in any way.
        // Managing the pointer is the user's responsibility.
        size_ = 0;
        front_ = 0;
    }

    /*
     * Print
     */

    /// Print the deque.
    friend std::ostream& operator<<(std::ostream& os, const ArrayDeque& deque)
    {
        return detail::print(os, deque.begin(), deque.end(), "Deque");
    }
};

} // namespace hellods

#endif // ARRAYDEQUE_HPP
