/**
 * @file LinkedDeque.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Deque implemented by double linked list.
 * @date 2023.01.02
 */

#ifndef LINKEDDEQUE_HPP
#define LINKEDDEQUE_HPP

#include "../List/LinkedList.hpp"
#include "Deque.hpp"

namespace hellods
{

/// Deque implemented by double linked list.
template <typename T>
class LinkedDeque : protected LinkedList<T>, virtual Deque<T>
{
    using LinkedList<T>::MAX_CAPACITY;
    using LinkedList<T>::size_;
    using LinkedList<T>::header_;
    using LinkedList<T>::trailer_;

public:
    using LinkedList<T>::Iterator;

    /*
     * Constructor / Destructor
     */

    /// Create an empty deque.
    LinkedDeque()
        : LinkedList<T>()
        , Deque<T>(0)
    {
    }

    /// Create a deque based on the given initializer list.
    LinkedDeque(const std::initializer_list<T>& il)
        : LinkedList<T>(il)
        , Deque<T>(int(il.size()))
    {
    }

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const LinkedDeque& that) const
    {
        return static_cast<const LinkedList<T>&>(*this) == static_cast<const LinkedList<T>&>(that);
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the deque.
    Iterator begin() const
    {
        return LinkedList<T>::begin();
    }

    /// Return an iterator to the element following the last element of the deque.
    Iterator end() const
    {
        return LinkedList<T>::end();
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the deque.
    T& front() override
    {
        detail::check_empty(size());
        return header_->succ_->data_;
    }

    using Deque<T>::front; // const

    /// Return the reference to the element at the back in the deque.
    T& back() override
    {
        detail::check_empty(size());
        return trailer_->pred_->data_;
    }

    using Deque<T>::back; // const

    /*
     * Examination
     */

    using LinkedList<T>::is_empty;
    using LinkedList<T>::size;

    /*
     * Manipulation
     */

    /// Push front, insert an element at the front of the deque.
    void push_front(const T& element)
    {
        detail::check_full(size_, MAX_CAPACITY);
        LinkedList<T>::insert_node(header_->succ_, element);
    }

    /// Push back, insert an element at the back of the deque.
    void push_back(const T& element)
    {
        detail::check_full(size_, MAX_CAPACITY);
        LinkedList<T>::insert_node(trailer_, element);
    }

    /// Pop front, pop the front element of the deque.
    T pop_front()
    {
        detail::check_empty(size_);
        return LinkedList<T>::remove_node(header_->succ_);
    }

    /// Pop back, pop the back element of the deque.
    T pop_back()
    {
        detail::check_empty(size_);
        return LinkedList<T>::remove_node(trailer_->pred_);
    }

    /// Remove all of the elements from the deque.
    void clear()
    {
        LinkedList<T>::clear();
    }

    /*
     * Print
     */

    /// Print the deque.
    friend std::ostream& operator<<(std::ostream& os, const LinkedDeque& deque)
    {
        return detail::print(os, deque.begin(), deque.end(), "Deque");
    }
};

} // namespace hellods

#endif // LINKEDDEQUE_HPP
