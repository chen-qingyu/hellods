/**
 * @file Queue.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Abstract queue interface.
 * @date 2025.10.12
 */

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "../detail.hpp"

namespace hellods
{

/// Abstract queue interface.
template <typename T>
class Queue : public detail::Container
{
public:
    /*
     * Constructor / Destructor
     */

    /// Constructor.
    Queue(int size)
        : detail::Container(size)
    {
    }

    /// Virtual destructor.
    virtual ~Queue() = default;

    /*
     * Access
     */

    /// Return the reference to the element at the front in the queue.
    virtual T& front() = 0;

    /// Return the const reference to the element at the front in the queue.
    virtual const T& front() const
    {
        return const_cast<Queue&>(*this).front();
    }

    /*
     * Manipulation
     */

    /// Enqueue, insert an element at the rear of the queue.
    virtual void enqueue(const T& element) = 0;

    /// Dequeue, pop the front element of the queue.
    virtual T dequeue() = 0;

    /// Remove all of the elements from the queue.
    virtual void clear() = 0;
};

} // namespace hellods

#endif // QUEUE_HPP
