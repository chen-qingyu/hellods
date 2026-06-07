/**
 * @file Stack.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Abstract stack interface.
 * @date 2025.10.12
 */

#ifndef STACK_HPP
#define STACK_HPP

#include "../core.hpp"

namespace hellods
{

/// Abstract stack interface.
template <typename T>
class Stack : public detail::ConstIterable<T>
{
public:
    using typename detail::ConstIterable<T>::Iterator;

    /// @name Lifecycle
    /// @{

    /// Virtual destructor.
    ~Stack() override = default;

    /// Return the type name for printing.
    const char* name() const override
    {
        return "Stack";
    }
    /// @}

    /// @name Access
    /// @{

    /// Return the reference to the element at the top in the stack.
    virtual T& top() = 0;

    /// Return the const reference to the element at the top in the stack.
    virtual const T& top() const
    {
        return const_cast<Stack&>(*this).top();
    }
    /// @}

    /// @name Manipulation
    /// @{

    /// Push an element at the top of the stack.
    virtual void push(const T& element) = 0;

    /// Pop the top element of the stack.
    virtual T pop() = 0;

    /// @}
};

} // namespace hellods

#endif // STACK_HPP
