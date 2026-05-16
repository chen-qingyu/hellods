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
    LinkedList<T> list_;

public:
    using Iterator = typename Queue<T>::Iterator;

    /*
     * Lifecycle
     */

    /// Create an empty queue.
    LinkedQueue() = default;

    /// Create a queue based on the given initializer list.
    LinkedQueue(const std::initializer_list<T>& il)
        : list_(il)
    {
    }

    LinkedQueue(const LinkedQueue&) = default;
    LinkedQueue(LinkedQueue&&) = default;

    LinkedQueue& operator=(const LinkedQueue&) = default;
    LinkedQueue& operator=(LinkedQueue&&) = default;

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const LinkedQueue& that) const
    {
        return list_ == that.list_;
    }

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the queue.
    Iterator begin() const override
    {
        return list_.begin();
    }

    /// Return an iterator to the element following the last element of the queue.
    Iterator end() const override
    {
        return list_.end();
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the queue.
    T& front() override
    {
        detail::check_empty(list_.size());
        return list_[0];
    }

    using Queue<T>::front; // const

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return list_.size();
    }

    /*
     * Manipulation
     */

    /// Enqueue, insert an element at the rear of the queue.
    void enqueue(const T& element) override
    {
        list_.append(element);
    }

    /// Dequeue, pop the front element of the queue.
    T dequeue() override
    {
        return list_.remove(0);
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
        return detail::print(os, queue.begin(), queue.end(), "Queue");
    }
};

} // namespace hellods

#endif // LINKEDQUEUE_HPP
