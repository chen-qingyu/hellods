/**
 * @file ArrayQueue.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Queue implemented by array.
 * @date 2022.01.28
 */

#ifndef ARRAYQUEUE_HPP
#define ARRAYQUEUE_HPP

#include "../Deque/ArrayDeque.hpp"
#include "Queue.hpp"

namespace hellods
{

/// Queue implemented by array.
template <typename T>
class ArrayQueue : public Queue<T>
{
    ArrayDeque<T> deque_;

public:
    using Iterator = typename Queue<T>::Iterator;

    /*
     * Lifecycle
     */

    /// Create an empty queue.
    ArrayQueue() = default;

    /// Create a queue based on the given initializer list.
    ArrayQueue(const std::initializer_list<T>& il)
        : deque_(il)
    {
    }

    ArrayQueue(const ArrayQueue&) = default;
    ArrayQueue(ArrayQueue&&) = default;

    ArrayQueue& operator=(const ArrayQueue&) = default;
    ArrayQueue& operator=(ArrayQueue&&) = default;

    /*
     * Iterator
     */

    /// Return an iterator to the first element of the queue.
    Iterator begin() const override
    {
        return deque_.begin();
    }

    /// Return an iterator to the element following the last element of the queue.
    Iterator end() const override
    {
        return deque_.end();
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the queue.
    T& front() override
    {
        return deque_.front();
    }

    using Queue<T>::front; // const

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return deque_.size();
    }

    /*
     * Manipulation
     */

    /// Enqueue, insert an element at the rear of the queue.
    void enqueue(const T& element) override
    {
        deque_.push_back(element);
    }

    /// Dequeue, pop the front element of the queue.
    T dequeue() override
    {
        return deque_.pop_front();
    }

    /// Remove all of the elements from the queue.
    void clear() override
    {
        deque_.clear();
    }
};

} // namespace hellods

#endif // ARRAYQUEUE_HPP
