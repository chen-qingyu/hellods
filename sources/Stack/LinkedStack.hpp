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
class LinkedStack : protected LinkedList<T>, virtual Stack<T>
{
    using LinkedList<T>::MAX_CAPACITY;
    using LinkedList<T>::size_;
    using LinkedList<T>::header_;
    using LinkedList<T>::trailer_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty stack.
    LinkedStack()
        : LinkedList<T>()
        , Stack<T>(0)
    {
    }

    /// Create a stack based on the given initializer list.
    LinkedStack(const std::initializer_list<T>& il)
        : LinkedList<T>(il)
        , Stack<T>(int(il.size()))
    {
    }

    /*
     * Comparison
     */

    /// Check whether two stacks are equal.
    bool operator==(const LinkedStack& that) const
    {
        return static_cast<const LinkedList<T>&>(*this) == static_cast<const LinkedList<T>&>(that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the top in the stack.
    T& top() override
    {
        detail::check_empty(size());
        return trailer_->pred_->data_;
    }

    using Stack<T>::top; // const

    /*
     * Examination
     */

    using LinkedList<T>::is_empty;
    using LinkedList<T>::size;

    /*
     * Manipulation
     */

    /// Push an element at the top of the stack.
    void push(const T& element) override
    {
        detail::check_full(size_, MAX_CAPACITY);
        LinkedList<T>::insert_node(trailer_, element);
    }

    /// Pop the top element of the stack.
    T pop() override
    {
        detail::check_empty(size_);
        return LinkedList<T>::remove_node(trailer_->pred_);
    }

    /// Remove all of the elements from the stack.
    void clear() override
    {
        LinkedList<T>::clear();
    }

    /*
     * Print
     */

    /// Print the stack.
    friend std::ostream& operator<<(std::ostream& os, const LinkedStack& stack)
    {
        std::ostringstream oss;
        oss << static_cast<const LinkedList<T>&>(stack);
        return os << "Stack" << oss.str().erase(0, 4);
    }
};

} // namespace hellods

#endif // LINKEDSTACK_HPP
