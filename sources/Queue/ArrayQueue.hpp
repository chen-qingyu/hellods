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
    /*
     * Constructor / Destructor
     */

    /// Create an empty queue.
    ArrayQueue()
        : deque_()
    {
    }

    /// Create a queue based on the given initializer list.
    ArrayQueue(const std::initializer_list<T>& il)
        : deque_(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const ArrayQueue& that) const
    {
        return deque_ == that.deque_;
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
        return deque_.size_;
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

    /*
     * Print
     */

    /// Print the queue.
    friend std::ostream& operator<<(std::ostream& os, const ArrayQueue& queue)
    {
        std::ostringstream oss;
        oss << queue.deque_;
        return os << "Queue" << oss.str().erase(0, 5);
    }
};

} // namespace hellods

#endif // ARRAYQUEUE_HPP
