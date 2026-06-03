/**
 * @file ArrayDeque.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Deque implemented by array.
 * @date 2024.03.29
 */

#ifndef ARRAYDEQUE_HPP
#define ARRAYDEQUE_HPP

#include "../core.hpp"
#include "Deque.hpp"

namespace hellods
{

/// Deque implemented by array.
template <typename T>
class ArrayDeque : public Deque<T, std::random_access_iterator_tag>
{
    template <bool Const>
    class Iter
    {
        friend class ArrayDeque;

    protected:
        using Value = std::conditional_t<Const, const T, T>;

        // Virtual pointer = buffer_begin_ + head_ + offset_ (linear, no modulo).
        Value* current_;

        // Begin of the ring buffer.
        Value* buffer_begin_;

        // End of the ring buffer.
        Value* buffer_end_;

        // Create an iterator that point to the current data of deque.
        Iter(Value* current, Value* begin, Value* end)
            : current_(current)
            , buffer_begin_(begin)
            , buffer_end_(end)
        {
        }

    public:
        /// Dereference.
        Value& operator*() const
        {
            return current_ < buffer_end_ ? *current_ : *(current_ - (buffer_end_ - buffer_begin_));
        }

        /// Check if two iterators are same.
        bool operator==(const Iter& that) const
        {
            return current_ == that.current_;
        }

        /// Increment the iterator.
        Iter& operator++()
        {
            ++current_;
            return *this;
        }

        /// Decrement the iterator.
        Iter& operator--()
        {
            --current_;
            return *this;
        }

        /// Advance by n elements.
        Iter& operator+=(std::ptrdiff_t n)
        {
            current_ += n;
            return *this;
        }

        /// Return a copy advanced by n elements.
        Iter operator+(std::ptrdiff_t n) const
        {
            auto tmp = *this;
            tmp += n;
            return tmp;
        }

        /// Retreat by n elements.
        Iter& operator-=(std::ptrdiff_t n)
        {
            current_ -= n;
            return *this;
        }

        /// Return a copy retreated by n elements.
        Iter operator-(std::ptrdiff_t n) const
        {
            auto tmp = *this;
            tmp -= n;
            return tmp;
        }

        /// Signed distance (number of elements) between two iterators.
        std::ptrdiff_t operator-(const Iter& that) const
        {
            return current_ - that.current_;
        }

        /// Access the element at offset n without advancing.
        Value& operator[](std::ptrdiff_t n) const
        {
            return *(*this + n);
        }

        /// Ordering comparisons (based on virtual pointer position).
        bool operator<(const Iter& that) const
        {
            return current_ < that.current_;
        }

        bool operator<=(const Iter& that) const
        {
            return current_ <= that.current_;
        }

        bool operator>(const Iter& that) const
        {
            return current_ > that.current_;
        }

        bool operator>=(const Iter& that) const
        {
            return current_ >= that.current_;
        }
    };

protected:
    using Deque<T, std::random_access_iterator_tag>::INIT_CAPACITY;
    using Deque<T, std::random_access_iterator_tag>::MAX_CAPACITY;

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

    // Swap with another deque.
    void swap(ArrayDeque& that)
    {
        std::swap(front_, that.front_);
        std::swap(size_, that.size_);
        std::swap(capacity_, that.capacity_);
        std::swap(data_, that.data_);
    }

public:
    /*
     * Lifecycle
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

    /// Copy constructor.
    ArrayDeque(const ArrayDeque& that)
        : front_(that.front_)
        , size_(that.size_)
        , capacity_(that.capacity_)
        , data_(new T[capacity_])
    {
        std::copy(that.data_, that.data_ + capacity_, data_);
    }

    /// Move constructor.
    ArrayDeque(ArrayDeque&& that)
        : ArrayDeque()
    {
        swap(that);
    }

    ArrayDeque& operator=(ArrayDeque that)
    {
        swap(that);
        return *this;
    }

    /// Destroy the deque object.
    ~ArrayDeque()
    {
        delete[] data_;
    }

    /*
     * Iterator
     */

    using Iterator = typename Deque<T, std::random_access_iterator_tag>::Iterator;
    using ConstIterator = typename Deque<T, std::random_access_iterator_tag>::ConstIterator;

    /// Return an iterator to the first element of the deque.
    Iterator begin() override
    {
        return Iterator(Iter<false>(data_ + front_, data_, data_ + capacity_));
    }

    ConstIterator begin() const override
    {
        return ConstIterator(Iter<true>(data_ + front_, data_, data_ + capacity_));
    }

    /// Return an iterator to the element following the last element of the deque.
    Iterator end() override
    {
        return Iterator(Iter<false>(data_ + front_ + size_, data_, data_ + capacity_));
    }

    ConstIterator end() const override
    {
        return ConstIterator(Iter<true>(data_ + front_ + size_, data_, data_ + capacity_));
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

    using Deque<T, std::random_access_iterator_tag>::front; // const

    /// Return the reference to the element at the back in the deque.
    T& back() override
    {
        detail::check_empty(size_);
        return data_[access(size_ - 1)];
    }

    using Deque<T, std::random_access_iterator_tag>::back; // const

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
};

} // namespace hellods

#endif // ARRAYDEQUE_HPP
