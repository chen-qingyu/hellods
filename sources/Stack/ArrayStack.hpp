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
    /*
     * Constructor / Destructor
     */

    /// Create an empty stack.
    ArrayStack()
        : list_()
    {
    }

    /// Create a stack based on the given initializer list.
    ArrayStack(const std::initializer_list<T>& il)
        : list_(il)
    {
    }

    /*
     * Comparison
     */

    /// Check whether two stacks are equal.
    bool operator==(const ArrayStack& that) const
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
        return list_.data_[list_.size_ - 1];
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
        list_.insert(list_.size_, element);
    }

    /// Pop the top element of the stack.
    T pop() override
    {
        return list_.remove(list_.size_ - 1);
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
    friend std::ostream& operator<<(std::ostream& os, const ArrayStack& stack)
    {
        std::ostringstream oss;
        oss << stack.list_;
        return os << "Stack" << oss.str().erase(0, 4);
    }
};

} // namespace hellods

#endif // ARRAYSTACK_HPP
