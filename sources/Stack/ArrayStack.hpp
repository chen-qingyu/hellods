/**
 * @file ArrayStack.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Stack implemented by array list.
 * @date 2022.01.28
 */

#ifndef ARRAYSTACK_HPP
#define ARRAYSTACK_HPP

#include "../List/ArrayList.hpp"

namespace hellods
{

/// Stack implemented by array list.
template <typename T>
class ArrayStack : private ArrayList<T>
{
    using ArrayList<T>::data_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty stack.
    ArrayStack()
        : ArrayList<T>()
    {
    }

    /// Create a stack based on the given initializer list.
    ArrayStack(const std::initializer_list<T>& il)
        : ArrayList<T>(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two stacks are equal.
    bool operator==(const ArrayStack& that) const
    {
        return static_cast<const ArrayList<T>&>(*this) == static_cast<const ArrayList<T>&>(that);
    }

    /// Check whether two stacks are not equal.
    bool operator!=(const ArrayStack& that) const
    {
        return !(*this == that);
    }

    /*
     * Access
     */

    /// Return the reference to the element at the top in the stack.
    T& top()
    {
        detail::check_empty(size());
        return data_[size() - 1];
    }

    /// Return the const reference to the element at the top in the stack.
    const T& top() const
    {
        return const_cast<ArrayStack&>(*this).top();
    }

    /*
     * Examination
     */

    /// Get the number of elements of the stack.
    int size() const
    {
        return ArrayList<T>::size();
    }

    /// Check if the stack is empty.
    bool is_empty() const
    {
        return ArrayList<T>::is_empty();
    }

    /*
     * Manipulation
     */

    /// Push an element at the top of the stack.
    void push(const T& element)
    {
        ArrayList<T>::insert(size(), element);
    }

    /// Pop the top element of the stack.
    T pop()
    {
        return ArrayList<T>::remove(size() - 1);
    }

    /// Remove all of the elements from the stack.
    void clear()
    {
        ArrayList<T>::clear();
    }

    /*
     * Print
     */

    /// Print the stack.
    friend std::ostream& operator<<(std::ostream& os, const ArrayStack& stack)
    {
        std::ostringstream oss;
        oss << static_cast<const ArrayList<T>&>(stack);
        return os << "Stack" << oss.str().erase(0, 4);
    }
};

} // namespace hellods

#endif // ARRAYSTACK_HPP
