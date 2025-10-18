/**
 * @file ArrayDeque.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Deque implemented by array.
 * @date 2024.03.29
 */

#ifndef ARRAYDEQUE_HPP
#define ARRAYDEQUE_HPP

#include "../detail.hpp"
#include "Deque.hpp"

namespace hellods
{

/// Deque implemented by array.
template <typename T>
class ArrayDeque : public Deque<T>
{
    template <typename U>
    friend class ArrayQueue;

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

protected:
    using detail::Container::INIT_CAPACITY;
    using detail::Container::MAX_CAPACITY;

    // Index of front in ring buffer. data[front] is the first element, except size == 0.
    int front_;

    // Number of elements.
    int size_;

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
        : front_(0)
        , size_(0)
        , capacity_(INIT_CAPACITY)
        , data_(new T[capacity_])
    {
    }

    /// Create a deque based on the given initializer list.
    ArrayDeque(const std::initializer_list<T>& il)
        : front_(0)
        , size_(int(il.size()))
        , capacity_(size_ > INIT_CAPACITY ? size_ : INIT_CAPACITY)
        , data_(new T[capacity_])
    {
        std::copy(il.begin(), il.end(), data_);
    }

    /// Destroy the deque object.
    ~ArrayDeque()
    {
        delete[] data_;
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

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the list.
    auto begin() const
    {
        return Iterator(data_ + front_, data_, data_ + capacity_);
    }

    /// Return an iterator to the element following the last element of the list.
    auto end() const
    {
        return Iterator(data_ + access(size_), data_, data_ + capacity_);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the deque.
    T& front() override
    {
        detail::check_empty(size_);
        return data_[front_];
    }

    using Deque<T>::front; // const

    /// Return the reference to the element at the back in the deque.
    T& back() override
    {
        detail::check_empty(size_);
        return data_[access(size_ - 1)];
    }

    using Deque<T>::back; // const

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return size_;
    }

    /*
     * Manipulation
     */

    /// Push front, insert an element at the front of the deque.
    void push_front(const T& element) override
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
    void push_back(const T& element) override
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
    T pop_front() override
    {
        detail::check_empty(size_);

        T data = std::move(data_[front_]);
        front_ = (front_ + 1) % capacity_;
        size_--;

        return data;
    }

    /// Pop back, pop the back element of the deque.
    T pop_back() override
    {
        detail::check_empty(size_);

        T data = std::move(data_[access(size_ - 1)]);
        size_--;

        return data;
    }

    /// Remove all of the elements from the deque.
    void clear() override
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
