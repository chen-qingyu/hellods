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
class LinkedDeque : public Deque<T>
{
    using detail::Container::MAX_CAPACITY;

    LinkedList<T> list_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty deque.
    LinkedDeque()
        : list_()
    {
    }

    /// Create a deque based on the given initializer list.
    LinkedDeque(const std::initializer_list<T>& il)
        : list_(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const LinkedDeque& that) const
    {
        return list_ == that.list_;
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the deque.
    auto begin() const
    {
        return list_.begin();
    }

    /// Return an iterator to the element following the last element of the deque.
    auto end() const
    {
        return list_.end();
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the deque.
    T& front() override
    {
        detail::check_empty(list_.size_);
        return list_.header_->succ_->data_;
    }

    using Deque<T>::front; // const

    /// Return the reference to the element at the back in the deque.
    T& back() override
    {
        detail::check_empty(list_.size_);
        return list_.trailer_->pred_->data_;
    }

    using Deque<T>::back; // const

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return list_.size_;
    }

    /*
     * Manipulation
     */

    /// Push front, insert an element at the front of the deque.
    void push_front(const T& element) override
    {
        detail::check_full(list_.size_, MAX_CAPACITY);
        list_.insert_node(list_.header_->succ_, element);
    }

    /// Push back, insert an element at the back of the deque.
    void push_back(const T& element) override
    {
        detail::check_full(list_.size_, MAX_CAPACITY);
        list_.insert_node(list_.trailer_, element);
    }

    /// Pop front, pop the front element of the deque.
    T pop_front() override
    {
        detail::check_empty(list_.size_);
        return list_.remove_node(list_.header_->succ_);
    }

    /// Pop back, pop the back element of the deque.
    T pop_back() override
    {
        detail::check_empty(list_.size_);
        return list_.remove_node(list_.trailer_->pred_);
    }

    /// Remove all of the elements from the deque.
    void clear() override
    {
        list_.clear();
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
