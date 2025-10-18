/**
 * @file Deque.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Abstract deque interface.
 * @date 2025.10.12
 */

#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "../detail.hpp"

namespace hellods
{

/// Abstract deque interface.
template <typename T>
class Deque : public detail::Container
{
public:
    /*
     * Constructor / Destructor
     */

    /// Virtual destructor.
    virtual ~Deque() = default;

    /*
     * Access
     */

    /// Return the reference to the element at the front in the deque.
    virtual T& front() = 0;

    /// Return the const reference to the element at the front in the deque.
    virtual const T& front() const
    {
        return const_cast<Deque&>(*this).front();
    }

    /// Return the reference to the element at the back in the deque.
    virtual T& back() = 0;

    /// Return the const reference to the element at the back in the deque.
    virtual const T& back() const
    {
        return const_cast<Deque&>(*this).back();
    }

    /*
     * Manipulation
     */

    /// Push front, insert an element at the front of the deque.
    virtual void push_front(const T& element) = 0;

    /// Push back, insert an element at the back of the deque.
    virtual void push_back(const T& element) = 0;

    /// Pop front, pop the front element of the deque.
    virtual T pop_front() = 0;

    /// Pop back, pop the back element of the deque.
    virtual T pop_back() = 0;

    /// Remove all of the elements from the deque.
    virtual void clear() = 0;
};

} // namespace hellods

#endif // DEQUE_HPP
