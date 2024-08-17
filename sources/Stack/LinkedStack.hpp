/**
 * @file LinkedStack.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Stack implemented by doubly linked list.
 * @date 2022.01.28
 */

#ifndef LINKEDSTACK_HPP
#define LINKEDSTACK_HPP

#include "../List/LinkedList.hpp"

namespace hellods
{

/// Stack implemented by doubly linked list.
template <typename T>
class LinkedStack : private LinkedList<T>
{
public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty stack.
    LinkedStack()
        : LinkedList()
    {
    }

    /// Create a stack based on the given initializer list.
    LinkedStack(const std::initializer_list<T>& il)
        : LinkedList(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two stacks are equal.
    bool operator==(const LinkedStack& that) const
    {
        return static_cast<const LinkedList&>(*this) == static_cast<const LinkedList&>(that);
    }

    /// Check whether two stacks are not equal.
    bool operator!=(const LinkedStack& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the top in the stack.
    T& top()
    {
        common::check_empty(size());
        return trailer_->pred_->data_;
    }

    /// Return the const reference to the element at the top in the stack.
    const T& top() const
    {
        return const_cast<LinkedStack&>(*this).top();
    }

    /*
     * Examination
     */

    /// Get the number of elements of the stack.
    int size() const
    {
        return LinkedList::size();
    }

    /// Check if the stack is empty.
    bool is_empty() const
    {
        return LinkedList::is_empty();
    }

    /*
     * Manipulation
     */

    /// Push an element at the top of the stack.
    void push(const T& element)
    {
        common::check_full(size_, MAX_CAPACITY);
        LinkedList::insert_node(trailer_, element);
    }

    /// Pop the top element of the stack.
    T pop()
    {
        common::check_empty(size_);
        return LinkedList::remove_node(trailer_->pred_);
    }

    /// Remove all of the elements from the stack.
    void clear()
    {
        LinkedList::clear();
    }

    /*
     * Print
     */

    /// Print the stack.
    friend std::ostream& operator<<(std::ostream& os, const LinkedStack& stack)
    {
        std::ostringstream oss;
        oss << static_cast<const LinkedList&>(stack);
        return os << "Stack" << oss.str().erase(0, 4);
    }
};

} // namespace hellods

#endif // LINKEDSTACK_HPP
