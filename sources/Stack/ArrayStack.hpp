/**
 * @file ArrayStack.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Stack implemented by array list.
 * @date 2022.01.28
 */

#ifndef ARRAYSTACK_HPP
#define ARRAYSTACK_HPP

#include "../List/ArrayList.hpp"
#include "Stack.hpp"

namespace hellods
{

/// Stack implemented by array list.
template <typename T>
class ArrayStack : public Stack<T>
{
    ArrayList<T> list_;

public:
    using Iterator = typename Stack<T>::Iterator;

    /// @name Lifecycle
    /// @{

    /// Create an empty stack.
    ArrayStack() = default;

    /// Create a stack based on the given initializer list.
    ArrayStack(const std::initializer_list<T>& il)
        : list_(il)
    {
    }

    ArrayStack(const ArrayStack&) = default;
    ArrayStack(ArrayStack&&) = default;

    ArrayStack& operator=(const ArrayStack&) = default;
    ArrayStack& operator=(ArrayStack&&) = default;
    /// @}

    /// @name Iterator
    /// @{

    /// Return an iterator to the first element of the stack.
    Iterator begin() const override
    {
        return list_.begin();
    }

    /// Return an iterator to the element following the last element of the stack.
    Iterator end() const override
    {
        return list_.end();
    }
    /// @}

    /// @name Access
    /// @{

    /// Return the reference to the element at the top in the stack.
    T& top() override
    {
        detail::check_empty(list_.size());
        return list_[list_.size() - 1];
    }

    using Stack<T>::top; // const
    /// @}

    /// @name Examination
    /// @{

    /// Get the number of elements.
    int size() const override
    {
        return list_.size();
    }
    /// @}

    /// @name Manipulation
    /// @{

    /// Push an element at the top of the stack.
    void push(const T& element) override
    {
        list_.append(element);
    }

    /// Pop the top element of the stack.
    T pop() override
    {
        return list_.pop();
    }

    /// Remove all of the elements from the stack.
    void clear() override
    {
        list_.clear();
    }

    /// @}
};

} // namespace hellods

#endif // ARRAYSTACK_HPP
