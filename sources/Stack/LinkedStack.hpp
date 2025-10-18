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
    using detail::Container::MAX_CAPACITY;

    LinkedList<T> list_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty stack.
    LinkedStack()
        : list_()
    {
    }

    /// Create a stack based on the given initializer list.
    LinkedStack(const std::initializer_list<T>& il)
        : list_(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two stacks are equal.
    bool operator==(const LinkedStack& that) const
    {
        return list_ == that.list_;
    }

    /*
     * Access
     */

    /// Return the reference to the element at the top in the stack.
    T& top() override
    {
        detail::check_empty(list_.size_);
        return list_.trailer_->pred_->data_;
    }

    using Stack<T>::top; // const

    /*
     * Examination
     */

    /// Get the number of elements.
    int size() const override
    {
        return list_.size_;
    }

    /*
     * Manipulation
     */

    /// Push an element at the top of the stack.
    void push(const T& element) override
    {
        detail::check_full(list_.size_, MAX_CAPACITY);
        list_.insert_node(list_.trailer_, element);
    }

    /// Pop the top element of the stack.
    T pop() override
    {
        detail::check_empty(list_.size_);
        return list_.remove_node(list_.trailer_->pred_);
    }

    /// Remove all of the elements from the stack.
    void clear() override
    {
        list_.clear();
    }

    /*
     * Print
     */

    /// Print the stack.
    friend std::ostream& operator<<(std::ostream& os, const LinkedStack& stack)
    {
        std::ostringstream oss;
        oss << stack.list_;
        return os << "Stack" << oss.str().erase(0, 4);
    }
};

} // namespace hellods

#endif // LINKEDSTACK_HPP
