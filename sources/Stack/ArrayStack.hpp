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
class ArrayStack : protected ArrayList<T>, virtual Stack<T>
{
    using ArrayList<T>::data_;

public:
    /*
     * Constructor / Destructor
     */

    /// Create an empty stack.
    ArrayStack()
        : ArrayList<T>()
        , Stack<T>(0)
    {
    }

    /// Create a stack based on the given initializer list.
    ArrayStack(const std::initializer_list<T>& il)
        : ArrayList<T>(il)
        , Stack<T>(int(il.size()))
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

    /*
     * Access
     */

    /// Return the reference to the element at the top in the stack.
    T& top() override
    {
        detail::check_empty(size());
        return data_[size() - 1];
    }

    using Stack<T>::top; // const

    /*
     * Examination
     */

    using ArrayList<T>::is_empty;
    using ArrayList<T>::size;

    /*
     * Manipulation
     */

    /// Push an element at the top of the stack.
    void push(const T& element) override
    {
        ArrayList<T>::insert(size(), element);
    }

    /// Pop the top element of the stack.
    T pop() override
    {
        return ArrayList<T>::remove(size() - 1);
    }

    /// Remove all of the elements from the stack.
    void clear() override
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
