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
class ArrayQueue : protected ArrayDeque<T>, virtual Queue<T>
{
public:
    using ArrayDeque<T>::is_empty;
    using ArrayDeque<T>::size;

    /*
     * Constructor / Destructor
     */

    /// Create an empty queue.
    ArrayQueue()
        : ArrayDeque<T>()
        , Queue<T>(0)
    {
    }

    /// Create a queue based on the given initializer list.
    ArrayQueue(const std::initializer_list<T>& il)
        : ArrayDeque<T>(il)
        , Queue<T>(int(il.size()))
    {
    }

    /*
     * Comparison
     */

    /// Check whether two queues are equal.
    bool operator==(const ArrayQueue& that) const
    {
        return static_cast<const ArrayDeque<T>&>(*this) == static_cast<const ArrayDeque<T>&>(that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the queue.
    T& front() override
    {
        return ArrayDeque<T>::front();
    }

    using Queue<T>::front; // const

    /*
     * Manipulation
     */

    /// Enqueue, insert an element at the rear of the queue.
    void enqueue(const T& element) override
    {
        ArrayDeque<T>::push_back(element);
    }

    /// Dequeue, pop the front element of the queue.
    T dequeue() override
    {
        return ArrayDeque<T>::pop_front();
    }

    /// Remove all of the elements from the queue.
    void clear() override
    {
        ArrayDeque<T>::clear();
    }

    /*
     * Print
     */

    /// Print the queue.
    friend std::ostream& operator<<(std::ostream& os, const ArrayQueue& queue)
    {
        std::ostringstream oss;
        oss << static_cast<const ArrayDeque<T>&>(queue);
        return os << "Queue" << oss.str().erase(0, 5);
    }
};

} // namespace hellods

#endif // ARRAYQUEUE_HPP
