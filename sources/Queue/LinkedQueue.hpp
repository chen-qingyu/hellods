/**
 * @file LinkedQueue.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Queue implemented by doubly linked list.
 * @date 2022.01.28
 */

#ifndef LINKEDQUEUE_HPP
#define LINKEDQUEUE_HPP

#include "../List/LinkedList.hpp"

namespace hellods
{

/// Queue implemented by doubly linked list.
template <typename T>
class LinkedQueue : private LinkedList<T>
{
protected:
    using LinkedList<T>::MAX_CAPACITY;
    using LinkedList<T>::size_;
    using LinkedList<T>::header_;
    using LinkedList<T>::trailer_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty queue.
    LinkedQueue()
        : LinkedList<T>()
    {
    }

    /// Create a queue based on the given initializer list.
    LinkedQueue(const std::initializer_list<T>& il)
        : LinkedList<T>(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const LinkedQueue& that) const
    {
        return static_cast<const LinkedList<T>&>(*this) == static_cast<const LinkedList<T>&>(that);
    }

    /// Check whether two queues are not equal.
    bool operator!=(const LinkedQueue& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the queue.
    T& front()
    {
        common::check_empty(size());
        return header_->succ_->data_;
    }

    /// Return the const reference to the element at the front in the queue.
    const T& front() const
    {
        return const_cast<LinkedQueue&>(*this).front();
    }

    /*
     * Examination
     */

    /// Get the number of elements of the queue.
    int size() const
    {
        return LinkedList<T>::size();
    }

    /// Check if the queue is empty.
    bool is_empty() const
    {
        return LinkedList<T>::is_empty();
    }

    /*
     * Manipulation
     */

    /// Enqueue, insert an element at the rear of the queue.
    void enqueue(const T& element)
    {
        common::check_full(size_, MAX_CAPACITY);
        LinkedList<T>::insert_node(trailer_, element);
    }

    /// Dequeue, pop the front element of the queue.
    T dequeue()
    {
        common::check_empty(size_);
        return LinkedList<T>::remove_node(header_->succ_);
    }

    /// Remove all of the elements from the queue.
    void clear()
    {
        LinkedList<T>::clear();
    }

    /*
     * Print
     */

    /// Print the queue.
    friend std::ostream& operator<<(std::ostream& os, const LinkedQueue& queue)
    {
        std::ostringstream oss;
        oss << static_cast<const LinkedList<T>&>(queue);
        return os << "Queue" << oss.str().erase(0, 4);
    }
};

} // namespace hellods

#endif // LINKEDQUEUE_HPP
