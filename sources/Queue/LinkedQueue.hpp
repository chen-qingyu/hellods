/**
 * @file LinkedQueue.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Queue implemented by doubly linked list.
 * @date 2022.01.28
 */

#ifndef LINKEDQUEUE_HPP
#define LINKEDQUEUE_HPP

#include "../List/LinkedList.hpp"
#include "Queue.hpp"

namespace hellods
{

/// Queue implemented by doubly linked list.
template <typename T>
class LinkedQueue : public Queue<T>
{
    using detail::Container::MAX_CAPACITY;

    LinkedList<T> list_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty queue.
    LinkedQueue()
        : list_()
    {
    }

    /// Create a queue based on the given initializer list.
    LinkedQueue(const std::initializer_list<T>& il)
        : list_(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const LinkedQueue& that) const
    {
        return list_ == that.list_;
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the queue.
    T& front() override
    {
        detail::check_empty(list_.size_);
        return list_.header_->succ_->data_;
    }

    using Queue<T>::front; // const

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

    /// Enqueue, insert an element at the rear of the queue.
    void enqueue(const T& element) override
    {
        detail::check_full(list_.size_, MAX_CAPACITY);
        list_.insert_node(list_.trailer_, element);
    }

    /// Dequeue, pop the front element of the queue.
    T dequeue() override
    {
        detail::check_empty(list_.size_);
        return list_.remove_node(list_.header_->succ_);
    }

    /// Remove all of the elements from the queue.
    void clear() override
    {
        list_.clear();
    }

    /*
     * Print
     */

    /// Print the queue.
    friend std::ostream& operator<<(std::ostream& os, const LinkedQueue& queue)
    {
        std::ostringstream oss;
        oss << queue.list_;
        return os << "Queue" << oss.str().erase(0, 4);
    }
};

} // namespace hellods

#endif // LINKEDQUEUE_HPP
