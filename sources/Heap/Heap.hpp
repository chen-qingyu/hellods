/**
 * @file Heap.hpp
 * @author Chen QingYu <chen_qingyu@qq.com>
 * @brief Abstract heap interface.
 * @date 2026.05.10
 */

#ifndef HEAP_HPP
#define HEAP_HPP

#include "../core.hpp"

namespace hellods
{

/// Abstract heap interface.
template <typename T>
class Heap : public detail::ConstIterable<T>
{
public:
    using typename detail::ConstIterable<T>::Iterator;

    /*
     * Lifecycle
     */

    /// Virtual destructor.
    ~Heap() override = default;

    /// Return the type name for printing.
    const char* name() const override
    {
        return "Heap";
    }

    /*
     * Access
     */

    /// Peek the top element in the heap.
    virtual const T& peek() const = 0;

    /*
     * Manipulation
     */

    /// Push an element onto the heap.
    virtual void push(const T& element) = 0;

    /// Remove the top element from the heap and return it.
    virtual T pop() = 0;

    /// Merge another heap into this one. The other heap becomes empty.
    virtual void meld(Heap& that)
    {
        if (this == &that)
        {
            return;
        }

        for (const auto& elem : that)
        {
            push(elem);
        }
        that.clear();
    }
};

} // namespace hellods

#endif // HEAP_HPP
