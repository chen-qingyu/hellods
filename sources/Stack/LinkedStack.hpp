/**
 * @file LinkedStack.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Stack implemented by doubly linked list.
 * @date 2022.01.28
 */

#ifndef LINKEDSTACK_HPP
#define LINKEDSTACK_HPP

#include "../List/LinkedList.hpp"
#include "Stack.hpp"

namespace hellods
{

/// Stack implemented by doubly linked list.
template <typename T>
class LinkedStack : public Stack<T>
{
    LinkedList<T> list_;

public:
    using Iterator = typename Stack<T>::Iterator;

    /*
     * Lifecycle
     */

    /// Create an empty stack.
    LinkedStack() = default;

    /// Create a stack based on the given initializer list.
    LinkedStack(const std::initializer_list<T>& il)
        : list_(il)
    {
    }

    LinkedStack(const LinkedStack&) = default;
    LinkedStack(LinkedStack&&) = default;

    LinkedStack& operator=(const LinkedStack&) = default;
    LinkedStack& operator=(LinkedStack&&) = default;

    /*
     * Comparison
     */

    /// Check whether two stacks are equal.
    bool operator==(const LinkedStack& that) const
    {
        return list_ == that.list_;
    }

    /*
     * Iterator
     */

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

    /*
     * Access
     */

    /// Return the reference to the element at the top in the stack.
    T& top() override
    {
        detail::check_empty(list_.size());
        return list_[list_.size() - 1];
    }

    using Stack<T>::top; // const

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
};

} // namespace hellods

#endif // LINKEDSTACK_HPP
