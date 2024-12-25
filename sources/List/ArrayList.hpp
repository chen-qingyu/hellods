/**
 * @file ArrayList.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief List implemented by array.
 * @date 2022.01.28
 */

#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include "../detail.hpp"

namespace hellods
{

/// List implemented by array.
template <typename T>
class ArrayList : public detail::Container
{
public:
    /// List iterator class.
    class Iterator
    {
        friend class ArrayList;

    protected:
        // Current data pointer.
        T* current_;

        // Create an iterator that point to the current data of list.
        Iterator(T* current)
            : current_(current)
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
            return *this;
        }

        /// Increment the iterator: it++.
        Iterator operator++(int)
        {
            auto it = *this;
            ++current_;
            return it;
        }

        /// Decrement the iterator: --it.
        Iterator& operator--()
        {
            --current_;
            return *this;
        }

        /// Decrement the iterator: it--.
        Iterator operator--(int)
        {
            auto it = *this;
            --current_;
            return it;
        }
    };

protected:
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
        : detail::Container(0)
        , capacity_(INIT_CAPACITY)
        , data_(new T[capacity_])
    {
    }

    /// Create a list based on the given initializer list.
    ArrayList(const std::initializer_list<T>& il)
        : detail::Container(int(il.size()))
        , capacity_(size_ > INIT_CAPACITY ? size_ : INIT_CAPACITY)
        , data_(new T[capacity_])
    {
        std::copy(il.begin(), il.end(), data_);
    }

    /// Copy constructor.
    ArrayList(const ArrayList& that)
        : detail::Container(that.size_)
        , capacity_(that.capacity_)
        , data_(new T[capacity_])
    {
        std::copy(that.begin(), that.end(), data_);
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
        detail::check_bounds(index, 0, size_);
        return data_[index];
    }

    /// Return the const reference to element at the specified position in the list.
    const T& operator[](int index) const
    {
        return const_cast<ArrayList&>(*this)[index];
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the list.
    /// If the list is empty, the returned iterator will be equal to end().
    Iterator begin() const
    {
        return Iterator(data_);
    }

    /// Return an iterator to the element following the last element of the list.
    /// This element acts as a placeholder, attempting to access it results in undefined behavior.
    Iterator end() const
    {
        return Iterator(data_ + size_); // not nullptr, because size_ <= capacity_
    }

    /*
     * Examination
     */

    /// Return an iterator to the first occurrence of the specified element, or end() if the list does not contains the element.
    Iterator find(const T& element) const
    {
        return std::find(begin(), end(), element);
    }

    /*
     * Manipulation
     */

    /// Add the specified element to the end of the list.
    void add(const T& element)
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
    void insert(int index, const T& element)
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
    T remove(int index)
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

    /// Perform the given action for each element of the list.
    template <typename F>
    ArrayList& map(const F& action)
    {
        std::for_each(data_, data_ + size_, action);

        return *this;
    }

    /// Reverse the list in place.
    ArrayList& reverse()
    {
        std::reverse(data_, data_ + size_);

        return *this;
    }

    /// Remove all of the elements from the list.
    void clear()
    {
        // If the elements themselves are pointers, the pointed-to memory is not touched in any way.
        // Managing the pointer is the user's responsibility.
        size_ = 0;
    }

    /*
     * Print
     */

    /// Print the list.
    friend std::ostream& operator<<(std::ostream& os, const ArrayList& list)
    {
        return detail::print(os, list, "List");
    }
};

} // namespace hellods

#endif // ARRAYLIST_HPP
