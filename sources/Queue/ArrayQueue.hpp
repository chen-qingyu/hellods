/**
 * @file ArrayQueue.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Queue implemented by array.
 * @date 2022.01.28
 */

#ifndef ARRAYQUEUE_HPP
#define ARRAYQUEUE_HPP

#include "../Deque/ArrayDeque.hpp"

namespace hellods
{

/// Queue implemented by array.
template <typename T>
class ArrayQueue : private ArrayDeque<T>
{
public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty queue.
    ArrayQueue()
        : ArrayDeque<T>()
    {
    }

    /// Create a queue based on the given initializer list.
    ArrayQueue(const std::initializer_list<T>& il)
        : ArrayDeque<T>(il)
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

    /// Check whether two queues are not equal.
    bool operator!=(const ArrayQueue& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the front in the queue.
    T& front()
    {
        return ArrayDeque<T>::front();
    }

    /// Return the const reference to the element at the front in the queue.
    const T& front() const
    {
        return ArrayDeque<T>::front();
    }

    /*
     * Examination
     */

    /// Get the number of elements of the queue.
    int size() const
    {
        return ArrayDeque<T>::size();
    }

    /// Check if the queue is empty.
    bool is_empty() const
    {
        return ArrayDeque<T>::is_empty();
    }

    /*
     * Manipulation
     */

    /// Enqueue, insert an element at the rear of the queue.
    void enqueue(const T& element)
    {
        ArrayDeque<T>::push_back(element);
    }

    /// Dequeue, pop the front element of the queue.
    T dequeue()
    {
        return ArrayDeque<T>::pop_front();
    }

    /// Remove all of the elements from the queue.
    void clear()
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
