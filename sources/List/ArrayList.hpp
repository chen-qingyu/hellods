/**
 * @file ArrayList.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief List implemented by array.
 * @date 2022.01.28
 */

#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include "List.hpp"

namespace hellods
{

/// List implemented by array.
template <typename T>
class ArrayList : public List<T>
{
protected:
    // T* is itself a valid input iterator — no wrapper class needed.

protected:
    using List<T>::INIT_CAPACITY;
    using List<T>::MAX_CAPACITY;

    // Number of elements.
    int size_;

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

    // Swap with another list.
    void swap(ArrayList& that)
    {
        std::swap(size_, that.size_);
        std::swap(capacity_, that.capacity_);
        std::swap(data_, that.data_);
    }

public:
    /*
     * Lifecycle
     */

    /// Create an empty list.
    ArrayList()
        : size_(0)
        , capacity_(INIT_CAPACITY)
        , data_(new T[capacity_])
    {
    }

    /// Create a list based on the given initializer list.
    ArrayList(const std::initializer_list<T>& il)
        : size_(int(il.size()))
        , capacity_(size_ > INIT_CAPACITY ? size_ : INIT_CAPACITY)
        , data_(new T[capacity_])
    {
        std::copy(il.begin(), il.end(), data_);
    }

    /// Copy constructor.
    ArrayList(const ArrayList& that)
        : size_(that.size_)
        , capacity_(that.capacity_)
        , data_(new T[capacity_])
    {
        std::copy(that.begin(), that.end(), data_);
    }

    /// Move constructor.
    ArrayList(ArrayList&& that)
        : size_(that.size_)
        , capacity_(that.capacity_)
        , data_(that.data_)
    {
        that.size_ = 0;
        that.capacity_ = INIT_CAPACITY;
        that.data_ = new T[that.capacity_];
    }

    ArrayList& operator=(ArrayList that)
    {
        swap(that);
        return *this;
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
        return size_ == that.size_ && std::equal(data_, data_ + size_, that.data_);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the specified position in the list.
    T& operator[](int index) override
    {
        detail::check_bounds(index, 0, size_);
        return data_[index];
    }

    using List<T>::operator[]; // const

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the list.
    /// If the list is empty, the returned iterator will be equal to end().
    typename List<T>::Iterator begin() override
    {
        return typename List<T>::Iterator(data_);
    }

    typename List<T>::ConstIterator begin() const override
    {
        return typename List<T>::ConstIterator(data_);
    }

    /// Return an iterator to the element following the last element of the list.
    /// This element acts as a placeholder, attempting to access it results in undefined behavior.
    typename List<T>::Iterator end() override
    {
        return typename List<T>::Iterator(data_ + size_);
    }

    typename List<T>::ConstIterator end() const override
    {
        return typename List<T>::ConstIterator(data_ + size_);
    }

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

    /// Append the specified element to the list.
    void append(const T& element) override
    {
        // check
        detail::check_full(size_, MAX_CAPACITY);

        // expand capacity if need
        if (size_ == capacity_)
        {
            expand_capacity();
        }

        // insert and resize
        data_[size_++] = element; // copy assignment on T
    }

    /// Insert the specified element at the specified position in the list.
    void insert(int index, const T& element) override
    {
        // check
        detail::check_full(size_, MAX_CAPACITY);
        detail::check_bounds(index, 0, size_ + 1);

        // expand capacity if need
        if (size_ == capacity_)
        {
            expand_capacity();
        }

        // shift
        std::copy_backward(data_ + index, data_ + size_, data_ + size_ + 1);

        // insert
        data_[index] = element; // copy assignment on T

        // resize
        ++size_;
    }

    /// Remove and return the element at the specified position in the list.
    T remove(int index) override
    {
        // check
        detail::check_empty(size_);
        detail::check_bounds(index, 0, size_);

        // move element
        T element = std::move(data_[index]);

        // shift
        std::copy(data_ + index + 1, data_ + size_, data_ + index);

        // resize
        --size_;

        // return element
        return element;
    }

    /// Remove all of the elements from the list.
    void clear() override
    {
        // If the elements themselves are pointers, the pointed-to memory is not touched in any way.
        // Managing the pointer is the user's responsibility.
        size_ = 0;
    }
};

} // namespace hellods

#endif // ARRAYLIST_HPP
