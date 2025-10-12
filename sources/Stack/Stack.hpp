/**
 * @file Stack.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Abstract stack interface.
 * @date 2025.10.12
 */

#ifndef STACK_HPP
#define STACK_HPP

#include "../detail.hpp"

namespace hellods
{

/// Abstract stack interface.
template <typename T>
class Stack : public detail::Container
{
public:
    /*
     * Constructor / Destructor
     */

    /// Constructor.
    Stack(int size)
        : detail::Container(size)
    {
    }

    /// Virtual destructor.
    virtual ~Stack() = default;

    /*
     * Access
     */

    /// Return the reference to the element at the top in the stack.
    virtual T& top() = 0;

    /// Return the const reference to the element at the top in the stack.
    virtual const T& top() const
    {
        return const_cast<Stack&>(*this).top();
    }

    /*
     * Manipulation
     */

    /// Push an element at the top of the stack.
    virtual void push(const T& element) = 0;

    /// Pop the top element of the stack.
    virtual T pop() = 0;

    /// Remove all of the elements from the stack.
    virtual void clear() = 0;
};

} // namespace hellods

#endif // STACK_HPP